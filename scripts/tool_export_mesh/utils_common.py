import pickle
import os
import hashlib
import datetime
import shutil
import re

default_assets_folder = 'YOUR_LOOSE_DATA_FOLDER'
export_mesh_folder_path = None
assets_folder = None

def save(filename, *args):
	# Get global dictionary
	glob = globals()
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

def edit_distance_similarity(word1, word2):
    m, n = len(word1), len(word2)
    
    dp = [[0] * (n + 1) for _ in range(m + 1)]

    for i in range(m + 1):
        dp[i][0] = i
    for j in range(n + 1):
        dp[0][j] = j

    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if word1[i - 1] == word2[j - 1]:
                cost = 0
            else:
                cost = 1
            dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost)

    return 1 - pow(dp[m][n] / max(len(word1), len(word2)), 0.5)

def _tag(name:str):
	tags = re.findall(r'\w+', name)
	final_tags = []
	for combined_tag in tags:
		sub_tags = combined_tag.lower().split('_')
		for tag in sub_tags:
			if tag == 'f':
				tag = 'female'
			elif tag == 'm':
				tag = 'male'
			elif tag == 'r' or tag == 'R' or tag == 'Right':
				tag = 'right'
			elif tag == 'l' or tag == 'L' or tag == 'Left':
				tag = 'left'
			elif tag == 'ss':
				tag == 'cloth'
			final_tags.append(tag)
    
	return list(set(final_tags))

def _match_tags(tags_a:list, tags_b:list, normalized = False):
	final_score = 0
	for tag_a in tags_a:
		tag_score = 0
		for tag_b in tags_b:
			tag_score += edit_distance_similarity(tag_a, tag_b)
		final_score += tag_score
	
	if normalized:
		final_score /= len(tags_a) * len(tags_b)

	return final_score


def _remove_suffix(name:str):
	return name[:name.rfind(".")]

def ParentDirIfExsit(path:str, recurs_depth:int = 1, near_first = True):
	if os.path.exists(os.path.dirname(path)) and recurs_depth > 0:
		lst = RecurseDirIfExsit(os.path.dirname(path), recurs_depth)
		if near_first:
			return lst
		else:
			return lst.reverse()
		
	return []

def RecurseDirIfExsit(path:str, recurs_depth:int = 1):
	lst = [path]
	if recurs_depth > 0:
		sub_lst = RecurseDirIfExsit(os.path.dirname(path), recurs_depth - 1)
		return lst + sub_lst
	
	return []

def FlattenDictToList(dictionary: dict, index_type = int, replace_none = False, replace_none_with = None):
	max_id = 0
	for id in dictionary.keys():
		if int(id) > max_id:
			max_id = int(id)

	if replace_none:
		return [dictionary[index_type(i)] if index_type(i) in dictionary else replace_none_with for i in range(max_id + 1)]
	else:
		return [dictionary[index_type(i)] for i in range(max_id + 1) if index_type(i) in dictionary]