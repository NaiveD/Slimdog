import json
import numpy as np
import matplotlib.pyplot as plt  

def main():
    with open('Experiment1/2020-09-20 13:33:45.json', 'r') as json_file:
        json_list = []
        for each in json_file.readlines():
            json_data = json.loads(each)
            json_list.append(json_data)
        
        x = list(range(1,51))
        y = []
        for each in json_list:
            y.append(each['target'])

        print("x = ", x)
        print("y = ", y)    

        l1=plt.plot(x, y,'b--',label='fitness')
        plt.plot(x,y,'bo-')

        plt.title('Fitness of Experiment1')
        plt.xlabel('Number of iterations')
        plt.ylabel('Fitness')
        plt.legend()
        plt.show()


if __name__ == "__main__":
    main()