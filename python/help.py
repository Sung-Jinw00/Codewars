"""
This script demonstrates how to use docstrings
and display help information for functions in the `functions` package.
"""
# ANSI color codes
CYAN   = "\033[36m"
GREEN  = "\033[32m"
YELLOW = "\033[33m"
RED    = "\033[31m"
RESET  = "\033[0m"

import functions
from inspect import isfunction, isclass, ismodule

from io import StringIO
from contextlib import redirect_stdout


def help_method(cls, method_name):
	methods = {}
	for attr_name in dir(cls):
		if attr_name.startswith("__"):
			continue
		attr = getattr(cls, attr_name)
		if isfunction(attr):
			methods[attr_name] = attr
	if method_name not in methods:
		print(f"{RED}Invalid method name '{method_name}'.")
		return
	full_name = f"{cls.__name__}.{method_name}"
	help_one(methods[method_name], full_name)

def handle_class_help(cls):
	methods = {}
	for attr_name in dir(cls):
		if attr_name.startswith("__"):
			continue
		attr = getattr(cls, attr_name)
		if isfunction(attr):
			methods[attr_name] = attr
	if not methods:
		print(f"{RED}Class {cls.__name__} has no public methods.")
		return
	choice = ""
	while choice not in ("quit", "1", "2"):
		print(f"\n{YELLOW}Show help for:")
		print(f"{CYAN}1 - a single method")
		print(f"{GREEN}2 - all methods")
		print(F"\n{RED}Type 'quit' to exit.")
		choice = input(F"{YELLOW}Your choice: {RESET}").strip().lower()
		if choice == "quit":
			return
		elif choice not in ("1", "2"):
			print(f"{RED}Invalid choice. Please try again.")
	if choice == "1":
		print(f"\n{GREEN}Methods available in {cls.__name__}:{CYAN}")
		for name in methods:
			print(f"- {name}")
		method_name = input(f"\n{YELLOW}Enter the method name: {RESET}").strip()
		if method_name in methods:
			help_method(cls, method_name)
		else:
			print(f"{RED}Invalid method name '{method_name}'.")
	elif choice == "2":
		for name, method in methods.items():
			help_one(method, f"{cls.__name__}.{name}")

def help_one(obj, name=None):
	if not (isfunction(obj) or isclass(obj)):
		print(f"Error: {obj} is not a function or class.")
		return
	display_name = name or obj.__name__
	nb = 17 + len(display_name) + 6
	print(f"\n{'='*nb}\n   Help on {display_name}\n{'='*nb}")
	f = StringIO()
	with redirect_stdout(f):
		help(obj)
	help_text = f.getvalue()
	lines = help_text.splitlines()
	help_text = "\n".join(lines[1:])
	print(help_text)


def help_all(module, prefix=""):
	for name in getattr(module, "__all__", []):
		attr = getattr(module, name)
		if isfunction(attr):
			# Call help_one instead of duplicating the code
			full_name = f"{prefix}{name}"
			help_one(attr, full_name)
			while True:
				answer = input(f"{YELLOW}Keep going ? ({GREEN}Enter{YELLOW}/{RED}quit{YELLOW}) : {RESET}").strip()
				if not answer:
					break
				elif answer == "quit":
					return 1
				else:
					print(f"{RED}Invalid input !")
		elif ismodule(attr):
			# Recurse into submodules with updated prefix
			sub_prefix = f"{prefix}{name}."
			if help_all(attr, prefix=sub_prefix):
				return 1
	return 0
			
from inspect import isfunction, isclass, ismodule

def get_all_functions(module):
	collected = {}
	for name in getattr(module, "__all__", []):
		attr = getattr(module, name)

		if isfunction(attr) or isclass(attr):
			collected[name] = attr

		elif ismodule(attr):
			# Merge functions from submodules, but keep flat names
			collected.update(get_all_functions(attr))
	return collected

def main():
	while True:	
		print(f"{YELLOW}Do you want the description of :\n{CYAN}1 - a single function ?\n{GREEN}2 - all functions ?")
		
		print(f"\n{RED}Type 'quit' to exit.")
		while True:
			choice = input(f"{YELLOW}Your choice : {RESET}").strip()
			if choice in ("1", "2"):
				break
			elif choice == 'quit':
				return
			print(f"{RED}Invalid input. Please enter 1 or 2.")

		if choice == "2":
			# Display help for all functions
			help_all(functions)
		else:
			# Display help for a single function
			funcs = get_all_functions(functions)
			print(f"\n{GREEN}Available functions:{CYAN}")
			for name in sorted(funcs):
				print(f"- {name}")

			while True:
				print(f"\n{RED}Type 'quit' to exit.")
				func_name = input(f"{YELLOW}Enter the function name: {RESET}").strip()

				if func_name.lower() == "quit":
					print(f"{RED}Exiting...{RESET}")
					break

				if func_name in funcs:
					obj = funcs[func_name]
					if isclass(obj):
						handle_class_help(obj)
					else:
						help_one(obj, func_name)
					break
				else:
					print(f"{RED}Invalid function name '{func_name}'. Please try again.")

from shutil import rmtree
import os

if __name__ == "__main__":
	main()
	print(f"{CYAN} Caches cleaned :")
	for root, dirs, files in os.walk("."):
		if "__pycache__" in dirs:
			cache_dir = os.path.join(root, "__pycache__")
			try:
				rmtree(cache_dir)
				print(f"\t{GREEN}- {cache_dir}{RESET}")
			except Exception as e:
				print(f"\t{RED}- Failed to remove '{cache_dir}': {e}{RESET}")