from shutil import copyfile
import subprocess
import time

source_input = "input/input{}.txt"
source_output = "output/output{}.txt"
for num in range(20):
	copyfile(source_input.format(num), "./input.txt")
	subprocess.call("./cicli")
	with open("output.txt", "r") as gen_out:
		gen = gen_out.read()
	with open(source_output.format(num), "r") as sol_out:
		sol = sol_out.read()
		
	print(("%2d") % num,  "BRAVO" if gen==sol else "FA CAGARE") 
