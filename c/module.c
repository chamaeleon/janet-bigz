#include <janet.h>
#include "bigz.h"
#include "bign.h"
#include "bigq.h"

static int bigz_gc(BigZ *p, size_t s)
{
    free(*p);
    return 0;
}

static void bigz_marshal(void *p, JanetMarshalContext *ctx)
{
}

static void *bigz_unmarshal(JanetMarshalContext *ctx)
{
    return NULL;
}

static void bigz_tostring(BigZ *bz_n, JanetBuffer *buffer)
{
    BzChar *n_str = BzToString(*bz_n, 10, 0);
    janet_formatb(buffer, "%s", n_str);
    BzFree(n_str);
}

static int bigz_compare(BigZ *a, BigZ *b)
{
    return BzCompare(*a, *b);
}

const JanetAbstractType janet_bigz_type = {
    .name = "bigz/BigZ",
    .gc = bigz_gc,
    // .marshal = bigz_marshal,
    // .unmarshal = bigz_unmarshal,
    .marshal = NULL,
    .unmarshal = NULL,
    .tostring = bigz_tostring,
    .compare = bigz_compare,
    JANET_ATEND_COMPARE
};

JANET_FN(cfun_BzVersion,
    "(bigz/version)",
    "Returns a string containing the version of bigz being used.")
{
    janet_fixarity(argc, 0);
    const char *version = BzVersion();
    return janet_stringv(version, strlen(version));
}

JANET_FN(cfun_BzCreate,
    "(bigz/create)",
    "Creates a new bigz instance. Not very useful since it can't be modified. "
    "The value of the instance will be zero.")
{
    janet_fixarity(argc, 1);
    BigNumLength size = janet_getuinteger(argv, 0);
    BigZ *bz_n = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_n = BzCreate(size);

    return janet_wrap_abstract(bz_n);
}

JANET_FN(cfun_BzNumDigits,
    "(bigz/num-digits)",
    "Returns the number of 'digits' used by a bigz number.")
{
    janet_fixarity(argc, 1);
    BigNumLength digits = BzNumDigits(*(BigZ*)janet_getabstract(argv, 0, &janet_bigz_type));
    return janet_wrap_integer(digits);
}

JANET_FN(cfun_BzLength,
    "(bigz/length)",
    "Returns the number of bits used by a bigz number.")
{
    janet_fixarity(argc, 1);
    BigNumLength digits = BzLength(*(BigZ*)janet_getabstract(argv, 0, &janet_bigz_type));
    return janet_wrap_integer(digits);
}

JANET_FN(cfun_BzNegate,
    "(bigz/negate n)",
    "Negates a bigz number.")
{
    janet_fixarity(argc, 1);
    BigZ *bz_n = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzNegate(*bz_n);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzAbs,
    "(bigz/abs n)",
    "Returns the absolute value of a bigz number.")
{
    janet_fixarity(argc, 1);
    BigZ *bz_n = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzAbs(*bz_n);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzCompare,
    "(bigz/compare a b)",
    "Compares two bigz numbers. Returns -1 if a is less than b, "
    "0 if a and b are equal, and 1 if a is greater than b.")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_b = janet_getabstract(argv, 1, &janet_bigz_type);
    return janet_wrap_integer(BzCompare(*bz_a, *bz_b));
}

JANET_FN(cfun_BzAdd,
    "(bigz/add a b)",
    "Returns the sum of two bigz numbers.")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_b = janet_getabstract(argv, 1, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzAdd(*bz_a, *bz_b);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzSubtract,
    "(bigz/subtract a b)",
    "Returns the difference between two bigz numbers.")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_b = janet_getabstract(argv, 1, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzSubtract(*bz_a, *bz_b);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzMultiply,
    "(bigz/multiply a b)",
    "Returns the product of two bigz numbers.")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_b = janet_getabstract(argv, 1, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzMultiply(*bz_a, *bz_b);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzDivide,
    "(bigz/divide a b)",
    "Returns a tuple containing the quotient and the remainder "
    "when dividing a bigz number by another bigz number.")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_b = janet_getabstract(argv, 1, &janet_bigz_type);
    BigZ *bz_quotient = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    BigZ *bz_remainder = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_quotient = BzDivide(*bz_a, *bz_b, bz_remainder);
    Janet *tuple = janet_tuple_begin(2);
    tuple[0] = janet_wrap_abstract(bz_quotient);
    tuple[1] = janet_wrap_abstract(bz_remainder);
    return janet_wrap_tuple(janet_tuple_end(tuple));
}

