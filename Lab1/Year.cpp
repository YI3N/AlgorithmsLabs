#include "Year.h"

int Year::GetNumber()
{
	return number;
}

int Year::GetNumberMAX()
{
	return numberMAX;
}

bool Year::GetGameOverState()
{
	return isGameOver;
}

void Year::SetSeed()
{
	if (seed == 0)
		seed = time(NULL);

	std::srand(seed);

	int toSkip = randomActions;
	while (toSkip > 0)
	{
		std::rand();
		toSkip--;
	}
}

void Year::IfPossibleProposeToLoad()
{
	std::ifstream save ("game.save");
	if (save)
	{
		save.close();
		if (HearYesOrNo("Вы бы хотели продолжить прерыдущую игру? д/н "))
			LoadGame();
		else
			std::remove("game.save");
	}
}

bool Year::ProposeToSave()
{
	if (HearYesOrNo("Вы бы хотели сделать перерыв? д/н "))
	{
		SaveGame();
		return true;
	}
	else
		return false;
}

void Year::SaveGame()
{
	std::ofstream save ("game.save");
	save << seed << "\n"
		<< randomActions << "\n"
		<< number << "\n"
		<< deathRatesSum << "\n"
		<< citizens << "\n"
		<< citizensStarved << "\n"
		<< citizensArrived << "\n"
		<< wheat << "\n"
		<< wheatHarvested << "\n"
		<< wheatHarvestedPerAcre << "\n"
		<< wheatEatenByRats << "\n"
		<< acres << "\n"
		<< acrePrice << "\n"
		<< plague;
	save.close();
}

void Year::LoadGame()
{
	std::string saveString;
	std::ifstream save ("game.save");
	if (save.is_open())
		save >> seed
		>> randomActions
		>> number
		>> deathRatesSum
		>> citizens
		>> citizensStarved
		>> citizensArrived
		>> wheat
		>> wheatHarvested
		>> wheatHarvestedPerAcre
		>> wheatEatenByRats
		>> acres
		>> acrePrice
		>> plague;
	save.close();
}

void Year::AboutTheYear()
{
	acrePrice = acrePriceMIN + (std::rand() % (acrePriceMAX - acrePriceMIN));

	std::cout << "Мой повелитель, соизвольте поведать вам,\n"
	"В " << number << " году вашего высочайшего правления...\n";
	if (number > 1)
		std::cout
		<< AboutCitizenShift()
		<< AboutPlague()
		<< "Население города составляет " << ProperOutputForm(citizens, "человек", "человека", "человек") << ";\n"
		<< AboutHarvest()
		<< AboutWheat()
		<< AboutAcres();
	else
		std::cout
		<< "В городе проживает " << citizens << " человек;\n"
		"В закромах города " << wheat << " бушелей пшеницы;\n"
		"Посевочные поля занимают " << acres << " акров земли;\n";
	
	std::cout << "1 акр земли сейчас стоит " << ProperOutputForm(acrePrice, "бушель", "бушеля", "бушелей") << ".\n";
}

std::string Year::AboutCitizenShift()
{
	if (citizensStarved == 0 and citizensArrived == 0)
		return "";

	std::string about = "";

	if (citizensStarved > 0)
	{
		about += ProperOutputForm(citizensStarved, "человек", "человека", "человек");
		if (citizensStarved == 1)
			about += " умер с голоду";
		else
			about += " умерли с голоду";
	}

	if (citizensArrived > 0)
	{
		if (about != "")
			about += ", и ";

		about += ProperOutputForm(citizensArrived, "человек", "человека", "человек");
		if (citizensArrived == 1)
			about += " прибыл в наш великий город";
		else
			about += " прибыли в наш великий город";
	}

	if (about != "")
		about += ";";
	about += "\n";

	return about;
}

std::string Year::AboutPlague()
{
	if (plague == false)
		return "";
	else
		return "Чума уничтожила половину населения; \n";
}

