import pickle
import os
import hashlib
import datetime
import shutil

default_assets_folder = 'YOUR_LOOSE_DATA_FOLDER'
export_mesh_folder_path = None
assets_folder = None

def save(filename, *args):
	# Get global dictionary
	glob = globals()
	print(glob)
	d = {}
	for v in args:
		# Copy over desired values
		d[v] = glob[v]
	with open(os.path.join(os.path.dirname(__file__), filename), 'wb') as f:
		# Put them in the file 
		pickle.dump(d, f)

def load(filename):
	# Get global dictionary
	glob = globals()
	print(glob)
	try:
		with open(os.path.join(os.path.dirname(__file__), filename), 'rb') as f:
			for k, v in pickle.load(f).items():
				# Set each global variable to the value from the file
				glob[k] = v
	except FileNotFoundError:
		print("No cached paths.")
		global export_mesh_folder_path
		export_mesh_folder_path = os.path.join(os.path.dirname(__file__),'Result')
		global assets_folder
		assets_folder = default_assets_folder

def sanitize_filename(filename):
	illegal_chars = ['<', '>', ':', '"', '/', '\\', '|', '?', '*']
	replacement_char = '_'  # You can replace illegal characters with another character or remove them

	# Replace illegal characters with the replacement character
	for char in illegal_chars:
		filename = filename.replace(char, replacement_char)

	return filename

def hash_string(input_string):
	# Create a SHA-1 hash object
	sha1 = hashlib.sha1()

	# Update the hash object with the input string encoded as bytes
	sha1.update(input_string.encode('utf-8'))

	# Get the hexadecimal representation of the hash
	hex_digest_input = sha1.hexdigest()

	# Take the first 20 characters of the input string's hexadecimal digest
	hex_result_input = hex_digest_input[:20]

	# Get the current date and time as a string
	current_datetime = datetime.datetime.now().strftime('%Y%m%d%H%M%S%f')

	# Create a SHA-1 hash object for the current date and time
	sha1 = hashlib.sha1()

	# Update the hash object with the current date and time encoded as bytes
	sha1.update(current_datetime.encode('utf-8'))

	# Get the hexadecimal representation of the hash
	hex_digest_datetime = sha1.hexdigest()

	# Take the first 20 characters of the datetime's hexadecimal digest
	hex_result_datetime = hex_digest_datetime[:20]

	# Combine the two hexadecimal results
	return hex_result_datetime, hex_result_input

def hash_string_2(input_string):
	# Create a SHA-1 hash object
	sha1 = hashlib.sha1()

	# Update the hash object with the input string encoded as bytes
	sha1.update(input_string.encode('utf-8'))

	# Get the hexadecimal representation of the hash
	hex_digest_input = sha1.hexdigest()

	# Take the first 20 characters of the input string's hexadecimal digest
	hex_result_input = hex_digest_input[:20]

	# Get the current timestamp as an integer
	current_timestamp = int(datetime.datetime.now().timestamp())

	# Convert the prefix and timestamp to integers
	prefix = int("fffff000000000000000", 16)
	timestamp = current_timestamp

	# Add the two integers together
	result = prefix + timestamp

	# Convert the result back to a 20-character hexadecimal string
	hex_result_datetime = format(result, '020x')

	# Combine the two hexadecimal results
	return hex_result_datetime, hex_result_input

def copy_and_rename_file(source_file, destination_folder, new_file_name):
	# Extract the file name and extension
	file_name, file_extension = os.path.splitext(source_file)

	# Construct the destination path
	destination_path = os.path.join(destination_folder, new_file_name + '.mesh')
	
	shutil.copy2(source_file, destination_path)

def delete_folder(path):
	try:
		shutil.rmtree(path)
		print(f"Folder '{path}' and its contents have been successfully deleted.")
	except FileNotFoundError:
		print(f"Folder '{path}' does not exist.")
	except Exception as e:
		print(f"An error occurred while deleting the folder '{path}': {e}")

def flatten(lst):
	result = []
	for item in lst:
		if isinstance(item, list):
			result.extend(flatten(item))
		else:
			result.append(item)
	return result