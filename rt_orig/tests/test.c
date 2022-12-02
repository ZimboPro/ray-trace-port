#include <check.h>
#include <rt.h>
#include <stdio.h>

t_obj test_setup() {
  char	**s;
	t_obj	obj;

	s = ft_read("/home/leslie/sandbox/rust/ray-trace-port/rt_orig/cylinder_1");
	if (s != NULL)
	{
		if (map_check(s) == 1)
		{
			obj = objects(s);
			obj_assign(&obj, s);
			ft_strarrdel(s);
			return obj;
			
		}
	}
  return obj;
}

START_TEST(RAY) {
  t_obj obj = test_setup();
  t_ray rv = ray(obj, 160, 200);
	t_color	p = trace_ray(obj, rv, 0, NULL);

  ck_assert_uint_eq(p.r,0);
  ck_assert_uint_eq(p.g,191);
  ck_assert_uint_eq(p.b,0);
  ck_assert_uint_eq(obj.camera.bg.r,0);
  ck_assert_uint_eq(obj.camera.bg.g,0);
  ck_assert_uint_eq(obj.camera.bg.b,0);
  // ck_assert(p.g == 0);
  // ck_assert(p.b == 0);
  // free(obj.objects);
  // obj.objects = NULL;
  // free(obj.lights);
  // obj.lights = NULL;
}END_TEST

START_TEST(RAY1) {
  t_obj obj = test_setup();
  t_ray rv = ray(obj, 160, 100);
  int i = intersection(obj, &(obj.d), rv.v, rv.sc);
  t_color p = get_color(obj, NULL, i, rv);

  ck_assert_uint_eq(p.r,0);
  ck_assert_uint_eq(p.g,255);
  ck_assert_uint_eq(p.b,255);
  // free(obj.objects);
  // obj.objects = NULL;
  // free(obj.lights);
  // obj.lights = NULL;
}END_TEST

START_TEST(RAY2) {
  t_obj obj = test_setup();
  t_ray rv = ray(obj, 160, 200);
  int i = intersection(obj, &(obj.d), rv.v, rv.sc);
  t_color p = get_color(obj, NULL, i, rv);

  ck_assert_uint_eq(p.r,0);
  ck_assert_uint_eq(p.g,191);
  ck_assert_uint_eq(p.b,0);
  ck_assert_uint_eq(i,2);
  ck_assert_uint_eq(obj.objects[i].plane,0);
  ck_assert_uint_eq(obj.objects[i].circle,1);
  ck_assert_uint_eq(obj.objects[i].cylinder,0);

  t_point		pt;
	t_objects	circ;
	t_vector	n;

	circ = obj.objects[i];
	pt = calc_vect_to_point(rv.sc, rv.v, (obj.d * 0.995));
  // ck_assert_float_eq(pt.x, -7117.7065);
  // ck_assert_float_eq(pt.y, -7117.71);
  // ck_assert_float_eq(pt.z, 0);
  // ck_assert_float_eq(pt.w, 0);

	n = calc_unit_v(calc_p_to_v(circ.c, pt));
  // ck_assert_float_eq(n.x, 0.928869);
  // ck_assert_float_eq(n.y, -0.00652354);
  // ck_assert_float_eq(n.z, 0.370351);
  ck_assert_float_eq(n.w, 0);
	// obj.objects[i] = texture(obj.objects[i], rv, n);
	if (obj.objects[i].reflect > 0) {

		t_color c = blinn_phong(obj, (t_ray){pt, n}, i, rv.v);
    ck_assert_uint_eq(c.r, 0);
  }
	 else  {
    t_color j = light_color(obj, (t_ray){pt, n}, i);
    ck_assert_uint_eq(j.r, 0);
    ck_assert_uint_eq(j.g, 191);
    ck_assert_uint_eq(j.b, 0);
   }
  // free(obj.objects);
  // obj.objects = NULL;
  // free(obj.lights);
  // obj.lights = NULL;
}END_TEST

START_TEST(RAY3) {
  t_obj obj = test_setup();
  t_ray rv = ray(obj, 320, 100);
	t_color	p = trace_ray(obj, rv, 0, NULL);

  ck_assert(p.r == 0);
  ck_assert(p.g == 0);
  ck_assert(p.b == 0);
  // free(obj.objects);
  // obj.objects = NULL;
  // free(obj.lights);
  // obj.lights = NULL;
}END_TEST

START_TEST(RAY4) {
  t_obj obj = test_setup();
  t_ray rv = ray(obj, 320, 300);
	t_color	p = trace_ray(obj, rv, 0, NULL);

  ck_assert(p.r == 0);
  ck_assert(p.g == 0);
  ck_assert(p.b == 0);
  // free(obj.objects);
  // obj.objects = NULL;
  // free(obj.lights);
  // obj.lights = NULL;
}END_TEST

START_TEST(RAY5) {
  float x =0;
  float y =0;
  t_obj obj = test_setup();
  while (y < obj.camera.height) {
    x = 0;
    while (x < obj.camera.width) {

      t_ray rv = ray(obj, x, y);
	    t_color	p = trace_ray(obj, rv, 0, NULL);
      char arr [60];
      sprintf (arr, "X: %2.f Y: %2.f", x, y);
      printf("R %d G%d B%d", p.r, p.g, p.b);
      ck_assert(p.r == 0);
      ck_assert(p.g == 0);
      ck_assert(p.b == 0);
      x++;
    }
    y++;
  }

}END_TEST

Suite * ray_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Ray");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, RAY);
    tcase_add_test(tc_core, RAY1);
    tcase_add_test(tc_core, RAY2);
    // tcase_add_test(tc_core, RAY3);
    // tcase_add_test(tc_core, RAY4);
    // tcase_add_test(tc_core, RAY5);
    suite_add_tcase(s, tc_core);

    return s;
}

 int main(void)
 {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = ray_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
 }