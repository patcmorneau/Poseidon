import os, math

# Replace 'path_to_directory' with the actual path to your directory
directory_path = '/home/ubuntu/share/port_MTL_LIDAR/finding_out'

original = [299.199, 177.512, 2.14659]

# List all files in the directory
files = os.listdir(directory_path)

good = []

# Loop through each file
for file_name in files:
	# Check if the item in the directory is a file (not a subdirectory)
	#print(file_name)
	if os.path.isfile(os.path.join(directory_path, file_name)):
		# Open the file in read mode
		with open(os.path.join(directory_path, file_name), 'r') as file:
			# Read the first line of the file
			first_line = file.readline()
			split = first_line.split(" ")
			values = [float(x) for x in split]
#			print(original)
#			print(values)
			if math.isclose(values[0], original[0], abs_tol=0.2) and math.isclose(values[1], original[1], abs_tol=0.2) and math.isclose(values[2], original[2], abs_tol=0.2):
				good.append(file_name)
	#break;

print(good)

