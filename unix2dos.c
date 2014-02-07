 *  The dos2unix package is distributed under FreeBSD style license.
 *  See also http://www.freebsd.org/copyright/freebsd-license.html
 *  --------
 * 
 *  Copyright (C) 2009-2012 Erwin Waterlander
 *  Copyright (C) 1994-1995 Benjamin Lin.
/* #define DEBUG 1 */
#include "common.h"
#include "querycp.h"
#ifdef D2U_UNICODE
#ifndef MSDOS  /* Unix, Cygwin */
# include <langinfo.h>
  fprintf(stderr, "%s", _("\
Copyright (C) 2009-2012 Erwin Waterlander\n\
Copyright (C) 1994-1995 Benjamin Lin\n\
All rights reserved.\n\n"));
  PrintBSDLicense();
#ifdef D2U_UNICODE
void AddDOSNewLineW(FILE* ipOutF, CFlag *ipFlag, wint_t CurChar, wint_t PrevChar)
  if (ipFlag->NewLine) {  /* add additional CR-LF? */
    /* Don't add line ending if it is a DOS line ending. Only in case of Unix line ending. */
    if ((CurChar == 0x0a) && (PrevChar != 0x0d)) {
      d2u_putwc(0x0d, ipOutF, ipFlag);
      d2u_putwc(0x0a, ipOutF, ipFlag);
    }
  }
void AddDOSNewLine(FILE* ipOutF, CFlag *ipFlag, int CurChar, int PrevChar)
      fputc('\x0d', ipOutF);
      fputc('\x0a', ipOutF);
