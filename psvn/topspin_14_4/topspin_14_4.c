#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#define __STDC_FORMAT_MACROS
#define __STDC_LIMIT_MACROS
#include <inttypes.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


#define psvn2c_PSVN_API

#define HAVE_FWD_MOVE_PRUNING
#define HAVE_BWD_MOVES
#define HAVE_BWD_MOVE_PRUNING
#define HAVE_ABSTRACTION


/* number of variables in a state */
#define NUMVARS 14


typedef int8_t var_t;
#define PRI_VAR PRId8
#define SCN_VAR SCNd8

#define NUMDOMAINS 1
static var_t domain_sizes[ NUMDOMAINS ] = { 14 };
static const char *name_of_domain[ NUMDOMAINS ] = { "14" };
static int var_domains[ NUMVARS ] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static const char *domain_0[ 14 ] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13" };
static const char **domain_to_domain_names[ NUMDOMAINS ] = { domain_0 };
static const char **var_domain_names[ NUMVARS ] = { domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0 };

typedef struct {
 var_t vars[ NUMVARS ];
} state_t;

typedef int (*funcptr)( const state_t *, void * );
typedef void (*actfuncptr)( const state_t *, state_t * );

typedef struct {
 const state_t *my_state;
 funcptr my_funcptr;
} ruleid_iterator_t;

#define num_fwd_rules 14
#define num_bwd_rules 14
static const char *fwd_rule_name[ 14 ] = { "REVAT0", "REVAT1", "REVAT2", "REVAT3", "REVAT4", "REVAT5", "REVAT6", "REVAT7", "REVAT8", "REVAT9", "REVAT10", "REVAT11", "REVAT12", "REVAT13" };
#define get_fwd_rule_label( ruleid ) (fwd_rule_name[(ruleid)]) 
static const char *bwd_rule_name[ 14 ] = { "REVAT0", "REVAT1", "REVAT2", "REVAT3", "REVAT4", "REVAT5", "REVAT6", "REVAT7", "REVAT8", "REVAT9", "REVAT10", "REVAT11", "REVAT12", "REVAT13" };
#define get_bwd_rule_label( ruleid ) (bwd_rule_name[(ruleid)]) 
#define cost_of_cheapest_fwd_rule 1
#define cost_of_costliest_fwd_rule 1
#define get_fwd_rule_cost( ruleid ) 1
#define cost_of_cheapest_bwd_rule 1
#define cost_of_costliest_bwd_rule 1
#define get_bwd_rule_cost( ruleid ) 1

static int fwd_rule_label_sets[196] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13};

static int bwd_rule_label_sets[196] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,13};

static int fwd_prune_table[ 210 ] = { 14, 28, 42, 56, 70, 84, 98, 112, 126, 140, 154, 168, 182, 196, 0, 28, 42, 56, 70, 84, 98, 112, 126, 140, 154, 168, 182, 196, 14, 0, 42, 56, 70, 84, 98, 112, 126, 140, 154, 168, 182, 196, 14, 28, 0, 56, 70, 84, 98, 112, 126, 140, 154, 168, 182, 196, 14, 28, 42, 0, 70, 84, 98, 112, 126, 140, 154, 168, 182, 196, 0, 28, 42, 56, 0, 84, 98, 112, 126, 140, 154, 168, 182, 196, 0, 0, 42, 56, 70, 0, 98, 112, 126, 140, 154, 168, 182, 196, 0, 0, 0, 56, 70, 84, 0, 112, 126, 140, 154, 168, 182, 196, 0, 0, 0, 0, 70, 84, 98, 0, 126, 140, 154, 168, 182, 196, 0, 0, 0, 0, 0, 84, 98, 112, 0, 140, 154, 168, 182, 196, 0, 0, 0, 0, 0, 0, 98, 112, 126, 0, 154, 168, 182, 196, 0, 0, 0, 0, 0, 0, 0, 112, 126, 140, 0, 168, 182, 196, 14, 0, 0, 0, 0, 0, 0, 0, 126, 140, 154, 0, 182, 196, 14, 28, 0, 0, 0, 0, 0, 0, 0, 140, 154, 168, 0, 196, 14, 28, 42, 0, 0, 0, 0, 0, 0, 0, 154, 168, 182, 0 };

static void fwdrule1( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 3 ];
  child_state->vars[ 1 ] = state->vars[ 2 ];
  child_state->vars[ 2 ] = state->vars[ 1 ];
  child_state->vars[ 3 ] = state->vars[ 0 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
}

