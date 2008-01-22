/* -*-C++-*- */
/*
 * XML Clients.
 *
 * Copyright 2003-2005 Carnegie Mellon University and Rutgers University
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
#ifndef _CLIENT_H
#define _CLIENT_H

#include "problems.h"
#include "formulas.h"
#include "expressions.h"
#include <string>


/* ====================================================================== */
/* Planner */

/*
 * An abstract planner.
 */
struct Planner {
  /* Constructs a planner. */
  Planner(const Problem& problem) : _problem(problem) {}

  /* Deletes this planner. */
  virtual ~Planner() {}

  /* Called to initialize a round. */
  virtual void initRound() = 0;

  /* Called to return an action for the given state. */
  virtual const Action* decideAction(const AtomSet& atoms,
                                     const ValueMap& values) = 0;

  /* Called to finalize a round. */
  virtual void endRound() = 0;

protected:
  /* Problem to solve. */
  const Problem& _problem;
};


/* ====================================================================== */
/* XMLClient */

/*
 * An XML client.
 */
struct XMLClient {
  /* Constructs an XML client. */
  XMLClient(Planner& planner, const Problem& problem, const std::string& name,
            int fd, bool light_com);
};


#endif /* _CLIENT_H */
