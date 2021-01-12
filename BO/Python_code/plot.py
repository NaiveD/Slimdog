from statistics import stdev
import matplotlib.pyplot as plt
import numpy as np

if __name__ == "__main__":
    file1 = open("./data/2020-12-23_13:42:25_all_data.out", mode = "r")
    file2 = open("./data/2021-01-11_15:14:24_all_data.out", mode = "r")
    
    file_line1 = file1.readlines()
    file_line2 = file2.readlines()

    x = list(range(1, 51))
    y1 = []
    y2 = []
    e1 = []
    e2 = []
    
    for each_iter in file_line1:
        each_iter_list = eval(each_iter)
        
        each_mean = each_iter_list[4]
        each_stdev = stdev([each_iter_list[1], each_iter_list[2], each_iter_list[3]])

        y1.append(each_mean)
        e1.append(each_stdev)
    
    for each_iter in file_line2:
        each_iter_list = eval(each_iter)
        
        each_mean = each_iter_list[4]
        each_stdev = stdev([each_iter_list[1], each_iter_list[2], each_iter_list[3]])

        y2.append(each_mean)
        e2.append(each_stdev)


    y1 = y1[:len(x)]
    max_indx1 = np.argmax(y1) #max value index

    y2 = y2[:len(x)]
    max_indx2 = np.argmax(y2) #max value index

    l1 = plt.plot(x, y1,'bo',label='Min_Support', zorder = 10, alpha = 0.6)
    plt.plot(x,y1,'bo-')

    l2 = plt.plot(x, y2,'r+',label='Reducing_Support', zorder = 11, alpha = 0.6)
    plt.plot(x,y2,'r+-', zorder = 11)



    plt.errorbar(x, y1, e1, linestyle='None', color='b')
    plt.errorbar(x, y2, e2, linestyle='None', color='r')

    plt.scatter(max_indx1+1, y1[max_indx1], 70, marker='x', color = 'black', zorder = 20)
    plt.annotate(r'Min_Support: ['+str(max_indx1)+', '+str("%.4f"%y1[max_indx1])+']', 
                        xy=(max_indx1+1, y1[max_indx1]), xycoords='data', xytext=(+10, +35), 
                        textcoords='offset points', fontsize=9, arrowprops=dict(arrowstyle="->", 
                        connectionstyle="arc3,rad=.2"))

    plt.scatter(max_indx2+1, y2[max_indx2], 70, marker='x', color = 'black', zorder = 20)
    plt.annotate(r'Reducing_Support: ['+str(max_indx2)+', '+str("%.4f"%y2[max_indx2])+']',
                        xy=(max_indx2+1, y2[max_indx2]), xycoords='data', xytext=(-10, +80), 
                        textcoords='offset points', fontsize=9, arrowprops=dict(arrowstyle="->", 
                        connectionstyle="arc3,rad=.2"))

    t = 10
    plt.plot([t,t],[0,50], color ='black', linewidth=2.5, linestyle="--")

    t = 20
    plt.plot([t,t],[0,50], color ='black', linewidth=2.5, linestyle="--")

    t = 30
    plt.plot([t,t],[0,50], color ='black', linewidth=2.5, linestyle="--")

    plt.title('Comparison of minimum-support and reducing-support')
    plt.xlabel('Number of iterations')
    plt.ylabel('Fitness')
    plt.legend()
    plt.show()

    file1.close()
    file2.close()
