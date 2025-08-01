#include "data.table.h"
#include <Rdefines.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Visibility.h>

// global constants extern in data.table.h for gcc10 -fno-common; #4091
// these are written to once here on initialization, but because of that write they can't be declared const
SEXP char_integer64;
SEXP char_ITime;
SEXP char_IDate;
SEXP char_Date;
SEXP char_POSIXct;
SEXP char_POSIXt;
SEXP char_UTC;
SEXP char_nanotime;
SEXP char_lens;
SEXP char_indices;
SEXP char_allLen1;
SEXP char_allGrp1;
SEXP char_factor;
SEXP char_ordered;
SEXP char_datatable;
SEXP char_dataframe;
SEXP char_NULL;
SEXP char_maxString;
SEXP char_AsIs;
SEXP sym_sorted;
SEXP sym_index;
SEXP sym_BY;
SEXP sym_starts, char_starts;
SEXP sym_maxgrpn;
SEXP sym_anyna;
SEXP sym_anyinfnan;
SEXP sym_anynotascii;
SEXP sym_anynotutf8;
SEXP sym_colClassesAs;
SEXP sym_verbose;
SEXP SelfRefSymbol;
SEXP sym_inherits;
SEXP sym_datatable_locked;
SEXP sym_tzone;
SEXP sym_old_fread_datetime_character;
SEXP sym_variable_table;
SEXP sym_as_character;
SEXP sym_as_posixct;
double NA_INT64_D;
long long NA_INT64_LL;
Rcomplex NA_CPLX;
size_t r_type_sizes[100];
size_t r_type_order[100];