JANET_FN(cfun_BzDiv,
    "(bigz/div a b)",
    "Returns the quotient when dividing a bigz number by another bigz number.")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_b = janet_getabstract(argv, 1, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzDiv(*bz_a, *bz_b);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzTruncate,
    "(bigz/truncate a b)",
    "Performs a division, exact semantics is currently a bit unclear. "
    "Negative values yields slightly different results from `div`.")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_b = janet_getabstract(argv, 1, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzTruncate(*bz_a, *bz_b);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzFloor,
    "(bigz/floor a b)",
    "Performs a division of two bigz numbers, rounding down.")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_b = janet_getabstract(argv, 1, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzFloor(*bz_a, *bz_b);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzCeiling,
    "(bigz/ceiling a b)",
    "Performs a division of two bigz numbers, rounding up.")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_b = janet_getabstract(argv, 1, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzCeiling(*bz_a, *bz_b);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzRound,
    "(bigz/round a b)",
    "Performs a divison of two bigz numbers, rounding towards an even result.")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_b = janet_getabstract(argv, 1, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzRound(*bz_a, *bz_b);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzMod,
    "(bigz/mod a b)",
    "Returns the modulus of two bigz numbers.")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_b = janet_getabstract(argv, 1, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzMod(*bz_a, *bz_b);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzRem,
    "(bigz/rem a b)",
    "Returns the remainder of a divison of two bigz numbers.")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_b = janet_getabstract(argv, 1, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzRem(*bz_a, *bz_b);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzPow,
    "(bigz/pow a b)",
    "Returns the exponentiation of a bigz number by an integer.")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BzUInt b = janet_getinteger(argv, 1);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzPow(*bz_a, b);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzIsEven,
    "(bigz/is-even n)",
    "Returns true if the bigz number is even, otherwise false.")
{
    janet_fixarity(argc, 1);
    BigZ *bz_n = janet_getabstract(argv, 0, &janet_bigz_type);
    BigNumBool result = BzIsEven(*bz_n);
    return janet_wrap_boolean(result);
}

JANET_FN(cfun_BzIsOdd,
    "(bigz/is-odd n)",
    "Returns true if the bigz number is odd, otherwise false.")
{
    janet_fixarity(argc, 1);
    BigZ *bz_n = janet_getabstract(argv, 0, &janet_bigz_type);
    BigNumBool result = BzIsOdd(*bz_n);
    return janet_wrap_boolean(result);
}

JANET_FN(cfun_BzToString,
    "(bigz/to-string n base sign)",
    "Converts a bigz number to a string. The specified base will be used, "
    "and if sign is true, an explicit plus will be included at the start "
    "for positive numbers.")
{
    janet_fixarity(argc, 3);
    BigZ *bz_n = janet_getabstract(argv, 0, &janet_bigz_type);
    BigNumDigit base = janet_getinteger(argv, 1);
    int sign = janet_getboolean(argv, 2);
    BzChar *n_str = BzToString(*bz_n, base, sign);
    Janet result = janet_cstringv(n_str);
    free(n_str);
    return result;
}

JANET_FN(cfun_BzFromString,
    "(bigz/from-string s base)",
    "Converts a string in a given base to a bigz number.")
{
    janet_fixarity(argc, 2);
    BigZ *bz_n = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_n = BzFromString(janet_getstring(argv, 0), janet_getinteger(argv, 1), BZ_UNTIL_END);
    return janet_wrap_abstract(bz_n);
}

JANET_FN(cfun_BzFromInteger,
    "(bigz/from-integer n)",
    "Converts an integer into a bigz number.")
{
    janet_fixarity(argc, 1);
    BigZ *bz_n = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_n = BzFromInteger(janet_getinteger(argv, 0));
    return janet_wrap_abstract(bz_n);
}

JANET_FN(cfun_BzToInteger,
    "(bigz/to-integer n)",
    "Converts a bigz number into an integer.")
{
    janet_fixarity(argc, 1);
    BigZ *bz_n = janet_getabstract(argv, 0, &janet_bigz_type);
    return janet_wrap_integer(BzToInteger(*bz_n));
}

JANET_FN(cfun_BzToDouble,
    "(bigz/to-double n)",
    "Converts a bigz number into a double.")
{
    janet_fixarity(argc, 1);
    BigZ *bz_n = janet_getabstract(argv, 0, &janet_bigz_type);
    return janet_wrap_number(BzToInteger(*bz_n));
}

