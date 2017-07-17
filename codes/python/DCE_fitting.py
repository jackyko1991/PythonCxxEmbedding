import numpy as np
import math
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

def DCE_funct(x,A,k,c,I0):
	return A*np.arctan(k*x+c) + I0

def find_nearest(array, value):     
	idx = np.abs(array - value).argmin()    
	return array.flat[idx]

def plotFitting(t,I,params):
	t_new = np.linspace(t[0], t[-1], 50)
	I_new = DCE_funct(t_new,params[0],params[1],params[2],params[3])
	# f = np.poly1d(params)
	# I_new = f(t_new)
	# print I_new

	# calculation Emax
	I_max = np.amax(I_new)
	I_base = np.amin(I_new)
	Emax = (I_max - I_base)/I_base*100

	# calculate Eslope
	I90 = (I_max - I_base)*0.9 + I_base
	I10 = (I_max - I_base)*0.1 + I_base
	I90 = find_nearest(I_new,I90)
	I10 = find_nearest(I_new,I10)
	I90_idx = np.argwhere(I_new == I90)
	I10_idx = np.argwhere(I_new == I10)
	t90 = t_new[I90_idx[0]]
	t10 = t_new[I10_idx[0]]

	Eslope = (I90-I10)/(t90[0]-t10[0])*100.0

	print Emax,Eslope

	plt.clf()
	# plt.plot(t,I,'.')
	plt.plot(t,I,'.',t_new,I_new,'-',t10,I10,'ro',t90,I90,'ro',[t10,t90],[I10,I90],'r-.')
	plt.xlim([t[0]-1, t[-1] + 1 ])
	plt.ylim([0,500])
	plt.ylabel('Time(s)')
	plt.ylabel('MRI Intensity')
	fig = plt.gcf()
	fig.canvas.set_window_title('DCE Curve Fit')
	plt.show()

#	return [Emax,Eslope]

def DCE_fit(val):
	t = range(0,13*7,7)
	t = np.array(t)
	params = curve_fit(DCE_funct, t[:], val[:], p0 = [100,0.1,-3,200])
	print t
	print val
	print params
	plotFitting(t,val,params[0])

