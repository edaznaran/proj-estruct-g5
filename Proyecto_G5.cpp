#include <iostream>
#include <iomanip>
#include <vector>
#include <stdio.h>
#include <string>
using namespace std;

struct compra
{
	int cod_producto;
	int cantidad;
	float subtotal;
	struct compra *sgte;
};
typedef struct compra *TpCompra; // para la compra del cliente

struct pedido
{
	int cod_pedido;
	string cliente;
	TpCompra compras; // Subcompras de un pedido
	float total;
	string estado;
	string motivo;
	struct pedido *sgte;
};
typedef struct pedido *TpPedido;

struct cliente
{
	string nombre;
	string contraseña;
	TpPedido pedidos; // Lista de pedidos de un cliente
	struct cliente *sgte;
};
typedef struct cliente *TpCliente;

struct producto
{
	string categoria;
	string nombre;
	int codigo;
	int stock;
	float precio;
	struct producto *sgte;
};
typedef struct producto *TpProducto; // para el catalogo de productos

void menu1()
{
	system("cls");
	cout << "\n\n\n\t\t BIENVENIDO A NUESTRA FARMACIA" << endl;
	cout << "\t\t===============================" << endl;
	cout << "\t1.- Iniciar sesion (Clientes)" << endl;
	cout << "\t2.- Registrar Clientes" << endl;
	cout << "\t3.- Iniciar sesion (Administrador)" << endl;
	cout << "\t4.- Mostrar cola de pedidos" << endl;
	cout << "\t0.- Salir" << endl
		 << endl;

	cout << "\tIngrese una opcion: [  ]\b\b\b ";
}

void menu2()
{
	cout << "\n\n\n\t\t CLIENTES" << endl;
	cout << "\t\t==========" << endl;
	cout << "\n\t1.- Solicitar pedido de compra" << endl;
	cout << "\t2.- Ver mis pedidos de compra" << endl;
	cout << "\t0.- Atras" << endl
		 << endl;

	cout << "\tIngrese una opcion: [  ]\b\b\b ";
}

void menu3()
{
	cout << "\n\n\n\t\t ADMINISTRADOR" << endl;
	cout << "\t\t===============" << endl;
	cout << "\n\t1.- Gestionar inventario" << endl;
	cout << "\t2.- Atender pedidos" << endl;
	cout << "\t0.- Atras" << endl
		 << endl;

	cout << "\tIngrese una opcion: [  ]\b\b\b ";
}

void menu4()
{
	cout << "\n\n\n\t\t INVENTARIO" << endl;
	cout << "\t\t============" << endl;
	cout << "\n\t1.- Agregar un producto" << endl;
	cout << "\t2.- Eliminar un producto" << endl;
	cout << "\t3.- Modificar precio de un producto" << endl;
	cout << "\t4.- Aumentar stock de un producto" << endl;
	cout << "\t0.- Atras" << endl
		 << endl;

	cout << "\tIngrese una opcion: [  ]\b\b\b ";
}

void menu5()
{
	cout << "\n\n\n\t\t PEDIDO" << endl;
	cout << "\t\t========" << endl;
	cout << "\t1.- Aprobar pedido" << endl;
	cout << "\t2.- Rechazar pedido" << endl;
	cout << "\t0.- Atras" << endl
		 << endl;

	cout << "\tIngrese una opcion: [  ]\b\b\b ";
}

void productosxdefecto(TpProducto &lista, string nombre, int codigo, float precio, int stock, string categoria)
{ // Agrega un producto por codigo
	TpProducto q = NULL, p = lista;
	q = new (struct producto);
	q->nombre = nombre;
	q->codigo = codigo;
	q->precio = precio;
	q->stock = stock;
	q->categoria = categoria;
	if (p == NULL)
	{
		q->sgte = lista;
		lista = q;
	}
	else
	{
		q->sgte = NULL;
		while (p->sgte != NULL)
			p = p->sgte;
		p->sgte = q;
	}
}