#ifdef D2U_UNICODE
int ConvertUnixToDosW(FILE* ipInF, FILE* ipOutF, CFlag *ipFlag, char *progname)
    wint_t TempChar;
    wint_t PreviousChar = 0;
    switch (ipFlag->FromToMode)
      case FROMTO_UNIX2DOS: /* unix2dos */
        while ((TempChar = d2u_getwc(ipInF, ipFlag->bomtype)) != WEOF) {  /* get character */
              (TempChar != 0x0a) &&  /* Not an LF */
              (TempChar != 0x0d) &&  /* Not a CR */
              (TempChar != 0x09) &&  /* Not a TAB */
              (TempChar != 0x0c)) {  /* Not a form feed */
          if (TempChar == 0x0a)
          {
            d2u_putwc(0x0d, ipOutF, ipFlag); /* got LF, put CR */
          } else {
             if (TempChar == 0x0d) /* got CR */
             {
               if ((TempChar = d2u_getwc(ipInF, ipFlag->bomtype)) == WEOF) /* get next char */
                 TempChar = 0x0d;  /* Read error, or end of file. */
               else
               {
                 d2u_putwc(0x0d, ipOutF, ipFlag); /* put CR */
                 PreviousChar = 0x0d;
               }
             }
          }
          if (d2u_putwc(TempChar, ipOutF, ipFlag) == WEOF)
              {
                if (!(ipFlag->status & UNICODE_CONVERSION_ERROR))
                {
                  fprintf(stderr, "%s: ", progname);
                  fprintf(stderr, "%s", _("can not write to output file\n"));
                }
              }
            AddDOSNewLineW( ipOutF, ipFlag, TempChar, PreviousChar);
      case FROMTO_UNIX2MAC: /* unix2mac */
        while ((TempChar = d2u_getwc(ipInF, ipFlag->bomtype)) != WEOF) {
              (TempChar != 0x0a) &&  /* Not an LF */
              (TempChar != 0x0d) &&  /* Not a CR */
              (TempChar != 0x09) &&  /* Not a TAB */
              (TempChar != 0x0c)) {  /* Not a form feed */
          if ((TempChar != 0x0a)) /* Not an LF */
            {
              if(d2u_putwc(TempChar, ipOutF, ipFlag) == WEOF){
                RetVal = -1;
                if (!ipFlag->Quiet)
                {
                  if (!(ipFlag->status & UNICODE_CONVERSION_ERROR))
                  {
                    fprintf(stderr, "%s: ", progname);
                    fprintf(stderr, "%s", _("can not write to output file\n"));
                  }
                }
                break;
              }
              PreviousChar = TempChar;
            }
          else{
            /* TempChar is an LF */
            /* Don't touch this delimiter if it's a CR,LF pair. */
            if ( PreviousChar == 0x0d ) {
              if (d2u_putwc(0x0a, ipOutF, ipFlag) == WEOF)  /* CR,LF pair. Put LF */
                {
                  RetVal = -1;
                  if (!ipFlag->Quiet)
                  {
                    if (!(ipFlag->status & UNICODE_CONVERSION_ERROR))
                    {
                      fprintf(stderr, "%s: ", progname);
                      fprintf(stderr, "%s", _("can not write to output file\n"));
                    }
                  }
                  break;
                }
              PreviousChar = TempChar;
              continue;
            }
            PreviousChar = TempChar;
            if (d2u_putwc(0x0d, ipOutF, ipFlag) == WEOF) /* Unix line end (LF). Put CR */
              {
                RetVal = -1;
                if (!ipFlag->Quiet)
                {
                  if (!(ipFlag->status & UNICODE_CONVERSION_ERROR))
                  {
                    fprintf(stderr, "%s: ", progname);
                    fprintf(stderr, "%s", _("can not write to output file\n"));
                  }
                }
                break;
              }
            if (ipFlag->NewLine) {  /* add additional CR? */
              d2u_putwc(0x0d, ipOutF, ipFlag);
            }
      default: /* unknown FromToMode */
      ;
#if DEBUG
      fprintf(stderr, "%s: ", progname);
      fprintf(stderr, _("program error, invalid conversion mode %d\n"),ipFlag->FromToMode);
      exit(1);
#endif
    }
    return RetVal;
}
#endif

/* converts stream ipInF to DOS format text and write to stream ipOutF
 * RetVal: 0  if success
 *         -1  otherwise
 */
int ConvertUnixToDos(FILE* ipInF, FILE* ipOutF, CFlag *ipFlag, char *progname)
{
    int RetVal = 0;
    int TempChar;
    int PreviousChar = 0;
    int *ConvTable;

    ipFlag->status = 0;

    switch (ipFlag->ConvMode)
    {
      case CONVMODE_ASCII: /* ascii */
        ConvTable = U2DAsciiTable;
        break;
      case CONVMODE_7BIT: /* 7bit */
        ConvTable = U2D7BitTable;
        break;
      case CONVMODE_437: /* iso */
        ConvTable = U2DIso437Table;
        break;
      case CONVMODE_850: /* iso */
        ConvTable = U2DIso850Table;
        break;
      case CONVMODE_860: /* iso */
        ConvTable = U2DIso860Table;
        break;
      case CONVMODE_863: /* iso */
        ConvTable = U2DIso863Table;
        break;
      case CONVMODE_865: /* iso */
        ConvTable = U2DIso865Table;
        break;
      case CONVMODE_1252: /* iso */
        ConvTable = U2DIso1252Table;
        break;
      default: /* unknown convmode */
        ipFlag->status |= WRONG_CODEPAGE ;
        return(-1);
    }
    if ((ipFlag->ConvMode > 1) && (!ipFlag->Quiet)) /* not ascii or 7bit */
    {
       fprintf(stderr, "%s: ", progname);
       fprintf(stderr, _("using code page %d.\n"), ipFlag->ConvMode);
    }

    /* LF    -> CR-LF */
    /* CR-LF -> CR-LF, in case the input file is a DOS text file */
    /* \x0a = Newline/Line Feed (LF) */
    /* \x0d = Carriage Return (CR) */

    switch (ipFlag->FromToMode)
    {
      case FROMTO_UNIX2DOS: /* unix2dos */
        while ((TempChar = fgetc(ipInF)) != EOF) {  /* get character */
              (TempChar != '\x09') &&  /* Not a TAB */
              (TempChar != '\x0c')) {  /* Not a form feed */
          {
            fputc('\x0d', ipOutF); /* got LF, put CR */
          } else {
             {
               if ((TempChar = fgetc(ipInF)) == EOF) /* get next char */
               else
               {
                 fputc('\x0d', ipOutF); /* put CR */
               }
             }
          }
          if (fputc(ConvTable[TempChar], ipOutF) == EOF)
              {
                fprintf(stderr, "%s: ", progname);
                fprintf(stderr, "%s", _("can not write to output file\n"));
              }
            AddDOSNewLine( ipOutF, ipFlag, TempChar, PreviousChar);
      case FROMTO_UNIX2MAC: /* unix2mac */
        while ((TempChar = fgetc(ipInF)) != EOF) {
              (TempChar != '\x09') &&  /* Not a TAB */
              (TempChar != '\x0c')) {  /* Not a form feed */
              if(fputc(ConvTable[TempChar], ipOutF) == EOF){
                {
                  fprintf(stderr, "%s: ", progname);
                  fprintf(stderr, "%s", _("can not write to output file\n"));
                }
              if (fputc('\x0a', ipOutF) == EOF)  /* CR,LF pair. Put LF */
                  {
                    fprintf(stderr, "%s: ", progname);
                    fprintf(stderr, "%s", _("can not write to output file\n"));
                  }
            if (fputc('\x0d', ipOutF) == EOF) /* Unix line end (LF). Put CR */
                {
                  fprintf(stderr, "%s: ", progname);
                  fprintf(stderr, "%s", _("can not write to output file\n"));
                }
              fputc('\x0d', ipOutF);
      default: /* unknown FromToMode */
#if DEBUG
      fprintf(stderr, "%s: ", progname);
      fprintf(stderr, _("program error, invalid conversion mode %d\n"),ipFlag->FromToMode);
int ConvertUnixToDosNewFile(char *ipInFN, char *ipOutFN, CFlag *ipFlag, char *progname)
  char *errstr;
#ifndef NO_CHMOD
  char *TargetFN = NULL;
  int ResolveSymlinkResult = 0;

  ipFlag->status = 0 ;

  /* Test if output file is a symbolic link */
  if (symbolic_link(ipOutFN) && !ipFlag->Follow)
  {
    ipFlag->status |= OUTPUTFILE_SYMLINK ;
    /* Not a failure, skipping input file according spec. (keep symbolic link unchanged) */
    return -1;
  }
  /* Test if input file is a regular file or symbolic link */
  if (regfile(ipInFN, 1, ipFlag, progname))
    /* Not a failure, skipping non-regular input file according spec. */
    return -1;
  }

  /* Test if input file target is a regular file */
  if (symbolic_link(ipInFN) && regfile_target(ipInFN, ipFlag,progname))
  {
    ipFlag->status |= INPUT_TARGET_NO_REGFILE ;
    /* Not a failure, skipping non-regular input file according spec. */
    return -1;
  }

  /* Test if output file target is a regular file */
  if (symbolic_link(ipOutFN) && (ipFlag->Follow == SYMLINK_FOLLOW) && regfile_target(ipOutFN, ipFlag,progname))
  {
    ipFlag->status |= OUTPUT_TARGET_NO_REGFILE ;
    /* Failure, input is regular, cannot produce output. */
    if (!ipFlag->error) ipFlag->error = 1;
  {
    if (!ipFlag->Quiet)
    {
      ipFlag->error = errno;
      errstr = strerror(errno);
      fprintf(stderr, "%s: %s: %s\n", progname, ipInFN, errstr);
    }
  }
  
    if (!ipFlag->Quiet)
    {
      ipFlag->error = errno;
      errstr = strerror(errno);
      fprintf(stderr, "%s: ", progname);
      fprintf(stderr, _("Failed to open temporary output file: %s\n"), errstr);
    }
#if DEBUG
  fprintf(stderr, "%s: ", progname);
  fprintf(stderr, _("using %s as temporary file\n"), TempPath);
  if (!RetVal)
    InF=OpenInFile(ipInFN);
    if (InF == NULL)
    {
      ipFlag->error = errno;
      errstr = strerror(errno);
      fprintf(stderr, "%s: %s: %s\n", progname, ipInFN, errstr);
      RetVal = -1;
    }
  /* can open output file? */
  if ((!RetVal) && (InF))
  {
    if ((TempF=fd) == NULL)
    {
    if ((TempF=OpenOutFile(fd)) == NULL)
    {
      ipFlag->error = errno;
      errstr = strerror(errno);
      fprintf(stderr, "%s: %s\n", progname, errstr);
      fclose (InF);
      InF = NULL;
    }
  InF = read_bom(InF, &ipFlag->bomtype);
#ifdef D2U_UNICODE
#ifndef MSDOS  /* Unix, Cygwin */
  if ((ipFlag->bomtype == FILE_UTF16LE) || (ipFlag->bomtype == FILE_UTF16BE))
    if (strcmp(nl_langinfo(CODESET), "UTF-8") != 0)
      /* Don't convert UTF-16 files when the locale encoding is not UTF-8
       * to prevent loss of characters. */
      ipFlag->status |= LOCALE_NOT_UTF8 ;
      if (!ipFlag->error) ipFlag->error = 1;
#if !defined(WIN32) && !defined(__CYGWIN__) /* Not Windows or Cygwin */
  if ((ipFlag->bomtype == FILE_UTF16LE) || (ipFlag->bomtype == FILE_UTF16BE))
    if (sizeof(wchar_t) < 4)
    {
      /* A decoded UTF-16 surrogate pair must fit in a wchar_t */
      ipFlag->status |= WCHAR_T_TOO_SMALL ;
      if (!ipFlag->error) ipFlag->error = 1;
      RetVal = -1;
    }
  if ((ipFlag->add_bom) || (ipFlag->bomtype > 0))
    fprintf(TempF, "%s", "\xEF\xBB\xBF");  /* UTF-8 BOM */
  /* Turn off ISO and 7-bit conversion for Unicode text files */
  if (ipFlag->bomtype > 0)
    ipFlag->ConvMode = CONVMODE_ASCII;
  /* conversion sucessful? */
#ifdef D2U_UNICODE
  if ((ipFlag->bomtype == FILE_UTF16LE) || (ipFlag->bomtype == FILE_UTF16BE))
    if ((!RetVal) && (ConvertUnixToDosW(InF, TempF, ipFlag, progname)))
      RetVal = -1;
    if (ipFlag->status & UNICODE_CONVERSION_ERROR)
    {
      if (!ipFlag->error) ipFlag->error = 1;
      RetVal = -1;
    }
  } else {
    if ((!RetVal) && (ConvertUnixToDos(InF, TempF, ipFlag, progname)))
      RetVal = -1;
#else
  if ((!RetVal) && (ConvertUnixToDos(InF, TempF, ipFlag, progname)))
#endif
#ifndef NO_CHMOD
  if (!RetVal)
  {
    if (ipFlag->NewFile == 0) /* old file mode */
    {
       RetVal = chmod (TempPath, StatBuf.st_mode); /* set original permissions */
    } 
    else
    {
       mask = umask(0); /* get process's umask */
       umask(mask); /* set umask back to original */
       RetVal = chmod(TempPath, StatBuf.st_mode & ~mask); /* set original permissions, minus umask */
    }
    
    if (RetVal)
    {
       if (!ipFlag->Quiet)
       {
         ipFlag->error = errno;
         errstr = strerror(errno);
         fprintf(stderr, "%s: ", progname);
         fprintf(stderr, _("Failed to change the permissions of temporary output file %s: %s\n"), TempPath, errstr);
       }
    }
  }
#endif

#ifndef NO_CHOWN
  if (!RetVal && (ipFlag->NewFile == 0))  /* old file mode */
  {
     /* Change owner and group of the the tempory output file to the original file's uid and gid. */
     /* Required when a different user (e.g. root) has write permission on the original file. */
     /* Make sure that the original owner can still access the file. */
     if (chown(TempPath, StatBuf.st_uid, StatBuf.st_gid))
     {
        if (!ipFlag->Quiet)
        {
          ipFlag->error = errno;
          errstr = strerror(errno);
          fprintf(stderr, "%s: ", progname);
          fprintf(stderr, _("Failed to change the owner and group of temporary output file %s: %s\n"), TempPath, errstr);
        }
        RetVal = -1;
     }
  }
#endif

    {
      if (!ipFlag->Quiet)
      {
        ipFlag->error = errno;
        errstr = strerror(errno);
        fprintf(stderr, "%s: %s: %s\n", progname, TempPath, errstr);
      }
    }
  /* any error? cleanup the temp file */
  if (RetVal && (TempPath != NULL))
  {
    if (unlink(TempPath) && (errno != ENOENT))
    {
      if (!ipFlag->Quiet)
      {
        ipFlag->error = errno;
        errstr = strerror(errno);
        fprintf(stderr, "%s: %s: %s\n", progname, TempPath, errstr);
      }
      RetVal = -1;
    }
  }
  /* If output file is a symbolic link, optional resolve the link and modify  */
  /* the target, instead of removing the link and creating a new regular file */
  TargetFN = ipOutFN;
  if (symbolic_link(ipOutFN) && !RetVal)
  {
    ResolveSymlinkResult = 0; /* indicates that TargetFN need not be freed */
    if (ipFlag->Follow == SYMLINK_FOLLOW)
    {
      ResolveSymlinkResult = ResolveSymbolicLink(ipOutFN, &TargetFN, ipFlag, progname);
      if (ResolveSymlinkResult < 0)
      {
        if (!ipFlag->Quiet)
        {
          fprintf(stderr, "%s: ", progname);
          fprintf(stderr, _("problems resolving symbolic link '%s'\n"), ipOutFN);
          fprintf(stderr, _("          output file remains in '%s'\n"), TempPath);
        }
        RetVal = -1;
      }
    }
  }

  /* can rename temporary file to output file? */
#ifdef NEED_REMOVE
    if (unlink(TargetFN) && (errno != ENOENT))
      if (!ipFlag->Quiet)
      {
        ipFlag->error = errno;
        errstr = strerror(errno);
        fprintf(stderr, "%s: %s: %s\n", progname, TargetFN, errstr);
      }
      RetVal = -1;
#endif
    if (rename(TempPath, TargetFN) == -1)
    {
      if (!ipFlag->Quiet)
      {
        ipFlag->error = errno;
        errstr = strerror(errno);
        fprintf(stderr, "%s: ", progname);
        fprintf(stderr, _("problems renaming '%s' to '%s': %s\n"), TempPath, TargetFN, errstr);
#ifdef S_ISLNK
        if (ResolveSymlinkResult > 0)
          fprintf(stderr, _("          which is the target of symbolic link '%s'\n"), ipOutFN);
#endif
        fprintf(stderr, _("          output file remains in '%s'\n"), TempPath);
      }
      RetVal = -1;
    }

    if (ResolveSymlinkResult > 0)
      free(TargetFN);
int ConvertUnixToDosStdio(CFlag *ipFlag, char *progname)
#if defined(WIN32) && !defined(__CYGWIN__)
#elif defined(MSDOS) || defined(__CYGWIN__) || defined(__OS2__)
#endif

    read_bom(stdin, &ipFlag->bomtype);

    if ((ipFlag->add_bom) || (ipFlag->bomtype > 0))
       fprintf(stdout, "%s", "\xEF\xBB\xBF");  /* UTF-8 BOM */

#ifdef D2U_UNICODE
    if ((ipFlag->bomtype == FILE_UTF16LE) || (ipFlag->bomtype == FILE_UTF16BE))
    {
       return (ConvertUnixToDosW(stdin, stdout, ipFlag, progname));
    } else {
       return (ConvertUnixToDos(stdin, stdout, ipFlag, progname));
    }
    return (ConvertUnixToDos(stdin, stdout, ipFlag, progname));
  char progname[9];
  int process_options = 1;
#endif
# ifdef __MINGW64__
  int _dowildcard = -1; /* enable wildcard expansion for Win64 */
# endif
  progname[8] = '\0';
  strcpy(progname,"unix2dos");

#ifdef ENABLE_NLS
         fprintf(stderr,"%s: ",progname);
         fprintf(stderr, "%s", _("error: Value of environment variable DOS2UNIX_LOCALEDIR is too long.\n"));
  pFlag->ConvMode = CONVMODE_ASCII;  /* default ascii */
  pFlag->FromToMode = FROMTO_UNIX2DOS;  /* default unix2dos */
  pFlag->Follow = SYMLINK_SKIP;
  pFlag->stdio_mode = 1;
  pFlag->error = 0;
#ifdef D2U_UNICODE
  pFlag->bomtype = FILE_MBS;
#endif
  pFlag->add_bom = 0;
    pFlag->FromToMode = FROMTO_UNIX2MAC;
    strcpy(progname,"unix2mac");
    if ((argv[ArgIdx][0] == '-') && process_options)
      if (strcmp(argv[ArgIdx],"--") == 0)
        process_options = 0;
      else if ((strcmp(argv[ArgIdx],"-h") == 0) || (strcmp(argv[ArgIdx],"--help") == 0))
      {
        PrintUsage(progname);
        return(pFlag->error);
      }
      else if ((strcmp(argv[ArgIdx],"-k") == 0) || (strcmp(argv[ArgIdx],"--keepdate") == 0))
      else if ((strcmp(argv[ArgIdx],"-f") == 0) || (strcmp(argv[ArgIdx],"--force") == 0))
      else if ((strcmp(argv[ArgIdx],"-s") == 0) || (strcmp(argv[ArgIdx],"--safe") == 0))
        pFlag->Force = 0;
      else if ((strcmp(argv[ArgIdx],"-q") == 0) || (strcmp(argv[ArgIdx],"--quiet") == 0))
      else if ((strcmp(argv[ArgIdx],"-l") == 0) || (strcmp(argv[ArgIdx],"--newline") == 0))
      else if ((strcmp(argv[ArgIdx],"-m") == 0) || (strcmp(argv[ArgIdx],"--add-bom") == 0))
        pFlag->add_bom = 1;
      else if ((strcmp(argv[ArgIdx],"-S") == 0) || (strcmp(argv[ArgIdx],"--skip-symlink") == 0))
        pFlag->Follow = SYMLINK_SKIP;
      else if ((strcmp(argv[ArgIdx],"-F") == 0) || (strcmp(argv[ArgIdx],"--follow-symlink") == 0))
        pFlag->Follow = SYMLINK_FOLLOW;
      else if ((strcmp(argv[ArgIdx],"-R") == 0) || (strcmp(argv[ArgIdx],"--replace-symlink") == 0))
        pFlag->Follow = SYMLINK_REPLACE;
      else if ((strcmp(argv[ArgIdx],"-V") == 0) || (strcmp(argv[ArgIdx],"--version") == 0))
        PrintVersion(progname);
        return(pFlag->error);
      else if ((strcmp(argv[ArgIdx],"-L") == 0) || (strcmp(argv[ArgIdx],"--license") == 0))
      {
        return(pFlag->error);
      }
      else if (strcmp(argv[ArgIdx],"-ascii") == 0)  /* SunOS compatible options */
        pFlag->ConvMode = CONVMODE_ASCII;
      else if (strcmp(argv[ArgIdx],"-7") == 0)
        pFlag->ConvMode = CONVMODE_7BIT;
      else if (strcmp(argv[ArgIdx],"-iso") == 0)
      {
        pFlag->ConvMode = (int)query_con_codepage();
        if (!pFlag->Quiet)
        {
           fprintf(stderr,"%s: ",progname);
           fprintf(stderr,_("active code page: %d\n"), pFlag->ConvMode);
        }
        if (pFlag->ConvMode < 2)
           pFlag->ConvMode = CONVMODE_437;
      }
      else if (strcmp(argv[ArgIdx],"-437") == 0)
        pFlag->ConvMode = CONVMODE_437;
      else if (strcmp(argv[ArgIdx],"-850") == 0)
        pFlag->ConvMode = CONVMODE_850;
      else if (strcmp(argv[ArgIdx],"-860") == 0)
        pFlag->ConvMode = CONVMODE_860;
      else if (strcmp(argv[ArgIdx],"-863") == 0)
        pFlag->ConvMode = CONVMODE_863;
      else if (strcmp(argv[ArgIdx],"-865") == 0)
        pFlag->ConvMode = CONVMODE_865;
      else if (strcmp(argv[ArgIdx],"-1252") == 0)
        pFlag->ConvMode = CONVMODE_1252;
      else if ((strcmp(argv[ArgIdx],"-c") == 0) || (strcmp(argv[ArgIdx],"--convmode") == 0))
          if (strcmpi(argv[ArgIdx],"ascii") == 0)  /* Benjamin Lin's legacy options */
            pFlag->ConvMode = CONVMODE_ASCII;
            pFlag->ConvMode = CONVMODE_7BIT;
          {
            pFlag->ConvMode = (int)query_con_codepage();
            if (!pFlag->Quiet)
            {
               fprintf(stderr,"%s: ",progname);
               fprintf(stderr,_("active code page: %d\n"), pFlag->ConvMode);
            }
            if (pFlag->ConvMode < 2)
               pFlag->ConvMode = CONVMODE_437;
          }
            pFlag->FromToMode = FROMTO_UNIX2MAC;
            fprintf(stderr,"%s: ",progname);
            fprintf(stderr, _("invalid %s conversion mode specified\n"),argv[ArgIdx]);
            pFlag->error = 1;
            pFlag->stdio_mode = 0;
          fprintf(stderr,"%s: ",progname);
          fprintf(stderr,_("option '%s' requires an argument\n"),argv[ArgIdx]);
          pFlag->error = 1;
          pFlag->stdio_mode = 0;
      else if ((strcmp(argv[ArgIdx],"-o") == 0) || (strcmp(argv[ArgIdx],"--oldfile") == 0))
          fprintf(stderr,"%s: ",progname);
          fprintf(stderr, _("target of file %s not specified in new file mode\n"), argv[ArgIdx-1]);
          pFlag->error = 1;
          pFlag->stdio_mode = 0;
      else if ((strcmp(argv[ArgIdx],"-n") == 0) || (strcmp(argv[ArgIdx],"--newfile") == 0))
          fprintf(stderr,"%s: ",progname);
          fprintf(stderr, _("target of file %s not specified in new file mode\n"), argv[ArgIdx-1]);
          pFlag->error = 1;
          pFlag->stdio_mode = 0;
      else { /* wrong option */
        PrintUsage(progname);
        ShouldExit = 1;
        pFlag->error = 1;
        pFlag->stdio_mode = 0;
      }
      pFlag->stdio_mode = 0;
          RetVal = ConvertUnixToDosNewFile(argv[ArgIdx-1], argv[ArgIdx], pFlag, progname);
            {
              fprintf(stderr,"%s: ",progname);
              fprintf(stderr, _("Skipping %s, not a regular file.\n"), argv[ArgIdx-1]);
            }
          } else if (pFlag->status & OUTPUTFILE_SYMLINK)
          {
            if (!pFlag->Quiet)
            {
              fprintf(stderr,"%s: ",progname);
              fprintf(stderr, _("Skipping %s, output file %s is a symbolic link.\n"), argv[ArgIdx-1], argv[ArgIdx]);
            }
          } else if (pFlag->status & INPUT_TARGET_NO_REGFILE)
          {
            if (!pFlag->Quiet)
            {
              fprintf(stderr,"%s: ",progname);
              fprintf(stderr, _("Skipping symbolic link %s, target is not a regular file.\n"), argv[ArgIdx-1]);
            }
          } else if (pFlag->status & OUTPUT_TARGET_NO_REGFILE)
          {
            if (!pFlag->Quiet)
            {
              fprintf(stderr,"%s: ",progname);
              fprintf(stderr, _("Skipping %s, target of symbolic link %s is not a regular file.\n"), argv[ArgIdx-1], argv[ArgIdx]);
            }
            {
              fprintf(stderr,"%s: ",progname);
              fprintf(stderr, _("Skipping binary file %s\n"), argv[ArgIdx-1]);
            }
          } else if (pFlag->status & WRONG_CODEPAGE)
          {
            if (!pFlag->Quiet)
            {
              fprintf(stderr,"%s: ",progname);
              fprintf(stderr, _("code page %d is not supported.\n"), pFlag->ConvMode);
            }
          } else if (pFlag->status & LOCALE_NOT_UTF8)
          {
            if (!pFlag->Quiet)
            {
              fprintf(stderr,"%s: ",progname);
              fprintf(stderr, _("Skipping UTF-16 file %s, the current locale character encoding is not UTF-8.\n"), argv[ArgIdx-1]);
            }
          } else if (pFlag->status & WCHAR_T_TOO_SMALL)
          {
            if (!pFlag->Quiet)
            {
              fprintf(stderr,"%s: ",progname);
              fprintf(stderr, _("Skipping UTF-16 file %s, the size of wchar_t is %d bytes.\n"), argv[ArgIdx-1], (int)sizeof(wchar_t));
            }
          } else if (pFlag->status & UNICODE_CONVERSION_ERROR)
          {
            if (!pFlag->Quiet)
            {
              fprintf(stderr,"%s: ",progname);
              fprintf(stderr, _("Skipping UTF-16 file %s, an UTF-16 conversion error occurred.\n"), argv[ArgIdx-1]);
            }
              fprintf(stderr,"%s: ",progname);
              if (pFlag->FromToMode == FROMTO_UNIX2MAC)
                fprintf(stderr, _("converting file %s to file %s in Mac format ...\n"), argv[ArgIdx-1], argv[ArgIdx]);
                fprintf(stderr, _("converting file %s to file %s in DOS format ...\n"), argv[ArgIdx-1], argv[ArgIdx]);
              {
                fprintf(stderr,"%s: ",progname);
                fprintf(stderr, _("problems converting file %s to file %s\n"), argv[ArgIdx-1], argv[ArgIdx]);
              }
        RetVal = ConvertUnixToDosNewFile(argv[ArgIdx], argv[ArgIdx], pFlag, progname);
          {
            fprintf(stderr,"%s: ",progname);
            fprintf(stderr, _("Skipping %s, not a regular file.\n"), argv[ArgIdx]);
          }
        } else if (pFlag->status & OUTPUTFILE_SYMLINK)
        {
          if (!pFlag->Quiet)
          {
            fprintf(stderr,"%s: ",progname);
            fprintf(stderr, _("Skipping symbolic link %s.\n"), argv[ArgIdx]);
          }
        } else if (pFlag->status & INPUT_TARGET_NO_REGFILE)
        {
          if (!pFlag->Quiet)
          {
            fprintf(stderr,"%s: ",progname);
            fprintf(stderr, _("Skipping symbolic link %s, target is not a regular file.\n"), argv[ArgIdx]);
          }
          {
            fprintf(stderr,"%s: ",progname);
            fprintf(stderr, _("Skipping binary file %s\n"), argv[ArgIdx]);
          }
        } else if (pFlag->status & WRONG_CODEPAGE)
        {
          if (!pFlag->Quiet)
          {
            fprintf(stderr,"%s: ",progname);
            fprintf(stderr, _("code page %d is not supported.\n"), pFlag->ConvMode);
          }
        } else if (pFlag->status & LOCALE_NOT_UTF8)
        {
          if (!pFlag->Quiet)
          {
            fprintf(stderr,"%s: ",progname);
            fprintf(stderr, _("Skipping UTF-16 file %s, the current locale character encoding is not UTF-8.\n"), argv[ArgIdx]);
          }
        } else if (pFlag->status & WCHAR_T_TOO_SMALL)
        {
          if (!pFlag->Quiet)
          {
            fprintf(stderr,"%s: ",progname);
            fprintf(stderr, _("Skipping UTF-16 file %s, the size of wchar_t is %d bytes.\n"), argv[ArgIdx], (int)sizeof(wchar_t));
          }
        } else if (pFlag->status & UNICODE_CONVERSION_ERROR)
        {
          if (!pFlag->Quiet)
          {
            fprintf(stderr,"%s: ",progname);
            fprintf(stderr, _("Skipping UTF-16 file %s, an UTF-16 conversion error occurred.\n"), argv[ArgIdx]);
          }
            fprintf(stderr,"%s: ",progname);
            if (pFlag->FromToMode == FROMTO_UNIX2MAC)
              fprintf(stderr, _("converting file %s to Mac format ...\n"), argv[ArgIdx]);
              fprintf(stderr, _("converting file %s to DOS format ...\n"), argv[ArgIdx]);
            {
              fprintf(stderr,"%s: ",progname);
              fprintf(stderr, _("problems converting file %s\n"), argv[ArgIdx]);
            }
  /* no file argument, use stdin and stdout */
  if (pFlag->stdio_mode)
  {
    exit(ConvertUnixToDosStdio(pFlag, progname));
  }


  if (!CanSwitchFileMode)
    fprintf(stderr,"%s: ",progname);
    fprintf(stderr, _("target of file %s not specified in new file mode\n"), argv[ArgIdx-1]);
    pFlag->error = 1;
  return (pFlag->error);