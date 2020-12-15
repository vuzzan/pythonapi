//============================================================================
// Name        : PythonTest.cpp
// Author      : D
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <sstream>
#include <Python.h>
#include "pyhelper.h"

static PyObject* arnav_printmsg(PyObject* self, PyObject* args)
{
	printf("print msg call\n");
	const char *a;
	if(!PyArg_ParseTuple(args, "s", &a))
	{
		printf("C++: msg(%s)\n", a);
		return PyLong_FromLong(0);
	}
	printf("%s \n", a);
	return PyLong_FromLong(0);
}
static PyObject* arnav_neoneo(PyObject* self, PyObject* args)
{
	printf("... in C++...: arnav_neoneo() method\n");
	const char *command;
    try {
	    if (!PyArg_ParseTuple(args, "s", &command)){
			printf("PyArg_ParseTuple Error\n");
			return PyLong_FromLong(0);
		}
		printf("PyArg_ParseTuple %s \n", command);
    }
    catch(...)
	{
		return NULL;
	}
	return PyLong_FromLong(51);
}

static PyObject* arnav_show(PyObject* self, PyObject* args)
{
	PyObject *a;
	if(PyArg_UnpackTuple(args, "", 1, 1, &a))
	{
		printf("C++: show(%ld)\n", PyLong_AsLong(a));
	}

	return PyLong_FromLong(0);
}



static struct PyMethodDef methods[] = {
	{ "neoneo", arnav_neoneo, METH_VARARGS, "Returns the number"},
	{ "show", arnav_show, METH_VARARGS, "Show a number" },
	{ "printmsg", arnav_printmsg, METH_VARARGS, "Print string" },
	{ NULL, NULL, 0, NULL }
};

static struct PyModuleDef modDef = {
	PyModuleDef_HEAD_INIT, "arnav", NULL, -1, methods,
	NULL, NULL, NULL, NULL
};

static PyObject* PyInit_arnav(void)
{
	return PyModule_Create(&modDef);
}


int main()
{
	PyImport_AppendInittab("arnav", &PyInit_arnav);

	CPyInstance hInstance;

	CPyObject pName4 = PyUnicode_FromString("pyemb4");
	CPyObject pModule4 = PyImport_Import(pName4);

	CPyObject pName = PyUnicode_FromString("pyemb3");
	CPyObject pModule = PyImport_Import(pName);

	printf("pModule=%x pModule4=%x\n", pModule.getObject(), pModule4.getObject());
	if(pModule && pModule4)
	{
		CPyObject pFunc4 = PyObject_GetAttrString(pModule4, "processMsg");
		CPyObject pFunc = PyObject_GetAttrString(pModule, "getInteger");

		if(pFunc && PyCallable_Check(pFunc) && pFunc4 && PyCallable_Check(pFunc4))
		{
			PyObject* args4 =  Py_BuildValue("({s:i,s:i})", "NGHIA", 123, "TRANG", 456);

			int n=10;
			//PyObject *argsList = PyList_New(n);
			CPyObject args = PyDict_New();
			for (int i = 0; i < n; i++) {
			    //PyTuple_SET_ITEM(args, i, PyLong_FromLong(i));
				std::stringstream ss;
				ss << i;
				std::string temp = "NEO" + std::string(ss.str());
				//PyTuple_SET_ITEM(args, i, Py_BuildValue("{s:i}", temp.c_str(), i));
				PyDict_SetItem(args, Py_BuildValue("s", temp.c_str()), Py_BuildValue("i", i));
			}
			CPyObject args0 =  Py_BuildValue("({s:O})", "msg", args.getObject());
			//

			CPyObject pValue4 = PyObject_CallObject(pFunc4, args0.getObject());
			//printf("C444: processMsg() = %ud\n", PyLong_AsLong(pValue4));
			printf("OK: function processMsg()\n");
		}
		else
		{
			printf("ERROR: function getInteger()\n");
		}

	}
	else
	{
		printf("ERROR: Module not imported\n");
	}
	printf("\nPress any key to exit...\n");
	if(!_getch()) _getch();
	return 0;
}
int main2()
{
	PyObject* pInt;

	Py_Initialize();

	PyRun_SimpleString("print('Hello World from Embedded Python!!!');\nprint('Neo')");

	Py_Finalize();

	printf("\nPress any key to exit...\n");
	if(!_getch()) _getch();
	return 0;
}
