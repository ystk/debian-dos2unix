 *
 *  Copyright (C) 2009-2013 Erwin Waterlander
 * Wed Feb  4 19:12:58 EST 1998
 * Thu Nov 19 1998
 *
#if !defined(__MSDOS__) && !defined(_WIN32) && !defined(__OS2__)  /* Unix, Cygwin */
Copyright (C) 2009-2013 Erwin Waterlander\n\
    int line_nr = 1;
    char *errstr;
            if (!ipFlag->Quiet)
            {
              fprintf(stderr, "%s: ", progname);
              fprintf(stderr, _("Binary symbol 0x00%02X found at line %d\n"),TempChar, line_nr);
            }
            if (TempChar == 0x0a) /* Count all DOS and Unix line breaks */
              ++line_nr;
                  errstr = strerror(errno);
                  fprintf(stderr, _("can not write to output file: %s\n"), errstr);
            }
            if (!ipFlag->Quiet)
            {
              fprintf(stderr, "%s: ", progname);
              fprintf(stderr, _("Binary symbol 0x00%02X found at line %d\n"),TempChar, line_nr);
            }
              if (TempChar == 0x0a) /* Count all DOS and Unix line breaks */
                ++line_nr;
                    errstr = strerror(errno);
                    fprintf(stderr, _("can not write to output file: %s\n"), errstr);
                    errstr = strerror(errno);
                    fprintf(stderr, _("can not write to output file: %s\n"), errstr);
            line_nr++; /* Count all Mac line breaks */
    int line_nr = 1;
    char *errstr;
      case CONVMODE_UTF16LE: /* Assume UTF-16LE */
      case CONVMODE_UTF16BE: /* Assume UTF-16BE */
            if (!ipFlag->Quiet)
            {
              fprintf(stderr, "%s: ", progname);
              fprintf(stderr, _("Binary symbol 0x%02X found at line %d\n"),TempChar, line_nr);
            }
            if (TempChar == '\x0a') /* Count all DOS and Unix line breaks */
              ++line_nr;
                errstr = strerror(errno);
                fprintf(stderr, _("can not write to output file: %s\n"), errstr);
            }
            if (!ipFlag->Quiet)
            {
              fprintf(stderr, "%s: ", progname);
              fprintf(stderr, _("Binary symbol 0x%02X found at line %d\n"),TempChar, line_nr);
            }
              if (TempChar == '\x0a') /* Count all DOS and Unix line breaks */
                ++line_nr;
                  errstr = strerror(errno);
                  fprintf(stderr, _("can not write to output file: %s\n"), errstr);
                  errstr = strerror(errno);
                  fprintf(stderr, _("can not write to output file: %s\n"), errstr);
            line_nr++; /* Count all Mac line breaks */

#ifdef D2U_UNICODE
  if ((ipFlag->bomtype == FILE_MBS) && (ipFlag->ConvMode == CONVMODE_UTF16LE))
    ipFlag->bomtype = FILE_UTF16LE;
  if ((ipFlag->bomtype == FILE_MBS) && (ipFlag->ConvMode == CONVMODE_UTF16BE))
    ipFlag->bomtype = FILE_UTF16BE;
#endif
#if !defined(__MSDOS__) && !defined(_WIN32) && !defined(__OS2__)  /* Unix, Cygwin */
#if !defined(_WIN32) && !defined(__CYGWIN__) /* Not Windows or Cygwin */
  /* When we assume UTF16, don't change the conversion mode. We need to remember it. */
  if ((ipFlag->bomtype > 0) && (ipFlag->ConvMode != CONVMODE_UTF16LE) && (ipFlag->ConvMode != CONVMODE_UTF16BE))
  if (TempF)
  {
    if (fclose(TempF) == EOF)
    {
       if (!ipFlag->Quiet)
       {
         ipFlag->error = errno;
         errstr = strerror(errno);
         fprintf(stderr, "%s: ", progname);
         fprintf(stderr, _("Failed to write to temporary output file %s: %s\n"), TempPath, errstr);
       }
      RetVal = -1;
    }
  }
    }

#if defined(_WIN32) && !defined(__CYGWIN__)
    /* POSIX 'setmode' was deprecated by MicroSoft since
     * Visual C++ 2005. Use ISO C++ conformant '_setmode' instead. */
    _setmode(_fileno(stdout), _O_BINARY);
    _setmode(_fileno(stdin), _O_BINARY);
#elif defined(__MSDOS__) || defined(__CYGWIN__) || defined(__OS2__)
#ifdef D2U_UNICODE
    if ((ipFlag->bomtype == FILE_MBS) && (ipFlag->ConvMode == CONVMODE_UTF16LE))
      ipFlag->bomtype = FILE_UTF16LE;
    if ((ipFlag->bomtype == FILE_MBS) && (ipFlag->ConvMode == CONVMODE_UTF16BE))
      ipFlag->bomtype = FILE_UTF16BE;
#endif
#endif
#if defined(ENABLE_NLS) || (defined(D2U_UNICODE) && !defined(__MSDOS__) && !defined(_WIN32) && !defined(__OS2__))
/* setlocale() is also needed for nl_langinfo() */
#endif

#ifdef ENABLE_NLS
  pFlag = (CFlag*)malloc(sizeof(CFlag));
#ifdef D2U_UNICODE
      else if ((strcmp(argv[ArgIdx],"-ul") == 0) || (strcmp(argv[ArgIdx],"--assume-utf16le") == 0))
        pFlag->ConvMode = CONVMODE_UTF16LE;
      else if ((strcmp(argv[ArgIdx],"-ub") == 0) || (strcmp(argv[ArgIdx],"--assume-utf16be") == 0))
        pFlag->ConvMode = CONVMODE_UTF16BE;
#endif