void insertarProductosxdefecto(TpProducto &productos)
{ // Lista est�tica de productos base
	productosxdefecto(productos, "Jabón antibacterial", 1001, 0.25, 10, "Cuidado Personal");
	productosxdefecto(productos, "Torta", 1002, 35, 10, "Aseo");
	productosxdefecto(productos, "Paracetamol 500mg (100 un)", 1003, 10.00, 10, "Medicamentos");
	productosxdefecto(productos, "Leche", 2001, 4.10, 10, "Limpieza");
	productosxdefecto(productos, "Queso", 2002, 10.4, 10, "Nutrición");
	productosxdefecto(productos, "Aspirina 100mg (10 un)", 3001, 6.00, 10, "Medicamentos");
	productosxdefecto(productos, "Aspirina Ultra 500mg (4 un)", 3002, 2.50, 10, "Medicamentos");
	productosxdefecto(productos, "Ibuprofeno 400mg", 3003, 10.50, 10, "Medicamentos");
	productosxdefecto(productos, "Chorizo", 3004, 9.5, 10, "Medicamentos");
	productosxdefecto(productos, "Huevo", 4001, 13.9, 10, "Otros");
	productosxdefecto(productos, "Cafe", 4002, 8.7, 10, "Otros");
	productosxdefecto(productos, "Chocolate", 4003, 14.9, 10, "Otros");
	productosxdefecto(productos, "Mantequilla", 2003, 2.4, 10, "Lacteos");
}

TpCliente validarCliente(TpCliente lista)
{ // Busca y devuelve un usuario de la lista
	TpCliente q = NULL;
	q = new (struct cliente);
	string usuario;
	cout << endl
		 << "\tUsuario: ",
		cin >> usuario;
	while (lista != NULL)
	{
		if (lista->nombre == usuario)
			return lista;
		lista = lista->sgte;
	}
	cout << endl
		 << "\tERROR: USUARIO NO ENCONTRADO" << endl
		 << endl;
	q->nombre = "";
	q->pedidos = NULL;
	q->contraseña = "";
	return q;
}

void vectorCategorias(TpProducto lista, vector<string> &categorias)
{ // Crea un vector con las categorias de la estructura lista
	int cond = 0;
	while (lista != NULL)
	{
		categorias.push_back(lista->categoria);
		lista = lista->sgte;
		while (cond != categorias.size())
		{
			cond = 0;
			for (int i = 0; i < categorias.size(); i++)
			{
				if (lista == NULL)
					return;
				if (lista->categoria == categorias[i])
				{
					lista = lista->sgte;
				}
				else
					cond++;
			}
		}
	}
}

string tab(string cadena)
{ // Ayuda para ordenar el catalogo
	if (cadena.size() > 7 && cadena.size() < 16)
	{
		return "\t\t\t";
	}
	else if (cadena.size() > 15 && cadena.size() < 24)
	{
		return "\t\t";
	}
	else if (cadena.size() > 23 && cadena.size() < 32)
	{
		return "\t";
	}
	else
	{
		return "\t\t\t\t";
	}
}

void mostrarCatalogo(TpProducto lista)
{
	vector<string> categorias;
	vectorCategorias(lista, categorias);
	TpProducto p = lista;
	cout << "\t\tLISTA DE PRODUCTOS" << endl
		 << endl;
	cout << "\tNOMBRE" << tab(lista->nombre) << "\t\tCODIGO\tSTOCK\tPRECIO" << endl;
	for (int i = 0; i < categorias.size(); i++)
	{
		cout << "[" << categorias[i] << "]" << endl;
		while (p != NULL)
		{
			if (p->categoria == categorias[i] && p->stock != 0)
			{
				cout << "\t" << p->nombre << tab(p->nombre) << p->codigo << "\t" << p->stock << "\tS/." << p->precio << endl;
			}
			p = p->sgte;
		}
		p = lista;
	}
}

