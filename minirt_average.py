import subprocess
import re
import time
from pynput.keyboard import Controller, Key

render_times = []
keyboard = Controller()

def run_minirt():
    global render_times
    try:
        # Run the minirt command
        process = subprocess.Popen(['./miniRT'], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        
        # Simulate pressing the escape key
        time.sleep(1)  # Wait a moment to ensure minirt has started
        print("Sending ESC key to minirt...")
        keyboard.press(Key.esc)
        keyboard.release(Key.esc)
        
        # Wait for the process to complete
        stdout, stderr = process.communicate()
        
        # Extract render time from the output
        match = re.search(r'Time to render: (\d+\.\d+) seconds', stdout)
        if match:
            render_time = float(match.group(1))
            render_times.append(render_time)
            print(f"Render time: {render_time} seconds")
        else:
            print("Render time not found in the output.")
    except Exception as e:
        print(f"An error occurred: {e}")

def calculate_average_render_time():
    if render_times:
        average_time = sum(render_times) / len(render_times)
        print(f"Average render time: {average_time} seconds")
    else:
        print("No render times collected.")

if __name__ == "__main__":
    # Run minirt 10 times
    for _ in range(10):
        run_minirt()
        time.sleep(1)  # Optional: Add a delay between runs if needed
    
    # Calculate and print the average render time
    calculate_average_render_time()