static const
R_CallMethodDef callMethods[] = {
{"Csetattrib", (DL_FUNC) &setattrib, -1},
{"Cbmerge", (DL_FUNC) &bmerge, -1},
{"Cassign", (DL_FUNC) &assign, -1},
{"Cdogroups", (DL_FUNC) &dogroups, -1},
{"Ccopy", (DL_FUNC) &copy, -1},
{"Cshallowwrapper", (DL_FUNC) &shallowwrapper, -1},
{"Csetdt_nrows", (DL_FUNC) &setdt_nrows, -1},
{"Calloccolwrapper", (DL_FUNC) &alloccolwrapper, -1},
{"Cselfrefokwrapper", (DL_FUNC) &selfrefokwrapper, -1},
{"Ctruelength", (DL_FUNC) &truelength, -1},
{"Csetcharvec", (DL_FUNC) &setcharvec, -1},
{"Csetcolorder", (DL_FUNC) &setcolorder, -1},
{"Cchmatch", (DL_FUNC) &chmatch_R, -1},
{"Cchmatchdup", (DL_FUNC) &chmatchdup_R, -1},
{"Cchin", (DL_FUNC) &chin_R, -1},
{"CfreadR", (DL_FUNC) &freadR, -1},
{"CfwriteR", (DL_FUNC) &fwriteR, -1},
{"Creorder", (DL_FUNC) &reorder, -1},
{"Crbindlist", (DL_FUNC) &rbindlist, -1},
{"Cvecseq", (DL_FUNC) &vecseq, -1},
{"Csetlistelt", (DL_FUNC) &setlistelt, -1},
{"CsetS4elt", (DL_FUNC) &setS4elt, -1},
{"Caddress", (DL_FUNC) &address, -1},
{"CexpandAltRep", (DL_FUNC) &expandAltRep, -1},
{"Cfmelt", (DL_FUNC) &fmelt, -1},
{"Cfcast", (DL_FUNC) &fcast, -1},
{"Cuniqlist", (DL_FUNC) &uniqlist, -1},
{"Cuniqlengths", (DL_FUNC) &uniqlengths, -1},
{"CforderReuseSorting", (DL_FUNC) &forderReuseSorting, -1},
{"Cforder", (DL_FUNC) &forder, -1},
{"Cissorted", (DL_FUNC) &issorted, -1},
{"Cgforce", (DL_FUNC) &gforce, -1},
{"Cgsum", (DL_FUNC) &gsum, -1},
{"Cgmean", (DL_FUNC) &gmean, -1},
{"Cgmin", (DL_FUNC) &gmin, -1},
{"Cgmax", (DL_FUNC) &gmax, -1},
{"CisOrderedSubset", (DL_FUNC) &isOrderedSubset, -1},
{"CsetNumericRounding", (DL_FUNC) &setNumericRounding, -1},
{"CgetNumericRounding", (DL_FUNC) &getNumericRounding, -1},
{"Cbinary", (DL_FUNC) &binary, -1},
{"CsubsetDT", (DL_FUNC) &subsetDT, -1},
{"CsubsetVector", (DL_FUNC) &subsetVector, -1},
{"CconvertNegAndZeroIdx", (DL_FUNC) &convertNegAndZeroIdx, -1},
{"Cfrank", (DL_FUNC) &frank, -1},
{"Cdt_na", (DL_FUNC) &dt_na, -1},
{"Clookup", (DL_FUNC) &lookup, -1},
{"Coverlaps", (DL_FUNC) &overlaps, -1},
{"Cwhichwrapper", (DL_FUNC) &whichwrapper, -1},
{"Cshift", (DL_FUNC) &shift, -1},
{"Ctranspose", (DL_FUNC) &transpose, -1},
{"CanyNA", (DL_FUNC) &anyNA, -1},
{"CfitsInInt32R", (DL_FUNC) &fitsInInt32R, -1},
{"CfitsInInt64R", (DL_FUNC) &fitsInInt64R, -1},
{"Csetlevels", (DL_FUNC) &setlevels, -1},
{"Crleid", (DL_FUNC) &rleid, -1},
{"Cgmedian", (DL_FUNC) &gmedian, -1},
{"Cgtail", (DL_FUNC) &gtail, -1},
{"Cghead", (DL_FUNC) &ghead, -1},
{"Cglast", (DL_FUNC) &glast, -1},
{"Cgfirst", (DL_FUNC) &gfirst, -1},
{"Cgnthvalue", (DL_FUNC) &gnthvalue, -1},
{"Cdim", (DL_FUNC) &dim, -1},
{"Cgvar", (DL_FUNC) &gvar, -1},
{"Cgsd", (DL_FUNC) &gsd, -1},
{"Cgprod", (DL_FUNC) &gprod, -1},
{"Cgshift", (DL_FUNC) &gshift, -1},
{"Cnestedid", (DL_FUNC) &nestedid, -1},
{"CsetDTthreads", (DL_FUNC) &setDTthreads, -1},
{"CgetDTthreads", (DL_FUNC) &getDTthreads_R, -1},
{"CnqRecreateIndices", (DL_FUNC) &nqRecreateIndices, -1},
{"Cfsort", (DL_FUNC) &fsort, -1},
{"Cinrange", (DL_FUNC) &inrange, -1},
{"Cbetween", (DL_FUNC) &between, -1},
{"ChasOpenMP", (DL_FUNC) &hasOpenMP, -1},
{"CuniqueNlogical", (DL_FUNC) &uniqueNlogical, -1},
{"CfrollfunR", (DL_FUNC) &frollfunR, -1},
{"CdllVersion", (DL_FUNC) &dllVersion, -1},
{"CnafillR", (DL_FUNC) &nafillR, -1},
{"CcolnamesInt", (DL_FUNC) &colnamesInt, -1},
{"CinitLastUpdated", (DL_FUNC) &initLastUpdated, -1},
{"Ccj", (DL_FUNC) &cj, -1},
{"Ccoalesce", (DL_FUNC) &coalesce, -1},
{"CfifelseR", (DL_FUNC) &fifelseR, -1},
{"CfcaseR", (DL_FUNC) &fcaseR, -1},
{"C_lock", (DL_FUNC) &lock, -1},  // _ for these 3 to avoid Clock as in time
{"C_unlock", (DL_FUNC) &unlock, -1},
{"C_islocked", (DL_FUNC) &islockedR, -1},
{"CfrollapplyR", (DL_FUNC) &frollapplyR, -1},
{"CtestMsgR", (DL_FUNC) &testMsgR, -1},
{"C_allNAR", (DL_FUNC) &allNAR, -1},
{"CcoerceAs", (DL_FUNC) &coerceAs, -1},
{"Ctest_dt_win_snprintf", (DL_FUNC)&test_dt_win_snprintf, -1},
{"Cdt_zlib_version", (DL_FUNC)&dt_zlib_version, -1},
{"Cdt_has_zlib", (DL_FUNC)&dt_has_zlib, -1},
{"Csubstitute_call_arg_namesR", (DL_FUNC) &substitute_call_arg_namesR, -1},
{"CstartsWithAny", (DL_FUNC)&startsWithAny, -1},
{"CconvertDate", (DL_FUNC)&convertDate, -1},
{"Cnotchin", (DL_FUNC)&notchin, -1},
{"Ccbindlist", (DL_FUNC) &cbindlist, -1},
{"CperhapsDataTableR", (DL_FUNC) &perhapsDataTableR, -1},
{"CcopyCols", (DL_FUNC) &copyCols, -1},
{"Cwarn_matrix_column_r", (DL_FUNC)&warn_matrix_column_r, -1},
{"Cfrev", (DL_FUNC) &frev, -1},
{NULL, NULL, 0}
};

