/*
 * Copyright 2004, 2005 Carnegie Mellon University
 * Copyright 2007 H�kan Younes
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <config.h>
#include "mtbdd.h"
#include "problems.h"
#include "domains.h"
#if HAVE_GETOPT_LONG
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <getopt.h>
#else
#include "port/getopt.h"
#endif
#include <iostream>
#include <fstream>
#include <cerrno>
#include <cstdio>
#include <stdexcept>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

/* The parse function. */
extern int yyparse();
/* File to parse. */
extern FILE* yyin;

/* Name of current file. */
std::string current_file;
/* Level of warnings. */
int warning_level;
/* Verbosity level. */
int verbosity;

/* Program options. */
static struct option long_options[] = {
  { "tolerance", required_argument, 0, 'E' },
  { "discount-factor", required_argument, 0, 'G' },
  { "host", required_argument, 0, 'H' },
  { "port", required_argument, 0, 'P' },
  { "lightcoms", no_argument, 0, 'l' },
  { "verbose", optional_argument, 0, 'v' },
  { "warnings", optional_argument, 0, 'W' },
  { "help", no_argument, 0, 'h' },
  { 0, 0, 0, 0 }
};
static const char OPTION_STRING[] = "E:G:H:P:lv::W::h";


/* Displays help. */
static void display_help() {
  std::cout << "usage: mtbddclient [options] [file ...]" << std::endl
            << "options:" << std::endl
            << "  -E e,  --tolerance=e\t"
            << "use error tolerance e (default is 0.1)" << std::endl
            << "  -G g,  --discount-factor=g" << std::endl
            << "\t\t\tuse discount factor g (default is 0.9)" << std::endl
            << "  -H h,  --host=h\t"
            << "connect to host h" << std::endl
            << "  -P p,  --port=p\t"
            << "connect to port p" << std::endl
	    << "  -l, --lightcoms"
	    << "light communications\t" << std::endl
            << "  -v[n], --verbose[=n]\t"
            << "use verbosity level n;" << std::endl
            << "\t\t\t  n is a number from 0 (verbose mode off) and up;"
            << std::endl
            << "\t\t\t  default level is 1 if optional argument is left out"
            << std::endl
            << "  -W[n], --warnings[=n]\t"
            << "determines how warnings are treated;" << std::endl
            << "\t\t\t  0 supresses warnings; 1 displays warnings;"
            << std::endl
            << "\t\t\t  2 treats warnings as errors" << std::endl
            << "  -h     --help\t\t"
            << "display this help and exit" << std::endl
            << "  file ...\t\t"
            << "files containing domain and problem descriptions;" << std::endl
            << "\t\t\t  if none, descriptions are read from standard input"
            << std::endl
            << std::endl
            << "Report bugs to <" PACKAGE_BUGREPORT ">." << std::endl;
}


/* Parses the given file, and returns true on success. */
static bool read_file(const char* name) {
  yyin = fopen(name, "r");
  if (yyin == 0) {
    std::cerr << "mtbddclient:" << name << ": " << strerror(errno)
              << std::endl;
    return false;
  } else {
    current_file = name;
    bool success = (yyparse() == 0);
    fclose(yyin);
    return success;
  }
}


/* Connect to the given port on the given host. */
int connect(const char *hostname, int port)
{
  struct hostent* host = ::gethostbyname(hostname);
  if (!host) {
    perror("gethostbyname");
    return -1;
  }

  int sock = ::socket(PF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    perror("socket");
    return -1;
  }
  
  struct sockaddr_in addr;
  addr.sin_family=AF_INET;
  addr.sin_port=htons(port);
  addr.sin_addr = *(struct in_addr*) host->h_addr;
  memset(&addr.sin_zero, '\0', 8);

  if (::connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
    perror("connect");
    return -1;
  }
  return sock;
}


/* The main program. */
int main(int argc, char* argv[]) {
  /* Set default verbosity. */
  verbosity = 0;
  /* Set default warning level. */
  warning_level = 1;
  /* Set default tolerance. */
  double epsilon = 0.1;
  /* Set default discount factor. */
  double gamma = 0.9;
  /* Host. */
  std::string host;
  /* Port. */
  int port = 0;
  /* Light communications. */
  bool light_com = false;

  try {
    /*
     * Get command line options.
     */
    while (1) {
      int option_index = 0;
      int c = getopt_long(argc, argv, OPTION_STRING,
                          long_options, &option_index);
      if (c == -1) {
        break;
      }
      switch (c) {
      case 'E':
        epsilon = atof(optarg);
        if (epsilon <= 0.0) {
          throw std::invalid_argument("tolerance must be positive");
        }
        break;
      case 'G':
        gamma = atof(optarg);
        if (gamma <= 0.0) {
          throw std::invalid_argument("discount factor must be positive");
        }
        if (gamma >= 1.0) {
          throw std::invalid_argument("discount factor must be less than 1");
        }
        break;
      case 'H':
        host = optarg;
        break;
      case 'P':
        port = atoi(optarg);
        break;
      case 'l':
        light_com = true;
	break;
      case 'v':
        verbosity = (optarg != 0) ? atoi(optarg) : 1;
        break;
      case 'W':
        warning_level = (optarg != 0) ? atoi(optarg) : 1;
        break;
      case 'h':
        display_help();
        return 0;
      case ':':
      default:
        std::cerr << "Try `mtbddclient --help' for more information."
                  << std::endl;
        return -1;
      }
    }

    /*
     * Read pddl files.
     */
    if (optind < argc) {
      /*
       * Use remaining command line arguments as file names.
       */
      while (optind < argc) {
        if (!read_file(argv[optind++])) {
          return -1;
        }
      }
    } else {
      /*
       * No remaining command line argument, so read from standard input.
       */
      yyin = stdin;
      if (yyparse() != 0) {
        return -1;
      }
    }

    if (verbosity > 1) {
      /*
       * Display domains and problems.
       */
      std::cerr << "----------------------------------------"<< std::endl
                << "domains:" << std::endl;
      for (Domain::DomainMap::const_iterator di = Domain::begin();
           di != Domain::end(); di++) {
        std::cerr << std::endl << *(*di).second << std::endl;
      }
      std::cerr << "----------------------------------------"<< std::endl
                << "problems:" << std::endl;
      for (Problem::ProblemMap::const_iterator pi = Problem::begin();
           pi != Problem::end(); pi++) {
        std::cerr << std::endl << *(*pi).second << std::endl;
      }
      std::cerr << "----------------------------------------"<< std::endl;
    }

    int socket = 0;
    if (port > 0) {
      socket = connect(host.c_str(), port);
      if (socket <= 0) {
        std::cerr << "mtbddclient: could not connect to " << host << ':'
                  << port << std::endl;
        return 1;
      }
    }

    std::cout.setf(std::ios::unitbuf);
    for (Problem::ProblemMap::const_iterator pi = Problem::begin();
         pi != Problem::end(); pi++) {
      const Problem& problem = *(*pi).second;
      MTBDDPlanner planner(problem, gamma, epsilon);
      if (port > 0) {
	  XMLClient(planner, problem, "mtbddclient", socket, light_com);
      } else {
        planner.initRound();
      }
    }
  } catch (const std::exception& e) {
    std::cerr << std::endl << "mtbddclient: " << e.what() << std::endl;
    return 1;
  } catch (...) {
    std::cerr << "mtbddclient: fatal error" << std::endl;
    return -1;
  }

  Problem::clear();
  Domain::clear();

  return 0;
}
