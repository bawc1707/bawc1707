/**
 * @file nfc-utils.c
 * @brief Provide some examples shared functions like print, parity calculation, options parsing.
 */
#include <nfc/nfc.h>
#include <err.h>

#include "nfc-utils.h"

uint8_t oddparity(const uint8_t bt)
{
  // cf http://graphics.stanford.edu/~seander/bithacks.html#ParityParallel
  return (0x9669 >> ((bt ^ (bt >> 4)) & 0xF)) & 1;
}

void oddparity_bytes_ts(const uint8_t *pbtData, const size_t szLen, uint8_t *pbtPar)
{
  size_t  szByteNr;
  // Calculate the parity bits for the command
  for (szByteNr = 0; szByteNr < szLen; szByteNr++) {
    pbtPar[szByteNr] = oddparity(pbtData[szByteNr]);
  }
}

void print_hex(const uint8_t *pbtData, const size_t szBytes)
{
  size_t  szPos;

  for (szPos = 0; szPos < szBytes; szPos++) {
    printf("%02x  ", pbtData[szPos]);
  }
  printf("\n");
}

void print_hex_bits(const uint8_t *pbtData, const size_t szBits)
{
  uint8_t uRemainder;
  size_t  szPos;
  size_t  szBytes = szBits / 8;

  for (szPos = 0; szPos < szBytes; szPos++) {
    printf("%02x  ", pbtData[szPos]);
  }

  uRemainder = szBits % 8;
  // Print the rest bits
  if (uRemainder != 0) {
    if (uRemainder < 5)
      printf("%01x (%d bits)", pbtData[szBytes], uRemainder);
    else
      printf("%02x (%d bits)", pbtData[szBytes], uRemainder);
  }
  printf("\n");
}

void print_hex_par(const uint8_t *pbtData, const size_t szBits, const uint8_t *pbtDataPar)
{
  uint8_t uRemainder;
  size_t  szPos;
  size_t  szBytes = szBits / 8;

  for (szPos = 0; szPos < szBytes; szPos++) {
    printf("%02x", pbtData[szPos]);
    if (oddparity(pbtData[szPos]) != pbtDataPar[szPos]) {
      printf("! ");
    } else {
      printf("  ");
    }
  }

  uRemainder = szBits % 8;
  // Print the rest bits, these cannot have parity bit
  if (uRemainder != 0) {
    if (uRemainder < 5)
      printf("%01x (%d bits)", pbtData[szBytes], uRemainder);
    else
      printf("%02x (%d bits)", pbtData[szBytes], uRemainder);
  }
  printf("\n");
}

void print_nfc_target(const nfc_target *pnt, bool verbose)
{
  char *s;
  str_nfc_target(&s, pnt, verbose);
  printf("%s", s);
  nfc_free(s);
}