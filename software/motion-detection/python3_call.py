import subprocess

script = ["python2.7", "motion_detection.py"]    
process = subprocess.Popen(" ".join(script),
                                        shell=True,  
                                        env={"PYTHONPATH": "."})
print("finished calling py2 script")
print(output)