static void fwdrule2( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 4 ];
  child_state->vars[ 2 ] = state->vars[ 3 ];
  child_state->vars[ 3 ] = state->vars[ 2 ];
  child_state->vars[ 4 ] = state->vars[ 1 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
}

static void fwdrule3( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 5 ];
  child_state->vars[ 3 ] = state->vars[ 4 ];
  child_state->vars[ 4 ] = state->vars[ 3 ];
  child_state->vars[ 5 ] = state->vars[ 2 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
}

static void fwdrule4( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 6 ];
  child_state->vars[ 4 ] = state->vars[ 5 ];
  child_state->vars[ 5 ] = state->vars[ 4 ];
  child_state->vars[ 6 ] = state->vars[ 3 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
}

static void fwdrule5( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 7 ];
  child_state->vars[ 5 ] = state->vars[ 6 ];
  child_state->vars[ 6 ] = state->vars[ 5 ];
  child_state->vars[ 7 ] = state->vars[ 4 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
}

static void fwdrule6( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 8 ];
  child_state->vars[ 6 ] = state->vars[ 7 ];
  child_state->vars[ 7 ] = state->vars[ 6 ];
  child_state->vars[ 8 ] = state->vars[ 5 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
}

static void fwdrule7( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 9 ];
  child_state->vars[ 7 ] = state->vars[ 8 ];
  child_state->vars[ 8 ] = state->vars[ 7 ];
  child_state->vars[ 9 ] = state->vars[ 6 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
}

static void fwdrule8( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 10 ];
  child_state->vars[ 8 ] = state->vars[ 9 ];
  child_state->vars[ 9 ] = state->vars[ 8 ];
  child_state->vars[ 10 ] = state->vars[ 7 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
}

static void fwdrule9( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 11 ];
  child_state->vars[ 9 ] = state->vars[ 10 ];
  child_state->vars[ 10 ] = state->vars[ 9 ];
  child_state->vars[ 11 ] = state->vars[ 8 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
}

static void fwdrule10( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 12 ];
  child_state->vars[ 10 ] = state->vars[ 11 ];
  child_state->vars[ 11 ] = state->vars[ 10 ];
  child_state->vars[ 12 ] = state->vars[ 9 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
}

static void fwdrule11( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 13 ];
  child_state->vars[ 11 ] = state->vars[ 12 ];
  child_state->vars[ 12 ] = state->vars[ 11 ];
  child_state->vars[ 13 ] = state->vars[ 10 ];
}

static void fwdrule12( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 11 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 0 ];
  child_state->vars[ 12 ] = state->vars[ 13 ];
  child_state->vars[ 13 ] = state->vars[ 12 ];
}

static void fwdrule13( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 13 ];
  child_state->vars[ 1 ] = state->vars[ 12 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 1 ];
  child_state->vars[ 13 ] = state->vars[ 0 ];
}

static void fwdrule14( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 1 ];
  child_state->vars[ 1 ] = state->vars[ 0 ];
  child_state->vars[ 2 ] = state->vars[ 13 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 2 ];
}

static actfuncptr fwd_rules[ 14 ] = { fwdrule1, fwdrule2, fwdrule3, fwdrule4, fwdrule5, fwdrule6, fwdrule7, fwdrule8, fwdrule9, fwdrule10, fwdrule11, fwdrule12, fwdrule13, fwdrule14 };

static int fwdfn0_r13( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = NULL;
  return 13;
}

static int fwdfn0_r12( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r13;
  return 12;
}

static int fwdfn0_r11( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r12;
  return 11;
}

static int fwdfn0_r10( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r11;
  return 10;
}

static int fwdfn0_r9( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r10;
  return 9;
}

static int fwdfn0_r8( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r9;
  return 8;
}

static int fwdfn0_r7( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r8;
  return 7;
}

static int fwdfn0_r6( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r7;
  return 6;
}

static int fwdfn0_r5( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r6;
  return 5;
}

static int fwdfn0_r4( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r5;
  return 4;
}

static int fwdfn0_r3( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r4;
  return 3;
}

static int fwdfn0_r2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r3;
  return 2;
}

static int fwdfn0_r1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r2;
  return 1;
}

static int fwdfn0_r0( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r1;
  return 0;
}

