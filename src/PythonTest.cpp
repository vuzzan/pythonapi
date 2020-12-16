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
#include <map>

#include <Python.h>
#include "pyhelper.h"

static PyObject* secsgemdriver_printmsg(PyObject* self, PyObject* args)
{
	//printf("print msg call\n");
	const char *a;
	if(!PyArg_ParseTuple(args, "s", &a))
	{
		printf("C++: msg(%s)\n", a);
		return PyLong_FromLong(0);
	}
	printf("%s \n", a);
	return PyLong_FromLong(0);
}
static PyObject* secsgemdriver_getdata(PyObject* self, PyObject* args)
{
	//printf("... in C++...: secsgemdriver_getdata() method\n");
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
	//PyObject* args4 =  Py_BuildValue("({s:i,s:i})", "NGHIA", 123, "TRANG", 456);
    PyObject* args4 = PyDict_New();
	for (int i = 0; i < 10; i++) {
		std::stringstream ss;
		ss << i;
		std::string temp = "NEO" + std::string(ss.str());
		PyDict_SetItem(args4, Py_BuildValue("s", temp.c_str()), Py_BuildValue("i", i));
	}
	PyObject* args0 =  Py_BuildValue("({s:O})", "msg", args4);
	return args0;
}

static PyObject* secsgemdriver_show(PyObject* self, PyObject* args)
{
	PyObject *a;
	if(PyArg_UnpackTuple(args, "", 1, 1, &a))
	{
		printf("C++: show(%ld)\n", PyLong_AsLong(a));
	}

	return PyLong_FromLong(0);
}

/**
 * Test to get dict from python code
 *  Example:
 *  dictvalue = {"NEO": "NEOVALUE","NEO1": "NEOVALUE", "NEO2": "NEOVALUE", "NEO3": "NEOVALUE", "NEO4": "NEOVALUE", "NEO5": "NEOVALUE"}
	print(dictvalue)
	print(dictvalue["NEO"])
	secsgemdriver.getdict( dictvalue );
 */
static PyObject* secsgemdriver_getdict(PyObject* self, PyObject* args)
{
	printf("secsgemdriver_getdict self=%x %x %d %d \n", self, args, PyDict_Check(self), PyDict_Check(args));
	//PyObject* some_py_dict = args;
	PyObject *some_py_dict;
	if(!PyArg_UnpackTuple(args, "(items)", 1, 1, &some_py_dict))
	{
		printf("C++: error parse tuple\n");
		PyObject* args0 =  Py_BuildValue("({s:s})", "msg", "getdict must pass the tuple");
		return args0;
	}

	std::map<std::string, std::string> as_map;

	printf("PyDict_Keys \n");
	// first get the keys
	PyObject* keys = PyDict_Keys(some_py_dict);

	printf("PyList_Size %x \n", keys);
	size_t key_count = PyList_Size(keys);

	printf("key_count %d\n", key_count);
	// loop on the keys and get the values
	for(size_t i = 0; i < key_count; ++i)
	{
	    PyObject* key = PyList_GetItem(keys, i);
	    PyObject* item = PyDict_GetItem(some_py_dict, key);

		PyObject* reprKey = PyObject_Repr(key);
		PyObject* strKeyObj = PyUnicode_AsEncodedString(reprKey, "utf-8", "~E~");
		const char *strKey = PyBytes_AS_STRING(strKeyObj);

		PyObject* reprValue = PyObject_Repr(key);
		PyObject* strValueObj = PyUnicode_AsEncodedString(reprValue, "utf-8", "~E~");
		const char *strValue = PyBytes_AS_STRING(strValueObj);

		printf("%s -> %s\n", strKey, strValue);
	    as_map.insert( std::pair<std::string, std::string>(std::string(strKey), std::string(strValue)) );

	    Py_DECREF(key);
	    Py_DECREF(item);
	}

	Py_DECREF(keys);
	Py_DECREF(some_py_dict);

	PyObject* args0 =  Py_BuildValue("({s:s})", "msg", "OK");
	return args0;
}


static struct PyMethodDef methods[] = {
	{ "getdata", secsgemdriver_getdata, METH_VARARGS, "Returns the number"},
	{ "show", secsgemdriver_show, METH_VARARGS, "Show a number" },
	{ "printmsg", secsgemdriver_printmsg, METH_VARARGS, "Print string" },
	{ "getdict", secsgemdriver_getdict, METH_VARARGS, "Print string" },

	{ NULL, NULL, 0, NULL }
};

static struct PyModuleDef modDef = {
	PyModuleDef_HEAD_INIT, "secsgemdriver", NULL, -1, methods,
	NULL, NULL, NULL, NULL
};

static PyObject* PyInit_arnav(void)
{
	return PyModule_Create(&modDef);
}


int main()
{
	PyImport_AppendInittab("secsgemdriver", &PyInit_arnav);

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
//			PyObject* args4 =  Py_BuildValue("({s:i,s:i})", "NGHIA", 123, "TRANG", 456);

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

			CPyObject result = PyObject_CallObject(pFunc4, args0.getObject());
			if( result== NULL){

			}
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
//int main2()
//{
//	PyObject* pInt;
//
//	Py_Initialize();
//
//	PyRun_SimpleString("print('Hello World from Embedded Python!!!');\nprint('Neo')");
//
//	Py_Finalize();
//
//	printf("\nPress any key to exit...\n");
//	if(!_getch()) _getch();
//	return 0;
//}
