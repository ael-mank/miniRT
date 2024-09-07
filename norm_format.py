import sys
import re
from colorama import init, Fore, Style

# Initialize colorama
init()

def colorize_line(line):
    if "Error!" in line:
        return Fore.RED + line + Style.RESET_ALL
    elif "OK!" in line:
        return Fore.GREEN + line + Style.RESET_ALL
    elif "Error:" in line:
        # Split the line to colorize only the "Error:" part
        parts = line.split("Error:", 1)
        return parts[0] + Fore.RED + "Error:" + Style.RESET_ALL + parts[1]
    else:
        return line

def format_output(output):
    formatted_output = []
    lines = output.split('\n')
    for line in lines:
        if re.match(r'.*\.c: Error!', line) or re.match(r'.*\.c: OK!', line):
            formatted_output.append(colorize_line(line))
        elif "Error:" in line:
            formatted_output.append("\t|-- " + colorize_line(line))
        else:
            formatted_output.append(line)
    return '\n'.join(formatted_output)

def main():
    if len(sys.argv) != 2:
        print("Usage: python norm_format.py <norm_output_file>")
        sys.exit(1)

    norm_output_file = sys.argv[1]

    with open(norm_output_file, 'r') as file:
        output = file.read()

    formatted_output = format_output(output)
    print(formatted_output)

if __name__ == "__main__":
    main()