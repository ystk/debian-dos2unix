 *   Copyright (C) 2009-2013 Erwin Waterlander
 *
 *
#if defined(_WIN32) || defined(__CYGWIN__)
#ifdef S_ISBLK
#endif
 -o, --oldfile         write to old file (default)\n\
#ifdef D2U_UNICODE
  fprintf(stderr, _("\
 -ul, --assume-utf16le Assume that the input format is UTF-16LE\n\
 -ub, --assume-utf16be Assume that the input format is UTF-16BE\n"));
#endif
#define MINGW32_W64 1
#elif defined(__TURBOC__) && defined(__MSDOS__)
#elif defined(__DJGPP__)
#elif defined(__WIN64__) && defined(__MINGW64__)
#elif defined(_WIN32) && defined(__MINGW32__) && (D2U_COMPILER == MINGW32_W64)
  fprintf(stderr, "%s", _("Windows 32 bit version (MinGW-w64).\n"));
#elif defined(_WIN32) && defined(__MINGW32__)
#elif defined(_WIN64) && defined(_MSC_VER)
  fprintf(stderr,_("Windows 64 bit version (MSVC %d).\n"),_MSC_VER);
#elif defined(_WIN32) && defined(_MSC_VER)
  fprintf(stderr,_("Windows 32 bit version (MSVC %d).\n"),_MSC_VER);
#elif defined (__OS2__) && defined(__WATCOMC__) /* OS/2 Warp */
  fprintf(stderr, "%s", _("OS/2 version (WATCOMC).\n"));
#elif defined (__OS2__) && defined(__EMX__) /* OS/2 Warp */
  fprintf(stderr, "%s", _("OS/2 version (EMX).\n"));
#if defined(__TURBOC__) || defined(__MSYS__) || defined(_MSC_VER)





#if defined(_WIN32) || defined(__CYGWIN__)
#else
       * pairs in UTF-16).
       *
       * Some smart viewers can still display this UTF-8 correctly (like Total
       * Commander lister), however the UTF-8 is not readable by Windows
       * Notepad (on Windows 7).  When we decode the UTF-16 surrogate pairs
       * ourselves the wcstombs() UTF-8 output is identical to what
       * WideCharToMultiByte() produces, and is readable by Notepad.
       *
       * Surrogate halves in UTF-8 are invalid. See also
       * http://en.wikipedia.org/wiki/UTF-8#Invalid_code_points
       * http://tools.ietf.org/html/rfc3629#page-5
       * It is a bug in (some implemenatations of) wcstombs().
       * On Cygwin 1.7 wcstombs() produces correct UTF-8 from UTF-16 surrogate pairs.
       */
      /* fprintf(stderr, "UTF-32  %x\n",wstr[0]); */
#if defined(_WIN32) || defined(__CYGWIN__)
   /* fprintf(stderr, "len  %d\n",len); */