import subprocess
from subprocess import STDOUT, check_output


script = ["python2.7", "~/l2b*/so*/mo*/motion_detection.py"]    
process = subprocess.Popen(" ".join(script), shell=True, stdout=subprocess.PIPE)

output, error = process.communicate()  # receive output from the python2 script

# script will not execute here unless python2 script exits

# TODO: add ret
