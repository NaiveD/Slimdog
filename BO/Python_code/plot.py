from statistics import stdev
import matplotlib.pyplot as plt
import numpy as np

if __name__ == "__main__":
    # Open files
    file1 = open("./data/2020-12-23_13:42:25_all_data_add_continue.out", mode = "r") # Min-support
    file2 = open("./data/2021-01-11_15:14:24_all_data_add_continue.out", mode = "r") # Reducing-support
    file3 = open("./data/2021-01-12_21:14:23_all_data_no_support.out", mode = "r") # No-support    

    # Read in all the data
    file_line1 = file1.readlines() # Min-support
    file_line2 = file2.readlines() # Reducing-support
    file_line3 = file3.readlines() # No-support

    # Store all the data
    # x-axis
    x = list(range(1, 62)) # x axis for Min-support and Reducing-support (50 + 10 + 1 = 61 iterations)   ([1, 2, ..., 61])
    x_10 = list(range(1, 11)) # x axis for No-support (10 iterations)   ([1, 2, ..., 10])

    # y-axis (data, mean value)
    y1 = [] # Min-support
    y2 = [] # Reducing-support
    y3 = [] # No-support

    # Standard deviation
    e1 = [] # Min-support
    e2 = [] # Reducing-support
    e3 = [] # No-support
    
    # Min-support
    for each_iter in file_line1:
        each_iter_list = eval(each_iter) # convert string to list
        
        each_mean = each_iter_list[4] # calculate mean
        each_stdev = stdev([each_iter_list[1], each_iter_list[2], each_iter_list[3]]) # calculate stdev

        y1.append(each_mean) # store mean
        e1.append(each_stdev) # store stdev
    
    # Reducing-support
    for each_iter in file_line2:
        if len(each_iter) > 1:
            each_iter_list = eval(each_iter) # convert string to list
            
            each_mean = each_iter_list[4] # calculate mean
            each_stdev = stdev([each_iter_list[1], each_iter_list[2], each_iter_list[3]]) # calculate stdev

            y2.append(each_mean) # store mean
            e2.append(each_stdev) # store stdev

    # No-support
    for each_iter in file_line3:
        each_iter_list = eval(each_iter) # convert string to list
        
        each_mean = each_iter_list[4] # calculate mean
        each_stdev = stdev([each_iter_list[1], each_iter_list[2], each_iter_list[3]]) # calculate stdev

        y3.append(each_mean) # store mean
        e3.append(each_stdev) # store stdev


    # Get critical points
    # Min-support
    y1 = y1[:len(x)] # Data for all the 61 iterations (content unchanged)
    y1_before60 = y1[:60] # Data before iteration 50 ([1, 2, ..., 60])
    y1_before50 = y1[:50] # Data before iteration 50 ([1, 2, ..., 50])
    max_indx1_before60 = np.argmax(y1_before60) # Max value index for all the 61 iterations
    max_indx1_before50 = np.argmax(y1_before50) # Max value index before iteration 50
    print("Min-support: ")
    print("max_indx1_before60 = ", max_indx1_before60)
    print("max_indx1_before50 = ", max_indx1_before50)


    # Reducing-support
    y2 = y2[:len(x)] # Data for all the 61 iterations
    y2_before60 = y2[:60] # Data before iteration 50
    y2_before50 = y2[:50] # Data before iteration 50
    max_indx2_before60 = np.argmax(y2_before60) # Max value index for all the 61 iterations
    max_indx2_before50 = np.argmax(y2_before50) # Max value index before iteration 50
    print("Reducing-support: ")
    print("max_indx2_before60 = ", max_indx2_before60)
    print("max_indx2_before50 = ", max_indx2_before50)

    # No-support
    y3 = y3[:len(x_10)] # Data for all the 10 iterations
    max_indx3_before10 = np.argmax(y3) # Max value index for all the 10 iterations
    print("No support: ")
    print("max_indx3_before10 = ", max_indx3_before10)


    # Plot the ploylines
    # Min-support (blue o)
    l1 = plt.plot(x, y1,'bo',label='Min_Support', zorder = 10, alpha = 0.6)
    plt.plot(x, y1, 'bo-')

    # Reducing-support (red +)
    l2 = plt.plot(x, y2,'r^',label='Reducing_Support', zorder = 11, alpha = 0.6)
    plt.plot(x, y2, 'r^-', zorder = 11)

    # No-support (green x)
    l2 = plt.plot(x_10, y3,'gx',label='No_Support', zorder = 11, alpha = 0.6)
    plt.plot(x_10, y3, 'gx-', zorder = 11)


    # Plot the error bars
    plt.errorbar(x, y1, e1, linestyle='None', color='b') # Min-support
    plt.errorbar(x, y2, e2, linestyle='None', color='r') # Reducing-support
    plt.errorbar(x_10, y3, e3, linestyle='None', color='g') # No-support


    # Plot the critical points
    # Min-support 
    # Max value point for all the 61 iterations
    plt.scatter(max_indx1_before60+1, y1[max_indx1_before60], 70, marker='x', color = 'black', zorder = 20)
    plt.annotate(r'Min_P1: ['+str(max_indx1_before60)+', '+str("%.4f"%y1[max_indx1_before60])+']', 
                        xy=(max_indx1_before60+1, y1[max_indx1_before60]), xycoords='data', xytext=(-150, +25), 
                        textcoords='offset points', fontsize=9, arrowprops=dict(arrowstyle="->", 
                        connectionstyle="arc3,rad=.2"))
    # Max value point before iteration 50
    plt.scatter(max_indx1_before50+1, y1[max_indx1_before50], 70, marker='x', color = 'black', zorder = 20)
    plt.annotate(r'Min_P2: ['+str(max_indx1_before50)+', '+str("%.4f"%y1[max_indx1_before50])+']', 
                        xy=(max_indx1_before50+1, y1[max_indx1_before50]), xycoords='data', xytext=(+10, +35), 
                        textcoords='offset points', fontsize=9, arrowprops=dict(arrowstyle="->", 
                        connectionstyle="arc3,rad=.2"))  
    # Last point using the best parameters with no support
    plt.scatter(60+1, y1[60], 70, marker='x', color = 'black', zorder = 20)
    plt.annotate(r'Min_P3: ['+str(60)+', '+str("%.4f"%y1[60])+']', 
                        xy=(60+1, y1[60]), xycoords='data', xytext=(+60, +15), 
                        textcoords='offset points', fontsize=9, arrowprops=dict(arrowstyle="->", 
                        connectionstyle="arc3,rad=.2"))  

    # Reducing-support
    # Max value point for all the 61 iterations
    plt.scatter(max_indx2_before60+1, y2[max_indx2_before60], 70, marker='x', color = 'black', zorder = 20)
    plt.annotate(r'Reduce_P1: ['+str(max_indx2_before60)+', '+str("%.4f"%y2[max_indx2_before60])+']',
                        xy=(max_indx2_before60+1, y2[max_indx2_before60]), xycoords='data', xytext=(-10, +80), 
                        textcoords='offset points', fontsize=9, arrowprops=dict(arrowstyle="->", 
                        connectionstyle="arc3,rad=.2"))
    # Max value point before iteration 50
    plt.scatter(max_indx2_before50+1, y2[max_indx2_before50], 70, marker='x', color = 'black', zorder = 20)
    plt.annotate(r'Reduce_P2: ['+str(max_indx2_before50)+', '+str("%.4f"%y2[max_indx2_before50])+']', 
                        xy=(max_indx2_before50+1, y2[max_indx2_before50]), xycoords='data', xytext=(-30, +75), 
                        textcoords='offset points', fontsize=9, arrowprops=dict(arrowstyle="->", 
                        connectionstyle="arc3,rad=.2"))  
    # Last point using the best parameters with no support
    plt.scatter(60+1, y2[60], 70, marker='x', color = 'black', zorder = 20)
    plt.annotate(r'Reduce_P3: ['+str(60)+', '+str("%.4f"%y2[60])+']', 
                        xy=(60+1, y2[60]), xycoords='data', xytext=(+60, +35), 
                        textcoords='offset points', fontsize=9, arrowprops=dict(arrowstyle="->", 
                        connectionstyle="arc3,rad=.2"))  

    # No-support     
    # Max value point for all the 10 iterations
    plt.scatter(max_indx3_before10+1, y3[max_indx3_before10], 70, marker='x', color = 'black', zorder = 20)
    plt.annotate(r'No_P1: ['+str(max_indx3_before10)+', '+str("%.4f"%y3[max_indx3_before10])+']',
                        xy=(max_indx3_before10+1, y3[max_indx3_before10]), xycoords='data', xytext=(-90, +60), 
                        textcoords='offset points', fontsize=9, arrowprops=dict(arrowstyle="->", 
                        connectionstyle="arc3,rad=.2"))                       

    t = 1
    plt.plot([t,t],[0,100], color ='black', linewidth=2.5, linestyle="--")

    t = 10
    plt.plot([t,t],[0,100], color ='black', linewidth=2.5, linestyle="--")

    t = 20
    plt.plot([t,t],[0,100], color ='black', linewidth=2.5, linestyle="--")

    t = 30
    plt.plot([t,t],[0,100], color ='black', linewidth=2.5, linestyle="--")

    t = 50
    plt.plot([t,t],[0,100], color ='black', linewidth=2.5, linestyle="--")

    t = 60
    plt.plot([t,t],[0,100], color ='black', linewidth=2.5, linestyle="--")

    plt.title('Comparison of Min-support (39->32.5 cm), Reducing-support (47.5->39->32.5 cm) and No-support (32.5 cm)')
    plt.xlabel('Number of iterations')
    plt.ylabel('Fitness')
    plt.legend()
    plt.show()

    file1.close()
    file2.close()
    file3.close()
