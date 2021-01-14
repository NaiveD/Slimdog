import csv
import matplotlib.pyplot as plt
import numpy as np

NO_FILE = "../../Experiment/Scaffold/12-23/No-support/Kinovea/No_P1_R1_RB_EE_J123o_Speed.csv"
MIN_FILE = "../../Experiment/Scaffold/12-23/Min-support/Kinovea/Min_P1_R1_RB_EE_J123o_Speed.csv"
RED_FILE = "../../Experiment/Scaffold/12-23/Reducing-support/Kinovea/Red_P1_R3_EE_J123o_Speed.csv"

if __name__ == "__main__":

    with open(NO_FILE) as csv_no_file:
        with open(MIN_FILE) as csv_min_file:
            with open(RED_FILE) as csv_red_file:
                # For csv reading
                csv_no_reader = csv.reader(csv_no_file, delimiter=',')
                csv_min_reader = csv.reader(csv_min_file, delimiter=',')
                csv_red_reader = csv.reader(csv_red_file, delimiter=',')

                no_line_count = 0
                min_line_count = 0
                red_line_count = 0

                # For storing data
                NO_TIME_list = [] # NO support Time
                NO_RB_EE_list = [] # No support Right Back leg End Effector
                NO_RB_J1O_list = [] # No support Right Back leg Joint 1 o point
                NO_RB_J2O_list = [] # No support Right Back leg Joint 2 o point
                NO_RB_J3O_list = [] # No support Right Back leg Joint 3 o point

                MIN_TIME_list = [] # MIN support Time
                MIN_RB_EE_list = [] # MIN support Right Back leg End Effector
                MIN_RB_J1O_list = [] # MIN support Right Back leg Joint 1 o point
                MIN_RB_J2O_list = [] # MIN support Right Back leg Joint 2 o point
                MIN_RB_J3O_list = [] # MIN support Right Back leg Joint 3 o point

                RED_TIME_list = [] # RED support Time
                RED_RB_EE_list = [] # RED support Right Back leg End Effector
                RED_RB_J1O_list = [] # RED support Right Back leg Joint 1 o point
                RED_RB_J2O_list = [] # RED support Right Back leg Joint 2 o point
                RED_RB_J3O_list = [] # RED support Right Back leg Joint 3 o point                

                # Store all the data
                # No support
                for row in csv_no_reader:
                    if no_line_count == 0:
                        print(f'No support: Headers are {", ".join(row)}')
                        no_line_count += 1
                    else:
                        # print(f'\tAt {row[0]} ms, RB_EE: {row[1]}, RB_J1o: {row[3]}, RB_J2o: {row[2]}, RB_J3o: {row[4]}.')
                        NO_TIME_list.append(float(row[0]))
                        NO_RB_EE_list.append(float(row[1]))
                        NO_RB_J2O_list.append(float(row[2]))
                        NO_RB_J1O_list.append(float(row[3]))
                        NO_RB_J3O_list.append(float(row[4]))
                        no_line_count += 1
                print("No support: ", len(NO_TIME_list), len(NO_RB_EE_list), len(NO_RB_J1O_list), len(NO_RB_J2O_list), len(NO_RB_J3O_list))

                # Min support
                for row in csv_min_reader:
                    if min_line_count == 0:
                        print(f'Min support: Headers are {", ".join(row)}')
                        min_line_count += 1
                    else:
                        # print(f'\tAt {row[0]} ms, RB_EE: {row[1]}, RB_J1o: {row[3]}, RB_J2o: {row[2]}, RB_J3o: {row[4]}.')
                        MIN_TIME_list.append(float(row[0]))
                        MIN_RB_EE_list.append(float(row[1]))
                        MIN_RB_J2O_list.append(float(row[2]))
                        MIN_RB_J1O_list.append(float(row[3]))
                        MIN_RB_J3O_list.append(float(row[4]))
                        min_line_count += 1
                print("MIN support: ", len(MIN_TIME_list), len(MIN_RB_EE_list), len(MIN_RB_J1O_list), len(MIN_RB_J2O_list), len(MIN_RB_J3O_list))
                
                # Reducing support
                for row in csv_red_reader:
                    if red_line_count == 0:
                        print(f'Reducing support: Headers are {", ".join(row)}')
                        red_line_count += 1
                    else:
                        # print(f'\tAt {row[0]} ms, RB_EE: {row[1]}, RB_J1o: {row[3]}, RB_J2o: {row[2]}, RB_J3o: {row[4]}.')
                        RED_TIME_list.append(float(row[0]))
                        RED_RB_EE_list.append(float(row[1]))
                        RED_RB_J2O_list.append(float(row[2]))
                        RED_RB_J1O_list.append(float(row[3]))
                        RED_RB_J3O_list.append(float(row[4]))
                        red_line_count += 1
                print("RED support: ", len(RED_TIME_list), len(RED_RB_EE_list), len(RED_RB_J1O_list), len(RED_RB_J2O_list), len(RED_RB_J2O_list))
                
                
                NO_x = NO_TIME_list[:]
                NO_y = NO_RB_EE_list[:]






                plt.plot(NO_x, NO_y,'gx-',label='No_Support', zorder = 10, alpha = 0.6)
                
                plt.title('Comparison of Min-support (39->32.5 cm), Reducing-support (47.5->39->32.5 cm) and No-support (32.5 cm)')
                plt.xlabel('Time (ms)')
                plt.ylabel('Right rear leg end effector speed (m/s)')
                plt.legend()
                plt.show()