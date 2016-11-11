#ifndef __MEMBRANE_H__
#define __MEMBRANE_H__

#include <stdio.h>
#include <stdarg.h>
#include <erl_nif.h>



#define MEMBRANE_DEBUG(message, ...) membrane_debug(MEMBRANE_LOG_TAG, message, ##__VA_ARGS__);


/**
 * Prints debug message to the stderr.
 *
 * Accepts standard printf format specifiers and syntax.
 *
 * Moreover, it allows to use %T format specifier to dump erlang terms.
 *
 * Use MEMBRANE_DEBUG instead.
 */
static void membrane_debug(const char *tag, const char *format, ...) {
  char debug[256];
  va_list args;

  va_start(args, format);
  enif_snprintf(debug, 256, format, args);
  fprintf(stderr, "[%s] %s\n", tag, debug);

  va_end(args);
}


/**
 * Builds `{:error, reason}`.
 */
static ERL_NIF_TERM membrane_util_make_error(ErlNifEnv* env, ERL_NIF_TERM reason) {
  ERL_NIF_TERM tuple[2] = {
    enif_make_atom(env, "error"),
    reason
  };

  return enif_make_tuple_from_array(env, tuple, 2);
}


/**
 * Builds `{:ok, arg}`.
 */
static ERL_NIF_TERM membrane_util_make_ok_tuple(ErlNifEnv* env, ERL_NIF_TERM arg) {
  ERL_NIF_TERM tuple[2] = {
    enif_make_atom(env, "ok"),
    arg
  };

  return enif_make_tuple_from_array(env, tuple, 2);
}


/**
 * Builds `:ok`.
 */
static ERL_NIF_TERM membrane_util_make_ok(ErlNifEnv* env) {
  return enif_make_atom(env, "ok");
}


/**
 * Builds `:todo`.
 */
static ERL_NIF_TERM membrane_util_make_todo(ErlNifEnv* env) {
  return enif_make_atom(env, "todo");
}


/**
 * Builds `{:error, {:args, field, description}}` for returning when
 * certain constructor-style functions get invalid arguments.
 */
static ERL_NIF_TERM membrane_util_make_error_args(ErlNifEnv* env, const char* field, const char *description) {
  ERL_NIF_TERM tuple[3] = {
    enif_make_atom(env, "args"),
    enif_make_atom(env, field),
    enif_make_string(env, description, ERL_NIF_LATIN1)
  };

  return membrane_util_make_error(env, enif_make_tuple_from_array(env, tuple, 3));
}

/**
 * Builds `{:error, {:internal, reason}}` for returning when certain
 * constructor-style functions fails on internal stuff that should generally
 * speaking, not fail.
 */
static ERL_NIF_TERM membrane_util_make_error_internal(ErlNifEnv* env, const char* reason) {
  ERL_NIF_TERM tuple[3] = {
    enif_make_atom(env, "internal"),
    enif_make_atom(env, reason)
  };

  return membrane_util_make_error(env, enif_make_tuple_from_array(env, tuple, 2));
}

#endif
