# import math
# !/usr/local/bin/python


# need to iterate through the file
# While iterating through the file need to call convert_to_cartesian on values
# add the conversions to a list
# every 3 values phi and rho need to be updated, every 90 values theta is updated
# values are separated by the /n character
# values are floats
# append list onto file


data = []

# ________________________________________Convert To Cartesian Functions______________________________________________#
def convert_x_coordinate(rho, phi, theta):
    phi= math.radians(phi)
    theta = math.radians(theta)
    x = rho * math.cos(phi) * math.sin(theta);
    return x

def convert_y_coordinate(rho, phi, theta):
    phi= math.radians(phi)
    theta = math.radians(theta)
    y = rho * sin(phi) * sin(theta)
    return y

def convert_z_coordinate(rho, phi):
    phi= math.radians(phi)
    z = rho * cos(phi)
    return z
#_________________________________________Convert To Cartesian Functions_______________________________________________#





# def convert_to_cartesian(rho, phi, theta):
#     # pi=3.14
#
#     # # Measurements are in degrees
#     # # Conversion to radians convert to radians
#     # phi= (phi*pi)/180
#     # theta = (theta*pi)/180
#
#     phi = math.radians(phi)
#     theta = math.radians(theta)
#
#     x = rho * math.cos(phi) * math.sin(theta)
#     y = rho * sin(phi) * sin(theta)
#     z = rho * cos(phi)
#
#     print ('x coordinate: ' + x, 'y coordinate: ' + y, 'z coordinate: ' + z);



#_________________________________________Read and Write Log File Functions____________________________________________#


def get_numbers():

    # data = []


    with open('/Users/Jables/Desktop/LOG2Edited.txt') as input_file:

        for line in input_file:
            line = line.strip()
            for number in line.split():
                data.append(number)
                print(number)






def make_converted_file():
    with open('/Users/Jables/Desktop/convertedData.txt', 'w') as newFile:
        for value in data:
            newFile.write("%s\n" % value)


#_________________________________________Read and Write Log File Functions____________________________________________#


get_numbers()
make_converted_file()



