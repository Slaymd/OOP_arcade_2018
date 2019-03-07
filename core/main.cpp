/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/

int main(void)
{
	void *handle = dlopen(path, RTLD_LAZY);
	void (*entryPoint)(void);

	if (!handle)
		return (0);
	entryPoint = dlsym(handle, "entryPoint");
	(*entryPoint)();
	dlclose(handle);
	return (0);
}