//============================================================================
// Name        : PythonTest.cpp
// Author      : D
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <conio.h>
#include <Python.h>
#include "pyhelper.h"

static PyObject* arnav_foo(PyObject* self, PyObject* args)
{
	printf("... in C++...: foo() method\n");
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

static PyObject* arnav_printmsg(PyObject* self, PyObject* args)
{
	printf("print msg call\n");
	PyObject *a;
	if(PyArg_UnpackTuple(args, "", 1, 1, &a))
	{
		printf("C++: msg(%s)\n", PyUnicode_AsASCIIString(a));
	}

	return PyUnicode_AsASCIIString(PyUnicode_AsASCIIString(a));
}

static struct PyMethodDef methods[] = {
	{ "foo", arnav_foo, METH_VARARGS, "Returns the number"},
	{ "show", arnav_show, METH_VARARGS, "Show a number" },
	{ "PrintMsg", arnav_printmsg, METH_VARARGS, "Print string" },
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
		CPyObject pFunc4 = PyObject_GetAttrString(pModule4, "getInteger4");
		CPyObject pFunc = PyObject_GetAttrString(pModule, "getInteger");

		if(pFunc && PyCallable_Check(pFunc) && pFunc4 && PyCallable_Check(pFunc4))
		{
			CPyObject pValue = PyObject_CallObject(pFunc, NULL);
			printf("C: getInteger() = %ld\n", PyLong_AsLong(pValue));

			CPyObject pValue4 = PyObject_CallObject(pFunc4, NULL);
			printf("C444: getInteger4() = %ld\n", PyLong_AsLong(pValue4));
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