float mostrarCarrito(TpCompra carrito)
{
	TpCompra p = carrito;
	float total_pedido = 0;
	if (carrito == NULL)
	{
		cout << "\n\t-vacio-\n";
		cout << endl;
	}
	else
	{
		cout << " +-------------------------------------------+" << endl;
		cout << " | " << left << setw(13) << "CODIGO"
			 << "| " << left << setw(10) << "CANTIDAD"
			 << "| " << left << setw(15) << "IMPORTE"
			 << "| " << endl;
		cout << " +-------------------------------------------+" << endl;
		while (p != NULL)
		{
			cout << " | " << left << setw(13) << p->cod_producto << "| " << left << setw(10) << p->cantidad << "| " << left << setw(15) << p->subtotal << "| " << endl;
			cout << " +-------------------------------------------+" << endl;
			total_pedido = total_pedido + p->subtotal;
			p = p->sgte;
		}
		cout << " | " << setw(25) << "COSTO TOTAL:"
			 << "| " << left << setw(15) << total_pedido << "|" << endl;
		cout << " +-------------------------------------------+" << endl
			 << endl;
	}
	return total_pedido;
}

bool verificarCod(TpProducto lista, int cod)
{
	TpProducto p = lista;
	while (p != NULL)
	{
		if (p->codigo == cod)
		{
			return false;
		}
		p = p->sgte;
	}
	return true;
}

TpProducto consultarProducto(TpProducto lista, int codigo)
{ // Retorna el producto buscado por codigo
	TpProducto p = lista;
	while (p != NULL)
	{
		if (p->codigo == codigo)
		{
			return p;
		}
		p = p->sgte;
	}
	return NULL;
}

void agregarCarrito(TpCompra &carrito, int cod, int cant, float subt)
{
	TpCompra p = carrito;
	// Creando el subpedido
	TpCompra q = NULL;
	q = new (struct compra);
	q->cod_producto = cod;
	q->cantidad = cant;
	q->subtotal = subt;
	q->sgte = NULL;
	// Cuando el carrito esta vacio
	if (carrito == NULL)
	{
		carrito = q;
		return;
	}
	// 1 o m�s elemento
	while (p->sgte != NULL)
	{
		p = p->sgte;
	}
	p->sgte = q;
}

TpPedido crearPedido(string cliente, float total, TpCompra carrito, int &id)
{
	// creamos un elemento de pedido, luego debe ser insertado en la lista de pedido
	TpPedido nuevo = NULL;
	nuevo = new (struct pedido);
	nuevo->cliente = cliente;
	nuevo->cod_pedido = 1000 + id;
	nuevo->compras = carrito;
	nuevo->total = total;
	nuevo->estado = "Pendiente";
	nuevo->motivo = "";
	nuevo->sgte = NULL;
	return nuevo;
}

void agregarPedido(TpPedido &lista, TpPedido pedido)
{
	// se agrega en la lista de pedidos, al final
	TpPedido p = lista;
	if (lista == NULL)
	{
		lista = pedido;
		return;
	}
	while (p->sgte != NULL)
	{
		p = p->sgte;
	}
	p->sgte = pedido;
}

