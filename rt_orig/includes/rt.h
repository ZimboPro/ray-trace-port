/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 08:35:27 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/27 16:30:29 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <SDL2/SDL.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <pthread.h>
# include "libft.h"

# define PIXEL_RATIO 200
# define AMB 0.20
# define DEPTH 10
# define FT_RAND_MAX 20
# define FT_RAND_MIN -20
# define ROTATE 1
# define DIST 100
# define TAU 2 * M_PI
# define OBJI obj.objects[obj.i]

/*
 ** x and y coordinates
*/

typedef struct	s_pixel
{
	int			x;
	int			y;
}				t_pixel;

/*
 ** rgb color
*/

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

/*
 ** used in quadratic formula for intersection
*/

typedef struct	s_quad
{
	float		a;
	float		b;
	float		c;
	float		t1;
	float		t2;
}				t_quad;

/*
 ** components of vecotrs and points
*/

typedef struct	s_vector
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vector;

/*
 ** renaming vector to point for  differentiating
*/

typedef t_vector	t_point;

/*
 ** the data stored of objects
*/

typedef struct	s_objects
{
	int			circle;
	int			cylinder;
	int			cone;
	int			plane;
	int			texture;
	t_point		c;
	float		h;
	float		rad;
	t_color		col;
	t_vector	dir;
	float		reflect;
	int			refract;
	int			pattern;
	int			filter;
	char		*texmap;
}				t_objects;

/*
 ** camera data
*/

typedef struct	s_camera
{
	int			mode;
	int			width;
	int			height;
	float		dist;
	float		ar;
	float		scale;
	float		xdeg;
	float		ydeg;
	t_point		c;
	t_vector	view;
	t_vector	up;
	t_vector	hor;
	float		h_fov;
	float		v_fov;
	t_color		bg;
}				t_camera;

/*
 ** light data
*/

typedef struct	s_light
{
	int			total;
	t_point		c;
}				t_light;

/*
 ** ray data, a vector and point of origin
*/

typedef struct	s_ray
{
	t_point		sc;
	t_vector	v;
}				t_ray;

/*
 ** sturcts that contains world data
*/

typedef struct	s_obj
{
	float		d;
	int			obj_total;
	int			light;
	int			progress;
	int			first;
	t_objects	*objects;
	t_camera	camera;
	t_light		*lights;
	int			i;
}				t_obj;

/*
 ** the color and cordinates of a specific pixel
*/

typedef struct		s_pix_colors
{
	t_color			c;
	t_pixel			p;
}					t_pix_colors;

/*
 ** data needed for multithreads
*/

typedef struct		s_temp
{
	size_t			len;
	size_t			size;
	t_pix_colors	*img;
	t_obj			*obj;
	SDL_Renderer	*ren;
	int				x_b;
	int				y_b;
	int				x_e;
	int				y_e;
}					t_temp;

typedef struct	s_texmap
{
	Uint8		bpp;
	float		phi;
	float		theta;
	float		u;
	float		v;
	int			height;
	int			width;
	Uint8		*p;
	Uint32		pixelcol;
	t_color		col;
	Uint8		red;
	Uint8		green;
	Uint8		blue;
	Uint8		alpha;
}				t_texmap;

typedef struct	s_noise
{
	int		x_int;
	int		y_int;
	float	x_frac;
	float	y_frac;
	int		s;
	int		t;
	int		u;
	int		v;
	float	low;
	float	high;
	float	xa;
	float	ya;
	float	amp;
	float	fin;
	float	div;
}				t_noise;

typedef struct	s_tex
{
	float		tex_x;
	float		tex_y;
	float		scale_s;
	float		scale_t;
	float		s;
	float		t;
	float		pattern;
	float		angle;
}				t_tex;

/*
 ** reading map and checking if it is valid
*/

typedef struct	s_cart
{
	int			k;
	int			i;
	float		j;
	float		tmp;
	t_color		co;
	t_vector	l;
}				t_cart;

typedef struct	s_traceh
{
	int		i;
	float	f;
	t_color	p_c;
	t_color	rlc;
	t_ray	temp;
}				t_traceh;

typedef struct	s_coneh
{
	t_ray		rf;
	float		di;
	t_vector	n;
	float		c1;
	float		c2;

}				t_coneh;

