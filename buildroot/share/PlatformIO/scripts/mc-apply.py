#!/usr/bin/env python
#
<<<<<<< HEAD
# Create a Configuration from marlin_config.json
#
import json
import sys
import shutil
import re

opt_output = '--opt' in sys.argv
output_suffix = '.sh' if opt_output else '' if '--bare-output' in sys.argv else '.gen'

try:
	with open('marlin_config.json', 'r') as infile:
		conf = json.load(infile)
		for key in conf:
			# We don't care about the hash when restoring here
			if key == '__INITIAL_HASH':
				continue
			if key == 'VERSION':
				for k, v in sorted(conf[key].items()):
					print(k + ': ' + v)
				continue
			# The key is the file name, so let's build it now
			outfile = open('Marlin/' + key + output_suffix, 'w')
			for k, v in sorted(conf[key].items()):
				# Make define line now
				if opt_output:
					if v != '':
						if '"' in v:
							v = "'%s'" % v
						elif ' ' in v:
							v = '"%s"' % v
						define = 'opt_set ' + k + ' ' + v + '\n'
					else:
						define = 'opt_enable ' + k + '\n'
				else:
					define = '#define ' + k + ' ' + v + '\n'
				outfile.write(define)
			outfile.close()

			# Try to apply changes to the actual configuration file (in order to keep useful comments)
			if output_suffix != '':
				# Move the existing configuration so it doesn't interfere
				shutil.move('Marlin/' + key, 'Marlin/' + key + '.orig')
				infile_lines = open('Marlin/' + key + '.orig', 'r').read().split('\n')
				outfile = open('Marlin/' + key, 'w')
				for line in infile_lines:
					sline = line.strip(" \t\n\r")
					if sline[:7] == "#define":
						# Extract the key here (we don't care about the value)
						kv = sline[8:].strip().split(' ')
						if kv[0] in conf[key]:
							outfile.write('#define ' + kv[0] + ' ' + conf[key][kv[0]] + '\n')
							# Remove the key from the dict, so we can still write all missing keys at the end of the file
							del conf[key][kv[0]]
						else:
							outfile.write(line + '\n')
					else:
						outfile.write(line + '\n')
				# Process any remaining defines here
				for k, v in sorted(conf[key].items()):
					define = '#define ' + k + ' ' + v + '\n'
					outfile.write(define)
				outfile.close()

			print('Output configuration written to: ' + 'Marlin/' + key + output_suffix)
except:
	print('No marlin_config.json found.')
=======
# mc-apply.py
#
#  Apply firmware configuration from a JSON file (marlin_config.json).
#
#  usage: mc-apply.py [-h] [--opt] [config_file]
#
#  Process Marlin firmware configuration.
#
#  positional arguments:
#    config_file  Path to the configuration file.
#
#  optional arguments:
#    -h, --help   show this help message and exit
#    --opt        Output as an option setting script.
#
import json, sys, os
import config
import argparse

def report_version(conf):
    if 'VERSION' in conf:
        for k, v in sorted(conf['VERSION'].items()):
            print(k + ': ' + v)

def write_opt_file(conf, outpath='Marlin/apply_config.sh'):
    with open(outpath, 'w') as outfile:
        for key, val in conf.items():
            if key in ('__INITIAL_HASH', 'VERSION'): continue

            # Other keys are assumed to be configs
            if not type(val) is dict:
                continue

            # Write config commands to the script file
            lines = []
            for k, v in sorted(val.items()):
                if v != '':
                    v.replace('"', '\\"').replace("'", "\\'").replace(' ', '\\ ')
                    lines += [f'opt_set {k} {v}']
                else:
                    lines += [f'opt_enable {k}']

            outfile.write('\n'.join(lines))

        print('Config script written to: ' + outpath)

def back_up_config(name):
    # Back up the existing file before modifying it
    conf_path = 'Marlin/' + name
    with open(conf_path, 'r') as f:
        # Write a filename.bak#.ext retaining the original extension
        parts = conf_path.split('.')
        nr = ''
        while True:
            bak_path = '.'.join(parts[:-1]) + f'.bak{nr}.' + parts[-1]
            if os.path.exists(bak_path):
                nr = 1 if nr == '' else nr + 1
                continue

            with open(bak_path, 'w') as b:
                b.writelines(f.readlines())
                break

def apply_config(conf):
    for key in conf:
        if key in ('__INITIAL_HASH', 'VERSION'): continue

        back_up_config(key)

        for k, v in conf[key].items():
            if v:
                config.set('Marlin/' + key, k, v)
            else:
                config.enable('Marlin/' + key, k)

def main():
    parser = argparse.ArgumentParser(description='Process Marlin firmware configuration.')
    parser.add_argument('--opt', action='store_true', help='Output as an option setting script.')
    parser.add_argument('config_file', nargs='?', default='marlin_config.json', help='Path to the configuration file.')

    args = parser.parse_args()

    try:
        infile = open(args.config_file, 'r')
    except:
        print(f'No {args.config_file} found.')
        sys.exit(1)

    conf = json.load(infile)
    report_version(conf)

    if args.opt:
        write_opt_file(conf)
    else:
        apply_config(conf)

if __name__ == '__main__':
    main()
>>>>>>> origin/release-2.1.3-beta2
