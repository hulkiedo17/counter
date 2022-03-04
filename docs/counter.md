# counter options
usage: counter [options]

options:
- (--path) -p [path-name] - specifying another directory for counting lines in files
- (--help) -h - prints this help message
- (--conf) -c - include to count config files
- (--no-recursion) -R - do not use files in nested(recursive) directories
- (--cur-path)	 -P - just show the current path
- (--detail)	 -d - show exactly which files are in use and the path to them
- (--version)	 -v - shows the program version
- (--no-spaces)	 -n - dont count the empty lines
- (--comments)	 -C - count only comment lines in files
- (--without-zero) -w - only show file count that bigger than 0
- (--output)	 -o [ps | pl | pf | d] - sets the output format, main arguments:
	
	ps (pipe_short) - short output (only final count)
	
	pl (pipe_long) - long output (without final count)
	
	pf (pipe_full) - full output (without spaces)
	
	ds (default) - default output