JANET_FN(cfun_BzTestBit,
    "(bigz/test-bit bit n)",
    "Returns true if the specified bit is set in the bigz number.")
{
    janet_fixarity(argc, 2);
    BigNumLength bit = janet_getuinteger(argv, 0);
    BigZ *bz_n = janet_getabstract(argv, 1, &janet_bigz_type);
    return janet_wrap_integer(BzTestBit(bit, *bz_n));
}

JANET_FN(cfun_BzBitCount,
    "(bigz/bit-count n)",
    "Returns the number of bits that are set to 1 in the bigz number.")
{
    janet_fixarity(argc, 1);
    BigZ *bz_n = janet_getabstract(argv, 0, &janet_bigz_type);
    BigNumLength count = BzBitCount(*bz_n);
    return janet_wrap_integer(count);
}

JANET_FN(cfun_BzNot,
    "(bigz/not n)",
    "Returns the bitwise not value of a bigz number.")
{
    janet_fixarity(argc, 1);
    BigZ *bz_n = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *result = BzNot(*bz_n);
    return janet_wrap_abstract(result);
}

JANET_FN(cfun_BzAnd,
    "(bigz/and a b)",
    "Returns the bitwise and result of two bigz numbers.")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_b = janet_getabstract(argv, 1, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzAnd(*bz_a, *bz_b);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzOr,
    "(bigz/or a b)",
    "Returns the bitwise or result of two bigz numbers.")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_b = janet_getabstract(argv, 1, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzOr(*bz_a, *bz_b);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzXor,
    "(bigz/xor a b)",
    "Returns the bitwize xor result of two bigz numbers.")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_b = janet_getabstract(argv, 1, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzXor(*bz_a, *bz_b);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzNand,
    "(bigz/nand a b)",
    "Returns the bitwise nand result of two bigz numbers.")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_b = janet_getabstract(argv, 1, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzNand(*bz_a, *bz_b);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzNor,
    "(bigz/nor a b)",
    "Returns the bitwise nor result of two bigz numbers.")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_b = janet_getabstract(argv, 1, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzNor(*bz_a, *bz_b);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzEqv,
    "(bigz/eqv a b)",
    "Returns the bitwise not of the xor result of two bigz numbers (~(a^b)).")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_b = janet_getabstract(argv, 1, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzEqv(*bz_a, *bz_b);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzAndC1,
    "(bigz/and-c1 a b)",
    "Returns the bitwise and result of a bitwise not of the first argument, "
    "and the second argument (~a ^ b)")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_b = janet_getabstract(argv, 1, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzAndC1(*bz_a, *bz_b);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzAndC2,
    "(bigz/and-c2 a b)",
    "Returns the bitwise and result of the first argument with the bitwise "
    "not of the second argument.")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_b = janet_getabstract(argv, 1, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzAndC2(*bz_a, *bz_b);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzOrC1,
    "(bigz/or-c1 a b)",
    "Returns the bitwise or result of a bitwise not of the first argument, "
    "and the second argument (~a ^ b)")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_b = janet_getabstract(argv, 1, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzOrC1(*bz_a, *bz_b);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzOrC2,
    "(bigz/or-c2 a b)",
    "Returns the bitwise or result of the first argument with the bitwise "
    "not of the second argument.")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_b = janet_getabstract(argv, 1, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzOrC2(*bz_a, *bz_b);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzAsh,
    "(bigz/ash a b)",
    "Returns the value of performing an arithmetic shift of a bigz number "
    "with an integer. A positive shift will multiply by powers of two, "
    "a negative shift will divide by powers of two.")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    int b = janet_getinteger(argv, 1);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzAsh(*bz_a, b);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzSqrt,
    "(bigz/sqrt n)",
    "Returns a bigz number that is the integral value of the square root "
    "of the argument.")
{
    janet_fixarity(argc, 1);
    BigZ *bz_n = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzSqrt(*bz_n);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzLcm,
    "(bigz/lcm a b)",
    "Returns the least common multiple of two bigz numbers.")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_b = janet_getabstract(argv, 1, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzLcm(*bz_a, *bz_b);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzGcd,
    "(bigz/gcd a b)",
    "Returns the greatest common divisor of two bigz numbers.")
{
    janet_fixarity(argc, 2);
    BigZ *bz_a = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_b = janet_getabstract(argv, 1, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzGcd(*bz_a, *bz_b);
    return janet_wrap_abstract(bz_result);
}

static unsigned int random_seed = 0;

JANET_FN(cfun_set_random_seed,
    "(bigz/set-random-seed n)",
    "Set the random seed.")
{
    janet_fixarity(argc, 1);
    random_seed = janet_getuinteger(argv, 0);
    return janet_wrap_nil();
}

JANET_FN(cfun_get_random_seed,
    "(bigz/get-random-seed)",
    "Get the random seed.")
{
    janet_fixarity(argc, 0);
    return janet_wrap_number(random_seed);
}

JANET_FN(cfun_BzRandom,
    "(bigz/random n)",
    "Generate a random number between zero and up, to but not including, "
    "the bigz number n.")
{
    janet_fixarity(argc, 1);
    BigZ *bz_n = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzRandom(*bz_n, &random_seed);
    return janet_wrap_abstract(bz_result);
}

JANET_FN(cfun_BzModExp,
    "(bigz/mod-exp base exponent modulus)",
    "Returns the modular exponentiation of a bigz number by another bigz number "
    "(the modulus is also a bigz number).")
{
    janet_fixarity(argc, 3);
    BigZ *bz_base = janet_getabstract(argv, 0, &janet_bigz_type);
    BigZ *bz_exponent = janet_getabstract(argv, 1, &janet_bigz_type);
    BigZ *bz_modulus = janet_getabstract(argv, 2, &janet_bigz_type);
    BigZ *bz_result = janet_abstract(&janet_bigz_type, sizeof(BigZ *));
    *bz_result = BzModExp(*bz_base, *bz_exponent, *bz_modulus);
    return janet_wrap_abstract(bz_result);
}

JANET_MODULE_ENTRY(JanetTable *env) {
    // janet_cfuns(env, "bigz", cfuns);
    JanetRegExt cfuns[] = {
        JANET_REG("version", cfun_BzVersion),
        JANET_REG("create", cfun_BzCreate),
        JANET_REG("num-digits", cfun_BzNumDigits),
        JANET_REG("length", cfun_BzLength),
        JANET_REG("negate", cfun_BzNegate),
        JANET_REG("abs", cfun_BzAbs),
        JANET_REG("compare", cfun_BzCompare),
        JANET_REG("add", cfun_BzAdd),
        JANET_REG("subtract", cfun_BzSubtract),
        JANET_REG("multiply", cfun_BzMultiply),
        JANET_REG("divide", cfun_BzDivide),
        JANET_REG("div", cfun_BzDiv),
        JANET_REG("truncate", cfun_BzTruncate),
        JANET_REG("floor", cfun_BzFloor),
        JANET_REG("ceiling", cfun_BzCeiling),
        JANET_REG("round", cfun_BzRound),
        JANET_REG("mod", cfun_BzMod),
        JANET_REG("rem", cfun_BzRem),
        JANET_REG("pow", cfun_BzPow),
        JANET_REG("even?", cfun_BzIsEven),
        JANET_REG("odd?", cfun_BzIsOdd),
        JANET_REG("to-string", cfun_BzToString),
        JANET_REG("from-string", cfun_BzFromString),
        JANET_REG("from-integer", cfun_BzFromInteger),
        JANET_REG("to-integer", cfun_BzToInteger),
        JANET_REG("to-double", cfun_BzToDouble),
        JANET_REG("test-bit", cfun_BzTestBit),
        JANET_REG("bit-count", cfun_BzBitCount),
        JANET_REG("not", cfun_BzNot),
        JANET_REG("and", cfun_BzAnd),
        JANET_REG("or", cfun_BzOr),
        JANET_REG("nand", cfun_BzNand),
        JANET_REG("nor", cfun_BzNor),
        JANET_REG("eqv", cfun_BzEqv),
        JANET_REG("and-c1", cfun_BzAndC1),
        JANET_REG("and-c2", cfun_BzAndC2),
        JANET_REG("or-c1", cfun_BzOrC1),
        JANET_REG("or-c2", cfun_BzOrC2),
        JANET_REG("ash", cfun_BzAsh),
        JANET_REG("sqrt", cfun_BzSqrt),
        JANET_REG("lcm", cfun_BzLcm),
        JANET_REG("gcd", cfun_BzGcd),
        JANET_REG("set-random-seed", cfun_set_random_seed),
        JANET_REG("get-random-seed", cfun_get_random_seed),
        JANET_REG("random", cfun_BzRandom),
        JANET_REG("mod-exp", cfun_BzModExp),
        JANET_REG_END
    };
    janet_cfuns_ext(env, "bigz", cfuns);
    janet_register_abstract_type(&janet_bigz_type);
}