static const
R_ExternalMethodDef externalMethods[] = {
{"Cfastmean", (DL_FUNC) &fastmean, -1},
{NULL, NULL, 0}
};

static void setSizes(void) {
  for (int i=0; i<100; ++i) { r_type_sizes[i]=0; r_type_order[i]=0; }
  // only these types are currently allowed as column types :
  r_type_sizes[LGLSXP] =  sizeof(int);       r_type_order[LGLSXP] =  0;
  r_type_sizes[RAWSXP] =  sizeof(Rbyte);     r_type_order[RAWSXP] =  1;
  r_type_sizes[INTSXP] =  sizeof(int);       r_type_order[INTSXP] =  2;   // integer and factor
  r_type_sizes[REALSXP] = sizeof(double);    r_type_order[REALSXP] = 3;   // numeric and integer64
  r_type_sizes[CPLXSXP] = sizeof(Rcomplex);  r_type_order[CPLXSXP] = 4;
  r_type_sizes[STRSXP] =  sizeof(SEXP *);    r_type_order[STRSXP] =  5;
  r_type_sizes[VECSXP] =  sizeof(SEXP *);    r_type_order[VECSXP] =  6;   // list column
  if (sizeof(char *)>8) error(_("Pointers are %zu bytes, greater than 8. We have not tested on any architecture greater than 64bit yet."), sizeof(char *));
  // One place we need the largest sizeof is the working memory malloc in reorder.c
}

