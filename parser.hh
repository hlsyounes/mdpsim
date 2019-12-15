/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    DEFINE = 258,
    DOMAIN_TOKEN = 259,
    PROBLEM = 260,
    REQUIREMENTS = 261,
    TYPES = 262,
    CONSTANTS = 263,
    PREDICATES = 264,
    FUNCTIONS = 265,
    STRIPS = 266,
    TYPING = 267,
    NEGATIVE_PRECONDITIONS = 268,
    DISJUNCTIVE_PRECONDITIONS = 269,
    EQUALITY = 270,
    EXISTENTIAL_PRECONDITIONS = 271,
    UNIVERSAL_PRECONDITIONS = 272,
    QUANTIFIED_PRECONDITIONS = 273,
    CONDITIONAL_EFFECTS = 274,
    FLUENTS = 275,
    ADL = 276,
    DURATIVE_ACTIONS = 277,
    DURATION_INEQUALITIES = 278,
    CONTINUOUS_EFFECTS = 279,
    PROBABILISTIC_EFFECTS = 280,
    REWARDS = 281,
    MDP = 282,
    ACTION = 283,
    PARAMETERS = 284,
    PRECONDITION = 285,
    EFFECT = 286,
    PDOMAIN = 287,
    OBJECTS = 288,
    INIT = 289,
    GOAL = 290,
    GOAL_REWARD = 291,
    METRIC = 292,
    TOTAL_TIME = 293,
    GOAL_ACHIEVED = 294,
    WHEN = 295,
    NOT = 296,
    AND = 297,
    OR = 298,
    IMPLY = 299,
    EXISTS = 300,
    FORALL = 301,
    PROBABILISTIC = 302,
    ASSIGN = 303,
    SCALE_UP = 304,
    SCALE_DOWN = 305,
    INCREASE = 306,
    DECREASE = 307,
    MINIMIZE = 308,
    MAXIMIZE = 309,
    NUMBER_TOKEN = 310,
    OBJECT_TOKEN = 311,
    EITHER = 312,
    LE = 313,
    GE = 314,
    NAME = 315,
    VARIABLE = 316,
    NUMBER = 317,
    ILLEGAL_TOKEN = 318
  };
#endif
/* Tokens.  */
#define DEFINE 258
#define DOMAIN_TOKEN 259
#define PROBLEM 260
#define REQUIREMENTS 261
#define TYPES 262
#define CONSTANTS 263
#define PREDICATES 264
#define FUNCTIONS 265
#define STRIPS 266
#define TYPING 267
#define NEGATIVE_PRECONDITIONS 268
#define DISJUNCTIVE_PRECONDITIONS 269
#define EQUALITY 270
#define EXISTENTIAL_PRECONDITIONS 271
#define UNIVERSAL_PRECONDITIONS 272
#define QUANTIFIED_PRECONDITIONS 273
#define CONDITIONAL_EFFECTS 274
#define FLUENTS 275
#define ADL 276
#define DURATIVE_ACTIONS 277
#define DURATION_INEQUALITIES 278
#define CONTINUOUS_EFFECTS 279
#define PROBABILISTIC_EFFECTS 280
#define REWARDS 281
#define MDP 282
#define ACTION 283
#define PARAMETERS 284
#define PRECONDITION 285
#define EFFECT 286
#define PDOMAIN 287
#define OBJECTS 288
#define INIT 289
#define GOAL 290
#define GOAL_REWARD 291
#define METRIC 292
#define TOTAL_TIME 293
#define GOAL_ACHIEVED 294
#define WHEN 295
#define NOT 296
#define AND 297
#define OR 298
#define IMPLY 299
#define EXISTS 300
#define FORALL 301
#define PROBABILISTIC 302
#define ASSIGN 303
#define SCALE_UP 304
#define SCALE_DOWN 305
#define INCREASE 306
#define DECREASE 307
#define MINIMIZE 308
#define MAXIMIZE 309
#define NUMBER_TOKEN 310
#define OBJECT_TOKEN 311
#define EITHER 312
#define LE 313
#define GE 314
#define NAME 315
#define VARIABLE 316
#define NUMBER 317
#define ILLEGAL_TOKEN 318

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 266 "parser.yy" /* yacc.c:1909  */

  const Effect* effect;
  std::vector<std::pair<Rational, const Effect*> >* outcomes;
  const StateFormula* formula;
  const Atom* atom;
  const Expression* expr;
  const Fluent* fluent;
  const Type* type;
  TypeSet* types;
  const std::string* str;
  std::vector<const std::string*>* strs;
  const Rational* num;

#line 194 "parser.hh" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