typedef struct	s_colh
{
	t_color	p_c;
	t_color	rlc;
	t_ray	temp;
	float	f;
}				t_colh;

typedef struct	s_prog
{
	int		x;
	int		y;
	int		p_s;
	int		p_e;
	int		p_h;
	int		t;
}				t_prog;
void			sequence(char *str);
void			update_pos(t_obj *obj, int *draw, int dir);
void			ft_eventloop(SDL_Event event, int *loop, t_obj *obj, int *draw);
char			**ft_read(char *str);
int				map_check(char **str);
int				cnt_space(char *str, int *i, int *chk, int value);
void			check_circle(char **str, int i, int *chk);
void			check_cone(char **str, int i, int *chk);
void			check_cylinder(char **str, int i, int *chk);
void			check_plane(char **str, int i, int *chk);
void			ft_evn(int *loop, t_obj *obj, int *draw);
void			check_camera(char **str, int i, int *chk);
void			check_light(char **str, int i, int *chk);
int				valid_count(int c, int l, int o);
int				valid(char **str);
int				map_check(char **str);

/*
 ** assigns values to array
*/

t_obj			objects(char **str);
void			obj_assign(t_obj *obj, char **str);
int				ft_cnt(char *str);
void			ft_circles(t_objects *obj, char **str, int i, int *j);
void			ft_cones(t_objects *obj, char **str, int i, int *j);
void			ft_cylinders(t_objects *obj, char **str, int i, int *j);
void			ft_planes(t_objects *obj, char **str, int i, int *j);
t_light			*ft_lights(int len, char **str);
t_camera		ft_camera(char **str);
void			camera_corners(t_camera *cam);
t_point			ft_rand(t_point p);

/*
 ** ray tracer starts here and progress bar
*/

void			ft_draw(t_obj *obj, SDL_Renderer *ren);
void			cartoon_draw(t_obj *obj, SDL_Renderer *ren);
void			ft_point(t_pix_colors *img, size_t len, SDL_Renderer *ren);
t_vector		normal(t_objects obj, float d, t_ray ray);
t_vector		cyl_norm(t_objects obj, float d, t_ray ray);
t_vector		cone_norm(t_objects obj, float d, t_ray ray);
void			progress_update(t_obj *obj);
void			progress(t_obj *obj, SDL_Renderer *ren);

/*
 ** multithreading
*/

void			*threading(void *arg);
void			*cartoon_threading(void *arg);
t_temp			thr_init(t_obj *obj, SDL_Renderer *ren, int i);

/*
 ** creates matrices based on input
*/

float			**rotation(float x, float y, float z);
float			**translation(float tx, float ty, float tz);
float			**scale(float sx, float sy, float sz);

/*
 ** line algebra and matrix calculations
*/

float			calc_m(t_vector a);
float			calc_dp(t_vector a, t_vector b);
t_vector		calc_con(t_vector a, float **b);
float			**calc_trans(float **a, float **b);
float			calc_vector_ang(t_vector a, t_vector b);
t_vector		calc_addition(t_vector a, t_vector b);
t_vector		calc_cross_product(t_vector a, t_vector b);
t_vector		calc_coplanar(t_vector a, t_vector b);
t_point			calc_vect_to_point(t_point p, t_vector v, float m);
t_vector		calc_p_to_v(t_point a, t_point b);
float			calc_p_dist(t_point a, t_point b);
t_vector		calc_unit_v(t_vector a);
t_vector		calc_normal(t_vector v, t_point origin, t_point p);
void			calc_w_to_c(t_obj *obj);
t_vector		calc_multi(t_vector a, float d);
t_vector		rot_x(t_vector v, float r);
t_vector		rot_y(t_vector v, float r);

/*
 ** intersections of objects
*/

int				intersection(t_obj obj, float *d, t_vector v, t_point n);
t_ray			ray(t_obj obj, float x, float y);
void			int_circle(t_objects obj, float *d, t_ray ray);
void			int_cone(t_objects obj, float *d, t_ray ray);
void			int_cone_lid(t_ray obj, float *d, t_ray ray, float r);
void			int_cyl(t_objects obj, float *d, t_ray ray);
void			int_cyl_lid(t_ray obj, float *d, t_ray ray, float r);
void			int_plane(t_objects obj, float *d, t_ray ray);
float			**transf(t_vector v);

