/**
 *  @file   CurvatureTest.cpp
 *  @brief  Curvatureクラスのテストファイル
 *  @author Oiwane
 **/
#include "Curvature.h"
#include <gtest/gtest.h>

namespace etrobocon2019_test
{
	TEST(Curvature, Curvature_init)
	{
		double target = 0.010;
		Curvature curvature(target, 1.0, 0.0, 0.0);
	}

	TEST(Curvature, controlTest)
	{
		Controller controller;
		double target = 0.0;
		Curvature curvature(target, 1.0, 0.0, 0.0);

		double pidValue
			= curvature.control(controller.getLeftMotorCount(), controller.getRightMotorCount());

		ASSERT_DOUBLE_EQ(0.0, pidValue);
	}

	TEST(Curvature, controlTest2)
	{
		Controller controller;
		double target = 0.0;
		Curvature curvature(target, 1.0, 0.0, 0.0);

		for (int i = 0; i < 10; i++)
		{
			int pwm = 30;
			controller.setLeftMotorPwm(pwm);
			controller.setRightMotorPwm(pwm - 1);
			controller.tslpTsk(4);
		}

		double pidValue
			= curvature.control(controller.getLeftMotorCount(), controller.getRightMotorCount());

		ASSERT_LE(0.0, pidValue);
		ASSERT_LE(pidValue, 1.0);
	}
}// namespace etrobocon2019_test