std::string Year::AboutHarvest()
{
	if (wheatHarvested > 0)
	{
		return "Мы собрали " + ProperOutputForm(wheatHarvested, "бушель", "бушеля", "бушелей") + " пшеницы, по "
			+ ProperOutputForm(wheatHarvestedPerAcre, "бушель", "бушеля", "бушелей") + " с акра;\n";
	}
	else
		return "В этот год мы остались без урожая;\n";
}

std::string Year::AboutWheat()
{
	std::string about = "";
	if (wheatEatenByRats > 0)
	{
		about += "Крысы истребили " + ProperOutputForm(wheatEatenByRats, "бушель", "бушеля", "бушелей") + " пшеницы";
		if (wheat > 0)
			about += ", оставив " + ProperOutputForm(wheat, "бушель", "бушеля", "бушелей") + " в амбарах;\n";
		else
			about += ", оставив нас без пропитания;\n";
	}
	else
	{
		if (wheat > 0)
			about += "В амбарах осталось" + ProperOutputForm(wheat, "бушель", "бушеля", "бушелей") + " пшеницы;\n";
		else
			about += "Амбары пустуют, мы остались без пропитания;\n";
	}
	return about;
}

std::string Year::AboutAcres()
{
	if (acres > 0)
		return "Посевочные поля занимают " + ProperOutputForm(acres, "акр", "акра", "акров") + " земли;\n";
	else
		return "Наши владения опустели, мы остались без земли для посева пшеницы;\n";
}

void Year::SetOrder()
{
	std::cout << "Что пожелаете, повелитель?\n";

	do
	{
		HearTheOrder(acresToBuy, "Сколько акров земли повелеваете купить? ");
		HearTheOrder(acresToSell, "Сколько акров земли повелеваете продать? ");
		HearTheOrder(wheatToEat, "Сколько бушелей пшеницы повелеваете съесть? ");
		HearTheOrder(acresToSow, "Сколько акров земли повелеваете засеять? ");
	} while (isOrderImpossible());
	std::cout << "\n";
}

void Year::HearTheOrder(int &order, std::string ask)
{
	std::string answer;

	std::cout << ask;
	std::cout << "\x1B[93m";
	std::cin >> answer;
	std::cout << "\033[0m";

	while (!isNumber(answer)) {
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "\033[F\33[2K\r";
		std::cout << ask;
		std::cout << "\x1B[93m";
		std::cin >> answer;
		std::cout << "\033[0m";
	}

	std::cin.ignore(256, '\n');
	order = std::stoi(answer);
}

bool Year::isOrderImpossible()
{
	bool isImpossible = acresToBuy * acrePrice - acresToSell * acrePrice + wheatToEat + acresToSow * acreSowPrice > wheat or acresToSow > acres - acresToSell + acresToBuy;

	if (isImpossible)
		std::cout << "О, повелитель, пощади нас! У нас только " << citizens << " человек, "
		<< wheat << " бушелей пшеницы и "
		<< acres << " акров земли!\n";

	return isImpossible;
}

void Year::YearPasses()
{
	wheat -= (acresToBuy * acrePrice - acresToSell * acrePrice + wheatToEat + acresToSow * acreSowPrice);

	acres += acresToBuy;
	acres -= acresToSell;

	SowAndHarvest();

	wheatEatenByRats = std::rand() % ((int)std::ceil(wheat * wheatRatShare) + 1);
	wheat -= wheatEatenByRats;

	FeastAndStarve();
	NewCitizensArrive();
	PlagueInfection();

	number++;
	if (number > numberMAX)
		isGameOver = true;

	randomActions += 4;
}

void Year::SowAndHarvest()
{
	wheatHarvestedPerAcre = wheatHarvestedPerAcreMIN + (std::rand() % wheatHarvestedPerAcreMAX);

	int citizensWorking = std::floor(acresToSow / citizenCanHandleAcres);
	if (citizensWorking > citizens)
	{
		int difference = citizensWorking - citizens;
		acresToSow -= difference * citizenCanHandleAcres;
		citizensWorking = citizens;
	}
	wheatHarvested = acresToSow * wheatHarvestedPerAcre;
	wheat += wheatHarvested;
}

