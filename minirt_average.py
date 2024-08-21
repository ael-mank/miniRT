import schedule
import time
import subprocess
import re
from datetime import datetime

render_times = []

def run_minirt():
    global render_times
    try:
        # Run the minirt command
        result = subprocess.run(['./minirt'], capture_output=True, text=True)
        
        # Extract render time from the output
        match = re.search(r'Time to render: (\d+\.\d+) seconds', result.stdout)
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

def schedule_minirt_run(run_time):
    # Schedule the minirt run at the specified time
    schedule.every().day.at(run_time).do(run_minirt)

    while True:
        schedule.run_pending()
        time.sleep(1)

if __name__ == "__main__":
    # Specify the time to run minirt (24-hour format, e.g., "14:30" for 2:30 PM)
    run_time = "14:30"
    
    # Schedule the minirt run
    schedule_minirt_run(run_time)
    
    # Run the script until interrupted
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print("Script interrupted. Calculating average render time...")
        calculate_average_render_time()