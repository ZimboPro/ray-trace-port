#include <check.h>
#include <rt.h>
#include <stdio.h>

t_obj test_setup() {
  char	**s;
	t_obj	obj;

  printf("Reading");
	s = ft_read("/home/leslie/sandbox/rust/ray-trace-port/rt_orig/cylinder_1");
	if (s != NULL)
	{
      printf("Checking");
		if (map_check(s) == 1)
		{
			obj = objects(s);
			obj_assign(&obj, s);
			ft_strarrdel(s);
      printf("Got values");
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
	t_color	p = trace_ray(obj, rv, 0, NULL);

  ck_assert(p.r == 0);
  ck_assert(p.g == 0);
  ck_assert(p.b == 0);
  // free(obj.objects);
  // obj.objects = NULL;
  // free(obj.lights);
  // obj.lights = NULL;
}END_TEST

START_TEST(RAY2) {
  t_obj obj = test_setup();
  t_ray rv = ray(obj, 160, 300);
	t_color	p = trace_ray(obj, rv, 0, NULL);

  ck_assert(p.r == 0);
  ck_assert(p.g == 0);
  ck_assert(p.b == 0);
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
    // tcase_add_test(tc_core, RAY1);
    // tcase_add_test(tc_core, RAY2);
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