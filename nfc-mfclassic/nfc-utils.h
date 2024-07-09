/**
 * @file nfc-utils.h
 * @brief Provide some examples shared functions like print, parity calculation, options parsing.
 */

#ifndef _EXAMPLES_NFC_UTILS_H_
#  define _EXAMPLES_NFC_UTILS_H_

#  include <stdlib.h>
#  include <string.h>
#  include <err.h>

/**
 * @macro DBG
 * @brief Print a message of standard output only in DEBUG mode
 */
#ifdef DEBUG
#  define DBG(...) do { \
    warnx ("DBG %s:%d", __FILE__, __LINE__); \
    warnx ("    " __VA_ARGS__ ); \
  } while (0)
#else
#  define DBG(...) {}
#endif

/**
 * @macro WARN
 * @brief Print a warn message
 */
#ifdef DEBUG
#  define WARN(...) do { \
    warnx ("WARNING %s:%d", __FILE__, __LINE__); \
    warnx ("    " __VA_ARGS__ ); \
  } while (0)
#else
#  define WARN(...) warnx ("WARNING: " __VA_ARGS__ )
#endif

/**
 * @macro ERR
 * @brief Print a error message
 */
#ifdef DEBUG
#  define ERR(...) do { \
    warnx ("ERROR %s:%d", __FILE__, __LINE__); \
    warnx ("    " __VA_ARGS__ ); \
  } while (0)
#else
#  define ERR(...)  warnx ("ERROR: " __VA_ARGS__ )
#endif

#ifndef MIN
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif

uint8_t  oddparity(const uint8_t bt);
void    oddparity_bytes_ts(const uint8_t *pbtData, const size_t szLen, uint8_t *pbtPar);

void    print_hex(const uint8_t *pbtData, const size_t szLen);
void    print_hex_bits(const uint8_t *pbtData, const size_t szBits);
void    print_hex_par(const uint8_t *pbtData, const size_t szBits, const uint8_t *pbtDataPar);

void    print_nfc_target(const nfc_target *pnt, bool verbose);

#endif