void comprar(TpProducto &catalogo, TpPedido &cola_pedidos, TpCliente &cliente, int &id)
{
	TpProducto p = NULL;				// con esto recorremos el catalago
	TpProducto catalogotemp = catalogo; // el catalogo contiene una lista de productos (Tprod) con su stock
	TpCompra carro = NULL;
	TpPedido pedido = NULL, aux = NULL;

	int cod;
	int cant;
	float subt;
	float total;
	char mas;

	do
	{
		system("CLS");
		cout << "\t\tBIENVENIDO '" << cliente->nombre << "'" << endl
			 << endl;
		mostrarCatalogo(catalogotemp); // catalogotemp
		cout << endl
			 << "Tu Carrito:" << endl;
		mostrarCarrito(carro);
		do
		{
			cout << "-Codigo del Producto: ", cin >> cod;
			if (verificarCod(catalogotemp, cod)) // si el codigo es incorrecto
				cout << "\tPor favor, ingrese un codigo valido." << endl;
		} while (verificarCod(catalogotemp, cod)); // mientras el codigo sea incorrecto

		// p es una lista enlazada, que apunta al producto seleccionado del catalogo
		p = consultarProducto(catalogotemp, cod); // Retorna el producto seleccionado

		do
		{
			cout << "-Cantidad de " << p->nombre << " a comprar: ", cin >> cant;
			if (cant > p->stock) // si la cantidad solicitada supera al stock
				cout << "\tCantidad de " << p->nombre << " no disponible." << endl;
			if (cant <= 0) // si la cantidad solicitada es menor de cero
				cout << "\tPor favor, ingrese una cantidad valida." << endl;
		} while (cant > p->stock || cant <= 0);

		subt = p->precio * cant; // calculo del subtotal
		do
		{
			cout << " Desea comprar mas? [S = si/N = no]: ", cin >> mas;
			mas = toupper(mas);
		} while (mas != 'S' && mas != 'N');
		p->stock = p->stock - cant;				// recucimos stock
		agregarCarrito(carro, cod, cant, subt); // agregamos el producto al final del carrito(lista de producto)
	} while (mas != 'N');

	do
	{
		cout << " Esta seguro con su compra? [S/N]: ", cin >> mas;
		mas = toupper(mas);
	} while (mas != 'S' && mas != 'N');

	// agregando el pedido
	if (mas == 'S')
	{
		system("cls");
		cout << "\n\tTu Carrito Final:" << endl;
		cout << "\t=================" << endl;
		total = mostrarCarrito(carro);
		// actualiza el cat�logo
		catalogo = catalogotemp;
		id += 10;
		// mensaje
		//  nombre del cliente, total a pagar, carro de compra, id del pedido
		pedido = crearPedido(cliente->nombre, total, carro, id);
		aux = crearPedido(cliente->nombre, total, carro, id); // creamos el mismo pedido
		//  cliente->pedidos es una lista de pedidos del cliente, pedido es lo que debemos insertar en esa lista
		agregarPedido(cliente->pedidos, pedido);
		agregarPedido(cola_pedidos, aux); // a�adimos el mismo pedido a la cola general de pedidos
		cout << "\tSu pedido ha sido generado exitosamente.." << endl;
		cout << "\tEl codigo del actual pedido es " << pedido->cod_pedido << "." << endl;
	}
}

bool verificarCodPedido(TpPedido lista, int cod)
{
	TpPedido p = lista;
	while (p != NULL)
	{
		if (p->cod_pedido == cod)
		{
			return false;
		}
		p = p->sgte;
	}
	return true;
}

TpPedido consultarPedido(TpPedido lista, int codigo)
{
	TpPedido p = lista;
	while (p != NULL)
	{
		if (p->cod_pedido == codigo)
		{
			return p;
		}
		p = p->sgte;
	}
	return NULL;
}

void reabastecer_cancelado(TpCompra carrito, TpProducto &lista)
{ // Reabastecer productos si se cancela pedido
	TpProducto inventario = lista;
	while (carrito != NULL)
	{
		inventario = consultarProducto(lista, carrito->cod_producto);
		inventario->stock += carrito->cantidad;
		carrito = carrito->sgte;
	}
}

void cancelarPedido(TpProducto &productos, TpPedido &cola, TpCliente &cliente, int codigo, string motivo)
{
	TpPedido p = cola, q = NULL, t = cliente->pedidos;
	// Eliminamos de la cola
	if (p->cod_pedido == codigo)
	{
		cola = cola->sgte;
		delete (p);
	}
	else
	{
		while (p->cod_pedido != codigo)
		{
			q = p;
			q = p->sgte;
		}
		q->sgte = p->sgte;
		delete (p);
	}
	// Modificamos el estado en los pedidos del cliente
	if (t->cod_pedido == codigo)
	{
		reabastecer_cancelado(p->compras, productos);
		t->estado = "Cancelado";
		t->motivo = motivo;
	}
	else
	{
		while (t->cod_pedido != codigo)
		{
			t = t->sgte;
		}
		reabastecer_cancelado(p->compras, productos);
		t->estado = "Cancelado";
		t->motivo = motivo;
	}
}

