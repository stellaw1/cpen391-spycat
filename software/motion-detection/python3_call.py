import subprocess

python3_command = "motion_detection_modified.py"  # launch your python2 script using bash

process = subprocess.Popen(python3_command.split(), stdout=subprocess.PIPE)
output, error = process.communicate()  # receive output from the python2 script

print("finished calling py2 script")
print(output)