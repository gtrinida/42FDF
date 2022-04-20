// -Сделать через int
// -Переписать и разобрать
// void bressemham(float x, float y, float x1, float y1, fdf *data) //[1,1] [50, 20]
// {
// 	float x_step;
// 	float y_step;
// 	int max;
// 	x_step = x1 - x; //посчитали шаги для x = 49
// 	y_step = y1 - y; //посчитали шаги для y = 19
// 	max = max_steps(sign(x_step), sign(y_step)); //записываем в переменную max значение из 
//  функции max_steps, max_steps вернёт только то что больше если больше x то x если больше y то y | x = 49 
// 	x_step /= max; //49 = 49 : 49 = 1;
// 	y_step /= max; //19 = 19 : 49 = 0.38;
// 	// За один шаг x, y делает 0.38 следовательно после того как x сделает приблизительно 3 шага, y сделает 1; 
// 	while ((int)(x - x1) || (int)(y - y1)) // пока мы не дойдем до концечных точек
// 	{
// 		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0xffffff); //mlx_ptr указатель на ..., ,win_ptr указатель на окно, x и y - точки отрисовки, 0xffffff - цвет(белый)
// 		x += x_step; //1 = 1 + 1 / делает шаг
// 		y += y_step; //1 = 1 + 0.38// делает шаг на третьей итерации
// 	}
// }
void draw_lines(basic *pos, fdf *data)
{
	basic pos_tmp;
	float x_steps;
	float y_steps;
	int max;
	// int z;
	// int z1;
	
	// z = data->z_matrix[(int)pos->y, (int)pos->x];
	// z1 = data->z_matrix[(int)pos->y1, (int)pos->y];
	pos_tmp = *pos;
	//продумать zoom для различных размеров карт
	pos_tmp.x *= data->zoom;
	pos_tmp.x1 *= data->zoom;
	pos_tmp.y *= data->zoom;
	pos_tmp.y1 *= data->zoom;
	// data->color = (z) ? 0x80c0c : 0xffffff;
	x_steps = pos_tmp.x1 - pos_tmp.x;
	y_steps = pos_tmp.y1 - pos_tmp.y;
	max = max_steps(sign(x_steps), sign(y_steps));
	x_steps /= max;
	y_steps /= max;
	
	while ((int)(pos_tmp.x - pos_tmp.x1) || (int)(pos_tmp.y - pos_tmp.y1))
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, (int)pos_tmp.x, (int)pos_tmp.y, 0xffffff);//data->color);
		pos_tmp.x += x_steps;
		pos_tmp.y += y_steps;
	}
}