void Year::FeastAndStarve()
{
	int citizensToFeed = std::floor(wheatToEat / citizenHungerForWheat);
	if (citizensToFeed < citizens)
		citizensStarved = citizens - citizensToFeed;
	else
		citizensStarved = 0;

	float deathRate = (float)citizensStarved / (float)citizens;
	deathRatesSum += deathRate;
	if (deathRate > lostConditionStarvation)
		isGameOver = true;

	citizens -= citizensStarved;
}

void Year::NewCitizensArrive()
{
	citizensArrived = citizensStarved / 2 + (5 - wheatHarvestedPerAcre) * wheat / 600 + 1;
	if (citizensArrived < 0)
		citizensArrived = 0;
	else if (citizensArrived > 50)
		citizensArrived = 50;

	citizens += citizensArrived;
}

void Year::PlagueInfection()
{
	if (std::rand() % 101 <= plaugueChance)
	{
		plague = true;
		citizens = std::floor(citizens / 2);
	}
	else
		plague = false;
}

void Year::ActIfGameOver()
{
	if (isGameOver == false)
		return;

	if (number <= 10)
		std::cout << "\x1B[31mРазозленные потерей родных и близких, народ устроил бунт и казнил вас.\033[0m\n\n";
	else if (number > numberMAX)
		GiveGrade();
}

void Year::GiveGrade()
{
	float averageDeathRate = deathRatesSum / numberMAX;
	int acresPerCitizen = acres / citizens;
	int grade = 0;

	if (averageDeathRate > averageDeathRateC)
		grade += 1;
	else if (averageDeathRate > averageDeathRateB)
		grade += 2;
	else if (averageDeathRate > averageDeathRateA)
		grade += 4;
	else
		grade += 6;

	if (acresPerCitizen < acresPerCitizenC)
		grade += 1;
	else if (acresPerCitizen < acresPerCitizenB)
		grade += 2;
	else if (acresPerCitizen < acresPerCitizenA)
		grade += 4;
	else
		grade += 6;

	if (grade <= 3)
		std::cout << "\x1B[91mИз-за вашей некомпетентности в управлении, народ устроил бунт и изгнал вас из города.\n"
		"Теперь вы вынуждены влачить жалкое существование в изгнании...\033[0m\n\n";
	else if (grade <= 7)
		std::cout << "\x1B[33mВы правили железной рукой, подобно Нерону и Ивану Грозному.\n"
		"Народ вздохнул с облегчением, и никто больше не желает видеть вас правителем.\033[0m\n\n";
	else if (grade <= 11)
		std::cout << "\x1B[96mВы справились вполне неплохо, у вас, конечно, есть недоброжелатели,\n"
		"но многие хотели бы увидеть вас во главе города снова!\033[0m\n\n";
	else
		std::cout << "\x1B[94mФантастика! Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше!\033[0m\n\n";
}

std::string ProperOutputForm(int number, std::string form1, std::string form2, std::string form5)
{
	std::string result = std::to_string(number);

	number = std::abs(number) % 100;
	int units = number % 10;
	if (number > 10 and number < 20) 
		return result + " " + form5;
	else if (units > 1 and units < 5)
		return result + " " + form2;
	else if (units == 1) 
		return result + " " + form1;
	else
		return result + " " + form5;
}

bool HearYesOrNo(std::string question)
{
	std::string answer;

	std::cout << "\x1B[92m";
	std::cout << question;
	std::cout << "\x1B[93m";
	std::cin >> answer;
	std::cout << "\033[0m";
	while (answer.size() != 1 or !((int)answer[0] == -92 or (int)answer[0] == -124 or (int)answer[0] == -83 or (int)answer[0] == -115)) {
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "\033[F\33[2K\r\x1B[92m";
		std::cout << question;
		std::cout << "\x1B[93m";
		std::cin >> answer;
		std::cout << "\033[0m";
	}
	std::cin.ignore(256, '\n');
	std::cout << "\n";

	if ((int)answer[0] == -92 or (int)answer[0] == -124)
		return true;
	else
		return false;
}

bool isNumber(std::string string)
{
	return !string.empty() and
		std::find_if(string.begin(), string.end(), [](char c) { return !std::isdigit(c) and !std::isspace(c); }) == string.end();
}