static int bwd_prune_table[ 210 ] = { 14, 28, 42, 56, 70, 84, 98, 112, 126, 140, 154, 168, 182, 196, 0, 28, 42, 56, 70, 84, 98, 112, 126, 140, 154, 168, 182, 196, 14, 0, 42, 56, 70, 84, 98, 112, 126, 140, 154, 168, 182, 196, 14, 28, 0, 56, 70, 84, 98, 112, 126, 140, 154, 168, 182, 196, 14, 28, 42, 0, 70, 84, 98, 112, 126, 140, 154, 168, 182, 196, 0, 28, 42, 56, 0, 84, 98, 112, 126, 140, 154, 168, 182, 196, 0, 0, 42, 56, 70, 0, 98, 112, 126, 140, 154, 168, 182, 196, 0, 0, 0, 56, 70, 84, 0, 112, 126, 140, 154, 168, 182, 196, 0, 0, 0, 0, 70, 84, 98, 0, 126, 140, 154, 168, 182, 196, 0, 0, 0, 0, 0, 84, 98, 112, 0, 140, 154, 168, 182, 196, 0, 0, 0, 0, 0, 0, 98, 112, 126, 0, 154, 168, 182, 196, 0, 0, 0, 0, 0, 0, 0, 112, 126, 140, 0, 168, 182, 196, 14, 0, 0, 0, 0, 0, 0, 0, 126, 140, 154, 0, 182, 196, 14, 28, 0, 0, 0, 0, 0, 0, 0, 140, 154, 168, 0, 196, 14, 28, 42, 0, 0, 0, 0, 0, 0, 0, 154, 168, 182, 0 };

static void bwdrule1( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 3 ];
  child_state->vars[ 1 ] = state->vars[ 2 ];
  child_state->vars[ 2 ] = state->vars[ 1 ];
  child_state->vars[ 3 ] = state->vars[ 0 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
}

static void bwdrule2( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 4 ];
  child_state->vars[ 2 ] = state->vars[ 3 ];
  child_state->vars[ 3 ] = state->vars[ 2 ];
  child_state->vars[ 4 ] = state->vars[ 1 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
}

static void bwdrule3( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 5 ];
  child_state->vars[ 3 ] = state->vars[ 4 ];
  child_state->vars[ 4 ] = state->vars[ 3 ];
  child_state->vars[ 5 ] = state->vars[ 2 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
}

static void bwdrule4( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 6 ];
  child_state->vars[ 4 ] = state->vars[ 5 ];
  child_state->vars[ 5 ] = state->vars[ 4 ];
  child_state->vars[ 6 ] = state->vars[ 3 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
}

static void bwdrule5( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 7 ];
  child_state->vars[ 5 ] = state->vars[ 6 ];
  child_state->vars[ 6 ] = state->vars[ 5 ];
  child_state->vars[ 7 ] = state->vars[ 4 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
}

static void bwdrule6( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 8 ];
  child_state->vars[ 6 ] = state->vars[ 7 ];
  child_state->vars[ 7 ] = state->vars[ 6 ];
  child_state->vars[ 8 ] = state->vars[ 5 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
}

static void bwdrule7( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 9 ];
  child_state->vars[ 7 ] = state->vars[ 8 ];
  child_state->vars[ 8 ] = state->vars[ 7 ];
  child_state->vars[ 9 ] = state->vars[ 6 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
}

static void bwdrule8( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 10 ];
  child_state->vars[ 8 ] = state->vars[ 9 ];
  child_state->vars[ 9 ] = state->vars[ 8 ];
  child_state->vars[ 10 ] = state->vars[ 7 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
}

static void bwdrule9( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 11 ];
  child_state->vars[ 9 ] = state->vars[ 10 ];
  child_state->vars[ 10 ] = state->vars[ 9 ];
  child_state->vars[ 11 ] = state->vars[ 8 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
}

static void bwdrule10( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 12 ];
  child_state->vars[ 10 ] = state->vars[ 11 ];
  child_state->vars[ 11 ] = state->vars[ 10 ];
  child_state->vars[ 12 ] = state->vars[ 9 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
}

static void bwdrule11( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 13 ];
  child_state->vars[ 11 ] = state->vars[ 12 ];
  child_state->vars[ 12 ] = state->vars[ 11 ];
  child_state->vars[ 13 ] = state->vars[ 10 ];
}

static void bwdrule12( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 11 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 0 ];
  child_state->vars[ 12 ] = state->vars[ 13 ];
  child_state->vars[ 13 ] = state->vars[ 12 ];
}

static void bwdrule13( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 13 ];
  child_state->vars[ 1 ] = state->vars[ 12 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 1 ];
  child_state->vars[ 13 ] = state->vars[ 0 ];
}

