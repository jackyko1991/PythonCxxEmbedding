#include <Python.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	Py_Initialize();

	//PyObject *pModule, *pFunc1, *pFunc2, *pFunc3, *pFunc4;
	//PyObject *pArgs, *pValue;

	///* import */
	//pModule = PyImport_Import(PyString_FromString("hello"));

	//// execute without argument parsing
	//pFunc1 = PyObject_GetAttrString(pModule, "Hello");
	//PyObject_CallObject(pFunc1, NULL);

	//// execute with string type argument parsing
	//// obtain function object
	//pFunc2 = PyObject_GetAttrString(pModule, "Hello2");
	//// build args and execute
	//pArgs = PyTuple_New(1);
	//PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", "string type argument parsing"));
	//PyObject_CallObject(pFunc2, pArgs);

	//// number type argument parsing
	//// obtain function object
	//pFunc3 = PyObject_GetAttrString(pModule, "addition");
	//// build args and execute
	////"i" is integer type, "d" is double type, "f" is float type. Note that double will auto cast to float in python
	//double a = 12.3;
	//double b = 45.6;
	//pArgs = Py_BuildValue("(f,f)", a, b);
	////pValue = PyObject_CallObject(pFunc3, pArgs);
	//double res = PyFloat_AsDouble(pValue);
	//cout << a <<" + "<<b<<" = "<< res << endl;

	//// multiple value retrun from python fucntion
	//pFunc4 = PyObject_GetAttrString(pModule, "MultipleReturn");
	//pValue = PyObject_CallObject(pFunc4, NULL);
	//cout << PyString_AsString(PyList_GetItem(pValue, (Py_ssize_t)0))<<" "<< PyString_AsString(PyList_GetItem(pValue, (Py_ssize_t)1)) <<endl; //similar approach can be applied on tuple return

	// test for curve fitting
	double val[13];
	val[0] = 57.3;
	val[1] = 57.6;
	val[2] = 57.9;
	val[3] = 58.7;
	val[4] = 59.4;
	val[5] = 63.3;
	val[6] = 68.0;
	val[7] = 74.2;
	val[8] = 81.2;
	val[9] = 84.7;
	val[10] = 89.7;
	val[11] = 93.7;
	val[12] = 94.5;

	PyObject* pModuleDCE = PyImport_Import(PyString_FromString("DCE_fitting"));
	PyObject* pFuncDCE = PyObject_GetAttrString(pModuleDCE, "DCE_fit");
	
	// convert C++ array to python List
	PyObject* pList = PyList_New(13);
	for (size_t i = 0; i != 13; i++) 
	{
		PyList_SetItem(pList, i, PyFloat_FromDouble(val[i]));
	}

	// argument parsing need to be a python tuple object, so use a tuple to store the python list
	PyObject* pArgs = PyTuple_New(1);
	PyTuple_SetItem(pArgs, 0, pList);

	// execute
	PyObject_CallObject(pFuncDCE, pArgs);

	Py_Finalize();
	system("pause");
	return 0;
}