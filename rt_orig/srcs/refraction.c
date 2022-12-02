/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 08:07:34 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/13 13:47:33 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** checks to see which function to use
*/

t_ray	get_refract_ray(t_objects obj, t_ray ray, float d)
{
	t_ray	rfrt;

	if (obj.circle == 1)
		rfrt = rl_sphere(obj, ray, d);
	else if (obj.cone == 1)
		rfrt = rl_cone(obj, ray, d);
	else if (obj.cylinder == 1)
		rfrt = rl_cylinder(obj, ray, d);
	else
		rfrt = rl_plane(obj, ray, d);
	return (rfrt);
}

/*
 ** returns point and refractive ray for sphere
*/

t_ray	rl_sphere(t_objects obj, t_ray ray, float d)
{
	t_ray		rf;
	t_vector	n;
	float		c1;
	float		c2;
	float		nr;

	rf.sc = calc_vect_to_point(ray.sc, ray.v, (d * 1.00005));
	if (calc_p_dist(rf.sc, obj.c) > obj.rad)
		return ((t_ray){rf.sc, ray.v});
	n = calc_unit_v(calc_p_to_v(obj.c, rf.sc));
	c1 = -calc_dp(calc_unit_v(ray.v), n);
	nr = 1.000293 / ((float)obj.refract / 1000000);
	c2 = sqrt(1 - nr * nr * (1 - c1 * c1));
	rf.v = calc_unit_v(calc_addition(calc_multi(calc_unit_v(ray.v), nr),
			calc_multi(n, nr * c1 - c2)));
	int_circle(obj, &d, rf);
	rf.sc = calc_vect_to_point(rf.sc, rf.v, (d * 1.005));
	n = calc_unit_v(calc_p_to_v(obj.c, rf.sc));
	c1 = calc_dp(calc_unit_v(rf.v), n);
	nr = ((float)obj.refract / 1000000) / 1.000293;
	c2 = sqrt(1 - nr * nr * (1 - c1 * c1));
	rf.v = calc_unit_v(calc_addition(calc_multi(rf.v, nr), calc_multi(n, nr *
					c1 - c2)));
	return (rf);
}

/*
 ** returns point and refractive ray for cone
*/

t_ray	rl_cone(t_objects obj, t_ray ray, float d)
{
	t_coneh h;

	h.rf.sc = calc_vect_to_point(ray.sc, ray.v, (d * 1.05));
	h.n = calc_unit_v(cone_norm(obj, d * 1.05, ray));
	h.c1 = -calc_dp(calc_unit_v(ray.v), h.n);
	h.di = 1.000293 / ((float)obj.refract / 1000000);
	h.c2 = sqrt(1 - h.di * h.di * (1 - h.c1 * h.c1));
	h.rf.v = calc_unit_v(calc_addition(calc_multi(calc_unit_v(ray.v), h.di),
			calc_multi(h.n, h.di * h.c1 - h.c2)));
	d = -1;
	int_cone(obj, &d, h.rf);
	if (d == -1)
		return ((t_ray){h.rf.sc, ray.v});
	h.n = calc_unit_v(cone_norm(obj, d * 1.005, h.rf));
	h.c1 = calc_dp(calc_unit_v(h.rf.v), h.n);
	h.di = ((float)obj.refract / 1000000) / 1.000293;
	h.c2 = sqrt(1 - h.di * h.di * (1 - h.c1 * h.c1));
	h.rf.v = calc_unit_v(calc_addition(calc_multi(h.rf.v, h.di), calc_multi(h.n,
				h.di * h.c1 - h.c2)));
	d = -1;
	int_cone(obj, &d, h.rf);
	if (d != -1)
		return ((t_ray){h.rf.sc, ray.v});
	return (h.rf);
}

/*
 ** returns point and refractive ray for cylinder
*/

t_ray	rl_cylinder(t_objects obj, t_ray ray, float d)
{
	t_ray		rf;
	float		di;
	t_vector	n;
	float		c1;
	float		c2;

	rf.sc = calc_vect_to_point(ray.sc, ray.v, (d * 1.00005));
	n = calc_unit_v(cyl_norm(obj, d * 1.005, ray));
	c1 = -calc_dp(calc_unit_v(ray.v), n);
	di = 1.000293 / ((float)obj.refract / 1000000);
	c2 = sqrt(1 - di * di * (1 - c1 * c1));
	rf.v = calc_unit_v(calc_addition(calc_multi(calc_unit_v(ray.v), di),
			calc_multi(n, di * c1 - c2)));
	d = -1;
	int_cyl(obj, &d, rf);
	if (d == -1)
		return ((t_ray){rf.sc, ray.v});
	rf.sc = calc_vect_to_point(rf.sc, rf.v, (d * 1.005));
	n = calc_unit_v(cyl_norm(obj, d * 1.005, rf));
	c1 = calc_dp(calc_unit_v(rf.v), n);
	di = ((float)obj.refract / 1000000) / 1.000293;
	c2 = sqrt(1 - di * di * (1 - c1 * c1));
	rf.v = calc_unit_v(calc_addition(calc_multi(rf.v, di), calc_multi(n,
					di * c1 - c2)));
	return (rf);
}

/*
 ** returns point and refractive ray for plane
*/

t_ray	rl_plane(t_objects obj, t_ray ray, float d)
{
	t_ray		rf;
	t_vector	n;
	float		c1;
	float		c2;
	float		nr;

	rf.sc = calc_vect_to_point(ray.sc, ray.v, (d * 0.995));
	n = (t_vector){obj.dir.x, obj.dir.y, obj.dir.z, 0};
	if (calc_dp(n, ray.v) < 0)
		n = (t_vector){-obj.dir.x, -obj.dir.y, -obj.dir.z, 0};
	n = calc_unit_v(n);
	c1 = -calc_dp(calc_unit_v(ray.v), n);
	nr = 1.000293 / obj.refract;
	c2 = sqrt(1 - nr * nr * (1 - c1 * c1));
	rf.v = calc_unit_v(calc_addition(calc_multi(calc_unit_v(ray.v), nr),
			calc_multi(n, nr * c1 - c2)));
	int_plane(obj, &d, rf);
	rf.sc = calc_vect_to_point(rf.sc, rf.v, (d * 1.005));
	n = calc_unit_v((t_vector){-obj.dir.x, -obj.dir.y, -obj.dir.z, 0});
	c1 = -calc_dp(calc_unit_v(rf.v), n);
	nr = obj.refract / 1.000293;
	c2 = sqrt(1 - nr * nr * (1 - c1 * c1));
	rf.v = calc_addition(calc_multi(rf.v, nr), calc_multi(n, nr * c1 - c2));
	return (rf);
}