static void bwdrule14( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 1 ];
  child_state->vars[ 1 ] = state->vars[ 0 ];
  child_state->vars[ 2 ] = state->vars[ 13 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 2 ];
}

static actfuncptr bwd_rules[ 14 ] = { bwdrule1, bwdrule2, bwdrule3, bwdrule4, bwdrule5, bwdrule6, bwdrule7, bwdrule8, bwdrule9, bwdrule10, bwdrule11, bwdrule12, bwdrule13, bwdrule14 };

static int bwdfn0_r13( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = NULL;
  return 13;
}

static int bwdfn0_r12( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r13;
  return 12;
}

static int bwdfn0_r11( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r12;
  return 11;
}

static int bwdfn0_r10( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r11;
  return 10;
}

static int bwdfn0_r9( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r10;
  return 9;
}

static int bwdfn0_r8( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r9;
  return 8;
}

static int bwdfn0_r7( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r8;
  return 7;
}

static int bwdfn0_r6( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r7;
  return 6;
}

static int bwdfn0_r5( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r6;
  return 5;
}

static int bwdfn0_r4( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r5;
  return 4;
}

static int bwdfn0_r3( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r4;
  return 3;
}

static int bwdfn0_r2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r3;
  return 2;
}

static int bwdfn0_r1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r2;
  return 1;
}

static int bwdfn0_r0( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r1;
  return 0;
}


#define init_history 0

#define max_fwd_children 14

/* NOTE: FOR ALL OF THE MOVE ITERATOR DEFINITIONS funcptr
   MUST BE A VARIABLE. */

/* initialise a forward move iterator */
#define init_fwd_iter( ruleid_iter, state ) { \
  (*ruleid_iter).my_funcptr = fwdfn0_r0 ; \
  (*ruleid_iter).my_state = state; \
}

/* use iterator to generate next applicable rule to apply 
   returns rule to use, -1 if there are no more rules to apply */
#define next_ruleid( ruleid_iter ) (((*ruleid_iter).my_funcptr)?((*ruleid_iter).my_funcptr)((*ruleid_iter).my_state,&((*ruleid_iter).my_funcptr)):-1)

/* apply a rule to a state */
#define apply_fwd_rule( rule, state, result ) fwd_rules[(rule)](state,result)
/* returns 0 if the rule is pruned, non-zero otherwise */
#define fwd_rule_valid_for_history( history, rule_used ) (fwd_prune_table[(history)+(rule_used)])
/* generate the next history from the current history and a rule */
#define next_fwd_history( history, rule_used ) (fwd_prune_table[(history)+(rule_used)])


static const int bw_max_children = 14;
#define max_bwd_children 14

/* initialise a backwards move iterator */
#define init_bwd_iter( ruleid_iter, state ) { \
  (*ruleid_iter).my_funcptr = bwdfn0_r0 ; \
  (*ruleid_iter).my_state = state; \
}

/* apply a rule to a state */
#define apply_bwd_rule( rule, state, result ) bwd_rules[(rule)](state,result)
/* returns 0 if the rule is pruned, non-zero otherwise */
#define bwd_rule_valid_for_history( history, rule_used ) (bwd_prune_table[(history)+(rule_used)])
/* generate the next history from the current history and a rule */
#define next_bwd_history( history, rule_used ) (bwd_prune_table[(history)+(rule_used)])