int posicion_cola(TpPedido cola, int codigo)
{
	int pos = 1;
	TpPedido t = cola, p = NULL;
	if (t->cod_pedido == codigo)
	{
		pos = 1;
	}
	else
	{
		while (t->cod_pedido != codigo)
		{
			pos++;
			t = t->sgte;
		}
	}
	return pos;
}

void verPedidosxcliente(TpProducto &productos, TpPedido &cola_pedidos, TpCliente &cliente)
{
	int cod_pedido;
	char resp;
	TpPedido p = cliente->pedidos, q = NULL;
	if (p == NULL)
	{
		cout << "\n\t-vacio-\n";
		cout << endl;
		return;
	}
	cout << "\n\tESTADO\t\tCODIGO\tTOTAL";
	while (p != NULL)
	{
		if (p->estado == "Cancelado")
			cout << "\tMOTIVO";
		p = p->sgte;
	}
	p = cliente->pedidos;
	cout << endl;
	while (p != NULL)
	{
		cout << "\t" << p->estado;
		cout << "\t" << p->cod_pedido;
		cout << "\t" << p->total;
		if (p->estado == "Cancelado")
			cout << "\t" << p->motivo;
		cout << endl;
		p = p->sgte;
	}
	do
	{
		cout << "\n\tIngrese el codigo del pedido que desea ver [0:Cancelar] :", cin >> cod_pedido;
		if (cod_pedido == 0)
			return;
		if (verificarCodPedido(cliente->pedidos, cod_pedido))
			cout << "\tPor favor, ingrese un codigo valido." << endl;
	} while (verificarCodPedido(cliente->pedidos, cod_pedido));
	q = consultarPedido(cliente->pedidos, cod_pedido); // q se coloca en la posicion del pedido solicitado
	mostrarCarrito(q->compras);						   // mostramos la lista de productos que tiene ese pedido
	if (q->estado == "Pendiente")
	{
		cout << "\n\tEl orden de este pedido en la cola es: " << posicion_cola(cola_pedidos, cod_pedido) << endl;
		do
		{
			cout << "\tDesea cancelarlo? [S/N]: ", cin >> resp;
			resp = toupper(resp);
		} while (resp != 'S' && resp != 'N');
		if (resp == 'S')
		{
			cancelarPedido(productos, cola_pedidos, cliente, cod_pedido, "Por el cliente");
		}
	}
}

TpCliente nuevoCliente()
{
	TpCliente q = NULL;
	q = new (struct cliente);
	cout << endl;
	cout << "\tIngrese un nombre de usuario: ", cin >> q->nombre;
	cout << "\tIngrese una contrasena: ", cin >> q->contraseña;
	q->pedidos = NULL;
	cout << endl;
	return q;
}

void crearCliente(TpCliente &lista)
{
	TpCliente q = nuevoCliente(), p = lista;
	if (p == NULL)
	{
		q->sgte = lista;
		lista = q;
	}
	else
	{
		q->sgte = NULL;
		while (p->sgte != NULL)
			p = p->sgte;
		p->sgte = q;
	}
}

TpProducto nuevoProducto()
{ // Ingreso manual de producto
	TpProducto q = NULL;
	q = new (struct producto);
	cout << "\nIngresar Nombre: ", cin >> q->nombre;
	q->nombre[0] = toupper(q->nombre[0]);
	for (int i = 1; i < q->nombre.size(); i++)
	{
		q->nombre[i] = tolower(q->nombre[i]);
	}
	cout << "Ingresar Precio: ", cin >> q->precio;
	cout << "Ingresar Stock: ", cin >> q->stock;
	cout << endl;
	return q;
}

