#pragma once

namespace Papyrus::Math
{
	inline int BinomialCoefficient(std::monostate,
		int a_n,
		int a_k)
	{
		int result{ 1 };

		for (int i = 1; i <= a_k; ++i) {
			result *= a_n - i + 1;
			result /= i;
		}

		return result;
	}

	inline float BinomialDistribution(std::monostate,
		int a_nTrials,
		float a_pChance,
		int a_kWins)
	{
		return BinomialCoefficient(std::monostate{}, a_nTrials, a_kWins) * static_cast<float>(pow(a_pChance, a_kWins) * pow(1 - a_pChance, a_nTrials - a_kWins));
	}

	inline float BinomialDistributionCumulative(std::monostate,
		int a_nTrials, 
		float a_pChance,
		int a_kWins)
	{
		float cumulativeProbability{ 0.0 };

		for (int i = 0; i <= a_kWins; ++i) {
			cumulativeProbability += BinomialDistribution(std::monostate{}, a_nTrials, a_pChance, i);
		}

		return cumulativeProbability;
	}

	inline float GaussianDistribution(std::monostate,
		float a_minValue,
		float a_maa_xValue)
	{
		if (a_minValue > a_maa_xValue) {
			std::swap(a_minValue, a_maa_xValue);
		} else if (a_minValue == a_maa_xValue) {
			return a_minValue;
		}

		float mean = (a_minValue + a_maa_xValue) / 2;
		float stdev = (a_maa_xValue - a_minValue) / 6;

		std::normal_distribution<float> dist(mean, stdev);

		std::chrono::system_clock::rep seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 generator(static_cast<unsigned int>(seed));

		float randomNumber = dist(generator);

		return randomNumber;
	}

	inline float LogAddExp(std::monostate,
		float a_xValue,
		float a_yValue)
	{
		if (a_xValue == -INFINITY) {
			return a_yValue;
		} else if (a_yValue == -INFINITY) {
			return a_xValue;
		} else if (a_xValue > a_yValue) {
			return a_xValue + log1p(exp(a_yValue - a_xValue));
		} else {
			return a_yValue + log1p(exp(a_xValue - a_yValue));
		}
	}

	inline float PoissonDistribution(std::monostate,
		float a_lambda,
		int a_kEvents)
	{
		float logProbability{ -a_lambda };

		for (int i = 1; i <= a_kEvents; i++) {
			logProbability += log(a_lambda / i);
		}

		return exp(logProbability);
	}

	inline float PoissonCumulativeProbability(std::monostate,
		float a_lambda,
		int a_kEvents)
	{
		float logSum{ -a_lambda };
		float term{ logSum };

		for (int i = 1; i <= a_kEvents; i++) {
			term += log(a_lambda / i);
			logSum = LogAddExp(std::monostate{}, logSum, term);
		}

		return exp(logSum);
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "BinomialCoefficient", BinomialCoefficient, true);
		a_vm.BindNativeMethod("Lighthouse", "BinomialDistribution", BinomialDistribution, true);
		a_vm.BindNativeMethod("Lighthouse", "BinomialDistributionCumulative", BinomialDistributionCumulative, true);
		a_vm.BindNativeMethod("Lighthouse", "GaussianDistribution", GaussianDistribution, true);
		a_vm.BindNativeMethod("Lighthouse", "LogAddExp", LogAddExp, true);
		a_vm.BindNativeMethod("Lighthouse", "PoissonDistribution", PoissonDistribution, true);
		a_vm.BindNativeMethod("Lighthouse", "PoissonCumulativeProbability", PoissonCumulativeProbability, true);

		logger::info("Math functions registered.");
	}
}