/* returns 1 if state is a goal state, 0 otherwise */
static int is_goal( const state_t *state )
{
  if( state->vars[ 0 ] == 0 && state->vars[ 1 ] == 1 && state->vars[ 2 ] == 2 && state->vars[ 3 ] == 3 && state->vars[ 4 ] == 4 && state->vars[ 5 ] == 5 && state->vars[ 6 ] == 6 && state->vars[ 7 ] == 7 && state->vars[ 8 ] == 8 && state->vars[ 9 ] == 9 && state->vars[ 10 ] == 10 && state->vars[ 11 ] == 11 && state->vars[ 12 ] == 12 && state->vars[ 13 ] == 13 ) {
    return 1;
  }
  if( state->vars[ 0 ] == 1 && state->vars[ 1 ] == 2 && state->vars[ 2 ] == 3 && state->vars[ 3 ] == 4 && state->vars[ 4 ] == 5 && state->vars[ 5 ] == 6 && state->vars[ 6 ] == 7 && state->vars[ 7 ] == 8 && state->vars[ 8 ] == 9 && state->vars[ 9 ] == 10 && state->vars[ 10 ] == 11 && state->vars[ 11 ] == 12 && state->vars[ 12 ] == 13 && state->vars[ 13 ] == 0 ) {
    return 1;
  }
  if( state->vars[ 0 ] == 2 && state->vars[ 1 ] == 3 && state->vars[ 2 ] == 4 && state->vars[ 3 ] == 5 && state->vars[ 4 ] == 6 && state->vars[ 5 ] == 7 && state->vars[ 6 ] == 8 && state->vars[ 7 ] == 9 && state->vars[ 8 ] == 10 && state->vars[ 9 ] == 11 && state->vars[ 10 ] == 12 && state->vars[ 11 ] == 13 && state->vars[ 12 ] == 0 && state->vars[ 13 ] == 1 ) {
    return 1;
  }
  if( state->vars[ 0 ] == 3 && state->vars[ 1 ] == 4 && state->vars[ 2 ] == 5 && state->vars[ 3 ] == 6 && state->vars[ 4 ] == 7 && state->vars[ 5 ] == 8 && state->vars[ 6 ] == 9 && state->vars[ 7 ] == 10 && state->vars[ 8 ] == 11 && state->vars[ 9 ] == 12 && state->vars[ 10 ] == 13 && state->vars[ 11 ] == 0 && state->vars[ 12 ] == 1 && state->vars[ 13 ] == 2 ) {
    return 1;
  }
  if( state->vars[ 0 ] == 4 && state->vars[ 1 ] == 5 && state->vars[ 2 ] == 6 && state->vars[ 3 ] == 7 && state->vars[ 4 ] == 8 && state->vars[ 5 ] == 9 && state->vars[ 6 ] == 10 && state->vars[ 7 ] == 11 && state->vars[ 8 ] == 12 && state->vars[ 9 ] == 13 && state->vars[ 10 ] == 0 && state->vars[ 11 ] == 1 && state->vars[ 12 ] == 2 && state->vars[ 13 ] == 3 ) {
    return 1;
  }
  if( state->vars[ 0 ] == 5 && state->vars[ 1 ] == 6 && state->vars[ 2 ] == 7 && state->vars[ 3 ] == 8 && state->vars[ 4 ] == 9 && state->vars[ 5 ] == 10 && state->vars[ 6 ] == 11 && state->vars[ 7 ] == 12 && state->vars[ 8 ] == 13 && state->vars[ 9 ] == 0 && state->vars[ 10 ] == 1 && state->vars[ 11 ] == 2 && state->vars[ 12 ] == 3 && state->vars[ 13 ] == 4 ) {
    return 1;
  }
  if( state->vars[ 0 ] == 6 && state->vars[ 1 ] == 7 && state->vars[ 2 ] == 8 && state->vars[ 3 ] == 9 && state->vars[ 4 ] == 10 && state->vars[ 5 ] == 11 && state->vars[ 6 ] == 12 && state->vars[ 7 ] == 13 && state->vars[ 8 ] == 0 && state->vars[ 9 ] == 1 && state->vars[ 10 ] == 2 && state->vars[ 11 ] == 3 && state->vars[ 12 ] == 4 && state->vars[ 13 ] == 5 ) {
    return 1;
  }
  if( state->vars[ 0 ] == 7 && state->vars[ 1 ] == 8 && state->vars[ 2 ] == 9 && state->vars[ 3 ] == 10 && state->vars[ 4 ] == 11 && state->vars[ 5 ] == 12 && state->vars[ 6 ] == 13 && state->vars[ 7 ] == 0 && state->vars[ 8 ] == 1 && state->vars[ 9 ] == 2 && state->vars[ 10 ] == 3 && state->vars[ 11 ] == 4 && state->vars[ 12 ] == 5 && state->vars[ 13 ] == 6 ) {
    return 1;
  }
  if( state->vars[ 0 ] == 8 && state->vars[ 1 ] == 9 && state->vars[ 2 ] == 10 && state->vars[ 3 ] == 11 && state->vars[ 4 ] == 12 && state->vars[ 5 ] == 13 && state->vars[ 6 ] == 0 && state->vars[ 7 ] == 1 && state->vars[ 8 ] == 2 && state->vars[ 9 ] == 3 && state->vars[ 10 ] == 4 && state->vars[ 11 ] == 5 && state->vars[ 12 ] == 6 && state->vars[ 13 ] == 7 ) {
    return 1;
  }
  if( state->vars[ 0 ] == 9 && state->vars[ 1 ] == 10 && state->vars[ 2 ] == 11 && state->vars[ 3 ] == 12 && state->vars[ 4 ] == 13 && state->vars[ 5 ] == 0 && state->vars[ 6 ] == 1 && state->vars[ 7 ] == 2 && state->vars[ 8 ] == 3 && state->vars[ 9 ] == 4 && state->vars[ 10 ] == 5 && state->vars[ 11 ] == 6 && state->vars[ 12 ] == 7 && state->vars[ 13 ] == 8 ) {
    return 1;
  }
  if( state->vars[ 0 ] == 10 && state->vars[ 1 ] == 11 && state->vars[ 2 ] == 12 && state->vars[ 3 ] == 13 && state->vars[ 4 ] == 0 && state->vars[ 5 ] == 1 && state->vars[ 6 ] == 2 && state->vars[ 7 ] == 3 && state->vars[ 8 ] == 4 && state->vars[ 9 ] == 5 && state->vars[ 10 ] == 6 && state->vars[ 11 ] == 7 && state->vars[ 12 ] == 8 && state->vars[ 13 ] == 9 ) {
    return 1;
  }
  if( state->vars[ 0 ] == 11 && state->vars[ 1 ] == 12 && state->vars[ 2 ] == 13 && state->vars[ 3 ] == 0 && state->vars[ 4 ] == 1 && state->vars[ 5 ] == 2 && state->vars[ 6 ] == 3 && state->vars[ 7 ] == 4 && state->vars[ 8 ] == 5 && state->vars[ 9 ] == 6 && state->vars[ 10 ] == 7 && state->vars[ 11 ] == 8 && state->vars[ 12 ] == 9 && state->vars[ 13 ] == 10 ) {
    return 1;
  }
  if( state->vars[ 0 ] == 12 && state->vars[ 1 ] == 13 && state->vars[ 2 ] == 0 && state->vars[ 3 ] == 1 && state->vars[ 4 ] == 2 && state->vars[ 5 ] == 3 && state->vars[ 6 ] == 4 && state->vars[ 7 ] == 5 && state->vars[ 8 ] == 6 && state->vars[ 9 ] == 7 && state->vars[ 10 ] == 8 && state->vars[ 11 ] == 9 && state->vars[ 12 ] == 10 && state->vars[ 13 ] == 11 ) {
    return 1;
  }
  if( state->vars[ 0 ] == 13 && state->vars[ 1 ] == 0 && state->vars[ 2 ] == 1 && state->vars[ 3 ] == 2 && state->vars[ 4 ] == 3 && state->vars[ 5 ] == 4 && state->vars[ 6 ] == 5 && state->vars[ 7 ] == 6 && state->vars[ 8 ] == 7 && state->vars[ 9 ] == 8 && state->vars[ 10 ] == 9 && state->vars[ 11 ] == 10 && state->vars[ 12 ] == 11 && state->vars[ 13 ] == 12 ) {
    return 1;
  }
  return 0;
}