string elegirCategorias(TpProducto lista, int &codigo)
{ // Usuario escoge una categoria existente o creaci�n de una nueva
	vector<string> categorias;
	vectorCategorias(lista, categorias);
	TpProducto p = lista;
	string nombre;
	cout << "Categorias: ";
	for (int i = 0; i < categorias.size(); i++)
	{
		cout << "[" << categorias[i] << "]";
	}
	cout << "[+]" << endl
		 << endl;
	bool cond = false;
	while (cond == false)
	{
		cout << "Elija una categoria: ", cin >> nombre;
		if (nombre == "+")
		{
			cout << "\nNueva Categoria: ", cin >> nombre;
			codigo = 1000 * (categorias.size() + 1) + 1;
			cond = true;
		}
		nombre[0] = toupper(nombre[0]); // Primera letra en mayuscula
		for (int i = 1; i < nombre.size(); i++)
		{ // Las demas letra en minuscula
			nombre[i] = tolower(nombre[i]);
		}
		if (cond != true)
		{
			for (int i = 0; i < categorias.size(); i++)
			{
				if (nombre == categorias[i])
				{
					codigo = 1000 * (i + 1) + 1;
					while (p != NULL)
					{
						if (p->categoria == nombre)
							codigo++;
						p = p->sgte;
					}
					cond = true;
				}
			}
		}
	}
	return nombre;
}

void agregarProducto(TpProducto &lista)
{ // Agrega un producto por teclado
	TpProducto q = nuevoProducto(), p = lista;
	string categoria;
	categoria = elegirCategorias(lista, q->codigo);
	q->categoria = categoria;
	if (p == NULL)
	{
		q->sgte = lista;
		lista = q;
	}
	else
	{
		q->sgte = NULL;
		while (p->sgte != NULL)
			p = p->sgte;
		p->sgte = q;
	}
	cout << "\n[NUEVO] " << q->nombre << tab(q->nombre) << q->codigo << "\t" << q->stock << "\tS/." << q->precio << endl;
}

void eliminarProducto(TpProducto &lista)
{ //"Elimina" un producto bajando su stock a 0
	TpProducto p = lista;
	if (p == NULL)
	{
		cout << "[ERROR] No hay productos" << endl;
	}
	else
	{
		string nombre;
		mostrarCatalogo(lista);
		cout << endl
			 << "Ingrese nombre del producto a eliminar: ",
			cin >> nombre;
		nombre[0] = toupper(nombre[0]);
		for (int i = 1; i < nombre.size(); i++)
		{
			nombre[i] = tolower(nombre[i]);
		}
		while (p != NULL)
		{
			if (p->nombre == nombre)
			{
				p->stock = 0;
				return;
			}
			p = p->sgte;
		}
		cout << "[ERROR] Producto no existente..." << endl;
	}
}

void cambiarPrecio(TpProducto &lista)
{
	TpProducto p = lista;
	if (p == NULL)
	{
		cout << "[ERROR] No hay productos" << endl;
	}
	else
	{
		string nombre;
		float nuevoPrecio;
		mostrarCatalogo(lista);
		cout << "\nIngrese el nombre del producto a cambiar el precio: ";
		cin >> nombre;
		nombre[0] = toupper(nombre[0]);
		for (int i = 1; i < nombre.size(); i++)
		{
			nombre[i] = tolower(nombre[i]);
		}
		while (p != NULL)
		{
			if (p->nombre == nombre)
			{
				cout << "\n\t" << p->nombre << tab(p->nombre) << p->codigo << "\t" << p->stock << "\tS/." << p->precio << endl
					 << endl;
				cout << "> Ingrese nuevo precio: S/.";
				cin >> nuevoPrecio;
				p->precio = nuevoPrecio;
				cout << "\n[NUEVO] " << p->nombre << tab(p->nombre) << p->codigo << "\t" << p->stock << "\tS/." << p->precio << endl;
				return;
			}
			p = p->sgte;
		}
		cout << "[ERROR] Producto no existente..." << endl;
	}
}