t_objects		pattern(t_objects object, t_vector n, t_ray rv);
float			perlin2d(float x, float y, float freq, int depth);
t_objects		texture(t_objects circ, t_ray rv, t_vector n);
t_color			sepia(t_color col);
t_color			filter(t_color col);
t_color			tex_map(SDL_Surface *surf, t_vector n);
float			modulo(float f);
float			checker(t_tex t);
t_color			marble(t_tex *t, t_vector n);
t_color			pattern_init(t_tex *t, t_vector n);
t_color	light_color(t_obj obj, t_ray n, int i);
/*
 ** gets object colors and shading if in normal mode
*/

t_color			get_color(t_obj obj, SDL_Renderer *ren, int n, t_ray v);
t_color			color_circle(t_obj obj, int  i, t_ray rv);
t_color			color_cylinder(t_obj obj, int n, t_ray v);
t_color			color_cone(t_obj obj, int n, t_ray v);
t_color			color_plane(t_obj obj, int n, t_ray v);
float			blinn_helper(t_obj obj, t_ray n, t_cart h);
t_color			blinn_phong(t_obj obj, t_ray n, int i, t_vector v);


/*
 ** recursice ray trace and fresnel equation if object is refractive
*/

t_color			trace_ray(t_obj obj, t_ray ray, int depth, SDL_Renderer *ren);
t_color			fresnel_equation(t_obj obj, int i, t_ray ray, int depth,
						SDL_Renderer *ren);
t_color			fresnel_effect(t_obj obj, t_ray ray, int depth,
						SDL_Renderer *ren);
float			fresnel(float n1, int n2, t_vector n, t_vector v);
t_color			trace_ray_cart(t_obj obj, t_ray ray, int depth,
						SDL_Renderer *ren);
t_color			fresnel_equation_cart(t_obj obj, int i, t_ray ray, int depth);
t_color			color_adjust(t_color a, float d);

/*
 ** gets the reflective point and direction of respective object
*/

t_ray			get_reflect_ray(t_objects obj, t_ray ray, float d);
t_ray			rf_sphere(t_objects obj, t_ray ray, float d);
t_ray			rf_cone(t_objects obj, t_ray ray, float d);
t_ray			rf_cylinder(t_objects obj, t_ray ray, float d);
t_ray			rf_plane(t_objects obj, t_ray ray, float d);

/*
 ** gets refractive ray and point of respective object
*/

t_ray			get_refract_ray(t_objects obj, t_ray ray, float d);
t_ray			rl_sphere(t_objects obj, t_ray ray, float d);
t_ray			rl_cone(t_objects obj, t_ray ray, float d);
t_ray			rl_cylinder(t_objects obj, t_ray ray, float d);
t_ray			rl_plane(t_objects obj, t_ray ray, float d);

/*
 ** gets object colors and shading if in cartoon mode
*/

void			cartoon_circle(t_obj obj, t_color *col, int i, t_ray ray);
void			cartoon_cone(t_obj obj, t_color *col, int i, t_ray ray);
void			cartoon_cylinder(t_obj obj, t_color *col, int i, t_ray ray);
void			cartoon_plane(t_obj obj, t_color *col, int i, t_ray ray);
t_color			get_cartoon_color(t_obj obj, SDL_Renderer *ren, int i,
					t_ray ray);
t_color			cartoon_color(t_obj obj, t_ray n, int i);
void			miss(SDL_Renderer *ren);

/*
 ** anti aliasing code and it's multithreading
*/

void			aa_seq(char *str);
void			ft_draw_aa(t_obj *obj, SDL_Renderer *ren);
void			*threading_aa(void *arg);
t_color			aa_col(t_obj obj, int x, int y, SDL_Renderer *ren);
void			cartoon_draw_aa(t_obj *obj, SDL_Renderer *ren);
void			*threading_cart_aa(void *arg);
t_color			aa_cartoon_col(t_obj obj, int x, int y, SDL_Renderer *ren);
void			interface(SDL_Renderer *ren);

#endif
