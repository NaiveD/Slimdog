import csv
import matplotlib.pyplot as plt
import numpy as np

NO_FILE = "../../Experiment/Scaffold/12-23/No-support/Kinovea/No_P1_R1_RB_J12_Angle.csv"
MIN_FILE = "../../Experiment/Scaffold/12-23/Min-support/Kinovea/Min_P1_R1_RB_J12_Angle_2.csv"
RED_FILE = "../../Experiment/Scaffold/12-23/Reducing-support/Kinovea/Red_P1_R3_J12_Angle.csv"

if __name__ == "__main__":

    with open(NO_FILE) as csv_no_file:
        with open(MIN_FILE) as csv_min_file:
            with open(RED_FILE) as csv_red_file: 
                # For csv reading
                csv_no_reader = csv.reader(csv_no_file, delimiter=',') # No support
                csv_min_reader = csv.reader(csv_min_file, delimiter=',') # Min support
                csv_red_reader = csv.reader(csv_red_file, delimiter=',') # Reducing support
                # Line count
                no_line_count = 0 # No support
                min_line_count = 0 # Min support
                red_line_count = 0 # Reducing support


                # For storing data
                NO_TIME_list = [] # NO support time list (x-axis)
                NO_data_list = [] # No support data list (y-axis)

                MIN_TIME_list = [] # MIN support time list (x-axis)
                MIN_data_list = [] # MIN support data list (y-axis)

                RED_TIME_list = [] # RED support time list (x-axis)
                RED_data_list = [] # RED support data list (y-axis)
      

                # Store all the data
                # ============================== No support =============================== 
                for row in csv_no_reader:
                    if no_line_count == 0:
                        print(f'No support: Headers are {", ".join(row)}')
                        no_line_count += 1
                    else:
                        NO_TIME_list.append(float(row[0]))
                        # NO_data_list.append(float(row[1])) # Joint 1 (Red)
                        NO_data_list.append(float(row[2])) # Joint 2 (Green)

                        no_line_count += 1

                # Set no support x and y lists for plotting
                NO_x = NO_TIME_list[:]
                NO_y = NO_data_list[:]
                
                print("No support: len(NO_x) = %d, len(NO_y) = %d" % (len(NO_x), len(NO_y)))
                # ============================================================================
                # ============================== Minimum support =============================== 
                for row in csv_min_reader:
                    if min_line_count == 0:
                        print(f'Minimum support: Headers are {", ".join(row)}')
                        min_line_count += 1
                    else:
                        MIN_TIME_list.append(float(row[0]))
                        # MIN_data_list.append(float(row[1])) # Joint 1 (Red)
                        MIN_data_list.append(float(row[2])) # Joint 2 (Green)

                        min_line_count += 1

                # Set no support x and y lists for plotting
                MIN_x = MIN_TIME_list[:]
                MIN_y = MIN_data_list[:]
                
                print("No support: len(MIN_x) = %d, len(MIN_y) = %d" % (len(MIN_x), len(MIN_y)))
                # ============================================================================
                # ============================== Minimum support =============================== 
                for row in csv_red_reader:
                    if red_line_count == 0:
                        print(f'Minimum support: Headers are {", ".join(row)}')
                        red_line_count += 1
                    else:
                        RED_TIME_list.append(float(row[0]))
                        # RED_data_list.append(float(row[1])) # Joint 1 (Red)
                        RED_data_list.append(float(row[2])) # Joint 2 (Green)

                        red_line_count += 1

                # Set no support x and y lists for plotting
                RED_x = RED_TIME_list[:]
                RED_y = RED_data_list[:]
                
                print("No support: len(RED_x) = %d, len(RED_y) = %d" % (len(RED_x), len(RED_y)))
                # ============================================================================
                

                # Plot the figures
                plt.plot(NO_x, NO_y,'gx-',label='No_Support', zorder = 10, alpha = 0.6) # No support
                plt.plot(MIN_x, MIN_y,'bo-',label='Min_Support', zorder = 10, alpha = 0.6) # Min support
                plt.plot(RED_x, RED_y,'r^-',label='Red_Support', zorder = 10, alpha = 0.6) # Reducing support
                
                plt.title('Comparison of Min-support (39->32.5 cm), Reducing-support (47.5->39->32.5 cm) and No-support (32.5 cm)')
                plt.xlabel('Time (ms)')
                plt.ylabel('Joint 2 Angle (degree)')
                plt.legend()
                plt.show()