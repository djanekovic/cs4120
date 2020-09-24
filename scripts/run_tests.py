import sys, os
import json
import subprocess

xic_binary = "./build/xic"

class TestRunner:
    def run(self):
        testcases = {}
        for f in os.listdir(self.test_dir):
            # get name of test without .xi extension
            input_file = self.test_dir + f;
            solution = input_file.replace(".xi", self.solution_extension)

            if f.endswith('xi'):
                # compare output. Command will return 0 if files are identical
                command = [xic_binary, self.test_flags, input_file, "|", "cmp", solution, "-"]
                res = subprocess.run(command, shell=True)

                testcases.update({f: not bool(res.returncode)})

        print ("Test output:")
        print(json.dumps(testcases, indent=2))

        for (key, value) in testcases.items():
            if value == False:
                sys.exit(1)

class LexerTest(TestRunner):
    def __init__(self):
        self.test_dir = "tests/pa1/"
        self.solution_extension = ".lexedsol"
        self.test_flags = "--lex"

if __name__ == "__main__":
    for test in [LexerTest]:
        test().run()