void aumentarStock(TpProducto &lista)
{
	TpProducto p = lista;
	if (p == NULL)
	{
		cout << "[ERROR] No hay productos" << endl;
	}
	else
	{
		string nombre;
		int masStock;
		mostrarCatalogo(lista);
		cout << "\nIngrese el nombre del producto a aumentar stock: ";
		cin >> nombre;
		nombre[0] = toupper(nombre[0]);
		for (int i = 1; i < nombre.size(); i++)
		{
			nombre[i] = tolower(nombre[i]);
		}
		while (p != NULL)
		{
			if (p->nombre == nombre)
			{
				cout << "\n\t" << p->nombre << tab(p->nombre) << p->codigo << "\t" << p->stock << "\tS/." << p->precio << endl
					 << endl;
				cout << "> Ingrese cantidad de stock a aumentar: ";
				cin >> masStock;
				p->stock += masStock;
				cout << "\n[NUEVO] " << p->nombre << tab(p->nombre) << p->codigo << "\t" << p->stock << "\tS/." << p->precio << endl;
				return;
			}
			p = p->sgte;
		}
		cout << "[ERROR] Producto no existente..." << endl;
	}
}

void verPedidos(TpPedido cola_pedidos)
{
	TpPedido p = cola_pedidos;
	if (p == NULL)
	{
		cout << "\n\t-vacio-\n";
		cout << endl;
		return;
	}
	cout << "\tLISTA DE PEDIDOS POR ATENDER" << endl;
	cout << "\n\tCLIENTE"
		 << "\t\tCODIGO"
		 << "\tTOTAL" << endl;
	while (p != NULL)
	{
		cout << "\t" << p->cliente;
		cout << tab(p->cliente) << p->cod_pedido;
		cout << "\t" << p->total;
		cout << endl;
		p = p->sgte;
	}
}

void mostrarPedido(TpPedido pedido)
{
	if (pedido != NULL)
	{
		cout << "\n\t\tDESCRIPCION DEL PEDIDO" << endl
			 << endl;
		cout << "\tCodigo del pedido: " << pedido->cod_pedido << endl;
		cout << "\tCliente: " << pedido->cliente << endl
			 << endl;
		mostrarCarrito(pedido->compras);
	}
	else
	{
		cout << "\tNo hay pedidos que atender" << endl;
	}
}

TpCliente consultarCliente(TpCliente lista, string nombre)
{ // Retorna el cliente buscado por nombre
	TpCliente p = lista;
	while (p != NULL)
	{
		if (p->nombre == nombre)
		{
			return p;
		}
		p = p->sgte;
	}
}

void atenderPedido(TpPedido &cola, TpCliente &cliente, int codigo)
{
	TpPedido p = cola, q = NULL, t = cliente->pedidos;
	// Eliminamos de la cola
	if (p->cod_pedido == codigo)
	{
		cola = cola->sgte;
		delete (p);
	}
	else
	{
		while (p->cod_pedido != codigo)
		{
			q = p;
			q = p->sgte;
		}
		q->sgte = p->sgte;
		delete (p);
	}
	// Modificamos el estado en los pedidos del cliente
	if (t->cod_pedido == codigo)
	{
		t->estado = "Atendido";
	}
	else
	{
		while (t->cod_pedido != codigo)
		{
			t = t->sgte;
		}
		t->estado = "Atendido";
	}
}

void verPedidosCola(TpPedido cola_pedidos)
{
	int cod_pedido;
	TpPedido p = cola_pedidos, q = NULL;
	if (p == NULL)
	{
		cout << "\n\t-vacio-\n";
		cout << endl;
		return;
	}
	cout << "\n\tCLIENTE"
		 << "\t\tCODIGO"
		 << "\tTOTAL" << endl;
	while (p != NULL)
	{
		cout << "\t" << p->cliente;
		cout << tab(p->cliente) << p->cod_pedido;
		cout << "\t" << p->total;
		cout << endl;
		p = p->sgte;
	}
	do
	{
		cout << "\nIngrese el codigo del pedido que desea ver [0:Cancelar]:", cin >> cod_pedido;
		if (cod_pedido == 0)
			return;
		if (verificarCodPedido(cola_pedidos, cod_pedido))
			cout << "\tPor favor, ingrese un codigo valido." << endl;
	} while (verificarCodPedido(cola_pedidos, cod_pedido));
	q = consultarPedido(cola_pedidos, cod_pedido);
	mostrarCarrito(q->compras);
}