static void init_goal_state( state_t *state, int goal_rule )
{
  switch( goal_rule ) {
  case 0:
    state->vars[ 0 ] = 0;
    state->vars[ 1 ] = 1;
    state->vars[ 2 ] = 2;
    state->vars[ 3 ] = 3;
    state->vars[ 4 ] = 4;
    state->vars[ 5 ] = 5;
    state->vars[ 6 ] = 6;
    state->vars[ 7 ] = 7;
    state->vars[ 8 ] = 8;
    state->vars[ 9 ] = 9;
    state->vars[ 10 ] = 10;
    state->vars[ 11 ] = 11;
    state->vars[ 12 ] = 12;
    state->vars[ 13 ] = 13;
    break;
  case 1:
    state->vars[ 0 ] = 1;
    state->vars[ 1 ] = 2;
    state->vars[ 2 ] = 3;
    state->vars[ 3 ] = 4;
    state->vars[ 4 ] = 5;
    state->vars[ 5 ] = 6;
    state->vars[ 6 ] = 7;
    state->vars[ 7 ] = 8;
    state->vars[ 8 ] = 9;
    state->vars[ 9 ] = 10;
    state->vars[ 10 ] = 11;
    state->vars[ 11 ] = 12;
    state->vars[ 12 ] = 13;
    state->vars[ 13 ] = 0;
    break;
  case 2:
    state->vars[ 0 ] = 2;
    state->vars[ 1 ] = 3;
    state->vars[ 2 ] = 4;
    state->vars[ 3 ] = 5;
    state->vars[ 4 ] = 6;
    state->vars[ 5 ] = 7;
    state->vars[ 6 ] = 8;
    state->vars[ 7 ] = 9;
    state->vars[ 8 ] = 10;
    state->vars[ 9 ] = 11;
    state->vars[ 10 ] = 12;
    state->vars[ 11 ] = 13;
    state->vars[ 12 ] = 0;
    state->vars[ 13 ] = 1;
    break;
  case 3:
    state->vars[ 0 ] = 3;
    state->vars[ 1 ] = 4;
    state->vars[ 2 ] = 5;
    state->vars[ 3 ] = 6;
    state->vars[ 4 ] = 7;
    state->vars[ 5 ] = 8;
    state->vars[ 6 ] = 9;
    state->vars[ 7 ] = 10;
    state->vars[ 8 ] = 11;
    state->vars[ 9 ] = 12;
    state->vars[ 10 ] = 13;
    state->vars[ 11 ] = 0;
    state->vars[ 12 ] = 1;
    state->vars[ 13 ] = 2;
    break;
  case 4:
    state->vars[ 0 ] = 4;
    state->vars[ 1 ] = 5;
    state->vars[ 2 ] = 6;
    state->vars[ 3 ] = 7;
    state->vars[ 4 ] = 8;
    state->vars[ 5 ] = 9;
    state->vars[ 6 ] = 10;
    state->vars[ 7 ] = 11;
    state->vars[ 8 ] = 12;
    state->vars[ 9 ] = 13;
    state->vars[ 10 ] = 0;
    state->vars[ 11 ] = 1;
    state->vars[ 12 ] = 2;
    state->vars[ 13 ] = 3;
    break;
  case 5:
    state->vars[ 0 ] = 5;
    state->vars[ 1 ] = 6;
    state->vars[ 2 ] = 7;
    state->vars[ 3 ] = 8;
    state->vars[ 4 ] = 9;
    state->vars[ 5 ] = 10;
    state->vars[ 6 ] = 11;
    state->vars[ 7 ] = 12;
    state->vars[ 8 ] = 13;
    state->vars[ 9 ] = 0;
    state->vars[ 10 ] = 1;
    state->vars[ 11 ] = 2;
    state->vars[ 12 ] = 3;
    state->vars[ 13 ] = 4;
    break;
  case 6:
    state->vars[ 0 ] = 6;
    state->vars[ 1 ] = 7;
    state->vars[ 2 ] = 8;
    state->vars[ 3 ] = 9;
    state->vars[ 4 ] = 10;
    state->vars[ 5 ] = 11;
    state->vars[ 6 ] = 12;
    state->vars[ 7 ] = 13;
    state->vars[ 8 ] = 0;
    state->vars[ 9 ] = 1;
    state->vars[ 10 ] = 2;
    state->vars[ 11 ] = 3;
    state->vars[ 12 ] = 4;
    state->vars[ 13 ] = 5;
    break;
  case 7:
    state->vars[ 0 ] = 7;
    state->vars[ 1 ] = 8;
    state->vars[ 2 ] = 9;
    state->vars[ 3 ] = 10;
    state->vars[ 4 ] = 11;
    state->vars[ 5 ] = 12;
    state->vars[ 6 ] = 13;
    state->vars[ 7 ] = 0;
    state->vars[ 8 ] = 1;
    state->vars[ 9 ] = 2;
    state->vars[ 10 ] = 3;
    state->vars[ 11 ] = 4;
    state->vars[ 12 ] = 5;
    state->vars[ 13 ] = 6;
    break;
  case 8:
    state->vars[ 0 ] = 8;
    state->vars[ 1 ] = 9;
    state->vars[ 2 ] = 10;
    state->vars[ 3 ] = 11;
    state->vars[ 4 ] = 12;
    state->vars[ 5 ] = 13;
    state->vars[ 6 ] = 0;
    state->vars[ 7 ] = 1;
    state->vars[ 8 ] = 2;
    state->vars[ 9 ] = 3;
    state->vars[ 10 ] = 4;
    state->vars[ 11 ] = 5;
    state->vars[ 12 ] = 6;
    state->vars[ 13 ] = 7;
    break;
  case 9:
    state->vars[ 0 ] = 9;
    state->vars[ 1 ] = 10;
    state->vars[ 2 ] = 11;
    state->vars[ 3 ] = 12;
    state->vars[ 4 ] = 13;
    state->vars[ 5 ] = 0;
    state->vars[ 6 ] = 1;
    state->vars[ 7 ] = 2;
    state->vars[ 8 ] = 3;
    state->vars[ 9 ] = 4;
    state->vars[ 10 ] = 5;
    state->vars[ 11 ] = 6;
    state->vars[ 12 ] = 7;
    state->vars[ 13 ] = 8;
    break;
  case 10:
    state->vars[ 0 ] = 10;
    state->vars[ 1 ] = 11;
    state->vars[ 2 ] = 12;
    state->vars[ 3 ] = 13;
    state->vars[ 4 ] = 0;
    state->vars[ 5 ] = 1;
    state->vars[ 6 ] = 2;
    state->vars[ 7 ] = 3;
    state->vars[ 8 ] = 4;
    state->vars[ 9 ] = 5;
    state->vars[ 10 ] = 6;
    state->vars[ 11 ] = 7;
    state->vars[ 12 ] = 8;
    state->vars[ 13 ] = 9;
    break;
  case 11:
    state->vars[ 0 ] = 11;
    state->vars[ 1 ] = 12;
    state->vars[ 2 ] = 13;
    state->vars[ 3 ] = 0;
    state->vars[ 4 ] = 1;
    state->vars[ 5 ] = 2;
    state->vars[ 6 ] = 3;
    state->vars[ 7 ] = 4;
    state->vars[ 8 ] = 5;
    state->vars[ 9 ] = 6;
    state->vars[ 10 ] = 7;
    state->vars[ 11 ] = 8;
    state->vars[ 12 ] = 9;
    state->vars[ 13 ] = 10;
    break;
  case 12:
    state->vars[ 0 ] = 12;
    state->vars[ 1 ] = 13;
    state->vars[ 2 ] = 0;
    state->vars[ 3 ] = 1;
    state->vars[ 4 ] = 2;
    state->vars[ 5 ] = 3;
    state->vars[ 6 ] = 4;
    state->vars[ 7 ] = 5;
    state->vars[ 8 ] = 6;
    state->vars[ 9 ] = 7;
    state->vars[ 10 ] = 8;
    state->vars[ 11 ] = 9;
    state->vars[ 12 ] = 10;
    state->vars[ 13 ] = 11;
    break;
  case 13:
    state->vars[ 0 ] = 13;
    state->vars[ 1 ] = 0;
    state->vars[ 2 ] = 1;
    state->vars[ 3 ] = 2;
    state->vars[ 4 ] = 3;
    state->vars[ 5 ] = 4;
    state->vars[ 6 ] = 5;
    state->vars[ 7 ] = 6;
    state->vars[ 8 ] = 7;
    state->vars[ 9 ] = 8;
    state->vars[ 10 ] = 9;
    state->vars[ 11 ] = 10;
    state->vars[ 12 ] = 11;
    state->vars[ 13 ] = 12;
    break;
  }
}

