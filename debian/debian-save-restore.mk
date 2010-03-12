#   debian-autotools.mk -- Common settings for Autotoolsx
#
#   Copyright
#
#       Copyright (C) 2008-2010 Jari Aalto <jari.aalto@cante.net>
#
#   License
#
#       This program is free software; you can redistribute it and/or modify
#       it under the terms of the GNU General Public License as published by
#       the Free Software Foundation; either version 2 of the License, or
#       (at your option) any later version.
#
#       This program is distributed in the hope that it will be useful,
#       but WITHOUT ANY WARRANTY; without even the implied warranty of
#       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#       GNU General Public License for more details.
#
#       You should have received a copy of the GNU General Public License
#       along with this program. If not, see <http://www.gnu.org/licenses/>.
#
#   Description
#
#       This is GNU makefile part, that defines common variables,
#       targets and macros to be used from debian/rules.
#
#   Usage (format 3.0)
#
#	FILE_LIST_PRESERVE = <file list of upstream files>
#
#	override_dh_clean:
#		$(file-state-save)
#		dh_clean
# 		$(file-state-restore)
#
#   Alternative usage, in case more file updates happens during configure etc.
#
#       override_dh_auto_configure:
#               $(file-state-save)
#               <configure call>
#
#       binary-arch:
#               $(file-state-restore)
#               ...

define file-state-save
	# save files
	suffix=.original; \
        for file in $(FILE_LIST_PRESERVE); \
        do \
	        backup=/tmp/$$(echo $$file | sed 's,/,%,g')$$suffix; \
                if [ -f "$$file" ] && [ ! -f "$$backup" ]; then \
		 	cp --verbose "$$file" "$$backup"; \
		fi; \
        done
endef

define file-state-restore
	# restore files
	suffix=.original; \
        for file in $(FILE_LIST_PRESERVE); \
        do \
	        backup=/tmp/$$(echo $$file | sed 's,/,%,g')$$suffix; \
                if [ -f "$$backup" ]; then \
			 mv --verbose "$$backup" "$$file"; \
		fi; \
        done
endef

# End of file
