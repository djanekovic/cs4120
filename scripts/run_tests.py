import sys, os
import json
import subprocess

def call_command(args):
    res = subprocess.run(args)
    print ("[SH] {} returned {}".format(" ".join(args), res.returncode))

def mkdir(folder):
    try:
        os.mkdir(folder)
    except FileExistsError as e:
        pass

basedir = os.getcwd()
assert os.path.exists('CMakeLists.txt'), ("CMakeLists.txt is not found in " +
        basedir + " folder. Please run script from project root " +
        "folder.")

mkdir('build')
os.chdir('build')
build_dir = os.getcwd()

call_command(['cmake', '..'])
call_command(['make'])

xic_binary = build_dir + "/xic"

os.chdir('../tests/pa1')
mkdir('output')

testcases = {}
for f in os.listdir('.'):
    # get name of test without .xi extension
    basename = os.path.splitext(f)[0]

    if f.endswith('xi'):
        # out_filename: output/name.xiout
        out_filename = 'output/' + f + 'out'

        # open file and save the compiler output there
        with open(out_filename, 'w') as out:
            subprocess.run([xic_binary, '--lex', f], stdout=out)

        # compare output. Command will return 0 if files are identical
        res = subprocess.run(['cmp', out_filename, basename + '.lexedsol'])
        testcases.update({basename: not bool(res.returncode)})

print ("Test output:")
print(json.dumps(testcases, indent=2))

for i, (key, value) in enumerate(testcases.items()):
    if value == False:
        sys.exit(1)