/* get the first goal state and initialise iterator */
#define first_goal_state( state_ptr, int_ptr_goal_iter ) init_goal_state(state_ptr,*(int_ptr_goal_iter)=0)

/* get the next goal state
   returns 1 if there is another goal state, 0 otherwise */
static int8_t next_goal_state( state_t *state, int *goal_iter )
{
  switch( *goal_iter ) {
  case 0:
    ++(*goal_iter);
    init_goal_state( state, *goal_iter );
    return 1;
  case 1:
    ++(*goal_iter);
    init_goal_state( state, *goal_iter );
    return 1;
  case 2:
    ++(*goal_iter);
    init_goal_state( state, *goal_iter );
    return 1;
  case 3:
    ++(*goal_iter);
    init_goal_state( state, *goal_iter );
    return 1;
  case 4:
    ++(*goal_iter);
    init_goal_state( state, *goal_iter );
    return 1;
  case 5:
    ++(*goal_iter);
    init_goal_state( state, *goal_iter );
    return 1;
  case 6:
    ++(*goal_iter);
    init_goal_state( state, *goal_iter );
    return 1;
  case 7:
    ++(*goal_iter);
    init_goal_state( state, *goal_iter );
    return 1;
  case 8:
    ++(*goal_iter);
    init_goal_state( state, *goal_iter );
    return 1;
  case 9:
    ++(*goal_iter);
    init_goal_state( state, *goal_iter );
    return 1;
  case 10:
    ++(*goal_iter);
    init_goal_state( state, *goal_iter );
    return 1;
  case 11:
    ++(*goal_iter);
    init_goal_state( state, *goal_iter );
    return 1;
  case 12:
    ++(*goal_iter);
    init_goal_state( state, *goal_iter );
    return 1;
  case 13:
    return 0;
  }
  return 0;
}

