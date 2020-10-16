import json
import numpy as np
import matplotlib.pyplot as plt  

def main():
    # with open('func_test/AGP/AGP.json', 'r') as json_file:
    with open('func_test/Discrete/Discrete.json', 'r') as json_file:
    # with open('func_test/Continuous/Continuous.json', 'r') as json_file:
        json_list = []
        for each in json_file.readlines():
            json_data = json.loads(each)
            json_list.append(json_data)
        
        x = list(range(1,61))
        y = []
        for each in json_list:
            y.append(each['target'])

        print("x = ", x)
        print("y = ", y)    

        max_indx = np.argmax(y)#max value index

        l1=plt.plot(x, y,'b--',label='fitness')
        plt.plot(x,y,'bo-')

        show_max='['+str(max_indx)+' '+str(y[max_indx])+']'
        plt.annotate(show_max,xytext=(max_indx,y[max_indx]),xy=(max_indx,y[max_indx]))

        # plt.title('Fitness of Experiment5 (Continuous)')
        plt.title('Fitness of Experiment5 (Discrete)')
        # plt.title('Fitness of Experiment5 (AGP)')

        plt.xlabel('Number of iterations')
        plt.ylabel('Fitness')
        plt.legend()
        plt.show()


if __name__ == "__main__":
    main()