void attribute_visible R_init_data_table(DllInfo *info)
{
  // C exported routines
  // must be also listed in inst/include/datatableAPI.h
  // for end user documentation see ?cdt
  R_RegisterCCallable("data.table", "DT_subsetDT", (DL_FUNC) &subsetDT);

  R_registerRoutines(info, NULL, callMethods, NULL, externalMethods);
  R_useDynamicSymbols(info, FALSE);
  setSizes();
  const char *msg = _("... failed. Please forward this message to maintainer('data.table').");
  if ((int)NA_INTEGER != (int)INT_MIN) error(_("Checking NA_INTEGER [%d] == INT_MIN [%d] %s"), NA_INTEGER, INT_MIN, msg);
  if ((int)NA_INTEGER != (int)NA_LOGICAL) error(_("Checking NA_INTEGER [%d] == NA_LOGICAL [%d] %s"), NA_INTEGER, NA_LOGICAL, msg);
  if (sizeof(int) != 4)       error(_("Checking sizeof(%s) [%zu] is %d %s"), "int", sizeof(int), 4, msg);
  if (sizeof(double) != 8)    error(_("Checking sizeof(%s) [%zu] is %d %s"), "double", sizeof(double), 8, msg);     // 8 on both 32bit and 64bit
  // alignof not available in C99: if (alignof(double) != 8) error(_("Checking alignof(double) [%lu] is 8 %s"), alignof(double), msg);  // 8 on both 32bit and 64bit
  if (sizeof(long long) != 8) error(_("Checking sizeof(%s) [%zu] is %d %s"), "long long", sizeof(long long), 8, msg);
  if (sizeof(char *) != 4 && sizeof(char *) != 8) error(_("Checking sizeof(pointer) [%zu] is 4 or 8 %s"), sizeof(char *), msg);
  if (sizeof(SEXP) != sizeof(char *)) error(_("Checking sizeof(SEXP) [%zu] == sizeof(pointer) [%zu] %s"), sizeof(SEXP), sizeof(char *), msg);
  if (sizeof(uint64_t) != 8) error(_("Checking sizeof(%s) [%zu] is %d %s"), "uint64_t", sizeof(uint64_t), 8, msg);
  if (sizeof(int64_t) != 8)  error(_("Checking sizeof(%s) [%zu] is %d %s"), "int64_t", sizeof(int64_t), 8, msg);
  if (sizeof(signed char) != 1) error(_("Checking sizeof(%s) [%zu] is %d %s"), "signed char", sizeof(signed char), 1, msg);
  if (sizeof(int8_t) != 1)   error(_("Checking sizeof(%s) [%zu] is %d %s"), "int8_t", sizeof(int8_t), 1, msg);
  if (sizeof(uint8_t) != 1)  error(_("Checking sizeof(%s) [%zu] is %d %s"), "uint8_t", sizeof(uint8_t), 1, msg);
  if (sizeof(int16_t) != 2)  error(_("Checking sizeof(%s) [%zu] is %d %s"), "int16_t", sizeof(int16_t), 2, msg);
  if (sizeof(uint16_t) != 2) error(_("Checking sizeof(%s) [%zu] is %d %s"), "uint16_t", sizeof(uint16_t), 2 ,msg);

  SEXP tmp = PROTECT(allocVector(INTSXP,2));
  if (LENGTH(tmp)!=2) error(_("Checking LENGTH(allocVector(INTSXP,2)) [%d] is 2 %s"), LENGTH(tmp), msg);
  // Use (long long) to cast R_xlen_t to a fixed type to robustly avoid -Wformat compiler warnings, see #5768
  if (TRUELENGTH(tmp)!=0) error(_("Checking TRUELENGTH(allocVector(INTSXP,2)) [%lld] is 0 %s"), (long long)TRUELENGTH(tmp), msg);
  UNPROTECT(1);

  // According to IEEE (http://en.wikipedia.org/wiki/IEEE_754-1985#Zero) we can rely on 0.0 being all 0 bits.
  // But check here anyway just to be sure, just in case this answer is right (http://stackoverflow.com/a/2952680/403310).
  int i = 314;
  memset(&i, 0, sizeof(i));
  if (i != 0) error(_("Checking memset(&i,0,sizeof(int)); i == (int)0 %s"), msg);
  unsigned int ui = 314;
  memset(&ui, 0, sizeof(ui));
  if (ui != 0) error(_("Checking memset(&ui, 0, sizeof(unsigned int)); ui == (unsigned int)0 %s"), msg);
  double d = 3.14;
  memset(&d, 0, sizeof(d));
  if (d != 0.0) error(_("Checking memset(&d, 0, sizeof(double)); d == (double)0.0 %s"), msg);
  long double ld = 3.14;
  memset(&ld, 0, sizeof(ld));
  if (ld != 0.0) error(_("Checking memset(&ld, 0, sizeof(long double)); ld == (long double)0.0 %s"), msg);

  // Check unsigned cast used in fread.c. This isn't overflow/underflow, just cast.
  if ((uint_fast8_t)('0'-'/') != 1) error(_("Unlike the very common case, e.g. ASCII, the character '/' is not just before '0'."));
  if ((uint_fast8_t)('/'-'0') < 10) error(_("The C expression (uint_fast8_t)('/'-'0')<10 is true. Should be false."));
  if ((uint_fast8_t)(':'-'9') != 1) error(_("Unlike the very common case, e.g. ASCII, the character ':' is not just after '9'."));
  if ((uint_fast8_t)('9'-':') < 10) error(_("The C expression (uint_fast8_t)('9'-':')<10 is true. Should be false."));

  // Variables rather than #define for NA_INT64 to ensure correct usage; i.e. not casted
  NA_INT64_LL = LLONG_MIN;
  NA_INT64_D = LLtoD(NA_INT64_LL);
  if (NA_INT64_LL != DtoLL(NA_INT64_D)) error(_("Conversion of NA_INT64 via double failed %"PRId64"!=%"PRId64), (int64_t)NA_INT64_LL, (int64_t)DtoLL(NA_INT64_D));
  // LLONG_MIN when punned to double is the sign bit set and then all zeros in exponent and significand i.e. -0.0
  //   That's why we must never test for NA_INT64_D using == in double type. Must always DtoLL and compare long long types.
  //   Assigning NA_INT64_D to a REAL is ok however.
  if (NA_INT64_D != 0.0)  error(_("NA_INT64_D (negative -0.0) is not == 0.0."));
  if (NA_INT64_D != -0.0) error(_("NA_INT64_D (negative -0.0) is not ==-0.0."));
  if (ISNAN(NA_INT64_D)) error(_("ISNAN(NA_INT64_D) is TRUE but should not be"));
  if (isnan(NA_INT64_D)) error(_("isnan(NA_INT64_D) is TRUE but should not be"));

  NA_CPLX.r = NA_REAL;  // NA_REAL is defined as R_NaReal which is not a strict constant and thus initializer {NA_REAL, NA_REAL} can't be used in .h
  NA_CPLX.i = NA_REAL;  // https://github.com/Rdatatable/data.table/pull/3689/files#r304117234

  setNumericRounding(PROTECT(ScalarInteger(0))); // #1642, #1728, #1463, #485
  UNPROTECT(1);

  // create needed strings in advance for speed, same technique as R_*Symbol
  // Following R-exts 5.9.4; paragraph and example starting "Using install ..."
  // either use PRINTNAME(install()) or R_PreserveObject(mkChar()) here.
  char_integer64 = PRINTNAME(install("integer64"));
  char_ITime =     PRINTNAME(install("ITime"));
  char_IDate =     PRINTNAME(install("IDate"));
  char_Date =      PRINTNAME(install("Date"));   // used for IDate too since IDate inherits from Date
  char_POSIXct =   PRINTNAME(install("POSIXct"));
  char_POSIXt =    PRINTNAME(install("POSIXt"));
  char_UTC =       PRINTNAME(install("UTC"));
  char_nanotime =  PRINTNAME(install("nanotime"));
  char_starts =    PRINTNAME(sym_starts = install("starts"));
  char_lens =      PRINTNAME(install("lens"));
  char_indices =   PRINTNAME(install("indices"));
  char_allLen1 =   PRINTNAME(install("allLen1"));
  char_allGrp1 =   PRINTNAME(install("allGrp1"));
  char_factor =    PRINTNAME(install("factor"));
  char_ordered =   PRINTNAME(install("ordered"));
  char_datatable = PRINTNAME(install("data.table"));
  char_dataframe = PRINTNAME(install("data.frame"));
  char_NULL =      PRINTNAME(install("NULL"));
  char_maxString = PRINTNAME(install("\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"));
  char_AsIs =      PRINTNAME(install("AsIs"));

  if (TYPEOF(char_integer64) != CHARSXP) {
    // checking one is enough in case of any R-devel changes
    error(_("PRINTNAME(install(\"integer64\")) has returned %s not %s"), type2char(TYPEOF(char_integer64)), type2char(CHARSXP));  // # nocov
  }

  // create commonly used symbols, same as R_*Symbol but internal to DT
  // Not really for speed but to avoid leak in situations like setAttrib(DT, install(), allocVector()) where
  // the allocVector() can happen first and then the install() could gc and free it before it is protected
  // within setAttrib. Thanks to Bill Dunlap finding and reporting. Using these symbols instead of install()
  // avoids the gc without needing an extra PROTECT and immediate UNPROTECT after the setAttrib which would
  // look odd (and devs in future might be tempted to remove them). Avoiding passing install() to API calls
  // keeps the code neat and readable. Also see grep's added to CRAN_Release.cmd to find such calls.
  sym_sorted  = install("sorted");
  sym_index   = install("index");
  sym_BY      = install(".BY");
  sym_maxgrpn = install("maxgrpn");
  sym_anyna   = install("anyna");
  sym_anyinfnan = install("anyinfnan");
  sym_anynotascii = install("anynotascii");
  sym_anynotutf8 = install("anynotutf8");
  sym_colClassesAs = install("colClassesAs");
  sym_verbose = install("datatable.verbose");
  SelfRefSymbol = install(".internal.selfref");
  sym_inherits = install("inherits");
  sym_datatable_locked = install(".data.table.locked");
  sym_tzone = install("tzone");
  sym_old_fread_datetime_character = install("datatable.old.fread.datetime.character");
  sym_variable_table = install("variable_table");
  sym_as_character = install("as.character");
  sym_as_posixct = install("as.POSIXct");

  initDTthreads();
  avoid_openmp_hang_within_fork();
}