int main()
{
	TpCliente usuarios = NULL;
	TpProducto productos = NULL;
	TpCliente cliente = NULL;
	TpPedido cola = NULL;
	string pass;
	int ident = 0;
	int opc1, opc2, opc3, opc4;
	insertarProductosxdefecto(productos);
	do
	{
		menu1();
		cin >> opc1;
		switch (opc1)
		{
		case 1:
		{
			if (usuarios == NULL)
			{
				cout << endl
					 << "\tERROR: NO HAY USUARIOS REGISTRADOS" << endl
					 << endl;
				system("pause");
			}
			else
			{
				cliente = new (struct cliente);
				cliente = validarCliente(usuarios);
				if (cliente->nombre != "")
				{
					cout << "\tContrasena: ", cin >> pass;
					if (cliente->contraseña == pass)
					{
						cout << endl
							 << "\tAUTENTICACION EXITOSA! BIENVENIDO, " << cliente->nombre << endl
							 << endl;
						system("pause");
						do
						{
							system("cls");
							menu2();
							cin >> opc2;
							switch (opc2)
							{
							case 1:
								comprar(productos, cola, cliente, ident);
								break;
							case 2:
								verPedidosxcliente(productos, cola, cliente);
								break;
							}
							system("pause");
						} while (opc2 != 0);
					}
					else
					{
						cout << endl
							 << "\tERROR: NOMBRE DE USUARIO Y CONTRASENA NO COINCIDEN" << endl
							 << endl;
						system("pause");
					}
				}
				else
					system("pause");
			}
			break;
		}
		case 2:
		{
			crearCliente(usuarios);
			cout << "\tUSUARIO REGISTRADO EXITOSAMENTE!" << endl
				 << endl;
			system("pause");
			break;
		}
		case 3:
		{
			cout << "\tCONTRASENA: ";
			cin >> pass;
			if (pass == "1111")
			{
				do
				{
					system("cls");
					menu3();
					cin >> opc3;
					switch (opc3)
					{
					case 1:
						do
						{
							system("cls");
							menu4();
							cin >> opc4;
							switch (opc4)
							{
							case 1:
								system("cls");
								cout << "\t>>AGREGAR NUEVO PRODUCTO<<" << endl;
								agregarProducto(productos);
								break;
							case 2:
								system("cls");
								cout << "\t>>ELIMINAR PRODUCTO<<" << endl;
								eliminarProducto(productos);
								break;
							case 3:
								system("cls");
								cout << "\t   >>CAMBIAR PRECIO DE PRODUCTO<<" << endl;
								cambiarPrecio(productos);
								break;
							case 4:
								system("cls");
								cout << "\t   >>AUMENTAR STOCK A UN PRODUCTO<<" << endl;
								aumentarStock(productos);
								break;
							}
							cout << endl;
							system("PAUSE");
						} while (opc4 != 0);
						break;
					case 2:
						system("cls");
						verPedidos(cola);
						mostrarPedido(cola);
						if (cola != NULL)
						{ // si hay pedidos
							do
							{
								TpCliente temp = NULL;
								menu5();
								cin >> opc4;
								switch (opc4)
								{
								case 1:
								{ // atender pedido
									temp = consultarCliente(usuarios, cola->cliente);
									atenderPedido(cola, temp, cola->cod_pedido);
									opc4 = 0;
									break;
								}
								case 2:
								{ // cancelar pedido
									string motivo;
									cout << "Motivo por el cual : ";
									cin.ignore();
									getline(cin, motivo); // Respuesta al cliente
									temp = consultarCliente(usuarios, cola->cliente);
									cancelarPedido(productos, cola, temp, cola->cod_pedido, motivo);
									opc4 = 0;
									break;
								}
								}
							} while (opc4 != 0);
						}
						break;
					}
					system("PAUSE");
				} while (opc3 != 0);
			}
			else
			{
				cout << "\t[CONTRASENIA EQUIVOCADA]" << endl;
				system("pause");
			}
			break;
		}
		case 4:
		{
			verPedidosCola(cola);
			system("pause");
			break;
		}
		}
		system("cls");
	} while (opc1 != 0);
}