inline long long DtoLL(double x) {
  // Type punning such as
  //     *(long long *)&REAL(column)[i]
  // is undefined by C standards. This may have been the cause of 1.10.2 failing on 31 Jan 2017
  // under clang 3.9.1 -O3 and solaris-sparc but not solaris-x86 or gcc.
  // There is now a grep in CRAN_Release.cmd; use this union method instead.
  // int64_t may help rather than 'long long' (TODO: replace all long long with int64_t)
  // The two types must be the same size. That is checked in R_init_data_table (above)
  // where sizeof(int64_t)==sizeof(double)==8 is checked.
  // Endianness should not matter because whether big or little, endianness is the same
  // inside this process, and the two types are the same size.
  union {double d; int64_t i64;} u;  // not static, inline instead
  u.d = x;
  return (long long)u.i64;
}

inline double LLtoD(long long x) {
  union {double d; int64_t i64;} u;
  u.i64 = (int64_t)x;
  return u.d;
}

int GetVerbose(void) {
  // don't call repetitively; save first in that case
  SEXP opt = GetOption1(sym_verbose);
  if ((!isLogical(opt) && !isInteger(opt)) || LENGTH(opt)!=1 || INTEGER(opt)[0]==NA_INTEGER)
    error(_("verbose option must be length 1 non-NA logical or integer"));
  return INTEGER(opt)[0];
}

// # nocov start
SEXP hasOpenMP(void) {

#if defined(_OPENMP)
  // gcc build of libomp
  return ScalarInteger(_OPENMP); // return the version; e.g. 201511 (i.e. 4.5)
#elif defined(KMP_VERSION_BUILD)
  // LLVM builds of libomp
  return ScalarInteger(KMP_VERSION_BUILD);
#else
  // no OpenMP support detected
  return ScalarInteger(0);
#endif

}

// # nocov end

extern int *_Last_updated;  // assign.c

SEXP initLastUpdated(SEXP var) {
  if (!isInteger(var) || LENGTH(var)!=1) error(_(".Last.updated in namespace is not a length 1 integer"));
  _Last_updated = INTEGER(var);
  return R_NilValue;
}

SEXP dllVersion(void) {
  // .onLoad calls this and checks the same as packageVersion() to ensure no R/C version mismatch, #3056
  return(ScalarString(mkChar("1.17.99")));
}
