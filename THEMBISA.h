///< THEMBISA.h
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>
//#using <mscorlib.dll>

using namespace std;


//=============================================================================
///< Parameters in the 'Projection' sheet & other settings
//=============================================================================

int StartYear = 1985;
int ProjectionTerm = 70; ///< Note that entering term of 10 will give you results in 1994
int CurrYear;
int CurrMonth; ///< 0 to 11


int FixedUncertainty = 1;
const int VaryFutureInterventions = 0; ///< 0 = fix the future rollout at Rollout.txt values
const int VaryFutureInterventionsTB = 0; ///< 0 = fix the future rollout at TBrollout.txt values
const int FixedARTinitiation = 0; ///< 1 = fix the rates of ART initiation at the values generated in
								  ///< the uncertainty analysis (only valid if FixedUncertainty = 1)
const int InputARTinitiationRates = 0; ///< 1 = specify rates of ART initiation in Rollout.txt
									   ///< 0 = specify numbers starting ART in Rollout.txt
const int PropnalImmART = 1; ///< 1 if immediate ART start is proportional to later rate of ART start
const int ExcludeInterrupters = 1; ///< 1 = exclude temporary ART interrupters when calculating
								   ///< numbers currently on ART
const int UseNumbersTests = 1; ///< 1 = calculate rates of testing from numbers of HIV tests
const int ProvModel = 0; ///< 1 if modelling a province, 0 for national model | remember to set CalibHCTprevP=0, CalibHCTtotP=0 for provincial
string ProvID = "EC"; ///< Choose from EC, FS, GT, KZ, LM, MP, NC, NW, WC
const int UseBrassLogit = 0; ///< 1 if using Brass relational logit to get non-HIV mort over 1996-2018
int PrEPorVM = 0; ///< 1 if allowing for PrEP or vaginal microbicides. Keep set to 0 as default; it
				  ///< will automatically get recalculated if there is PrEP/VM rollout.
const int IncludeTB = 1;//< 1 if including TB simulations // MK edits
const int IncludeDR_TB = 0; ///< 1 if including drug-resisant (DR) TB 
const int FixedTBscreening = 0; ///< 1 = fix the rates of TB screening at the values generated in
								///< the uncertainty analysis (only valid if FixedUncertainty = 1)
double RRtestingDiagnosed = 1.0; ///< Relative rate of consent to testing if individual is diagnosed
								 ///< positive (relevant in calibration to HSRC data)

const int CalibPaedPrev = 0;
const int CalibAdultPrev = 1; ///< 1 = calibrate to adult HIV prevalence data from HSRC & DHS surveys
const int CalibANCprev = 1; ///< 1 = calibrate to HIV prevalence data from antenatal surveys
const int InclANCpre1997 = 1; ///< 1 = include ANC prevalence data prior to 1997
const int InclAS_ANCprov = 1; ///< 1 = include age-specific ANC prevalence data in prov calibration
const int CalibYouthPrev = 0; ///< 1 = include HIV prevalence for 15-24 year olds
const int CalibFSWprev = 1; ///< 1 = calibrate to HIV prevalence data from sex worker surveys
const int CalibMSMprev = 1; ///< 1 = calibrate to HIV prevalence data from MSM surveys
const int CalibPWIDprev = 0; ///< 1 = calibrate to HIV prevalence data from PWID surveys
const int CalibCD4 = 0; ///< 1 = calibrate to CD4 distributions in household/workforce surveys
const int CalibCD4ANC = 0; ///< 1 = calibrate to CD4 distributions in antenatal surveys
const int CalibHCT_HH = 1; ///< 1 = calibrate to propn ever tested in HSRC surveys
const int CalibHCT_ANC = 0; ///< 1 = calibrate to propn ever tested in antenatal surveys
const int CalibHCTprev = 1; ///< 1 = calibrate to HIV prevalence in adults receiving HCT
const int CalibHCTprevP = 1; ///< 1 = calibrate to HIV prevalence in children receiving HCT - set =0 for province model, was =1 for national
const int CalibHCTtotP = 0; ///< 1 = calibrate to recorded number of kids receiving HCT -  set =0 for province model, was =0 for national
const int CalibHCTageSex = 0; ///< 1 = calibrate to proportions tested by age/sex and prev by age/sex
const int CalibDeathsA = 1; ///< 1 = calibrate to recorded numbers of adult deaths
const int AgeLimitMortCalib = 60; ///< Death data below this age are used in mort calibration
								  ///< Should be multiple of 5 (set to 95 if all ages included)
const int CalibDeathsP = 1; ///< 1 = calibrate to recorded numbers of paediatric deaths
const int CalibAIDStrend = 0; ///< 1 = calibrate to reported new AIDS cases in adults (1990-4)
const int CalibAIDSage = 0; ///< 1 = calibrate to reported new AIDS cases by age and sex (1993-4)
const int CalibARTtotals = 0; ///< 1 = calibrate to reported total numbers of ART patients
const int CalibARTtotalsP = 0; ///< 1 = calibrate to reported total numbers of children on ART
const int CalibCD4atARTstart = 0; ///< 1 = calibrate to recorded # starting ART by CD4 (WC only)
const int CalibARTbyAge = 1; ///< 1 = calibrate to age distribution of adults on ART
const int CalibARTbyAgeP = 0; ///< 1 = calibrate to age distribution of kids starting ART
const int CalibARTbyAgeP2 = 0; ///< 1 = calibrate to age distribution of kids on ART
const int CalibChildPIP = 0; ///< 1 = calibrate to child deaths in facilities
const int CalibARTcoverage = 1; ///< 1 = calibrate to ARV metabolite data
const int CalibMarriageData = 0; ///< 1 = calibrate to marriage data
const int CalibANC_ART = 0; ///< 1 = calibrate to % of HIV+ ANC attenders previously on ART
const int CalibAHDpaedART = 0; ///< 1 = calibrate to % of kids starting ART w severe immunodeficiency

const int CalibTBdeathsA = 0; ///< 1 = calibrate to recorded TB deaths in adults
const int CalibTBdeathsPLHIV = 0; ///< 1 = calibrate to expected TB deaths in HIV-pos adults
const int CalibETRdeathsA = 0; ///< 1 = calibrate to recorded death rate in treated TB patients
const int CalibTBcasesA = 0; ///< 1 = calibrate to recorded # treated TB cases in adults
const int CalibTBdiagnosesA = 0; ///< 1 = calibrate to adult TB microbiological tests
const int CalibHIVprevETR = 0; ///< 1 = calibrate to HIV prev data in adult TB cases
const int CalibTBprev = 0; ///< 1 = calibrate to adult TB prevalence survey data
const int CalibRifResPropn = 0; ///< 1 = calibrate to % of TB cases that are rifampicin-resistant
const int CalibSmPosHH = 0; ///< 1 = calibrate to TB prevalence survey data on smear-pos propn
const int CalibRRscreen = 0; ///< 1 = calibrate to RR screening in TB symptomatic patients
const int CalibTB_HIV_OR = 0; ///< 1 = calibrate to odds ratios of HIV-TB associations

//=============================================================================
///< Parameters in the 'AdultAssumps' file
//=============================================================================

///< Sexual behaviour assumptions

///< (a) Partnership formation, sexual debut, mixing
double HighRiskPropn[2]; ///< % of adults in high risk group, by sex
double PartnerRate20F; ///< rate of partnership formation in 20-year old unmarried women in high risk
double RRpartnerLow[2]; ///< relative rate of partnership formation in low risk group
double RRpartnerMarried[2]; ///< relative rate of partnership formation in married high risk group
double GammaMeanF; ///< partnership formation age adjustment factor: gamma mean
double GammaSDF; ///< partnership formation age adjustment factor: gamma standard deviation
double IncreaseGammaMeanF; ///< Factor by which mean increases, comparing 2016 to 1998
double DebutMedian[2]; ///< Median age at start of sexual activity in high risk group
double DebutLow[2]; ///< relative rate of starting sexual activity in low risk group
double DebutShape[2]; ///< Log-logistic shape parameter for rate of starting sexual activity
double MeanAgeDif; ///< Mean age difference in short-term relationships (years)
double SDageDif; ///< Standard deviation of age difference in short-term relationships
double MeanAgeDifLT; ///< Mean age difference in long-term relationships (years)
double SDageDifLT; ///< Standard deviation of age difference in long-term relationships
double Assortativeness; ///< Assortativeness of sexual mixing (0 = completely assortative, 1 = random)
double MarriageConstant[3]; ///< Scale parameter for log-logistic distribution (M, F, MSM)
double MarriageTrend[3]; ///< Effect of birth cohort on log-logistic distribution (M, F, MSM)
double MarriageShape[3]; ///< Shape parameter for log-logistic distribution (M, F, MSM)
double MarriageMin[3]; ///< Minimum age at which marriage can occur (M, F, MSM)
double DivorceAdj; ///< Multiplier applied to empirically-derived rates of union dissolution
double DivorceTrend; ///< Annual change in rates of union dissolution (multiplier)
double ORremarriage[3]; ///< Odds of remarriage in recently divorced/widowed, relative to never-married
double RRmarriageMSM[3]; ///< RR of marriage in MSM up to 2006, 2007-2010 and post-2010

///< (b) Commercial sex
double FSWageAlpha; ///< Alpha parameter for gamma distribution of FSW ages
double FSWageLambda; ///< Lambda parameter for gamma distribution of FSW ages
double ClientsPA; ///< Number of sex acts with clients per annum
double FSWcontactAge21; ///< Annual # contacts with FSW for unmarried high risk male aged 21
double FSWcontactMarried; ///< Relative rate of visiting FSWs in married men
double FSWcontactMean; ///< FSW contact age adjustment factor: gamma mean
double FSWcontactSD; ///< FSW contact age adjustment factor: gamma standard deviation
double FSWcontactAlpha; ///< Alpha parameter for gamma distribution of FSW contact rates
double FSWcontactLambda; ///< Lambda parameter for gamma distribution of FSW contact rates

///< (c) Coital frequencies and condom use
double SexActsST; ///< Average # sex acts per short-term relationship
double SexActsLT; ///< Average monthly frequency of sex for married women aged 20
double RelFreqSexAge; ///< Relative freq of sex in marital relationships, per 20-yr increase in age
double AgeEffectCondom; ///< Redn in log odds of condom use per yr of increase in age
double RRcondomMarital; ///< OR of condom use in LT relationships relative to ST relationships
double ORcondomFSW; ///< OR of condom use in FSW-client contacts relative to ST relationships
double InitCondom; ///< Initial condom use in 1985 (women aged 20 in ST relationships)
double CondomBias; ///< Condom reporting bias parameter (0 = no bias, 1 = maximum bias)
double CondomAdjProv; ///< Constant multiplier for specific province (1 for national)
double RRcondomContracep; ///< RR of reporting of condom use for contraceptive purposes
double IncrCondomBCC; ///< Increase in condom use due to behaviour change communication (BCC) programmes
double RiskCompensation; ///< Change in condom use due to risk compensation in recent years
double MedianCondomBCC; ///< Median time to increase in condom use following BCC
double ShapeCondomBCC; ///< Shape parameter for time to increase in condom use following BCC

///< (d) Effect of HIV and knowledge of HIV status
double VCTcondom; ///< Reduction in propn of sex acts that are unprotected after HIV diagnosis
double VCT_FSWentry; ///< Reduction in entry into sex work after HIV diagnosis
double ARTcondom; ///< Reduction in propn of sex acts that are unprotected after ART initiation
double HIVeffectSex[4]; ///< Reduction in freq of sex by HIV disease stage
double HIVeffectFSWentry[4]; ///< Reduction in rate of entry into commercial sex, by HIV disease stage
double HIVeffectFSWexit[4]; ///< Increase in rate of exit from commercial sex, by HIV disease stage

///< HIV transmission assumptions (sexual)

double InitFSWprev; ///< Initial HIV prevalence in FSWs and high risk group, ages 15-49
double MaxInitFSWprev; ///< Maximum initial HIV prevalence in FSWs and high risk group, ages 15-49
double TransmST[2]; ///< Transm prob per act of unprotected sex with infected ST partner, by sex
					///< of susceptible partner (0 ==> F-to-M transmission prob)
double TransmLT[2]; ///< Transm prob per act of unprotected sex with infected LT partner
double TransmFSW[2]; ///< Transm prob per act of unprotected sex between FSW and client
double RRclientToFSW1985; ///< RR client-to-FSW transmission in 1985 compared to 1995
double EctopyEffect[2]; ///< Increase in transm prob, per yr of age below 25 (M and F)
double RelInfecRiskST[2][2][2]; ///< Relative infectiousness by risk of M (1st index), risk of F
								///< (2nd index) and sex of susceptible partner (3rd index), in ST rels
double RelInfecRiskLT[2][2][2]; ///< Relative infectiousness in LT relationships
double RelInfecStage[5]; ///< Relative infectiousness by HIV stage
double MedianVLuntreated200; ///< Median VL (log scale) prior to ART initiation at CD4 <200
double ShapeVL; ///< Weibull shape parameter for distribution of viral loads (log scale) /
				///< modifier for effect of VL of HIV infectiousness
double ShapeVL50; ///< Weibull shape parameter that applies at low VL (only relevant for VLS<50 output)
double VLeffectInfectivity; ///< Increase in HIV infectiousness per unit increase in log of VL (at 4 log)
double VLdifPer100CD4[2]; ///< Decrease in VL per 100-unit increase in baseline CD4 count (M, F)
double ORsuppressionIeDEA; ///< Ratio of odds of viral suppression, to that in IeDEA-SA cohorts
double ORsuppressionCD4[4][2][2]; ///< OR for VLS by baseline CD4 category, sex, age (15-24, 50+)
double ORsuppressionPWID; ///< OR for VLS in PWID compared to age- & sex-matched ART patients
double ARTinfectivity[4][2][81]; ///< Relative infectivity after ART start, by CD4, sex, age
double CondomEfficacy; ///< Condom efficacy in preventing transmission, per act of sex
double DiscordantPropn; ///< % of individuals married to HIV+ partners, who are HIV-negative
double InfToVirulenceRatio; ///< Ratio of increase in infectivity to increase in virulence, per unit
							///< increase in log VL, on ln scale

///< HIV survival assumptions

double CD4decline[3]; ///< Rate of transition to next CD4 stage
double CD4duration[4]; ///< Average time to next CD4 stage
double RRmort200to350; ///< Ratio of untreated mort at CD4 200-349 to that at CD4 <200
double CD4mort[2]; ///< HIV mortality rate in last 2 CD4 stages
double OIincidence[6]; ///< Annual OI incidence rate by CD4 stage
double WHO4incidence[5]; ///< Annual incidence of WHO stage IV-defining conditions
double PTBincidence[5]; ///< Annual incidence of pulmonary TB by CD4 stage
double RR_ARTinitiation[5]; ///< Rate of ART initiation (relative to CD4 <200) if eligible
double Haemodilution[4]; ///< Propn of pregnant women with CD4 reduced to next stage due to haemodilution
double RRper10yr; ///< Increase in rate of CD4 decline and HIV mortality per 10 yr increase in age
double RRperCalYr; ///< Increase in rate of CD4 decline per calendar year
double RRuntreatedMortF; ///< Rate of CD4 decline & mort in females relative to that in males
double MinMort[3]; ///< Minimum mort (as ART access -> infinity) as fraction of mort when ART access -> 0
				   ///< 1st elt is for untreated mort, 2nd for 1st yr of ART, 3rd for >1 yr on ART
double RednLogMort[3]; ///< Redn in log of mort per unit increase in rate of ART initiation
double IeDEAbias[2]; ///< Bias in IeDEA mortality rates (1 = no bias)
double ProvARTmortAdj; ///< Relative rate of ART mortality in province, compared to national
double ARTinterruptionRate; ///< Annual rate of ART interruption
double RRinterruptionM; ///< Relative rate of ART interruption in males
double ARTinterruption20mult; ///< RR ART interruption at age 20 relative to age 35
double ARTresumptionRate[2]; ///< Annual rate of resuming ART after interruption (M, F)
double ARTresumptionMin[2]; ///< Minimum rate of resuming ART after interruption (M, F)
double RR_ARTstartM; ///< Relative rate of ART initiation in men (compared to women)
double RR_ARTstart100CD4; ///< Relative rate of ART initiation per 100 cell increase in CD4 count
double RR_ARTstart1stMo; ///< RR of ART initiation in 1st month after diagnosis (vs longer durations)
double RR_ART1stMo2011; ///< RR of ART initiation in 1st month after diagnosis (in 2011-12)
double COVIDimpactARTstart; ///< % reduction in ART initiation due to COVID, April-June 2020
double USAIDexitImpact; ///< % reduction in ART initiation due to US funding disruptions, post-Jan 2025
double UltARTdelay[2]; ///< Ultimate delay to starting ART in adults if CD4 <200 (M then F)
double MinARTdelay[2]; ///< Minimum average delay to starting ART in adults if CD4 <200 (M then F)
int ARTdataYr; ///< Year to which ART initiation numbers are specified
int UltARTyr[2]; ///< Year in which ultimate ART initiation rates first apply
double RRper10yrART[2]; ///< Increase in rate of HIV mortality on ART, per 10 yr increase in age
double AnnHIVmortART[5][4][2]; ///< Annual HIV mortality rate, by ART duration (1st index), CD4 stage at
							   ///< ART initiation (2nd index) and sex (3rd index)
double SwitchAdult[4]; ///< Annual rate of switching by baseline CD4

///< HIV testing assumptions

double VCTmale2002; ///< Rate of testing in asymptomatic males in 2002, relative to non-pregnant females
double VCTmale2010; ///< Rate of testing in asymptomatic males in 2010, relative to non-pregnant females
double VCTage[2]; ///< Age at which VCT uptake peaks, in men and women
double QuadParam[2]; ///< Coefficient for age^2 term (absolute)
double RetestAdj; ///< Factor by which testing rate increases in previously tested individuals
double RetestAdjInit;
double RetestAdjMax;
double RetestPos; ///< Factor by which testing rate reduces in HIV-diagnosed individuals
double RetestPosInit;
double RetestART; ///< Factor by which testing rate reduces in ART patients
double RetestARTinit;
double HIVeffectVCT; ///< Factor by which testing rates reduces in HIV-positive individuals
double OItoTBtestingRatio; ///< Ratio of HIV testing in all OI patients to that in TB patients
double ORdiagOItreat; ///< OR for HIV diagnosis in OI patients at OI treatment service compared to
					  ///< all HIV diagnosis as a result of the OI episode
double RapidDiagSp; ///< Specificity of rapid testing algorithm
double SelfTestConfirm; ///< Fraction of positive self-testers who seek confirmatory testing at clinic
double SelfTestDataYr[6]; ///< Year to which annual # self-tests are available, by distribution strategy
double SelfTestUptakeUlt[6]; ///< Annual rate of self-test uptake in future, by distribution strategy
double SelfTestWastage[6]; ///< Fraction of self-test kits that aren't used, by distribution strategy
double STageTaxi[2]; ///< Alpha and lambda parameters for age effects on self-test uptake through taxi ranks
double STageWork[2][2]; ///< Alpha and lambda parameters for age effects on ST uptake through work, by sex
double STtaxiMtoFratio; ///< M-to-F ratio of self-test uptake through taxi ranks
double STworkMtoFratio[2]; ///< M-to-F ratio of ST uptake through workplace campaigns (primary & 2ndary)
double EmployedPropn[10][2]; ///< Proportion employed, by age (15-19, 20-24, ..., 60-64) and sex 
double RetestPosST[2]; ///< RR retesting in previously diagnosed ART-naive and ART-experienced
double ORpartnerPosMetareg[2]; ///< Constant and log(prevalence) coefficients in meta-regression of
///< log OR for HIV if partner is positive compared to negative
double DiscloseAndTest; ///< Prob that newly diagnosed individual discloses to partner and partner tests

///< Male circumcision assumptions

double CircPrevBirth; ///< Propn of males circumcised soon after birth
double CircPrevUlt; ///< Propn of men who ever get circumcised (pre-MMC promotion)
double MedianCirc; ///< Median age at circumcisions (including infants)
double ShapeCirc; ///< Weibull shape parameter for times to MC post-infancy
double MCefficacy; ///< Redn in susceptibility in men who are circumcised
double MCefficacyF; ///< Redn in M-to-F transmission from men who are circumcised
int MMCdataYear; ///< Year to which numbers of MMCs are specified
double UltMMCprob; ///< Ultimate annual prob of MMC in males aged 10-14
int UltMMCyear; ///< Year in which ultimate MMC prob first applies
double VMMCdataAdj; ///< Ratio of true number of VMMCs to number reported

///< PrEP and vaginal microbicide (VM) assumptions

double PrEPefficacy[2]; ///< Oral PrEP efficacy in heterosexual M and F
double PrEPefficacyMSM; ///< Oral PrEP efficacy in MSM
double PrEPefficacyPreg; ///< PrEP efficacy in pregnant women
double CondomRednPrEP[2]; ///< Reduction in condom use if using oral PrEP (M, F)
double FreqHCTinPrEP[2]; ///< Frequency of HIV testing (per annum) if receiving PrEP
double PrEPdur[3]; ///< Average duration of retention in oral PrEP programme (years)
double PrEPdurPreg; ///< Average duration of oral PrEP in pregnant/breastfeeding women
double PrEPdataYr; ///< Last year for which we have data on number initiating PrEP
double UltPrEPrateFSW; ///< Monthly rate at which FSWs start oral PrEP after PrEPdataYr
double CurrPrEPrateFSW; ///< Current monthly rate at which FSWs start oral PrEP 
double StoredPrEPrateFSW; ///< monthly rate at which FSWs start oral PrEP in PrEPdataYr
//double RR_PrEPlow[2]; ///< Relative rate of PrEP initiation in low risk heterosexuals
double OR_PrEPlowPreg; ///< Relative odds of PrEP initiation in low risk pregnant women
double CABLAefficacy[2]; ///< CAB-LA efficacy in heterosexual M and F
double CABLAefficacyMSM; ///< CAB-LA efficacy in MSM
double CABLAefficacyPreg; ///< CAB-LA efficacy in pregnant women
double CondomRednCABLA[2]; ///< Reduction in condom use if using CAB-LA (M, F)
double CABLAdur[3]; ///< Average duration of protection from CAB-LA (years)
double CABLAdurPreg; ///< Ave duration of CAB-LA protection if pregnant/breastfeeding 
double CABLAdataYr; ///< Last year for which we have data on number initiating CAB-LA
double UltCABLArateFSW; ///< Monthly rate at which FSWs start CAB-LA after PrEPdataYr
double CurrCABLArateFSW; ///< Current monthly rate at which FSWs start oral PrEP
double StoredCABLArateFSW; ///< monthly rate at which FSWs start CAB-LA in CABLAdataYr
double MicrobicideEff; ///< Microbicide efficacy
double CondomRednVM; ///< Reduction in condom use if using microbicide
double FreqHCTinVM; ///< Frequency of HIV testing (per annum) if receiving microbicide
double VMdur; ///< Average duration of retention in microbicide programme (years)

///< Demographic assumptions

double RecencyBiasANC; ///< Effect of recency on bias in ANC HIV prevalence data
double RRfertHIV; ///< RR of fertility in newly-infected HIV+ women (undiagnosed)
double RRfertCD4[5]; ///< RR of fertility in HIV+ women by current CD4
double RRfertDiag; ///< RR of fertility in diagnosed untreated women (cf undiagnosed)
double RRfertART; ///< RR of fertility in treated women (cf diagnosed ART-naive)
double RRfertVertHIV; ///< RR of fertility in AGYW with vertically acquired HIV
double RR_ARTeffectAge; ///< RR for ART effect per 10-year increase in age
double RR_ARTeffect2020; ///< RR - 1 for ART effect in 2020 (compared to 2010)
double SexRatio; ///< Propn of births that are male

///< MSM assumptions

double MSMpropn; ///< Fraction of men who start sexual activity as MSM
double MSMpartnersM20; ///< Fraction of MSM partners who are male at age 20
double RednMSMpartnersM; ///< Factor by which % of MSM partners who are male
						 ///< reduces per year of age
double MeanAgeDifMSM25; ///< Average partner age dif in MSM at age 25
double ChangeAgeDifMSM; ///< Change in partner age dif in MSM per year of age
double SDageDifMSM; ///< Standard deviation of partner age differences in MSM
double MtoM_ST; ///< Ave transmission prob per sex act (male-to-male)
double InitMSMprevRatio; ///< Ratio of init HIV prev in MSM to that in hetero men
double RR_HIV_TGW; ///< RR of HIV in transgender women to cis-gender MSM
double PropnTGW; ///< Proportion of MSM and TGW who are TGW

///< PWID assumptions

double InitPWIDpropnM; ///< % of unmarried men 15-49 who are PWID at start of projection
double StartInjDrugs; ///< Ann rate of starting injecting drug use in M aged 25 in 2015
double RR_IDfem[2]; ///< RR of starting injecting drug use in F, by risk group 
double GammaMeanInj; ///< Mean of gamma distribution for age effect on starting injecting
double GammaSDinj; ///< SD of gamma distribution for age effect on starting injecting
double RRinjDrug2000; ///< RR of starting injecting drugs in 2000 (ref. 2015)
double StopInjDrugs; ///< Annual rate of stopping injecting drug use
double BaseTransmNS; ///< Transmission prob per act of needle sharing with HIV-pos indiv
double MonthlyInj; ///< Monthly # times PWID inject drugs

//=============================================================================
///< Parameters in the 'PaedAssumps' file
//=============================================================================

double TransmUntreated; ///< prob of transm at/before birth if mother is untreated
double CD4transm[4]; ///< prob of transm at/before birth by CD4 category
double TransmAcute; ///< transm prob at/before birth if untreated and acutely infected
double TransmBFfirst3; ///< transm prob per month of breastfeeding for 1st 3 months
double TransmBFafter3; ///< transm prob per month of breastfeeding after 1st 3 months
double RRforEBF; ///< relative risk of transm if practising EBF instead of mixed feeding
double TransmBFacute; ///< transm prob per month of breastfeeding if acutely infected
double FirstANCwk; ///< mean gestation (in weeks) at first ANC screening visit
double DeliveryWk; ///< mean gestation (in weeks) at delivery

double RRprogressionPostnatal; ///< RR of progression to ART eligibility if infected postnatally
double ProgToNeedLT; ///< annual rate of progression to need in older children infected at birth
double ExcessProgToNeed; ///< excess rate of progression to need in newborn
double ExcessProgRedn; ///< factor by which excess rate of progression reduces per year of age
double ProgAdjNoPMTCT; ///< factor by which the excess progression is adjusted if no PMTCT received
double AIDSmortLT; ///< annual AIDS mortality rate in older children who are ART-eligible & untreated
double ExcessAIDSmort; //excess rate of AIDS mortality in untreated ART-eligible newborn
double ExcessMortRedn; ///< factor by which excess rate of AIDS mortality reduces per year of age
double ProvAdjPaedMort; ///< RR mortality in province relative to national 

///< Paed ART
double RRmortART1; ///< relative rate of mortality on ART during the initial high risk phase
double RRmortART2; ///< relative rate of mortality on ART during the subsequent low risk phase
double EarlyARTmort; ///< AIDS mortality at age 0 in children starting ART in early disease
double RRearlyARTmort; ///< RR AIDS mortality per year of age, for children starting ART in early disease
double ARTinterruptionPaed; ///< rate of ART discontinuation in children
double ARTresumptionPaed; ///< rate of ART resumption in children, after an interruption
double Discontinuation1; ///< rate of ART discontinuation during the initial high risk phase (REDUNDANT)
double Discontinuation2; ///< rate of ART discontinuation during the subsequent low risk phase (REDUNDANT)
double RRearlyPaedART; ///< relative rate of ART initiation in diagnosed early HIV cf diagnosed late HIV
double UltARTdelayC; ///< Ultimate delay to starting ART in kids if 2006 WHO eligibility criteria are met
double MinARTdelayC; ///< Minimum average delay to starting ART in kids if 2006 WHO criteria are met
int InterpolationStart; ///< Year in which interpolation of ART initiation rate begins
int UltimateYr; ///< Year in which ultimate ART coverage is reached
double MinMortP[3]; ///< Minimum mort (as ART access -> infinity) as fraction of mort when ART access -> 0
					///< 1st elt is for untreated mort, 2nd for 1st 3 mo of ART, 3rd for >3 mo on ART
double RednLogMortP[3]; ///< Redn in log of mort per unit increase in rate of ART initiation
double SwitchPaed[2]; ///< Annual rate of switch to 2nd line in kids starting ART in early/late disease

double IMRshape; ///< shape parameter for non-AIDS mortality in 1st year of life

double Sensitivity; ///< sensitivity of HIV screening algorithm
double Window; ///< window period (weeks) for rapid test
double NVPefficacy; ///< redn in transm prob at/before birth if mother receives sd NVP
double DualEfficacy; ///< redn in transm prob at/before birth if mother receives sd NVP + AZT from 28 wks
double AZTefficacy; ///< redn in transm prob at/before birth if mother receives AZT from 28 wks
double TransmART200; ///< transm prob at/before birth if mother starts ART with CD4 <200
double TransmARTpre200; ///< transm prob at/before birth if mother starts ART with CD4 >=200
double InitTransmART200; ///< baseline value (pre-2010 guidelines)
double InitTransmARTpre200; ///< baseline value (pre-2010 guidelines)
double TransmARTprePreg; ///< transm prob at/before birth if mother started ART prior to pregnancy
double RRtransmPerWeekART; ///< RR of transm at/before birth per week of ART prior to delivery
double MeanARTdurPreg; ///< Mean duration of ART prior to delivery if LT ART is started during pregnancy
double SD_ARTdurPreg; ///< SD of duration of ART prior to delivery if LT ART is started during pregnancy
double NVPuptake; ///< prob that a woman testing positive receives sd NVP
double AZTpropnAdj; ///< prob that a woman testing positive but not getting sd NVP receives AZT
double RescreenWk; ///< mean gestation (weeks) at time of retesting for HIV
double RescreenUptake; ///< % of women testing negative on initial screen who agree to rescreening
double UntestedRescreen; ///< % of women who missed initial screen who agree to screening
double RednExtNVP; ///< % redn in rate of MTCT after birth if child receives extended NVP
double RednHAARTduringPreg; ///< % redn in rate of postnatal MTCT if mother started ART during pregnancy
double RednHAARTbeforePreg; ///< % redn in rate of postnatal MTCT if mother started ART before pregnancy
double RednHAART; ///< Average redn in rate of MTCT after birth if mother receives HAART

///< Paed HIV testing
double RRtestVirginTrend[2]; ///< RR virgin testing up to 2005 and 2010+
double RRtestVirgin; ///< Relative rate of testing in virgins to that in sexually experienced girls aged 15
double RRtestPaedAdvanced; ///< Relative rate of testing in advanced HIV disease to that in early disease
double RRtestAgePaed; ///< Relative rate of testing at ages 19-59 mo (compared to ages 5-14 years)
double RetestPosP; ///< Relative rate of testing in children previously diagnosed positive
double BirthSe[2]; ///< sensitivity of PCR at birth in detecting HIV in non-PMTCT and PMTCT-exposed
double SixWeekSe[3]; ///< sensitivity of PCR at 6 weeks in detecting HIV in non-PMTCT and PMTCT-exposed
					 ///< early disease and in late disease
double BaseARTuptakeEID; ///< % of kids starting ART soon after early infant diagnosis, before correction
double PaedARTuptakeEID; ///< % of kids starting ART soon after early infant diagnosis
double ImmARTcorrectionP; ///< Adjustment to % of kids starting ART immediately after diagnosis (excl EID)
double VirginTestAdjProv; ///< RR testing in virgins in province, relative to national

///< Breastfeeding durations
double EverFeed[3]; ///< propn of mothers who ever adopt the feeding strategy (0 = mixed feeding
					///< by HIV-neg mothers, 1 = mixed feeding by mothers who know they're HIV+,
					///< 2 = EBF by mothers who know they're EBF, under original PMTCT programme
double EverFeedCurr[3]; ///< updated to reflect change in policy on free formula provision in 2011
double MedianFeed[3]; ///< median duration of feeding (in months)
double ShapeFeed[3]; ///< shape parameter for duration of feeding
double SwitchingToFF; ///< propn of mothers who switch to formula if they discover they're HIV+
double AbruptWeaningFirst3; ///< propn of women who practise abrupt weaning if stopping EBF in
							///< 1st 3 months of feeding
double AbruptWeaningAfter3; ///< propn of women who practise abrupt weaning if stopping EBF 
							///< after 1st 3 months of feeding
double InitAbruptWeaning1; ///< baseline parameter for first 3 months
double InitAbruptWeaning2; ///< baseline parameter after first 3 months

double NoBFmortAdj[24]; ///< Factors by which mort rates increase in non-breastfed kids in 1st 12m
double BFbiasAdj; ///< exponential adjustment to NoBFmortAdj to allow for bias
double BFadjProv; ///< Increase in mean duration of BF in undiagnosed HIV+ women in relevant province

//============================================================================
///< Parameters and arrays in the 'Rollout' file
//============================================================================

///< VCT assumptions
double HCT1stTimeF25[86]; ///< rate of 1st-time HIV testing in women aged 25
double HCT1stTimeF25init[86];
double NumbersTested[86]; ///< Numbers of individuals 15+ tested for HIV
double NumbersTested5to14[86]; ///< Numbers of individuals 5-14 tested for HIV
double OIsDiagnosed[86]; ///< propn of HIV-positive OI patients who are diagnosed 
double OIsTested[86]; ///< propn of OIs that lead to HIV diagnosis
double PCR6week[86]; ///< propn of HIV+ mothers who get infant PCR tested at 6 weeks
					 ///< AND receive the test results
double PCRuptake; ///< propn of perinatally-infected infants diagnosed at 6 weeks, in current year
double PCRbirth[86]; ///< propn of HIV+ mothers who get infant PCR tested at birth
double PCRuptakeB; ///< propn of HIV+ mothers who get infant PCR tested at birth, in current year
double PCR6month[86]; ///< propn of HIV+ mothers who get infant PCR tested at 6 months
double PCRuptake6; ///< propn of HIV+ mothers who get infant PCR tested at 6 months, in current year
double TestingAt18mo[86]; ///< propn of kids who get tested for HIV at 18 months
double CurrTesting18mo[2]; ///< % screened at 18 months, in HIV-negative and HIV-positive children
double HBCTuptake[86]; ///< rate of HCT through home-based testing
double SelfTestTotals[86][6]; ///< Numbers of self-test kits distributed, by distribution strategy
double SelfTestUptake[6]; ///< Proportion using self-test kits, by distribution strategy

///< PMTCT assumptions
double PregnantWomenTested[86]; ///< propn of pregnant women who receive HIV testing, by year
double VCTuptake; ///< propn of pregnant women who receive HIV testing in current year
double AZTrollout[86]; ///< propn of women receiving sd NVP who also get AZT, by year
double AZTpropn; ///< propn of women receiving sd NVP who also get AZT in current year
double RescreenPropnLate[86]; ///< propn of clinics that offer rescreening in late pregnancy, by year
double RescreenLate; ///< propn of clinics that offer rescreening in late pregnancy in current year
double RescreenPropnImm[86]; ///< propn of women who get rescreened at 6-wk immunization, by yr
double RescreenImm; ///< propn of women who get rescreened at immunization in current year
double ExtNVProllout[86]; ///< propn of women knowing they are HIV+ whose infants receive extended NVP
double ExtNVPpropn; ///< propn of women whose infants receive extended NVP, in current yr
double EligibleOptionB[86]; ///< propn of pregnant women eligible for lifelong ART under WHO option B
double OptionB; ///< propn of pregnant women eligible for lifelong ART under option B, in current yr
double NoBFpropn[86]; ///< propn of HIV-diagnosed mothers choosing not to formula feed
double FFpropn; ///< propn of HIV-diagnosed mothers choosing not to breastfeed in current year
double IncreaseARTdurPreg[86]; ///< % increase in mean duration of ART prior to delivery if ART is
							   ///< is started during pregnancy (relative to pre-2010 period)

///< ART assumptions
double NumStartingART_M[86]; ///< number of males (15+) starting ART, by year
double StartingART_M; ///< number of males (15+) starting ART in current year
double NumStartingART_F[86]; ///< number of females (15+) starting ART, by year
double StartingART_F; ///< number of females (15+) starting ART in current year
double NumStartingART_P[86]; ///< number of children (<15) starting ART, by year
double StartingART_P; ///< number of children starting ART in current year
double RateARTstartF[86]; ///< monthly rates of ART start in diagnosed ART-eligible women with CD4 <200
double RateARTstartC[86]; ///< monthly rates of ART start in diagnosed ART-eligible kids with late HIV
double RR_ARTinterruption[86]; ///< Relative rates of ART interruption, by year
double EligiblePTB350[86]; ///< propn of pulmonary TB patients, CD4 200-349, who are ART-eligible
double EligiblePTBpre350[86]; ///< propn of pulmonary TB patients, CD4 350+, who are ART-eligible
double EligibleWHO3[86]; ///< propn of WHO stage 3 patients (excl. TB), CD4 350+, who are ART-eligible
double EligiblePreg350[86]; ///< propn of pregnant women, CD4 200-349, who are ART-eligible
double EligiblePregPre350[86]; ///< propn of pregnant women, CD4 350+, who are ART-eligible
double EligibleAsym350[86]; ///< propn of asymptomatic non-pregnant people, CD4 200-349, who are eligible
double EligibleAsym500[86]; ///< propn of asymptomatic non-pregnant people, CD4 350-499, who are eligible
double EligibleAsymPre500[86]; ///< propn of asymptomatic non-pregnant people, CD4 500+, who are eligible
double EligibleInfants[86]; ///< propn of infected infants eligible to start ART in early disease
double EligInfants; ///< propn of infected infants eligible to start ART in early disease in current year
double EarlyART1to4[86]; ///< % eligible in early disease in kids aged 1-4 
double EarlyART5to14[86]; ///< % eligible in early disease in kids aged 5-14 
double MatARTuptake[86]; ///< propn of newly-diagnosed ART-eligible women starting ART prior to delivery
double MatARTpropn; ///< propn of ART-eligible women starting ART prior to delivery in current yr
double OI_ARTuptake[86]; ///< propn of newly-diagnosed ART-eligible OI patients who start ART
double OIstart;
double HCT_ARTuptake[86]; ///< propn of other newly-diagnosed ART-eligible adults who start ART
double AsymStart[2]; ///< rate of ART start in first month after diagnosis, by sex 
					 ///< (or prob of ART start if PropnalImmART = 0)
double PaedARTuptake[86]; ///< propn of newly-diagnosed ART-eligible children who start ART
double PaedARTuptakeC; ///< propn of newly-diagnosed ART-eligible children who start ART in current yr
double POC_CD4[86]; ///< propn of HIV-positive patients in whom point-of-care CD4 tests are used
double VLsuppression200[86]; ///< % of adults starting ART with CD4 <200 who are virally suppressed (VL<400)
double CurrSuppression200; ///< VLsuppression200 in current year, after adjusting for ORsuppressionIeDEA
double VLsuppressionPaed[86]; ///< % of children on ART who are virally suppressed (VL<400)
//int ImmARTstage = 2; ///< Stage after which normal ART initiation rates apply (0 ==> no early ART for CSW)
double ImmART_CSW;

///< PrEP assumptions
double TotStartingPrEP[86]; ///< Annual PrEP initiations
double RR_PrEPstartMSM[86]; ///< RR of PrEP initiation in HR MSM age 20 (relative to FSW)
double RR_PrEPstartPWID[86]; ///< RR of PrEP initiation in PWID (relative to FSW)
double RR_PrEPstartF20[86]; ///< RR of PrEP initiation in HR fem age 20 (relative to FSW)
double PrEPeligMSM[86]; ///< Proportion of MSM eligible to initiate PrEP
double PrEPeligAGYW[86]; ///< Proportion of AGYW (fem 15-24) eligible to initiate PrEP
double PrEPeligOther[86]; ///< Proportion of other groups eligible to initiate PrEP
double PrEPpregnant[86]; ///< prob of oral PrEP initiation in pregnant women
double PrEPpregnantHigh; ///< current prob of oral PrEP in high-risk pregnant women
double TotStartingCABLA[86]; ///< Annual PrEP initiations
double RR_CABLAstartMSM[86]; ///< RR of PrEP initiation in HR MSM age 20 (relative to FSW)
double RR_CABLAstartPWID[86]; ///< RR of PrEP initiation in PWID (relative to FSW)
double RR_CABLAstartF20[86]; ///< RR of PrEP initiation in HR fem age 20 (relative to FSW)
double CABLAeligMSM[86]; ///< Proportion of MSM eligible to initiate PrEP
double CABLAeligAGYW[86]; ///< Proportion of AGYW (fem 15-24) eligible to initiate PrEP
double CABLAeligOther[86]; ///< Proportion of other groups eligible to initiate PrEP
double CABLApregnant[86]; ///< prob of CAB-LA initiation in pregnant women
double CABLApregnantHigh; ///< current prob of CAB-LA in high-risk pregnant women

///< Vaginal microbicide (VM) assumptions
double VM_FSW[86]; ///< monthly rate of VM initiation in FSWs
double VMpregnant[86]; ///< rate of VM initiation in pregnant women
double VMpregnantHigh; ///< current prob of VM in high-risk pregnant women

///< MMC assumptions
double MMCoperations[86]; ///< number of medical circumcisions performed
double RR_MMCpromo10[86]; ///< RR of MMC promotion at ages 10-14
double RR_MMCpromo15[86]; ///< RR of MMC promotion at ages 15-19
double RR_MMCpromo20[86]; ///< RR of MMC promotion at ages 20-24
double RR_MMCpromo25[86]; ///< RR of MMC promotion at ages 25-49
double RR_MMCpromo50[86]; ///< RR of MMC promotion at ages 50+
double NeonatalMMC[86]; ///< % of children circumcised at birth
double CurrCircPrev10; ///< prevalence of circumcision in 10-year olds at end of yr

///< FSW assumptions
double DurFSW[86]; ///< Average duration of sex work (years)
double FSWageMean[86]; ///< Mean age of FSWs (female sex workers)
double FSWageSD[86]; ///< Standard deviation of FSW ages

///< PWID assumptions
double PropnNeedleSharing[86]; ///< % of injections in which needle is shared 

//============================================================================
///< Parameters and arrays in the 'TBrollout' file
//============================================================================

double TotPosTBtestsAdult[86]; ///< # individuals testing positive for TB microbiologically
double TotPosTBtestsAdult1[86]; ///< # individuals testing positive for TB microbiologically
double MicroscopyPropn[86]; ///< % of TB-tested individuals screened by microscopy (not Xpert)
double UltraPropn[86]; ///< % of Xpert-tested individuals screened by Xpert Ultra
double CultureConfirmSmNeg[86][2]; ///< % smear-neg suspects sent for culture, by HIV status
double CultureConfirmXpNeg[86][2]; ///< % of Xpert-neg suspects sent for culture, by HIV status
double DSTcoveragePrevTB[86]; ///< % of previously-treated TB cases who undergo DST
double DSTcoverageNewTB[86]; ///< % of newly-treated TB cases who undergo DST
double MDR_TBproportion[86]; ///< % of rif-resistant TB cases that are MDR
double Dur1stLineRxTB[86]; ///< Duration (in months) of 1st-line Rx for TB
double Dur2ndLineRxTB[86]; ///< Duration (in months) of 2nd-line Rx for TB
double IPTinitiators[86]; ///< Number of HIV+ adults starting IPT
double IPTduration[86]; ///< ///< Recommended duration of IPT (months)
double TPTfraction3HP[86]; ///< Fraction of TPT initiators starting 3HP
double IPTcontinuePostRx[86]; ///< % of cured TB patients who continue on IPT post-treatment
double DOTrollout[86]; ///< % of TB patients under directly observed treatment (DOT)
double PropnHHcontactScreened[86]; ///< % of adult household contacts of TB cases screened
double PropnHHcontactTUTT[86]; ///< % of screened HH contacts tested without symptom screen
double PropnHHcontactTPT[86]; ///< % of TB-neg HH contacts offered TPT
double RateART_TBscreened[86]; ///< Annual rate of TB screening in ART patients
double PropnART_TB_TUTT[86]; ///< % of screened ART patients tested without symptom screen
double RatePrevTBscreened[86]; ///< Annual rate of screening if treated for TB in last 2 years
double PropnPrevTB_TUTT[86]; ///< % of screened previous TB patients tested without symptom screen
double RateD2Dscreen[86]; ///< Annual rate of TB symptom screening, door-to-door campaigns
double PropnD2DdCXR[86]; ///< % of door-to-door screening that includes digital CXR if asymptomatic
double NutritionSupportHHcontacts[86]; ///< % of HH contacts getting nutrition support

//==================================================================================
///< Parameters and arrays in intermediate output calculations (formlery 'Results')
//==================================================================================

double AdultMortBy5yr[86][16][2]; ///< Starting from age 15-19, up to 90+
double NonAIDSmortBy5yr[86][16][2]; ///< Starting from age 15-19, up to 90+
double AdultHHprev[86][10][2]; ///< Prevalence in households by year, age and sex
double ChildMortBy5yr[86][4][2]; ///< For ages 0, 1-4, 5-9, 10-14
double ChildAIDSmortDiag[86][2]; ///< For ages 1-4, 5-9
double ChildAIDSmortART[86][2]; ///< For ages 1-4, 5-9
double PrevPregnant[7][86]; ///< Rows 100-6 (last element is prevalence for all ages combined)
double AnyARTpreConcep[86][6]; ///< For ages 15-19, 20-24, 25-29, 30-34, 35-39
double RateARTstartU200[86][2]; ///< Rate of starting ART at CD4 <200 (rows 122-3)
double RateARTstartLate[86]; ///< Rate of starting ART in children (<10) in late HIV disease
double NetMigrPos[91][2]; ///< Net HIV+ migrants by age and sex (age & HIV status at yr end)
double NetMigrNeg[91][2]; ///< Net HIV- migrants by age and sex (age & HIV status at yr end)
double OnARTfem15[86]; ///< 15-year old girls on ART
int ARTerrorInd; ///< 1 if ART initiation rate ever exceeds maximum in adults/kids, 0 otherwise
double MaxARTerror;

///< Results not required for calibration purposes
//double AdolHIVprofile[56][4];
//double FSW_HIVprofile[56][15]; ///< 3 neg stages, 4 undiag pos, 4 diag pre-ART, 4 ART
double NewHIVinClients; ///< Only including transmission from SWs to clients
double NewHIVinClientsNotFromSW; ///< Transmission from non-SW partners to clients
double HIVprev15to49[86]; ///< Row 89
double FSWprev[86]; ///< Row 107
double PWIDprev[86]; ///< HIV prevalence in PWID
double PWIDprevM[86]; ///< HIV prevalence in male PWID
double PWIDprevF[86]; ///< HIV prevalence in female PWID
double CondomUseFSW[86]; ///< % of sex workers using condoms at last sex
double ClientPrev; ///< HIV prevalence in clients
double ClientARTcov; ///< ART coverage in clients of FSWs
double TotalSex;
double TotalSexProt;
double TotalSexProt18;
double NewPCRdiagBirth;
double NewPCRdiag12mo; 
double NewPCRdiag24mo;
double SummaryOutputs[2000][86]; ///< Means and 95% CIs
int SummOutRow = 0; ///< Row ID for SummaryOutputs

///< TB outputs 
double TBadultMortBy5yr[86][16][2]; ///< TB deaths by year, age group and sex
double TBadultMortOnRx[86][2]; ///< TB deaths in treated adults, by year and sex
double TBadultMortOnRx1[86][2]; ///< TB deaths in 1st line treated adults, by year and sex
double TBadultMortOnRx2[86][2]; ///< TB deaths in 2nd line treated adults, by year and sex
double TBadultRxBy5yr[86][16][2]; ///< True TB Rx initiations by year, age group and sex
double TBdeathsAdultHIV[86]; ///< Number of TB deaths in adults living with HIV
double TBdeathsAdultHIV_M[86][81]; // Number of TB deaths in adults living with HIV by year and age //lj
double TBdeathsAdultHIV_F[86][81]; // Number of TB deaths in adults living with HIV by year and age  //lj
double TBsymptomScreened[86]; ///< % of symptomatic TB patients screened microbiologically
							  ///< if specifically seeking Rx for TB or TB-like symptoms
double TBsymptomScreened2[86]; ///< % of patients with TB/TB-like symptoms screened micro-
							   ///< biologically if attending health services for other reasons
double SmPosRxScreen[86]; ///< # smear-pos TB cases starting Rx after active/intensive case finding
double TBadultRxSmDiag[86]; ///< True TB Rx initiations in adults diagnosed by smear
double SmPosRxDelay[86]; ///< Average delay (years) until active smear-pos TB is treated
double TBadultRxHIV[86][2]; ///< True TB Rx initiations in adults with HIV, by sex
double ModelTBtests[86]; ///< Total # adults tested for TB microbiologically
double TBadultLabDiag[86]; ///< TB diagnoses based on laboratory testing
double FalseTBadultLabDiag[86]; ///< False-positive TB diagnoses based on laboratory testing (passive)
double LabDiagFalsePosActive[86]; ///< False-positive TB diagnoses based on laboratory testing (active)
double TotSmPosTB[86]; ///< Number of adults with untreated smear-positive TB
double TotSmNegTB[86]; ///< Number of adults with untreated smear-negative TB
double TotSmPosRR_TB[86]; ///< Number of adults with untreated smear-positive rif-resistant TB
double TotSmNegRR_TB[86]; ///< Number of adults with untreated smear-negative rif-resistant TB
double UntreatedSmPosPropn[86]; ///< % of untreated TB that is smear-pos
double PropnNewTBrifRes[86]; ///< % of new TB that is ref-resistant (transmitted resistance)
double NewRR_TBnaive[86]; ///< new rif-resistant TB cases, never previously treated
double NewRR_TBprevRx[86]; ///< new rif-resistant TB cases, previously treated
double NewRS_TBnaive[86]; ///< new rif-sensitive TB cases, never previously treated
double NewRS_TBprevRx[86]; ///< new rif-sensitive TB cases, previously treated
double RifResFoundPreRx[86];
double RifResFoundOnRx[86]; ///< rif-resistant TB cases, either acquired or missed at baseline screen,
							///< who are subsequently diagnosed rif-resistant when failing Rx
double CultureOrLPAfailing[86]; ///< # culture/LPA tests in patients failing 1st-line Rx
double New2ndLineTB_NF[86]; ///< patients starting 2nd-line Rx (not having failed 1st line)
double New2ndLineTB_F[86]; ///< patients starting 2nd-line Rx (having failed 1st line)
double FailTB_Rx_RS[86]; ///< number who fail TB Rx but remain rif-susceptible
double FailTB_Rx_RR[86]; ///< number who fail TB Rx and are rif-resistant
double FailTB_RxNewRR[86]; ///< number who fail TB Rx and are newly rif-resistant
double PrevTreatedRifRes[86]; ///< % of rif-resistant Rx initiators who were previously treated
double BaseIPTuptake[86]; ///< monthly IPT uptake in HIV-diagnosed pre-ART, CD4 <200
double OddsTB_HIV[86]; ///< OR for TB-HIV association, by year
double HHcontactPropn[86]; ///< % of adults who are household contacts of people diagnosed in last mo
double AnnualRiskMTBpaed[86]; ///< Annual risk of Mtb infection in children aged 0-9 years
double EmpiricalAdj; ///< Time-varying adjustment to empirical Rx rate
double TotTUTTtests; ///< Total Xpert tests performed under TUTT
double TotTUTTdiag; ///< Total diagnoses under TUTT

//==================================================================================
///< Parameters and arrays for age/sex-specific outputs (formerly 'Population' sheet)
//==================================================================================

double StartingPop[91][2]; ///< Size of population in 1985, by age and by sex
double TotalPop[91][2]; ///< Size of the current population, by age and sex (cols E-F)
double TotalPositive[91][2]; ///< Size of HIV-positive population (cols G-H)
double TotalDiagnosed[91][2]; ///< Number of people diagnosed HIV-positive
double TotalART[91][2]; ///< Number of ART patients (cols I-J)
double TotalART2ndL[91][2]; ///< Number of ART patients on second-line
double TotalNaiveElig[91][2]; ///< Number who are ART-naive but eligible for ART
double TotalInterrupt[91][2]; ///< Number who have received ART but are currently off ART
double TotalSexuallyExp[91][2]; ///< Number of individuals who are sexually experienced
double TotalMarried[91][2]; ///< Number of individuals who are married (cols O-P)
double SumGroupsM[81][44]; ///< Sum of adult male risk groups (cols R-BI)
double SumGroupsF[81][44]; ///< Sum of adult female risk groups (cols R-BI)
double SumGroupsVM[20][44]; ///< Sum of virgin male risk groups (cols BK-DB)
double SumGroupsVF[20][44]; ///< Sum of virgin female risk groups (cols BK-DB)
double InitPrevAdj[35][2]; ///< Adjustments to initial prevalence in women aged 15-49

//=================================================================================
///< Parameters and arrays for sexual activity calcs (formerly 'Sex activity' sheet)
//=================================================================================

double MarriageRate[76][3]; ///< Average rates of marriage (1st row is for age 15)
double DivorceRate[76][3]; ///< Rates of divorce by age (1st index) & sex/MSM (2nd index)
double InitBehavDbn[81][6][2]; ///< Initial sex activity distribution by age (1st index),
							   ///< risk/behav (2nd index) and sex (3rd index)
double InitMarriedMSM[81][2]; ///< Number of married MSM by age and risk group
double CurrBehavDbn[81][4][2]; ///< Current sex activity distribution (omitting virgins)
double CurrBehavDbnMSM[81][4]; ///< Current MSM sex activity distribution by risk group
double PartnerAcqF[81]; ///< Age adjustment factor for female partnership formation rate
double MinPartnerAge[81]; ///< Minimum partner age, by female age
double GammaParametersST[81][2]; ///< Alpha and beta parameters for ST partner age prefs
double AgePrefST[81][81][2]; ///< Proportion of ST partners in different age groups (3rd 
							 ///< index is sex of selecting indiv, whose age is 1st index)
double GammaParametersLT[81][2]; ///< Alpha and beta parameters for LT partner age prefs
double AgePrefLT[81][81][2]; ///< Proportion of LT partners in different age groups
double MSMpartnersM[81]; ///< Fraction of MSM partners who are male
double InitWidowhoodRate[76][3]; ///< Initial rates at which married individuals become 
								 ///< widowed, indexed by sex/MSMind of the partner 
double CurrWidowhoodRate[76][3]; ///< Current rates at which married individuals become 
								 ///< widowed, due to non-AIDS mort
double FSWageDbn[81]; ///< Propn of sex workers at each age
double PartnerAcqM[81]; ///< Rate at which high risk unmarried men form ST partnerships
double FSWcontactRate[81]; ///< Rate at which high risk unmarried men visit sex workers
double TotalFSW; ///< Total demand for sex workers in current period
double DebutProb[21][2][2]; ///< Prob of debut by age, risk group and sex (last index)
double AnnAIDSmortM[76][2][2]; ///< By risk of male (2nd index) & risk of female (3rd index)
double AnnAIDSmortF[76][2][2]; ///< By risk of female (2nd index) & risk of male (3rd index)
double AnnAIDSmortMSM[76]; ///< AIDS mortality in men married to men, by age
double ProbDivorceOrWidowM[76][2][2]; ///< Prob male of age x (1st index) in risk group y 
									  ///< (2nd index) loses spouse of risk z (3rd index)
double ProbDivorceOrWidowF[76][2][2]; ///< Prob woman of age x (1st index) in risk group y 
									  ///< (2nd index) loses spouse of risk z (3rd index)
double ProbDivorceOrWidowMSM[76]; ///< Prob MSM of age x loses spouse 
double GammaParametersMSM[81][2]; ///< Alpha and beta parameters for MSM partner age prefs
double AgePrefMSM[81][81]; ///< Proportion of MSM partners in different age groups

//============================================================================
///< Parameters and arrays for sexual mixing (formerly 'Mixing' sheet)
//============================================================================

double ProbMarriageSE[76][2][3]; ///< Prob of marriage in sexually experienced adults, by
								 ///< age, risk group and sex/MSM (last index)
double InitMarriedHigh[2][2]; ///< Initial proportion of married individuals whose partners
							  ///< are high risk (1st index = sex, 2nd index = risk group)
double CurrSThigh[2][2]; ///< Current proportion of individuals in ST rels whose partners
						 ///< are high risk (1st index = sex, 2nd index = risk group)
double CurrLThigh[2][2]; ///< Current propn of individuals getting married whose partners
						 ///< are high risk (1st index = sex, 2nd index = risk group)
double MaleMarriageAdj; ///< Balancing factor to make # male marriages = # female marriages
double CurrSThighMSM[2]; ///< Current propn of MSM whose ST partners are high risk
double CurrLThighMSM[2]; ///< Current propn of MSM whose LT partners are high risk

//======================================================================================
///< Parameters and arrays for HIV prevention (formerly 'Condoms' and 'PrEP + VM' sheets)
//======================================================================================

double SexFreqMarital[76][2]; ///< Monthly frequency of sex in marital relationships
double MedianBehavChange[3]; ///< Median time to behaviour change
double ProbCondomST[81][2]; ///< Prob of condom use per sex act in ST relationships
double ProbCondomLT[81][2]; ///< Prob of condom use per sex act in LT relationships
double ProbCondomFSW; ///< Prob of condom use per sex act in FSW-client contacts
double RelativeInf[39][2][81]; ///< Relative infectiousness by HIV stage, sex, age
double RelativeCoit[39][2][81]; ///< Relative frequency of sex by HIV stage, sex, age
double RelativeUnprot[39]; ///< Relative proportion of sex acts that are unprotected
double RelativeTransm[39][3][2][81]; ///< RR of transm (HIV stage, , sex, age)
double RelativeCSWentry[39]; ///< Relative rates of CSW entry
double RelativeCSWexit[39]; ///< Relative rates of exit from sex work by HIV stage

double RR_PrEP_MSM[81][2]; ///< By age & risk group, relative to high-risk MSM aged 20
double RR_PrEP_Het[81][2][2]; ///< By age, risk group & sex, relative to high-risk F20
double RR_CABLA_MSM[81][2]; ///< By age & risk group, relative to high-risk MSM aged 20
double RR_CABLA_Het[81][2][2]; ///< By age, risk group & sex, relative to high-risk F20
double JoinPrEP[81][8]; ///< For HR MSM, LR MSM, HR MSF, LR MSF, FSW, HR F, LR F, PWID
double JoinVM[81][3]; ///< Rates of initiating VM (FSWs, high-risk F, low-risk F)
double JoinCABLA[81][8]; ///< For HR MSM, LR MSM, HR MSF, LR MSF, FSW, HR F, LR F, PWID

double PropnPrEPpreg[40][2]; ///< % of oral PrEP initiations in pregnancy, by age & risk
double PropnCABLApreg[40][2]; ///< % of CAB-LA initiations in pregnancy, by age & risk

//============================================================================
///< Parameters and arrays for male circumcision (formerly 'Circumcision' sheet)
//============================================================================

double InitCircumcised[91]; ///< Initial propn of men circumcised
double WeibullProb[81]; ///< Prob of getting traditionally circumcised if uncircumcised
						///< but still intending to get traditionally circumcised
double CurrNegCircumcised[91]; ///< % of HIV-negative men who are circumcised
double CircProbPreMMC[91]; ///< Prob of circumcision in next yr, before MMC campaigns
double CircProbStored; ///< MMC prob in last year for which MMC data were
					   ///< specified, for men who are high sexually active
double CurrCircProb[81][4]; ///< Prob of circumcision in current year, by age,
							///< risk group and marital status 

//============================================================================
///< Parameters and arrays for people who inject drugs (PWID)
//============================================================================

double RR_IDage[81]; ///< RR of starting injecting drugs, by age (ref. 25)

//============================================================================
///< Parameters and arrays for HIV transmission (formerly 'Transmission' sheet)
//============================================================================

double TransmMtoF_ST[81][16]; ///< See ProbTransm.xlsx workbook for definitions
double TransmMtoM_ST[81][12]; ///< See ProbTransm.xlsx workbook for definitions
double TransmFtoM_ST[81][24]; ///< See ProbTransm.xlsx workbook for definitions
double TransmMtoF_LT[81][16]; ///< See ProbTransm.xlsx workbook for definitions
double TransmMtoM_LT[81][6]; ///< See ProbTransm.xlsx workbook for definitions
double TransmMtoFSW[4]; ///< No prevention, CABLA, oral PrEP, microbicides
double TransmFSWtoM[6]; ///< By client prevention method and MC status
double EctopyFactor[81][2];
double TransmNS[4]; ///< Prob of transmission through needle sharing, by PrEP group

//====================================================================================
///< Parameters and arrays for pre-ART HIV progression (formerly 'Progression' sheet)
//====================================================================================

double MnthlyCD4trans[81][4][2]; ///< Monthly rates of CD4 transition by age,
								 ///< CD4 stage and sex
double AveARTstartU200[2]; ///< Ave rate of starting ART at CD4<200, over last 3 yrs
double MortAdjBelow200[2]; ///< Adjustment for past ART rollout
double MnthlyAIDSmort[81][2][2]; ///< Monthly rates of AIDS mortality by age,
								 ///< CD4 stage and sex
double ProbExitAtEntry[81][5][2]; ///< Prob of exit in same month as entry

//============================================================================
///< Parameters and arrays for HIV testing and ART initiation
//============================================================================

double TestingRateSE[81][12][2]; ///< Monthly rates of HIV testing by age (1st index),
								 ///< HIV stage (2nd index) and sex (3rd index)
double TestingRateNPF[81]; ///< Testing rates in sexually-experienced non-pregnant women
double TestingRateM[81]; ///< Testing rates in sexually-experienced HIV-neg men
double TestingRateV[20][5][2]; ///< Testing rates in vertically-infected virgins
double TestingRateNegV[20][2]; ///< Testing rates in HIV-neg virgins by age and sex
double TestingRateEligSE[81][15][2]; ///< TestingRateSE * ART-eligible proportion
double TestingRateEligV[20][5][2]; ///< TestingRateV * ART-eligible proportion
double HCTtoART_SE[81][15][2]; ///< Monthly rates of HIV diagnosis leading to
							  ///< immediate ART initiation in sexually experienced
double HCTtoART_V[20][5][2]; ///< Monthly rates of HIV diagnosis leading to immediate
							 ///< ART initiation in vertically-infected virgins
double AdultRoot[2]; ///< AQ96, AS96
double StoredRoot[2]; ///< AQ98, AS98
double CurrARTinitiation[2]; ///< AQ99, AS99
double ARTinitByStage[5][3]; ///< AX14:AZ18

///< Self-testing and index testing

double AvePosTesting[81][2]; ///< Average testing rate in HIV+ indivs, by age & sex
double AvePartnerCoverage[81][2]; ///< Average ART coverage in HIV+ indivs, by age & sex
double ORpartnerPos[81]; ///< OR for HIV if partner is positive compared to negative
double PosPartnerProb[81][2][2]; ///< Prob that partner is pos, by indiv age, HIV & sex
double SelfTestingRate[81][12][2]; ///< Same indexing as for TestingRateSE
double SelfTestingRateM[81][12][2][6]; ///< As before, last index referring to modality
double TotTestingRateSE[81][12][2]; ///< Self-testing + other testing combined

//============================================================================
///< Parameters and arrays for CD4, mortality and interruptions after ART start 
//============================================================================

double OnARTbyIntDur[6][2][81]; ///< Fraction still on ART, by duration, sex, age
double OnARThalfIntDur[6][2][81]; ///< As above, but at durations 0.25, 0.5, 1.5, ... 4.5
double OnARThalfIntDurP[5]; ///< % kids still on ART at 0.5, 1.5, 2.5, 3.5, 4.5 yrs
double OnARTpaed[10]; ///< Fraction of ART-experienced kids currently on ART, by age
double InterruptedPaedLate[10]; ///< Fraction of paed interrupters who started ART late
double RestartRateByIntDur[6][2][81]; ///< Mnthly rate of re-initiation by dur, sex, age
double AgeAdjInterrupt[81][2]; ///< RR ART interruption by age & sex (ref. females 35)
double LowVLuntreated[5][2]; ///< Prob of VL<1000 if untreated, by CD4 stage and sex
double AveCD4byARTdur[4][6]; ///< Average CD4 count by baseline CD4 (1st index) and
							 ///< time since ART initiation (2nd index)
double InitAveCD4byARTdur[6]; ///< Initial assumps for CD4 <200 at ART start
double AveCD4nonIntDur[4][6]; ///< Average CD4 count by baseline CD4 (1st index) and
							 ///< non-integer ART duration (2nd index)
double CoV_CD4byARTdur[4][6]; ///< Coefficient of variation in CD4 counts by baseline 
							  ///< CD4 (1st index) and time since ART initiation
double CoV_CD4nonIntDur[4][6];
double CD4dbnByARTdur[4][4][6]; ///< Propn of ART patients in each CD4 band (1st index)
								///< by baseline CD4 (2nd index) & ART dur (3rd index)
double CD4dbnNonIntDur[4][4][6];
double MortByARTdurM[81][4][5]; ///< Monthly male mort by age, baseline CD4 and ART dur
double MortByARTdurF[81][4][5]; ///< Monthly female mort by age, baseline CD4 and ART dur
double MortAdj200M[2]; ///< Adjustments to mort in men starting ART at CD4 <200 in 1st
					   ///< year on ART and after >1 year on ART
double MortAdj200F[2]; ///< Adjustments to mort in women starting ART at CD4 <200
double MortStartART[81][4][2]; ///< Prob of AIDS death in month of starting ART, by age,
							   ///< baseline CD4 category and sex (3rd index)
double RatioMaxToMinCD4[6];
double CumPaedARTearly[11][5]; ///< Cum ART initiations by age and ART dur, in kids (early)
double CumPaedARTlate[11][5]; ///< Cum ART initiations by age and ART dur, in kids (late)

//============================================================================
///< Tuberculosis parameters
//============================================================================

///< Contact rates and mixing

double DoddMixMatrix[5][2][4][2]; ///< By age & sex of contact, and age & sex of indiv
double DoddAgeSexDbn[5][2]; ///< Proportion of Dodd population by age and sex
double CrudeContact[4][2]; ///< Daily contacts by age group and sex
double ContactRednCOVID[3]; ///< Reduction in crude contact rate in 2020 & 2021 due to COVID
double RRcontactPre2000; ///< RR of social contact up to 2000, relative to 2011 (base rate)

///< Transmission and natural history

double TBtransmProb; ///< Prob of transmission per infectious contact (per day)
double TBtransmProbCurr; ///< Prob of transmission per infectious contact (per day)
double RatioMinToBaseInfectivity; ///< RR smear-pos infectiousness with no Rx delay
double PropFastProg; ///< Proportion progressing to active TB soon after infection
double Reactivation; ///< Annual reactivation rate in HIV-negative individuals
double MortalitySmPos; ///< Mortality rate in untreated smear-positive TB
double MortalitySmNeg; ///< Mortality rate in untreated smear-negative TB
double NaturalRecSmPos; ///< Natural rate of recovery in smear-positive TB
double NaturalRecSmNeg; ///< Natural rate of recovery in smear-negative TB
double PartialImmunHIVneg; ///< Reduction in fast progression if reinfected with TB
double DurSTpostRxRisk; ///< Duation of increased short-term relapse risk post-TB Rx
///< Inverse of ToLongTermPostTreat in Mmamapudi's original code
double RelapseST; ///< Annual rate of relapse in individuals recently cured of TB
double PastTBfactor; ///< Increased TB risk if previously had active TB
double RR_TBadultM; ///< RR TB incidence in adult males
double RR_TBalcohol; ///< RR TB incidence for risky drinkers
double RR_TBdiabetes; ///< RR TB incidence for people with HbA1c>6.5 (diabetes)
double RR_TBcurrSmoke; ///< RR TB incidence for current smokers
double RR_TBsmoke10yr; ///< RR TB incidence per 10-year increase in smoking duration
double RR_TBlowBMI; ///< RR TB incidence for people with BMI < 18.5
double RiskyDrinkingPrev[76][2]; ///< Prevalence of risky drinking by age and sex
double DiabetesPrev[76][2]; ///< Prevalence of HbA1c > 6.5 (diabetes) by age and sex
double SmokingPrev[76][2]; ///< Prevalence of smoking by age and sex, in 2016
double InitAveYrsSmoking[76][2]; ///< Average # years previous smoking in 1985
double AveYearsSmoking[76][2]; ///< Average # years previous smoking in current year
double ChangeSmokingPrev[76][2]; ///< Annual change in smoking prevalence, 1998-2022
double LowBMIprev[76][2]; ///< Prevalence of low BMI (<18.5) by age and sex, in 2016
double RRsmoking2016; ///< RR of smoking in 2016 relative to 1992
double RRlowBMI2022; ///< RR of low BMI in 2022 relative to 1998
double TBincAdjByAgeSex[81][2]; ///< RR TB incidence by age and sex
double SmNegInfectiousness; ///< RR TB transmission from people with smear-neg TB
double RifResInfectiousness; ///< RR TB transmission from people with rif-resistant TB
double AveCD4HIVneg; ///< Average CD4 count in HIV-negative population
double RR_TBper100CD4increase; ///< RR TB per 100 increase in CD4 count if HIV-pos
double RR_TBtreatedHIV; ///< RR TB if on ART, after controlling for CD4
double RR_TBmortPer50CD4; ///< RR TB death per 50 increase in CD4 if HIV-pos
double RR_TBmortTreatedHIV; ///< RR TB death if on ART, after controlling for CD4
double RR_TBmortPer10yrAge; ///< RR TB death per 10-year increase in age
double RRnatRecPer100CD4increase; ///< RR natural recovery per 100 increase in CD4
double RRimmunePer100CD4increase; ///< RR partial innunity per 100 increase in CD4

///< TB testing and treatment 

double HealthSeekingTB; ///< Annual rate of health seeking due to active TB symptoms
///< (in HIV-negative men with smear-negative TB)
double HealthSeekingGen; ///< Annual rate of health seeking unrelated to TB symptoms
///< (in HIV-negative men)
double HealthSeekingTBLS; ///< Annual rate of health seeking for TB-like symptoms
double RRhealthSeekingFem; ///< Relative rate of health seeking in women vs men
double RRhealthSeekingHIV; ///< Relative rate of health seeking in HIV+ individuals
double Cough2wkActiveSmNeg; ///< Prevalence of cough >2 weeks in smear-neg active TB
double Cough2wkGen; ///< Prevalence of cough >2 weeks in general pop (no active TB)
double RRsymptomsSmPos; ///< Relative rate of TB symptoms if smear-positive
double RRscreenSymptoms; ///< RR of screening if seeking Rx due to TB symptoms
double RRscreenSymptomsBase; ///< RR of screening due to symptoms in low-screening scenario 
double RRscreenSymptomsUlt; ///< RR of screening due to symptoms in high-screening scenario
double EffectScreenRate2; ///< Effect of TB screening rates on RRscreenSymptoms
double RRscreenF; ///< RR of microbiologic screening in symptomatic F vs symptomatic M
int TBtestYear; ///< Year to which numbers of TB tests are specified
double PrivateTBdiagPropn; ///< % of positive diagnoses from the private sector
double RecordedTB80sAdj; ///< Ratio of true microbiologically diagnosed TB (1985-90) to recorded
double UltTBsymptomScreen; ///< LT % of active TB patients seeking Rx who get screened
double RatioSymptomToMicroScreen; ///< % symptom screened / % microbiologically tested
double XpertSe[2]; ///< Xpert sensitivity in smear-negative and -positive TB
double XpertSeActive[2]; ///< Xpert sensitivity in context of active case finding (HHCs)
double XpertSp; ///< Xpert specificity
double SmearSp; ///< Smear specificity
double XpertUltraSe[2]; ///< Xpert Ultra sensitivity in smear-negative and -positive TB
double XpertUltraSeActive[2]; ///< Xpert Ultra sensitivity in active case finding (HHCs)
double XpertUltraSp; ///< Xpert Ultra specificity
double Se_dCXR; ///< Sensitivity of digital chest X-ray
double Sp_dCXR; ///< Specificity of digital chest X-ray
double AbleSputum[2]; ///< % of asymptomatic/symptomatic able to provide sputum specimens
double TongueSwabRelSe[2]; ///< relative sensitivity of tongue swab test compared to sputum
double TongueSwabTested; ///< % of those not providing sputum who are offered tongue swab testing
double TongueSwabDetected[2]; ///< % of Xpert-detectable TB detected by swab, not sputum, in D2D
double InitialLTFU[2]; ///< % of diagnosed TB cases that never start Rx (smear, Xpert)
double EmpiricRx[2][2]; ///< % of TB suspects treated empirically without any testing,
///< by Rx-seeking (1 = TB symptoms, 0 = other) and true TB status 
double EmpiricRxNeg[2][2]; ///< % of TB suspects treated empirically after negative test
double EmpiricRednXpert; ///< % reduction in empiric Rx in Xpert-tested TB suspects
double LogEmpiricToMicro; ///< Ratio of log(empirical Rx rate) to log(microbiological testing rate)
double RRempiricOtherHealth; ///< RR of empiric Rx if seeking Rx for other health problems
double RRempiricNoTB; ///< RR of empiric Rx if patients doesn't actually have TB
double TBprevHHcontacts; ///< TB prevalence in adult contacts of TB cases
double HHcontactsPerCase; ///< # household contacts aged 10+, per index TB case
double HHcontactRxUptake; ///< % of TB-diagnosed household contacts who link to TB Rx
double ProbDSTifFailingRx1; ///< % of people failing Rx who get drug susceptibility testing
///< (excluding those failing Rx due to default) up to 2000
double ProbDSTifFailingRx2; ///< Ditto, 2001-2010
double ProbDSTifFailingRx3; ///< Ditto, post-2010
double RR_DSTdropout; ///< Relative rate of DST if failing Rx and dropping out of care
double AnnMortTB_Rx[2]; ///< Annual rate of TB mortality in patients receiving TB Rx (M, F)
double AnnMortTB_RxCurr[2]; ///< Current rate of TB mortality in patients receiving TB Rx
double ExcessMort1stMoTB_Rx; ///< Ratio of excess mort in 1st mo to monthly mort at >1 mo
double RatioMinToBaseTBmort; ///< RR treated TB mortality with no Rx delay
double RRmortRifRes1st; ///< RR mortality on 1st-line TB Rx if rif-resistant
double AnnDropoutTB_Rx[2]; ///< Annual rate of dropout in patients receiving TB Rx (M, F)
double RRdefaultDOT; ///< Relative rate of default if treatment is directly observed
double DOTSeffectivenessAdj; ///< Relative rate of DOTS effectiveness in the 'real world'
double UltTBdefaultAdj; ///< RR ultimate default, relative to pre-2016
double TBfullRxCure; ///< Probability of cure if treatment is completed
double TBpartialRxCure; ///< Fraction of TB Rx dropouts who are cured
double AcquireRifResIfFail; ///< Prob of acquiring rif resistance if failing treatment
double ORacquireRifRes100CD4; ///< Increase in odds of resistance per 100
double ORfailureRifRes; ///< OR for 1st-line Rx failure if rif-resistant

///< TB/isoniazid preventive therapy (TPT/IPT) and nutrition

double RR_IPTuptakeNoLTBI; ///< RR IPT uptake in people who are susceptible (no latency)
double RR_IPTuptakePrevTB; ///< RR IPT uptake in people who previously had TB
double RR_IPTuptakeCD4[4]; ///< RR IPT uptake in by CD4 (500+, 350-499, 200-349, <200)
double RR_IPTuptakeARTdur[6]; ///< Index 0 corresonds to ART-naive, 1 = 1st yr of ART
int IPTdataYr; ///< Year to which number of IPT initiators are specified
double IPTuptakeUlt; ///< Monthly rate of IPT uptake after IPTdataYr
double MnthlyTPTdropout; ///< Monthly rate of TPT dropout
double IPTefficacy; ///< % reduction in active TB risk while on IPT
double Cure3HP; ///< % of people cured after completing 3HP
double NutritionEfficacy; ///< % reduction in TB incidence due to nutrition support

///< Initalization parameters

double InitialActiveTB[16][2]; ///< Propn with initial active TB, by age and sex
double InitActiveTBsmPos[2]; ///< Propn of active TB that is initially smear-pos
double InitPreviousTB[6][2]; ///< History of previously treated TB, by age & sex
double InitLTBI[2];
double InitLTBIscaling;
double InitRR_TBprev; ///< Initial % of TB cases that are rifampicin-resistant

///< Variables/intermediate outputs that are calculated

double SocialMixMatrix[5][2][4][2]; ///< By age & sex of contact, and age & sex of indiv
double RateNewTBinfection[91][2]; ///< Monthly rate of new infection, by age and sex
double InitPropnSmPos[91][2];
double InitPropnSmNeg[91][2];
double InitLTBIprev[91]; ///< Initial prevalence of latent TB, by age
double InitTBhistory[91][2];
double SumTBgroupsM[81][44]; ///< Population totals by age and HIV stage, in men
double SumTBgroupsF[81][44]; ///< Population totals by age and HIV stage, in women
double SumTB[81][2]; ///< Population totals by age and sex
double RatioHIVtoTBpopM[81][44]; ///< Adjustment to bring TB total in line with HIV model
double RatioHIVtoTBpopF[81][44]; ///< Adjustment to bring TB total in line with HIV model
double HIVeffectTBinc[44];
double HIVeffectTBmort[44];
double HIVeffectTBimm[44];
double HIVeffectTBrecov[44];
double HIVeffectIPTstart[44];
double HIVeffectRifRes[44];
double RR_TBmortByAge[81];
double TBmortSmPos[81][2]; ///< Total TB deaths in smear-pos cases, by age & sex
double TBmortSmNeg[81][2]; ///< Total TB deaths in smear-neg cases, by age & sex
double TBmortTreated[81][2]; ///< Total TB deaths after treatment initiation
double CurrXpertSe[2]; ///< Current sensitivity of Xpert/Ultra testing, by smear status
double CurrXpertSp; ///< Current specificity of Xpert/Ultra testing
double CurrSeTB[2][2]; ///< Current sensitivity of TB testing, by smear status and HIV status
double CurrSeTB_HHC[2]; ///< Current sensitivity of TB testing in HH contacts, by smear status
double CurrSeTB_ART[2]; ///< Current sensitivity of TB testing in ART patients, by smear status
double CurrSeTBprev[2]; ///< Current sensitivity of TB testing in previous TB patients, by smear status
double CurrSeTB_D2D[2]; ///< Current sensitivity of TB door-to-door testing, by smear status
double CurrSpTB; ///< Current specificity of TB testing
double CurrDSTcoverageRR; ///< Current % of rif-res TB cases that get drug sensitivity testing pre-Rx
double ProbDSTifFailingRx; ///< % of failing patients who get DST, if continuing treatment
double CurrInitLTFU; ///< Current initial LTFU
double CurrDurTPTprotection; ///< Current average duration of TPT protection (in months)
double NewTBreactivation; ///< # new TB cases due to reactivation
double NewEmpiricTB[2]; ///< TB treated in absense of a test, or after a negative test
double TBindexCasesLastMonth; ///< New TB cases diagnosed in health facilities last month
double TBindexCasesLastYr; ///< New TB cases diagnosed in health facilities last year
double RelapseTBpropnLastYr; ///< % of new TB cases last year that were relapses in high-risk period
double NewRxACF[2]; ///< New TB cases starting Rx after diagnosis through HHC tracing (by smear status)
double NewRxART_ICF[2]; ///< New TB cases starting Rx after intensive case finding in ART patients
double NewRxTBscreenPrev[2]; ///< New TB cases starting Rx after screening previous TB patients
double NewRxTBscreenD2D[2]; ///< New TB cases starting Rx after door-to-door screening 
double HHscreeningProb; ///< Prob of being screened due to living with a TB index case
double HHscreeningProbNeg; ///< Prob of being screened if not currently experiencing TB
double TotARTbyTB[3]; ///< ART patients with smear-neg TB, smear-pos TB and no TB
double PrevTBbyCurrTB[3]; ///< # previous TB cases with smear-neg TB, smear-pos TB and no TB
double NewIPT_TSTpos; ///< Adults starting TPT, latently infected
double NewTPT_HH; ///< Adults starting TPT, latently infected, as a result of HH contact screening
double TBincRednNutrition; ///< Reduction in TB incidence due to nutrition

//============================================================================
///< Parameters and arrays for non-HIV mortality
//============================================================================

double CurrNonAIDSmortEA[91][2]; ///< Current non-AIDS mortality prob by EXACT age
double CurrNonAIDSmortALB[91][2]; ///< Current non-AIDS mortality prob by age last b'day
double NonAIDSmortM[91][38]; ///< non-AIDS mortality rates in males, by age and by year
double NonAIDSmortF[91][38]; ///< non-AIDS mortality rates in females, by age and by year
double UltNonAIDSmort[91][2]; ///< Ultimate non-AIDS mortality rates, by age and sex
double RednNonAIDSmort[91][2]; ///< Non-AIDS mortality reduction factor, post-2007
double WestLifeExpectP[11][2]; ///< West level 26 life expectancy for children, undiscounted 
double WestLifeExpectA[81][2]; ///< West level 26 life expectancy for adults, undiscounted 
double IHMEdisab[5]; ///< Disability weights by untreated CD4 stage (1-4) and ART (5)
double DisabilityWeights[39][2][81]; ///< IHME disability weights by HIV stage, sex and age
double DiscountRate; ///< Discount rate per annume (relevant to DALY calcs, LYs lost)
double NonHIVmortChange; ///< Alpha parameter in Brass relational logit model
						 ///< (Only relevant if UseBrassLogit = 1)

//============================================================================
///< Parameters and arrays for fertility
//============================================================================

double ObservedFert[35][36]; ///< Observed fertility rates by age and year up to 2020
double FertByAgeLB[36]; ///< col Y
double HIVnegSEfert[36]; ///< Fertility in sexually experienced HIV-neg women (col Z)
double StoredFert[36]; ///< Stored values of FertByAgeLB (col AB)
double FertLastYr[36][2]; ///< Fertility last year, in HIV-neg/undiagnosed and diagnosed
double UltFert[35]; ///< Ultimate fertility rate
double AdjustedFert[35]; ///< col AD
double RednFert[35]; ///< Fertility reduction factor post-2007
double CurrentFert[36]; ///< col AF
double RelativeFert[44][36]; ///< Relative rates of fertility by HIV stage & age
double LactatingAdj[36]; ///< RR of HIV-diagnosed fertility by age due to difs in lactation
double RelativeFertART[20][36]; ///< Relative rates of fertility x % on ART, in ART states
double BirthsByHIVstage[36][9]; ///< columns AR-AZ
double BirthsByHIVstageAdj[36][5]; ///< As before, adjusted to reflect CURRENT ART use
double TotBirthsByStage[9]; ///< Range AR42:AZ42
double CD4propn[4]; ///< Range AT50:AW50
double MatIncidenceAN; ///< Anual antenatal HIV incidence in pregnant women
double MatIncidencePN[36]; ///< HIV incidence in breastfeeding women, by age of kid (mo)

//============================================================================
///< Parameters and arrays for migration
//============================================================================

double MigrationAdj[91][2]; ///< Migration adjustment factors at end of current yr
double NetMigrants[91][38][2]; ///< Number of net in-mgrants, by age, year and sex
double MigrationHIVadj[91][4]; ///< RR HIV after migration: 1995, 2000, 2010, 2021
double RecentIntImmig; ///< Proportion of population that moved into SA over last yr
double RecentIntImmigP; ///< Proportion of children who moved into SA over last yr
double PrevRatioIntImmig; ///< Ratio of HIV prev in international immigrants to local

//=========================================================================
///< Variables for mother-to-child transmission (formerly 'Births' sheet)
//=========================================================================

double PTP; ///< positive at 1st ANC visit, tested positive
double PTN; ///< positive at 1st ANC visit, tested negative
double PUT; ///< positive at 1st ANC visit, untested
double PTNRP; ///< positive at 1st ANC visit, tested negative, retested positive
double PTNRN; ///< positive at 1st ANC visit, tested negative, retested negative
			  ///< or not retested
double PUTLP; ///< positive at 1st ANC visit, untested, later tested positive
double PUTLN; ///< positive at 1st ANC visit, untested, later tested negative or
			  ///< remained untested
double ARTmothers; ///< mothers already on HAART prior to 1st ANC visit

double NTNRP; ///< negative at 1st visit, tested negative, retested positive
double NTNRN; ///< tested negative, became infected, retested negative or not retested
double NUTLP; ///< untested at 1st visit, became infected, later tested positive
double NUTLN; ///< untested at 1st visit, became infected, later tested negative or
			  ///< remained untested
double NRN; ///< negative at 1st visit, remained negative

double TestedPosCD4[4]; ///< tested positive prior to delivery, not on HAART, by CD4
double TestedPosOnART[2]; ///< tested positive prior to delivery, initiated HAART
double UndiagnosedPos; ///< positive at 1st antenatal visit but never diagnosed
double RecentPosDet; ///< recent positive infection, detected
double RecentPosDetART; ///< recent positive infection, detected & started ART
double RecentPosUndet; ///< recent positive infection, undetected

double ChildPosNoPMTCT; ///< cell O4
double ChildPosPMTCT; ///< cell O5
double ChildNegMotherPosKnown; ///< cell O6
double ChildNegMotherPosUnknown; ///< cell O7
double ChildNegMotherNeg; ///< cell O8

//=============================================================================================
///< Parameters and arrays for age-specific transitions between paed HIV states ('Child rates')
//=============================================================================================

double AveARTstartLate; ///< average rate of ART start in last 3 years, for kids with late HIV
double MortAdjLate[3]; ///< effect of ART on change in CD4 distribution at CD4 <15%, current year
double PropnBF[37][3]; ///< propn of mothers practising breastfeeding strategy, by age of child
double RateOfBFchange[36][3]; ///< rate at which mothers change breastfeeding strategy
double StartingARTnoBirthPCR[132][2]; ///< Used to calculate ART initiation rate
double PaedARTinitiation; ///< Monthly rate of ART initiation in curr year (range U152)
double ARTinitiation[132]; ///< Monthly cts rate at which ART is initiated
double ARTinitiationStore; ///< Stored rate of ART initiation from last year for which data available
double ProgToNeedNoPMTCT[132]; ///< prob of progression to ART need if infected at birth, no PMTCT
double ProgToNeedPMTCT[132]; ///< prob of progression to ART need if infected at birth, failing PMTCT
double ProgToNeedPostnatal[132]; ///< prob of progression to ART need if infected postnatally
double AIDSmortNoART[132]; ///< prob of AIDS mortality if untreated and ART-eligible
double AIDSmortEarlyART[132]; ///< prob of AIDS mortality if initiated ART early
double NegMatExit[36][3]; ///< rates at which HIV-negative mothers leave the breastfeeding state
double AcuteMatExit[36][4]; ///< rates at which acutely-infected mothers leave the BF state
double ChronicMatExit[36][3]; ///< rates at which chronicly-infected mothers leave the BF state
double KnownMatMFexit[36][3]; ///< rates at which women of known HIV+ status leave the BF state
double KnownMatEBFexit[36][4]; ///< rates at which women of known HIV+ status leave the EBF state
double ARTmatMFexit[36][3]; ///< rates at which women on ART leave the BF state
double ARTmatEBFexit[36][4]; ///< rates at which women on ART leave the BF state
double ARTexitHR[132][4]; ///< rates at which treated children leave the high risk ART state
double MnthlyTestingPaed[132][2]; ///< Mnthly prob of testing in kids by age (early/late disease)
double MnthlyPaedTestToART[132][4]; ///< Mnthly prob of testing AND starting ART
double MnthlyPaedDiagNoART[132][4]; ///< Mnthly prob of being diagnosed but NOT starting ART

//=========================================================================
///< Intermediate outputs (formerly 'Monthly' sheet)
//=========================================================================

///< Flow variables that are updated monthly

double AIDSdeathsOnART;
double AIDSdeathsDiagP[3];
double AIDSdeathsART_P[3];
double AIDSdeathsYOB[2]; ///< AIDS deaths in kids born in the current projection year
double NewPerinatal;
double NewPerinatalART; ///< From mothers on ART
double NewPerinatalNoKOS; ///< From mothers who are undiagnosed (no knowledge of status)
double NewPostnatal;
double NewPostnatalART; ///< From mothers on ART
double NewPostnatalNoKOS; ///< From mothers who are undiagnosed
double NewPostnatal18;
double NewHIVinANC;
double NewHIVlactating;
double BirthsNegMothers;
double BirthsPosMothers;
double BirthsARTmothers;
double BirthsDiagMothers;
double AdultsNewARTbyCD4[4][2]; ///< Note stage runs from highest CD4 to lowest
double AdultsReinitARTbyCD4[4][2]; ///< Resuming ART after an interruption
double ChildNewARTlate;
double ChildReinitARTlate; ///< Children aged 10-14
double ChildReinitARTearly; ///< Children aged 10-14
double NewElig350[2]; ///< Number of M and F (15+) becoming eligible at 350 threshold
double NewElig500[2]; ///< Number of M and F (15+) becoming eligible at 500 threshold
double NewlyTestedNeg[3]; ///< Indivs who tested negative through HCT in current year (M, F, child)
double NewlyTestedPos[3];
double NewlyTestedFalseNeg[3]; ///< Indivs who tested in the acute phase of infection
double NewlyTested1stPos[2];
double NewlyTestedPaed[3][2]; ///< Newly tested by age (18, 19-59, 60-179 mo) and HIV status
double NewlyTestedAdult[3][2]; ///< Newly tested by age (15-24, 25-49, 50+) and sex
double PosTestedAdult[3][2]; ///< Positive tests by age (15-24, 25-49, 50+) and sex
double ANCtestsByAge[2][2]; ///< 1st ANC tests by maternal age (15-24, 25+) and HIV status
double NewlyTestedNegST[6]; ///< # HIV-neg self-test results, by testing modality
double NewlyTestedPosST[6]; ///< # HIV-pos self-test results, by testing modality
double NewSTtoART[6]; ///< # HIV-pos self-testers who subsequently start ART, by modality
double NewPrEP_AGYW;
double NewPrEP_FSW;
double NewPrEP_MSM;
double NewPrEP_PWID;
double NewCABLA_AGYW;
double NewCABLA_FSW;
double NewCABLA_MSM;
double NewCABLA_PWID;

///< Age-specific flow variables that are updated monthly

double PaedNewARTbyAge[15]; ///< Age groups
double PaedNewARTlate[11];
double NewHIVbyAgeSex[81][2];
double NonAIDSdeathsP[11][2]; ///< Non-AIDS deaths in children
double AIDSdeathsByAgeP[11][2]; ///< AIDS deaths at ages 0-10
double AIDSdeathsByAge[81][2]; ///< AIDS deaths at ages 10+
double TotBirthsByMatAge[36]; ///< Ages 14-49
double AIDSdeathsMarriedM[76][2][2]; ///< AIDS deaths in men married to women
double AIDSdeathsMarriedF[76][2][2]; ///< AIDS deaths in married women
double AIDSdeathsMarriedMSM[76]; ///< AIDS deaths in married MSM
double AdultsNewARTbyAge[4][2]; ///< Number of adults starting ART by age & sex
double NewOIdiagnoses[10][2]; ///< OIs leading to HIV diagnosis, by age and sex

double NewActiveTBbyAgeSex[81][2];
double NewHIVposTBbyAgeSex[81][2];
double NewTBonARTbyAgeSex[81][2];
double NewRecurrentTBbyAgeSex[81][2];
double NewRelapseTBbyAgeSex[81][2];

///< Age-specific flow variables that are calculated from monthly outputs

double NonAIDSdeathsA[81][2]; ///< Non-AIDS deaths in adults
double TotDeathsByAgeP[11][2]; ///< Total deaths in children, by age and sex
double TotDeathsByAge[81][2]; ///< Total deaths in adults, by age and sex
double MortProbExact[91][2]; ///< Mortality prob by exact age
double LifeTable[91][2];

///< Stock variables that are updated annually

double TotalPop_S[91][2]; ///< Size of the population, by age and sex, at start of yr
double TotalPositive_S[91][2]; ///< Size of HIV-positive population at start of yr
double TotalDiagnosed_S[91][2]; ///< Number of people diagnosed positive at start of yr
double TotalART_S[91][2]; ///< Number of ART patients at start of yr
double TotalNaiveElig_S[91][2]; ///< Number who are ART-naive but eligible for ART
double TotalInterrupt_S[91][2]; ///< Number who are ART-naive but eligible for ART
double TotalSexuallyExp_S[91][2]; ///< Number of individuals who are sexually experienced
double TotalMarried_S[91][2]; ///< Number of individuals who are married at start of yr

//=========================================================================
///< Arrays and variables used in calibration and uncertainty analysis
//=========================================================================

///< HIV data inputs

double ObservedPrev05[12][2]; ///< HIV prevalence in 2005 HSRC survey by age & sex
double ObservedPrev08[12][2];
double ObservedPrev12[12][2];
double ObservedPrev16[9][2];
double ObservedPrev17[12][2];
double ObservedPrev22[12][2];
double ObservedPrevU208; ///< HIV prevalence in kids aged <2 in 2008
double ObservedProvHH_P[5]; ///< HIV prevalence in kids aged 2-14 in selected province, by year
double ObservedProvHH[6][2]; ///< HIV prevalence in selected province by year and age (15-24, 25+)
double ObservedPrevANC[5][29]; ///< ANC prevalence by age and year (1991-2015, 2017, 2019, 2022, 2025)
double ObservedProvANC[26]; ///< ANC prevalence in selected province (1990-2015, 2017)
double ObservedPrevHCT[16]; ///< HIV prevalence in adults tested for HIV 2004-8, 2010, 2012, 2015-23
double ObservedPrevHCT_P[8]; ///< HIV prevalence in kids tested for HIV, 2015-21
double ObsHCTprevAgeSex[5][4]; ///< HIV prev in HCT by risk (M 15-24, F 15-24, 25-49, 50, ANC) & yr
double ObsCoverage[2][3]; ///< % of HIV-positive M & F (1st index) on ART by survey (2nd index)
double ObsAHDpaedART[4]; ///< % of kids starting ART w severe immunodeficiency (DHIS, by year)
double SEprev05[12][2]; ///< std error of HIV prevalence estimates in 2005 HSRC survey
double SEprev08[12][2];
double SEprev12[12][2];
double SEprev16[9][2];
double SEprev17[12][2];
double SEprev22[12][2];
double SEprevU208;
double SEprovHH_P[5];
double SEprovHH[6][2];
double SEprevANC[5][29];
double SEprovANC[26];
double SEprevHCT[16];
double SEprevHCT_P[8];
double SEcoverage[2][3];
double SE_AHDpaedART[4];
double RecordedHCT_P[5]; ///< Recorded numbers of HIV tests in children, 2015-17. Redundant
double RecordedHCT_P_CoV[5]; ///< Coefficients of variation for numbers of HIV tests in kids (on log scale)
double AdultTestsAgeSex[5][4]; ///< Propn of adult HIV tests by risk (M 15-24, F 15-24, 25-49, 50, ANC), year
const int nCSWstudies = 5;
double CSWstudyDetails[nCSWstudies][3];
const int nMSMstudies = 0;
double MSMstudyDetails[nMSMstudies+1][4];
const int nPWIDstudies = 0;
double PWIDstudyDetails[nPWIDstudies + 1][3];
const int nPWIDstudiesFtoM = 0;
double PWID_FtoMdetails[nPWIDstudiesFtoM + 1][3];
double AgeDbnAdultsOnART[7][9][2]; ///< % of treated adults in each age group (2nd index) by yr (1st index), sex
double AgeDbnKidsStartingART[10][2]; ///< Propn of kids starting ART in <1 and 1-4 age groups (2nd index)
									///< by year (1st index, starting 2004)
double AgeDbnKidsOnART[8][2]; ///< Propn of kids on ART in 0-4 & 5-9 age groups (2nd index), since 2011
							  ///< by year (1st index, starting 2004)

double ProvANCbias = 0.0; 
double ANCageWeights[6]; ///< Propn of births in 15-19, 20-24, 25-29, 30-34, 35-39, 40-49 age groups
double ANCageW_init[6]; ///< Initial ANC age weights, up to 2012
double ANCageW_change[6]; ///< Annual change in ANC age weights after 2012
double SpecificityANC; ///< Specificity of ELISA used in ANC surveys, 1997-2015
double RRprevPrivateANC; ///< RR HIV in women attending private antenatal clinics
double PropnPregPrivate[7]; ///< Proportion of pregnant women seeking private antenatal care, by age
double Miscarriage[2]; ///< Prob of miscarriage/stillbirth in HIV-neg and HIV-positive pregnant women
double FractionRecentF[6][81]; ///< % of F infections acquired in last year, by age (15-19, ..., 40-49)

double RecordedDeathsP[4][22][2]; ///< Stats SA recorded paed deaths by age, year (1997-2018) & sex
double RecordedDeathsA[16][22][2]; ///< Stats SA recorded adult deaths by age, year (1997-2018) & sex
double AdultCompleteness[16][22][2]; ///< % of deaths at ages 20+ that get recorded, by age, year & sex
double PaedCompleteness[4][22][2]; ///< % of paed deaths that get recorded, by age, year and sex
double AdjustedCompleteness[22][2]; ///< completeness adjustment in provincial model, by year and sex
double SElogNonHIVmort; ///< std error in non-HIV mortality estimates, on log scale

double EverTested05[5][2][2]; ///< Proportion ever tested in 2005 HSRC survey by age, sex & HIV status
double EverTested08[5][2][2]; ///< Proportion ever tested in 2008 HSRC survey by age, sex & HIV status
double EverTested12[5][2][2]; ///< Proportion ever tested in 2012 HSRC survey by age, sex & HIV status
double EverTested16[4][2][2]; ///< Proportion ever tested in 2016 DHS by age, sex & HIV status
double EverTested17[5][2][2]; ///< Proportion ever tested in 2017 HSRC survey by age, sex & HIV status
double EverTested22[5][2][2]; ///< Proportion ever tested in 2022 HSRC survey by age, sex & HIV status
double SEtested05[5][2][2]; ///< std error of HIV prevalence estimates in 2005 HSRC survey
double SEtested08[5][2][2];
double SEtested12[5][2][2];
double SEtested16[4][2][2];
double SEtested17[5][2][2];
double SEtested22[5][2][2];
double SeTestingHistory[2]; ///< Sensitivity of self-reported HIV testing history (HIV-neg & -pos)
double SpTestingHistory; ///< Specificity of self-reported HIV testing history 

double ChildPIPdeaths[13][2]; ///< Total audited deaths 2005-2017, ages 1-4 and 5-9
double ChildPIPdiag[13][2]; ///< % of deaths diagnosed HIV-positive, 2005-2017, ages 1-4 and 5-9
double ChildPIP_ART[13][2]; ///< % of HIV-diagnosed deaths on ART 2005-2017, ages 1-4 and 5-9
double RRdiagDeathsPIP[2]; ///< RR of death being recorded in facility if HIV-neg/undiagnosed compared to 
						   ///< (a) diagnosed ART-naive, and (b) ART-experienced

double AIDScasesByYr[5]; ///< Reported new adult AIDS cases, 1990-94
double AIDScasesProfile[10][2]; ///< Reported new adult AIDS cases (1993-94) by age (1st index) & sex

const int ARTdataPoints = 206; ///< Number of reported ART totals that combine adults and children
const int ARTdataPointsP = 192; ///< Number of reported ART totals in children
const int ARTdataPointsM = 8; ///< Number of estimates of fraction of adult ART patients who are men
double ARTtotals[ARTdataPoints][5]; ///< Total numbers on ART in public and private sectors
double ARTtotalsP[ARTdataPointsP][5]; ///< Total children on ART in public and private sectors
double ARTmale[ARTdataPointsM][3]; ///< Proportions of ART patients who are male (year, mean, SE)
double RecordedARTstart[12][4][2]; ///< Number starting ART by year, CD4 and sex
double LastDateCum; ///< Last date when reported public totals were definitely cumulative
double AnnSwitchCumToCurr; ///< Annual rate of switch from reporting cumulative totals to current 
						   ///< totals, after LastDateCum
double AveDurImmART[2]; ///< Average time spent on ART from outside SA for recent migrants (2017, 2022)
double SDchangeBspline; ///< Std deviation of change in B spline coefficient (sampled from hyperprior)
double MalePropnART[86]; ///< Fraction of adult ART initiators who are male (by year)
double TotBeginART[86]; ///< Total # patients starting ART (by year)
double RecordedARTpreConcep[6][5]; ///< % of HIV+ women in ANC previously on ART, by year and age
double MarriageData[15][2][4]; ///< % of adults married by age and sex, in 1996, 2001, 2007, 2016

///< HIV model outputs/parameters used in calibration

double ModelPIPdiag[13][2];
double ModelPIP_ART[13][2];

double OIsDiagnosedByYr[5]; ///< Modelled # OIs leading to HIV diagnosis, 1990-94
double OIsDiagnosedProfile[10][2]; ///< Modelled # OIs leading to HIV diagnosis (1993-4), by age & sex

double ModelPrevPaed[3][2][2]; ///< Prevalence by age (2-4, 5-9, 10-14), sex and year (2005, 2008)
double ModelPrevPaed2[2][2][3]; ///< Prevalence by age (0-4, 5-14), sex and year (2012, 2017, 2022)
double ModelPrevU208; ///< Prevalence under age 2 in 2008 
double ModelProvHH[6][2];
double ModelProvHH_P[5];
double ModelPrevHCT[16];
double ModelPrevHCT_P[8];
double ModelTestsAgeSex[5][4];
double ModelPosTestsAgeSex[5][4];
double ModelCoverage[2][3];
double ModelAHDpaedART[4];

double ModelDeathsP[4][22][2]; ///< Model estimates of paed deaths by age, year (1997-2018) & sex
double ModelDeathsA[16][22][2]; ///< Model estimates of adult deaths by age, year (1997-2018) & sex

double ModelTested05[5][2][2]; ///< Model estimate of % ever tested in 2005, by age, sex & HIV status
double ModelTested08[5][2][2]; ///< Model estimate of % ever tested in 2008, by age, sex & HIV status
double ModelTested12[5][2][2]; ///< Model estimate of % ever tested in 2012, by age, sex & HIV status
double ModelTested16[4][2][2]; ///< Model estimate of % ever tested in 2016, by age, sex & HIV status
double ModelTested17[5][2][2]; ///< Model estimate of % ever tested in 2017, by age, sex & HIV status
double ModelTested22[5][2][2]; ///< Model estimate of % ever tested in 2022, by age, sex & HIV status

double ARTmodelled[ARTdataPoints][2]; ///< Modelled total number on ART (current and cumulative)
double ARTmodelledP[ARTdataPointsP][2]; ///< Modelled total children on ART (current and cumulative)
double ARTmodelledM[ARTdataPointsM]; ///< Modelled % of adult ART patients who are male
double BsplineCoef[10]; ///< B spline coefficients for total numbers starting ART
double BsplineCoefP[10]; ///< B spline coefficients for total children starting ART
double ModelAgeDbnAdultART[7][9][2];

double ModelMarried[15][2][4]; ///< % of adults married by age and sex, in 1996, 2001, 2007, 2016

///< TB data inputs used in calibration

double RecordedTBdeathsA[16][23][2]; ///< Stats SA TB deaths by age, year (1997-2016) & sex
double ExpectedTBdeathsPLHIV[14]; ///< Expected # TB deaths in HIV+ adults, based on post-mortem studies
double SE_TBdeathsPLHIV[14]; ///< Std error for # TB deaths in HIV+ adults, based on post-mortem studies
double RecordedTBcasesA[16][13][2]; ///< ETR cases treated by age, year (2004-2016) & sex
double ETRmortPropn[13][2]; ///< % of TB cases recorded as dead in ETR, by year (2004-2016) & sex
double RecordedTBlabA[20]; ///< Recorded numbers of microbiologically-tested adults (negative & positive)
double ETR_HIVprev[8]; ///< HIV prevalence in adult TB patients in ETR
double TBprevSurvey[2]; ///< Recorded pulmonary TB prevalence in 2017 survey, by sex
double TBprevSurveySE[2]; ///< Std error for recorded pulmonary TB prevalence in 2017 survey, by sex
double PropnETB[2]; ///< Proportion of TB that is extrapulmonary, by HIV status
double DataRifResPrev[2]; ///< Proportion of TB that is rifampicin-resistant
double DataRifResSE[2]; ///< Stanard error for proportion of TB that is rifampicin-resistant
double TotRifResDiagnosed[11]; ///< Reported number of diagnosed rifampicin-resistant cases (2010-2020)
double Recorded2ndLineTB[13]; ///< Reported # patients starting 2nd-line TB treatment (2007-2019)
double SmPosStudyDetails[4][3]; ///< Details of household surveys measuring % of TB that is smear-pos
double RRscreenStudyDetails[4][3]; ///< Details of surveys measuring RR screening in symptomatic TB
double TB_HIV_ORdetails[9][3]; ///< Details of surveys measuring HIV-TB association

///< TB model outputs used in calibration

double ModelTBdeathsA[16][23][2]; ///< Model estimates of TB deaths by age, year (1997-2016) & sex
double ModelTBcasesA[16][13][2]; ///< Model estimates of TB cases treated by age, year (2004-16) & sex
double TBprev2018[2]; ///< Modelled pulmonary TB prevalence in 2018, by sex

///< Priors and likelihood

double LogLikelihood;
const int MCMCdim = 21; ///< Number of parameters in uncertainty analysis // MK updated to 21 from 49 to run TB model
const int MaxPriors = 145; ///< Number of input rows in Priors file (145 for HIV, 63 for TB) // MK updated to 63 from 145 to run TB model
int InclPriors[MaxPriors][2]; ///< Indicator of which priors are included (1st index) and if
							  ///< included their index in MCMCdim (2nd index)
double RandPrior[MCMCdim]; ///< Random numbers used to sample from prior in current simulation
double Cholesky1[MCMCdim][MCMCdim];
double Covariance[MCMCdim][MCMCdim]; ///< The covariance matrix for the MCMC parameters
const int InitSample = 10000;
const int ResampleSize = 14; // MK edit 
int SampleID[ResampleSize];
int CurrSim;
double temp[ResampleSize][41]; ///< Previously local to the SampleInput function in OutputArray class

///< Parameters for IMIS

const int IMISind=1; ///< 0 = no IMIS; 1 = IMIS
const int IMISsteps=200; ///< max # steps in IMIS algorithm
const int StepSample=1000; ///< # additional simulations at each IMIS step after the first
const int TotalSimulations=209000; ///< Must be = InitSample + StepSample * (IMISsteps - 1)
const int ImportanceSamplingStep1=0; ///< 1 if importance sampling is used in step 1, 0 otherwise
int CurrIMISstep; ///< indicates current position in IMIS algorithm
double LogLxWeight[TotalSimulations]; ///< Log of (likelihood * importance ratio)
double weights[TotalSimulations]; ///< Sample weights calculated from LogLxWeight
double RandomParameterIMIS[MCMCdim+1][TotalSimulations]; ///< The '+1' is to record logL
int PriorTypes[MCMCdim]; ///< Indicators for prior types (0 = beta, 1 = gamma, 2 = normal)
double aParameters[MCMCdim]; ///< Alpha parameters for priors
double bParameters[MCMCdim]; ///< Beta parameters for priors
double aParameters2[MCMCdim]; ///< Alpha parameters for importance distributions
double bParameters2[MCMCdim]; ///< Beta parameters for importance distributions
double MixtureMean[IMISsteps][MCMCdim]; ///< Means of the different mixture components
double PosteriorMean[IMISsteps][MCMCdim]; ///< Means of the posterior dbn at different IMIS steps
double NextMode[MCMCdim+1]; ///< Parameter values & LogLxWeight for best parameter combination
double cholIMIS[MCMCdim][MCMCdim][IMISsteps];
double invIMIS[MCMCdim][MCMCdim][IMISsteps];
double sorted[TotalSimulations]; ///< Used in the GetPercentile function
double LogIntegratedL[IMISsteps]; ///< Log of integrated likelihood estimated at each IMIS step
double FractionUnique[IMISsteps]; ///< Expected fraction of points in resample that are unique
double EffectiveSS[IMISsteps]; ///< Effective sample size
double Efficiency[IMISsteps]; ///< Effective sample size/ # function evaluations
double Distance[TotalSimulations]; ///< Mahalanobis distance
double CumLxWeight[TotalSimulations+1];
double ARTerrorHistory[TotalSimulations];

//===========================================================================
///< Classes
//===========================================================================

class Child
{
	public:

	int Sex; ///< 0 = male, 1 = female
	double PropnBirths;
	double NonAIDSmort[132];
	double NewNonVertCurrY;

	///< Arrays to represent population profile at START of month
	double NegMatMF[133];
	double NegMatEBF[133];
	double AcuteMatMF[133];
	double AcuteMatEBF[133];
	double UnawareMatMF[133];
	double UnawareMatEBF[133];
	double AwareMatMF[133];
	double AwareMatEBF[133];
	double ARTmatMF[133];
	double ARTmatEBF[133];
	double NegChildFF[133];
	double PosChildAtBirthNoPMTCT[133];
	double PosChildAtBirthPMTCT[133];
	double PosChildAfterBirth[133];
	double ARTeligible[133];
	double DiagChildAtBirthNoPMTCT[133];
	double DiagChildAtBirthPMTCT[133];
	double DiagChildAfterBirth[133];
	double DiagARTeligible[133];
	double OnARTearly[133];
	double OnARTlate1st3m[133];
	double OnARTlateAfter3m[133];
	double StoppedART[133];
	double Total[133];

	///< Arrays to represent population profile at END of month
	double NegMatMF_E[133];
	double NegMatEBF_E[133];
	double AcuteMatMF_E[133];
	double AcuteMatEBF_E[133];
	double UnawareMatMF_E[133];
	double UnawareMatEBF_E[133];
	double AwareMatMF_E[133];
	double AwareMatEBF_E[133];
	double ARTmatMF_E[133];
	double ARTmatEBF_E[133];
	double NegChildFF_E[133];
	double PosChildAtBirthNoPMTCT_E[133];
	double PosChildAtBirthPMTCT_E[133];
	double PosChildAfterBirth_E[133];
	double ARTeligible_E[133];
	double DiagChildAtBirthNoPMTCT_E[133];
	double DiagChildAtBirthPMTCT_E[133];
	double DiagChildAfterBirth_E[133];
	double DiagARTeligible_E[133];
	double OnARTearly_E[133];
	double OnARTlate1st3m_E[133];
	double OnARTlateAfter3m_E[133];
	double StoppedART_E[133];
	double Total_E[133];

	///< Arrays to represent movements in the course of the month
	double AIDSdeaths[133];
	double AIDSdeathsUntreated[133];
	double AIDSdeathsUndiagnosed[133];
	double NonAIDSdeaths[133];
	double NewHIVpostnatal[133];
	double StartingART[133];
	double StartingARTlate[133];
	double NewMatHIV[133];
	double NewMatUnaware[133];
	double NewMatAwareMF[133];
	double NewMatARTMF[133];
	double NewPostnatalDiag[18];

	Child(int Gender);
	void GetStartYrProfile();
	void GetNonAIDSmort(); ///< Converts annual mortality to monthly mortality
	void GetEndProfile();
	void UpdateStartProfile();
	void UpdateMigP();
};

class Adult
{
	public:

	int Sex; ///< 0 = male, 1 = female
	int Risk; ///< 1 = high risk, 2 = low risk
	int MarriedInd; ///< 0 = unmarried, 1 = married
	int VirginInd; ///< 0 = sexually experienced, 1 = virgin
	int FSWind; ///< 1 => Female sex worker
	int SpouseRisk; ///< 1 = high risk, 2 = low risk (only relevant if married)
	int CircInd; ///< 0 = uncircumcised, 1 = circumcised (only relevant to men)
	int MSMind; ///< 0 = heterosexual, 1 = bisexual/MSM (only relevant to men)
	int PWIDind; ///< 1 = people who inject drugs, 0 otherwise

	///< Arrays to represent population profile at START of month
	double NegNoHCT[81]; ///< HIV-negative, never tested for HIV
	double NegPastHCT[81]; ///< HIV-negative, previously tested
	double RegHCT[81]; ///< HIV-negative, receiving injectable PrEP (+ regular HCT)
	double RegPrEP[81]; ///< HIV-negative, receiving oral PrEP
	double RegVM[81]; ///< HIV-negative, receiving regular vaginal microbicide/DPV ring
	double PosNoHCT[81][5]; ///< HIV-positive, never tested for HIV (2nd index is CD4 stage)
	double PosHCTpreHIV[81][5]; ///< HIV-positive, last tested before HIV acquisition
	double PosDiagnosedPreART[81][5]; ///< Diagnosed HIV-positive, not yet on ART
	double OnARTpre500[81][5]; ///< On ART, having started at CD4 >=500 (2nd index is ART duration)
	double OnART500[81][5]; ///< On ART, having started at CD4 350-499
	double OnART350[81][5]; ///< On ART, having started at CD4 200-349 
	double OnART200[81][5]; ///< On ART, having started at CD4 <200 
	double StoppedART[81][4]; ///< Stopped ART (2nd index is CD4 stage)
	double Total[81];

	///< Arrays to represent population profile at END of month
	double NegNoHCT_E[81]; 
	double NegPastHCT_E[81]; 
	double RegHCT_E[81]; 
	double RegPrEP_E[81]; 
	double RegVM_E[81]; 
	double PosNoHCT_E[81][5];
	double PosHCTpreHIV_E[81][5]; 
	double PosDiagnosedPreART_E[81][5]; 
	double OnARTpre500_E[81][5]; 
	double OnART500_E[81][5]; 
	double OnART350_E[81][5]; 
	double OnART200_E[81][5]; 
	double StoppedART_E[81][4]; 
	double Total_E[81];

	///< Arrays to represent HIV transmission probabilities
	double ProbTransm[81][18]; ///< Stage indices are defined differently for M, F, MSM, FSW.
							   ///< See ProbTransm.xlsx for exact definitions.
	double ProbTransmPWID[4]; ///< For no PrEP, CAB-LA, oral PrEP and rings
	double ProbHIVacq[81][4]; ///< Prob of HIV acquisition
	double FSWcontactsByAge[81]; ///< Annual total, only relevant to high risk men

	///< Arrays to represent movements in the course of the month/year
	double AIDSdeathsUntreated[81];
	double AIDSdeathsTreated[81];
	double NewHIV[81];
	double StartingART[81][4]; ///< 2nd index is baseline CD4 stage
	double NewARTbyCD4[4];
	double NewARTbyAge[4]; ///< Age groups 15-24, 25-34, 35-44, 45+

	Adult(int Gender, int iRisk, int Married, int Virgin, int SRisk, int FSW, int Circ, int MSM, int PWID);
	void GetStartYrProfile();
	void UpdateProbTransmM();
	void UpdateProbTransmF();
	void UpdateProbTransmSW(); ///< Only applies to sex workers
	void UpdateProbTransmNS(); ///< Only applies to PWID
	void UpdateProbAcqM(int group);
	void UpdateProbAcqF(int group);
	void GetEndProfile();
	void SumNewART();
	void UpdateStartProfile();
	void UpdateStartTotal();
	void UpdateDemog(); ///< Changes in age, ART duration, non-AIDS mort, migration
	void GetFSWcontacts(); ///< Only relevant to high risk men
};

class AdultTB
{
public:

	int Sex; ///< 0 = male, 1 = female
	int RifRes; ///< 0 = rifampicin-susceptible, 1 = rifampicin-susceptible
	int SecondLine; ///< 1 = receiving 2nd-line Rx, 0 otherwise

	///< Arrays to represent population profile at START of month
	double HIVstage[81][44];
	double Total[81];

	///< Arrays to represent population profile at END of month
	double HIVstage_E[81][44];
	double Total_E[81];

	///< Other variables
	double NewEntrants[81][44]; ///< Only necessary for the treatment states

	AdultTB(int Gender, int Rif, int Rx2);
	void SetStartProfile();
	void UpdateStartProfile();
	void UpdateEndProfile();
	void AdjustPopTotals();
	void UpdateStartTotal();
	void UpdateDemog(); ///< Changes in age, ART duration
};

class OutputArray
{
	public:
	OutputArray(int n);

	int columns;
	double out[InitSample][70]; ///< None of the arrays require > 70 columns. 

	void Record(const char* filout, int n);
	void RecordSample(const char* filout, int n);
	void SampleInput();
};

class PostOutputArray
{
	///< Same as OutputArray class except that we only use this to record outputs from
	///< the posterior distribution (and hence require smaller output array).
	
	public:
	PostOutputArray(int n);

	int columns;
	double out[ResampleSize][86]; ///< None of the arrays require > 86 columns. 
	double Means[86][3]; ///< Mean, 95% LL and 95% UL

	void RecordSample(const char* filout);
	void RecordSampleOpt(char* filout); //LJ added this for optimisation
	void GetMeans(); ///< Calculate Means and 95% CIs
};

class OutputByAge
{
	///< Same as PostOutputArray class except that we only use this to record outputs from
	///< the posterior distribution (and hence require smaller output array).

	public:
	OutputByAge(int n1, int n2);

	int columns;
	int rows;
	double out[92][86]; ///< None of the arrays require > 86 columns. 

	void GetMeans(); ///< Calculate Means 
};

//============================================================================
///< General functions
//============================================================================

///< Input functions: HIV
void ReadPaedAssumps();
void ReadAdultAssumps();
void ReadRollout();
void ReadStartingPop();
void ReadMarriage();
void ReadCD4dbn();
void ReadNonHIVmort();
void ReadWestTable();
void ReadFertility();
void ReadMigration();
void ReadCalibData();
void ReadHIVprevData();
void ReadANCprevData();
void ReadCSWprevData();
void ReadMSMprevData();
void ReadPWIDprevData();
void ReadProvHIV();
void ReadHCTprevData();
void ReadHCTpaedData();
void ReadMortData();
void ReadCompleteness();
void ReadHCTdata();
void ReadAIDScases();
void ReadARTtotals();
void ReadChildPIP();
void ReadInitPrev();
void ReadAdultRoot();
void ReadAllFiles();

///< Input files: TB
void ReadInitTB();
void ReadTBadultAssumps();
void ReadTBrollout();
void ReadTBriskFactorPrev();
void ReadTBmortData();
void ReadTB_ETRdata();
void ReadTBlabDiag();
void ReadTBprevData();
void ReadTB_HIV_ORs();
void ReadTBscreening();

///< Initialization functions
void SetInitialParameters();
void SetInitSexActivity();
void InitializeTBprofiles();
void CalcHIVeffectTB();
void CalcTBincAdjByAgeSex();
double GetMarriedPropnAtStart(int Sex, int Age);
void SetCD4byARTdur(); ///< Calculations in cols G-S of "ART" sheet
void CalcInterruptions(); ///< Calculation of values in row 5 of "ART" sheet
void SetActivityByStage(); ///< Calculations in cols R-S and AA-AB of "Condoms" sheet
void SetFertByStage(); ///< Calculations in col AK of "Fertility" sheet
void SetProgression(int setting); ///< setting = 0 implies start year, 1 otherwise
void SetFutureRollout(); ///< Only gets called if VaryFutureInterventions = 1
void SetFutureRolloutTB(); ///< Only gets called if VaryFutureInterventionsTB = 1

///< Functions called on a monthly basis: HIV
void GetCurrBehavDbnM(); ///< Calculations in cols N-Q of 'Sex activity' sheet
void GetCurrBehavDbnF(); ///< Calculations in cols N-Q of 'Sex activity' sheet
void UpdatePop(); ///< Calculations in cols E-DB of "Population" sheet
void UpdateFSWdemand(); ///< Calculation of TotalFSW (V175 in 'Sex activity' sheet)
void UpdateAgePrefsF(); ///< Calculation of ST and LT age prefs for females
void UpdatePartnerAcqM(); ///< Male partnership formation rates, age prefs, coital freq
void UpdateMixingST(); ///< Calculation of propn of ST partners who are high risk
void UpdateCondomUse(); ///< Female and male rates of condom use
void UpdateFert(); ///< Calculations in cols Y-AF of 'Fertility' sheet
void UpdateBirths(); ///< Calculations in cols AN-AV of 'Fertility' sheet
void GetBirthsByHIV(); ///< Calculations in Births sheet
void GetPrevPregnant(); ///< Calculations of PrevPregnant in 'Monthly' sheet
void SetMnthlyPaedParameters(); ///< Calculations in "Child rates" depending on maternal
								///< HIV incidence & paediatric ART initiation rates
void UpdatePrEPandVM();
void UpdateTestingRates(); ///< Calcs in 'Testing' sheet 
void UpdateTestingToART(); ///< Calcs in B-AE of 'ART start' sheet
void UpdateTransmProbs();
void CalcHIVtransitions(); ///< Calculate movements between HIV states
void CopyEndToStart();
void SetARTinitiation(); ///< Calls the Adult and Paed ART initiation functions below
void SetAdultARTinitiation(); ///< Called when inputs are numbers starting ART
void SetAdultARTinitiation2(); ///< Called when inputs are numbers starting ART
void CalcARTdisruptionImpact(int Type); ///< Type = 1 for COVID, 2 for US funding disruptions
void SetPaedARTinitiation(); ///< Called when inputs are numbers starting ART
void SetPaedARTinitiation2(); ///< Called when inputs are numbers starting ART
void UpdateFSW();
void UpdateMonthlyCum();
void UpdateMonthlySTesting();
void OneMonth(int im);

///< Functions called on a monthly basis: TB
void CalcTBforceOfInf();
void UpdateTBsuscep(AdultTB* Suscep, AdultTB* Latent, AdultTB* SmPos, AdultTB* SmNeg, AdultTB* SmPosRR, AdultTB* SmNegRR);
void UpdateTBlatent(AdultTB* Latent, AdultTB* SmPos, AdultTB* SmNeg, AdultTB* SmPosRR, AdultTB* SmNegRR, AdultTB* IPT, AdultTB* Suscep, int IPTind);
void UpdateTBactive(AdultTB* Active, AdultTB* Latent, AdultTB* Treated, AdultTB* Treated2, int SmPos);
void UpdateTBtreated(AdultTB* Treated, AdultTB* Treated2, AdultTB* Active1, AdultTB* Active2, AdultTB* SmPosRR, AdultTB* SmNegRR, AdultTB* PostRx, AdultTB* IPT);
void UpdateTBrecovST(AdultTB* PostRxST, AdultTB* PostRxLT, AdultTB* Active1, AdultTB* Active2, AdultTB* SmPosRR, AdultTB* SmNegRR, AdultTB* IPT, AdultTB* Suscep, int IPTind);
void UpdateTBrecovLT(AdultTB* PostRxLT, AdultTB* Active1, AdultTB* Active2, AdultTB* SmPosRR, AdultTB* SmNegRR, AdultTB* IPT, AdultTB* Suscep, int IPTind);
void CalcTBtransitions();
void GetHIVtoTBpopRatios();
void BalanceTBpop();
void UpdateTBtotStart();
void GetTBcontactScreenPropns();

///< Functions called on an annual basis
void ResetMonthlyCum(); ///< Sets to zero the running totals in the Monthly sheet
void ResultsAtStartOfYr();
void TBresultsAtStartOfYr();
void TBresultsAtStartOfYr2();
void Get2ndLineOutput();
void CalcVLSstartYr();
void CalcYLDs();
void GetMarriageForCalib();
void CalcMultPartners();
void GetPrEPrateFSW();
void SetCurrYearParameters();
void SetCurrYearParametersTB();
void UpdateSocialMixing();
void SetAnnPaedParameters();
void CalcOIsTested(); 
void CalcPosPartnerProb();
void CalcSelfTestingRates();
void GetTotalTesting();
void CalcHCT1stTime(); ///< Only relevant if user specifies # HIV tests as model input
void CalcRRtestVirgin();
void CalcTBscreenPropn();
void UpdateIPTuptake();
void UpdateNonAIDSmort();
void UpdateAIDSmort();
void UpdateARTmort(); ///< Calculations in cols V-BS of ART sheet
void UpdateMigration();
void UpdateCircProb(); 
void UpdateMC(Adult* Uncirc, Adult* Circ);
void CalcCurrMarriageRates();
void GetMarriageAndDivorceRates();
double SpouseAIDSmort(int ia, int ir1, int ir2, int ig);
void UpdateMarital(Adult* Single, Adult* MarriedH, Adult* MarriedL);
void UpdateMarriedMSM(Adult* Single, Adult* Married);
void UpdatePWID(Adult* NonInjecting, Adult* Injecting);
void UpdateAllDemog();
void UpdateAllDemogTB();
void MoveIntoAdultGroups();
void MoveIntoAdultTB();
void UpdateDebut(Adult* Virgin, Adult* SexExp, Adult* SexExp2, int ind); ///< ind = 0 at month end, 1 at year end
void UpdateStartTot();
void ResultsAtEndOfYr();
void ResultsAtEndOfYr2(); ///< Mostly for HIV incidence outputs
void TBresultsAtEndOfYr();
void OneYear();

///< Output functions
//void SaveHSRCcalib(const char* filout);
//void SaveAdolProj(const char* filout);
//void SaveFSWprofile(const char* filout);
//void SaveHCTbyAge(const char* filout);
void GetSummaryOutputs(const char* filout);
void GetAddedOutputs(const char* filout);
void GetOutputsByAge(const char* filout);
void GetOutputsByAge2(const char* filout);
void GetTBoutputs(const char* filout);
void GetAddedTBoutputs(const char* filout);
void GetTBoutputsByAge(const char* filout);

//============================================================================
///< Functions used in uncertainty analysis
//============================================================================

///< SIR and HIV likelihood functions

void CalcLikelihood();
double CalcPaedPrevLogL();
double CalcAdultPrevLogL();
double CalcHHprovLogL();
double CalcHHprovPlogL();
double CalcANCprevLogL();
double CalcANCprevLogL2();
double CalcANCprovLogL();
double CalcCSWprevLogL();
double CalcMSMprevLogL();
double CalcPWIDprevLogL();
double CalcMortLikelihoodA();
double CalcMortLikelihoodP();
double CalcHCTlogL();
double CalcHCTprevLogL();
double CalcHCTprevPlogL();
double CalcRecHCT_PlogL();
double CalcHCTageSexLogL();
double CalcAIDStrendLogL();
double CalcAIDSageLogL();
double CalcARTtotalLogL();
double CalcMaleARTlogL();
double CalcARTbyCD4logL();
double CalcPaedAHDlogL();
double CalcAgeARTlogL();
double CalcAgeART_PlogL();
double CalcAgeART_P2logL();
double CalcChildPIPlogL();
double CalcARTcoverageLogL();
double CalcANC_ARTlogL();
double CalcMarriageLogL();
void GetCholesky1(double mat[MCMCdim][MCMCdim]);
void GetInverse1(double mat[MCMCdim][MCMCdim], double matinv[MCMCdim][MCMCdim]);
void SimulateParameters();
void SimulateParameters_FSW();
double SamplePrior(int PriorIndex);
void GetAnnNewART();
void GetCurrART();
void GenerateSample(); ///< Not yet updated in THEMBISA
void RunSample();

///< TB likelihood and prior sampling functions

double CalcAdultTBmortLogL();
double CalcTBmortPLHIVlogL();
double CalcETRmortLogL();
double CalcAdultTBcasesLogL();
double CalcAdultTBlabDiagLogL();
double CalcHIVprevETRlogL();
double CalcTBprevLogL();
double CalcRifResLogL();
double CalcSmPosHHlogL();
double CalcRRscreenLogL();
double CalcTB_HIV_ORlogL();
void SimulateTBparams();

///< IMIS functions

void ReadPriors();
void ReadImportanceDbns();
void ReadPrevIMIS();
void ReadPrevIMIS2(double completed);
void SaveTempIMIS();
void SaveTempIMIS2(double completed);
void GetMultNorm(double RandUnif[MCMCdim], double MultNorm[MCMCdim]); 
double GetMultNormPDF(double MultNorm[MCMCdim], int Component);
void GetMahalanobis(double distance[TotalSimulations]);
double GetPercentile(double values[TotalSimulations], double percentile);
void runIMIS(double CumSteps);
void OneIMISstep(double CumSteps);
void SimulateParameters_IMIS();
void SimulateTBparamsIMIS();
double GetParameter(int PriorIndex);

///< Nelder-Mead algorithm

double ReturnNegLogL(double ParameterSet[20]);
void ReadInitSimplex(const char* input, double ParameterCombinations[21][20], int Dimension);
void SaveFinalSimplex(const char* filout, double ParameterCombinations[21][20], int Dimension);
void SaveNegLogL(const char* filout, double NegLogL[21]);
void MaximizeLikelihood(double FTol, const char* input, const char* filout);

//============================================================================
///< Objects created from defined classes
//============================================================================

Child MaleChild(0);
Child FemChild(1);
///< Adult indices are Gender, Risk, Married, Virgin, SRisk, FSW, Circ, MSM, PWID
Adult MHU_virgin(0, 1, 0, 1, 0, 0, 0, 0, 0);
Adult MHC_virgin(0, 1, 0, 1, 0, 0, 1, 0, 0);
Adult MHU_ST(0, 1, 0, 0, 0, 0, 0, 0, 0);
Adult MHC_ST(0, 1, 0, 0, 0, 0, 1, 0, 0);
Adult MHU_STM(0, 1, 0, 0, 0, 0, 0, 1, 0);
Adult MHC_STM(0, 1, 0, 0, 0, 0, 1, 1, 0);
Adult MHU_ID(0, 1, 0, 0, 0, 0, 0, 0, 1);
Adult MHC_ID(0, 1, 0, 0, 0, 0, 1, 0, 1);
Adult MHU_LTH(0, 1, 1, 0, 1, 0, 0, 0, 0);
Adult MHC_LTH(0, 1, 1, 0, 1, 0, 1, 0, 0);
Adult MHU_LTL(0, 1, 1, 0, 2, 0, 0, 0, 0);
Adult MHC_LTL(0, 1, 1, 0, 2, 0, 1, 0, 0);
Adult MHU_LTM(0, 1, 1, 0, 2, 0, 0, 1, 0);
Adult MHC_LTM(0, 1, 1, 0, 2, 0, 1, 1, 0);
Adult MLU_virgin(0, 2, 0, 1, 0, 0, 0, 0, 0);
Adult MLC_virgin(0, 2, 0, 1, 0, 0, 1, 0, 0);
Adult MLU_ST(0, 2, 0, 0, 0, 0, 0, 0, 0);
Adult MLC_ST(0, 2, 0, 0, 0, 0, 1, 0, 0);
Adult MLU_STM(0, 2, 0, 0, 0, 0, 0, 1, 0);
Adult MLC_STM(0, 2, 0, 0, 0, 0, 1, 1, 0);
Adult MLU_ID(0, 2, 0, 0, 0, 0, 0, 0, 1);
Adult MLC_ID(0, 2, 0, 0, 0, 0, 1, 0, 1);
Adult MLU_LTH(0, 2, 1, 0, 1, 0, 0, 0, 0);
Adult MLC_LTH(0, 2, 1, 0, 1, 0, 1, 0, 0);
Adult MLU_LTL(0, 2, 1, 0, 2, 0, 0, 0, 0);
Adult MLC_LTL(0, 2, 1, 0, 2, 0, 1, 0, 0);
Adult MLU_LTM(0, 2, 1, 0, 2, 0, 0, 1, 0);
Adult MLC_LTM(0, 2, 1, 0, 2, 0, 1, 1, 0);
Adult FH_virgin(1, 1, 0, 1, 0, 0, 0, 0, 0);
Adult FH_ST(1, 1, 0, 0, 0, 0, 0, 0, 0);
Adult FH_SW(1, 1, 0, 0, 0, 1, 0, 0, 0);
Adult FH_ID(1, 1, 0, 0, 0, 0, 0, 0, 1);
Adult FH_LTH(1, 1, 1, 0, 1, 0, 0, 0, 0);
Adult FH_LTL(1, 1, 1, 0, 2, 0, 0, 0, 0);
Adult FL_virgin(1, 2, 0, 1, 0, 0, 0, 0, 0);
Adult FL_ST(1, 2, 0, 0, 0, 0, 0, 0, 0);
Adult FL_ID(1, 2, 0, 0, 0, 0, 0, 0, 1);
Adult FL_LTH(1, 2, 1, 0, 1, 0, 0, 0, 0);
Adult FL_LTL(1, 2, 1, 0, 2, 0, 0, 0, 0);

AdultTB TBsuscepM(0, 0, 0);
AdultTB TBlatentM(0, 0, 0);
AdultTB TBactiveSmPosM(0, 0, 0);
AdultTB TBactiveSmNegM(0, 0, 0);
AdultTB TBactiveSmPosRR_M(0, 1, 0); ///< RR = rifampicin-resistant
AdultTB TBactiveSmNegRR_M(0, 1, 0);
AdultTB TBtreatedM(0, 0, 0);
AdultTB RR_TBtreated1stM(0, 1, 0); ///< 1st = 1st-line drug regiment
AdultTB RR_TBtreated2ndM(0, 1, 1); ///< 2nd = 2nd-line drug regiment
AdultTB TBrecoveredST_M(0, 0, 0);
AdultTB TBrecoveredLT_M(0, 0, 0);
AdultTB TBlatentIPT_M(0, 0, 0);
AdultTB TBrecST_IPT_M(0, 0, 0);
AdultTB TBrecLT_IPT_M(0, 0, 0);
AdultTB TBsuscepF(1, 0, 0);
AdultTB TBlatentF(1, 0, 0);
AdultTB TBactiveSmPosF(1, 0, 0);
AdultTB TBactiveSmNegF(1, 0, 0);
AdultTB TBactiveSmPosRR_F(1, 1, 0);
AdultTB TBactiveSmNegRR_F(1, 1, 0);
AdultTB TBtreatedF(1, 0, 0);
AdultTB RR_TBtreated1stF(1, 1, 0);
AdultTB RR_TBtreated2ndF(1, 1, 1);
AdultTB TBrecoveredST_F(1, 0, 0);
AdultTB TBrecoveredLT_F(1, 0, 0);
AdultTB TBlatentIPT_F(1, 0, 0);
AdultTB TBrecST_IPT_F(1, 0, 0);
AdultTB TBrecLT_IPT_F(1, 0, 0);

OutputArray RandomUniform(MCMCdim);
OutputArray ModelParameters(MCMCdim);
PostOutputArray FutureInterventions(34);
PostOutputArray FutureInterventionsTB(30);
OutputArray LogL(1);

///< Prevalence outputs
PostOutputArray PrevPreg15to49(70);
PostOutputArray PrevPreg15to19(70);
PostOutputArray PrevPreg20to24(70);
PostOutputArray PrevPreg25to29(70);
PostOutputArray PrevPreg30to34(70);
PostOutputArray PrevPreg35to39(70);
PostOutputArray PrevPreg40to49(70);
PostOutputArray AdjPreg15to49(70);
PostOutputArray AdjPreg15to19(70);
PostOutputArray AdjPreg20to24(70);
PostOutputArray AdjPreg25to29(70);
PostOutputArray AdjPreg30to34(70);
PostOutputArray AdjPreg35to39(70);
PostOutputArray ANCbias(2);
PostOutputArray ErrorVariance(3);
PostOutputArray PrevFSW(70);
PostOutputArray PrevFSW15to24(70);
PostOutputArray PrevFSW25plus(70);
PostOutputArray PrevClients(70);
PostOutputArray PosClients(70);
PostOutputArray TotClients(70);
PostOutputArray TotalHIV(70);
PostOutputArray TotPaedHIV(70);
PostOutputArray TotHIV15M(70);
PostOutputArray TotHIV15F(70);
PostOutputArray TotHIV15(70);
PostOutputArray TotHIV15to24(70);
PostOutputArray TotHIV15to24M(70);
PostOutputArray TotHIV15to24F(70);
PostOutputArray TotHIV15to49(70);
PostOutputArray TotHIV15to49M(70);
PostOutputArray TotHIV15to49F(70);
PostOutputArray TotHIV25to49(70);
PostOutputArray TotHIV25to49M(70);
PostOutputArray TotHIV25to49F(70);
PostOutputArray TotHIV50plus(70);
PostOutputArray TotHIV50plusM(70);
PostOutputArray TotHIV50plusF(70);
PostOutputArray Prev0to14(70);
PostOutputArray Prev2to14(70);
PostOutputArray Prev15to24(70);
PostOutputArray Prev15to24M(70);
PostOutputArray Prev15to24F(70);
PostOutputArray Prev15to49(70);
PostOutputArray Prev15to49M(70);
PostOutputArray Prev15to49F(70);
PostOutputArray Prev25to49(70);
PostOutputArray Prev25to49M(70);
PostOutputArray Prev25to49F(70);
PostOutputArray Prev25plus(70);
PostOutputArray Prev50plus(70);
PostOutputArray Prev50plusM(70);
PostOutputArray Prev50plusF(70);
PostOutputArray Prev15plus(70);
PostOutputArray Prev15plusM(70);
PostOutputArray Prev15plusF(70);
PostOutputArray HSRCcalib2002(16);
PostOutputArray HSRCcalib2005(18);
PostOutputArray HSRCcalib2008(18);
PostOutputArray HSRCcalib2012(18);
PostOutputArray HSRCcalib2017(18);
PostOutputArray HSRCcalib2022(18);
PostOutputArray DHScalib2016(18);
PostOutputArray MSMprev18plus(70);
PostOutputArray MSMprev18to24(70);
PostOutputArray MSMprev25plus(70);
PostOutputArray MSMprev15to49(70);
PostOutputArray TGWprev18plus(70);
PostOutputArray PrevPWID(70);
PostOutputArray PrevPWID_M(70);
PostOutputArray PrevPWID_F(70);
PostOutputArray MalePrev18plus(70);
PostOutputArray HIVprevalence(70);
/*PostOutputArray Prev0to1(31);
PostOutputArray Prev2to4M(31);
PostOutputArray Prev2to4F(31);
PostOutputArray Prev5to9M(31);
PostOutputArray Prev5to9F(31);
PostOutputArray Prev10to14M(31);
PostOutputArray Prev10to14F(31);*/

///< HIV incidence outputs
PostOutputArray NewHIVinFSW(70);
PostOutputArray NewHIVclients(70);
PostOutputArray NewHIVclientsNotSW(70);
PostOutputArray NewHIVinMSM(70);
PostOutputArray NewHIVinTGW(70);
PostOutputArray NewHIVinPWID(70);
PostOutputArray HIVinc0to14(70);
PostOutputArray HIVinc15to49(70);
PostOutputArray HIVinc15to49adj(70);
PostOutputArray HIVinc15to49M(70);
PostOutputArray HIVinc15to49F(70);
PostOutputArray HIVinc15to24(70);
PostOutputArray HIVinc15to24M(70);
PostOutputArray HIVinc15to24F(70);
PostOutputArray HIVinc25to49(70);
PostOutputArray HIVinc25to49M(70);
PostOutputArray HIVinc25to49F(70);
PostOutputArray HIVinc50(70);
PostOutputArray HIVinc50M(70);
PostOutputArray HIVinc50F(70);
PostOutputArray HIVinc15plus(70);
PostOutputArray HIVinc15plusM(70);
PostOutputArray HIVinc15plusF(70);
PostOutputArray HIVinc2000(18); ///< HIV incidence by age, sex in 2000
PostOutputArray HIVinc2010(18); ///< HIV incidence by age, sex in 2010
PostOutputArray PAFforCSW(41);
PostOutputArray HIVincFSW(70);
PostOutputArray HIVincClients(70);
PostOutputArray HIVincMSM(70);
PostOutputArray HIVincTGW(70);
PostOutputArray HIVincPWID(70);
PostOutputArray ANCincidence(70);
PostOutputArray ANCincidenceAdj(70);
PostOutputArray NewMTCT(70);
PostOutputArray NewHIVatBirth(70);
PostOutputArray NewHIVatBirthART(70);
PostOutputArray NewHIVatBirthNoKOS(70);
PostOutputArray NewHIVafterBirth(70);
PostOutputArray NewHIVafterBirthART(70);
PostOutputArray NewHIVafterBirthNoKOS(70);
PostOutputArray NewHIVto18mo(70);
PostOutputArray NewHIVinANCandBF(70);
PostOutputArray NewHIVmothersBF(70);
PostOutputArray MTCTrateAtBirth(70);
PostOutputArray MTCTrateBirthDiag(70);
PostOutputArray MTCTrate18moDiag(70);
PostOutputArray TotMTCTrate(70);
PostOutputArray TotMTCTallBirths(70);
PostOutputArray TotalNewHIV(70);
PostOutputArray NewAdultHIV(70);
PostOutputArray NewHIV_M(70); ///< ages 10+
PostOutputArray NewHIV_F(70); ///< ages 10+
PostOutputArray TotIncidence(70);
PostOutputArray IncPrevRatio(70);
PostOutputArray IncPrevRatioFtoM(70);
PostOutputArray IncPrevRatioMtoF(70);

///< Mortality outputs
PostOutputArray TotDeathsM(70);
PostOutputArray TotDeathsF(70);
PostOutputArray Deaths0M(70);
PostOutputArray Deaths1M(70);
PostOutputArray Deaths5M(70);
PostOutputArray Deaths10M(70);
PostOutputArray Deaths15M(70);
PostOutputArray Deaths20M(70);
PostOutputArray Deaths25M(70);
PostOutputArray Deaths30M(70);
PostOutputArray Deaths35M(70);
PostOutputArray Deaths40M(70);
PostOutputArray Deaths45M(70);
PostOutputArray Deaths50M(70);
PostOutputArray Deaths55M(70);
PostOutputArray Deaths0F(70);
PostOutputArray Deaths1F(70);
PostOutputArray Deaths5F(70);
PostOutputArray Deaths10F(70);
PostOutputArray Deaths15F(70);
PostOutputArray Deaths20F(70);
PostOutputArray Deaths25F(70);
PostOutputArray Deaths30F(70);
PostOutputArray Deaths35F(70);
PostOutputArray Deaths40F(70);
PostOutputArray Deaths45F(70);
PostOutputArray Deaths50F(70);
PostOutputArray Deaths55F(70);
PostOutputArray AIDSdeathsTot(70);
PostOutputArray AIDSdeathsPaed(70);
PostOutputArray AIDSdeathsBoys(70);
PostOutputArray AIDSdeathsGirls(70);
PostOutputArray AIDSdeathsAdultM(70);
PostOutputArray AIDSdeathsAdultF(70);
PostOutputArray AIDSdeaths0(70);
PostOutputArray AIDSdeaths1to4(70);
PostOutputArray AIDSdeaths5to9(70);
PostOutputArray AIDSdeaths10to14(70);
PostOutputArray AIDSdeaths15to24(70);
PostOutputArray AIDSdeaths15to24M(70);
PostOutputArray AIDSdeaths15to24F(70);
PostOutputArray AIDSdeaths15to49(70);
PostOutputArray AIDSdeaths15to49M(70);
PostOutputArray AIDSdeaths15to49F(70);
PostOutputArray AIDSdeaths25to49(70);
PostOutputArray AIDSdeaths25to49M(70);
PostOutputArray AIDSdeaths25to49F(70);
PostOutputArray AIDSdeaths50plus(70);
PostOutputArray AIDSdeaths50plusM(70);
PostOutputArray AIDSdeaths50plusF(70);
PostOutputArray AIDSdeaths20to59M(31);
PostOutputArray AIDSdeaths20to59F(31);
PostOutputArray NonAIDSdeaths2005(16); ///< Males by age, then females by age
PostOutputArray NonAIDSdeaths(70);
PostOutputArray NonAIDSdeathsHIVpos(70);
PostOutputArray NonAIDSdeaths15M(70);
PostOutputArray NonAIDSdeaths20M(70);
PostOutputArray NonAIDSdeaths25M(70);
PostOutputArray NonAIDSdeaths30M(70);
PostOutputArray NonAIDSdeaths35M(70);
PostOutputArray NonAIDSdeaths40M(70);
PostOutputArray NonAIDSdeaths45M(70);
PostOutputArray NonAIDSdeaths50M(70);
PostOutputArray NonAIDSdeaths55M(70);
PostOutputArray NonAIDSdeaths15F(70);
PostOutputArray NonAIDSdeaths20F(70);
PostOutputArray NonAIDSdeaths25F(70);
PostOutputArray NonAIDSdeaths30F(70);
PostOutputArray NonAIDSdeaths35F(70);
PostOutputArray NonAIDSdeaths40F(70);
PostOutputArray NonAIDSdeaths45F(70);
PostOutputArray NonAIDSdeaths50F(70);
PostOutputArray NonAIDSdeaths55F(70);
PostOutputArray IMR(70);
PostOutputArray U5MR(70);
PostOutputArray Tot45q15(70);
PostOutputArray M45q15(70);
PostOutputArray F45q15(70);
PostOutputArray LifeExpectTot(70);
PostOutputArray LifeExpectM(70);
PostOutputArray LifeExpectF(70);
PostOutputArray AIDSdeathsUndiag(41);
PostOutputArray AIDSdeathsDiagPreART(41);
PostOutputArray AIDSdeaths1st6moART(41);
PostOutputArray AIDSdeathsAfter6moART(41);
PostOutputArray AIDSdeathsART(70);
PostOutputArray DiagDeaths1to4(70);
PostOutputArray DiagDeaths5to9(70);
PostOutputArray DiagDeaths10to14(70);
PostOutputArray DeathsDiagPos1to4(70);
PostOutputArray DeathsDiagPos5to9(70);
PostOutputArray ARTdeaths1to4(70);
PostOutputArray ARTdeaths5to9(70);
PostOutputArray ARTdeaths10to14(70);
PostOutputArray LYlostAIDS(70);
PostOutputArray YLD_HIV(86);
PostOutputArray DALY_HIV(86);
PostOutputArray LYlostAIDSpaed(86);
PostOutputArray YLD_HIVpaed(86);
PostOutputArray DALY_HIVpaed(86);
PostOutputArray YLD_AHD(86);
PostOutputArray YLD_AHDuntreated(86);
PostOutputArray CrudeAIDSmort(70);
PostOutputArray CompletenessPaed(16);
PostOutputArray CompletenessAdj(2);

///< Other demographic outputs
PostOutputArray TotPop(70);
PostOutputArray TotBirths(70);
PostOutputArray TotFertRate(70);
PostOutputArray BirthRate(70);
PostOutputArray TotInfants(70);
PostOutputArray Children1to2(70);
PostOutputArray Children3to5(70);
PostOutputArray Children6to13(70);
PostOutputArray TotalUnder15(70);
PostOutputArray Adolesc15to19(70);
PostOutputArray Children6to18(70);
PostOutputArray MalesOver15(70);
PostOutputArray FemalesOver15(70);
PostOutputArray Males15to64(70);
PostOutputArray Females15to64(70);
PostOutputArray Total15to24(70);
PostOutputArray Total15to24M(70);
PostOutputArray Total15to24F(70);
PostOutputArray Total15to49(70);
PostOutputArray Total15to49M(70);
PostOutputArray Total15to49F(70);
PostOutputArray Total25to49(70);
PostOutputArray Total25to49M(70);
PostOutputArray Total25to49F(70);
PostOutputArray Total50plus(70);
PostOutputArray Total50plusM(70);
PostOutputArray Total50plusF(70);
PostOutputArray DependencyRatio(70);
PostOutputArray AgingIndex(70);
PostOutputArray TotSexWorkers(70);
PostOutputArray TotalCisMSM(70);
PostOutputArray TotalTGW(70);
PostOutputArray TotalPWID(70);
PostOutputArray PWIDbyAge(81);
PostOutputArray MSMbyAge(20);
PostOutputArray PWIDpropnMale(70);
PostOutputArray MarriedPropn1996(30);
PostOutputArray MarriedPropn2001(30);
PostOutputArray MarriedPropn2007(30);
PostOutputArray MarriedPropn2016(30);

///< ART/disease stage outputs
PostOutputArray AHDnotOnART(70);
PostOutputArray AdultsUnder200(70);
PostOutputArray Adults200to349(70);
PostOutputArray Adults350to499(70);
PostOutputArray AdultsOver500(70);
PostOutputArray StartingART0(70);
PostOutputArray StartingART1(70);
PostOutputArray StartingART2to4(70);
PostOutputArray StartingART5to14(70);
PostOutputArray StartingART15to24M(70);
PostOutputArray StartingART25to34M(70);
PostOutputArray StartingART35to44M(70);
PostOutputArray StartingART45M(70);
PostOutputArray StartingART15to24F(70);
PostOutputArray StartingART25to34F(70);
PostOutputArray StartingART35to44F(70);
PostOutputArray StartingART45F(70);
PostOutputArray StartingARTtot(70);
PostOutputArray StartingART0to14(70);
PostOutputArray StartingART_M15(70);
PostOutputArray StartingART_F15(70);
PostOutputArray NewARTunder200(70);
PostOutputArray NewART200to349(70);
PostOutputArray NewART350to499(70);
PostOutputArray NewARTover500(70);
PostOutputArray NewARTpaedAdvanced(70);
PostOutputArray AdultsRestartingART(70);
PostOutputArray ReinitARTunder200(70);
PostOutputArray RestartARTchild(70);
PostOutputArray RestartARTpaedAdvanced(70);
PostOutputArray TotalOnART(70);
PostOutputArray TotalART15F(70);
PostOutputArray TotalART15M(70);
PostOutputArray TotalARTunder15(70);
PostOutputArray TotalART15to24(70);
PostOutputArray TotalART15to24M(70);
PostOutputArray TotalART15to24F(70);
PostOutputArray PaedARTpropn0to4(70);
PostOutputArray PaedARTpropn5to9(70);
PostOutputArray TotUnmet15F(31); ///< Based on guidelines in SA at start of 2014
PostOutputArray TotUnmet15M(31);
PostOutputArray TotUnmetUnder15(31);
PostOutputArray TotNewNeed15F(31);
PostOutputArray TotNewNeed15M(31);
PostOutputArray VLsuppressed(70);
PostOutputArray VLsuppressedM(70);
PostOutputArray VLsuppressedF(70);
PostOutputArray VLsuppressedU15(70);
PostOutputArray VLsuppressed1000(70);
PostOutputArray VLsuppressed1000M(70);
PostOutputArray VLsuppressed1000F(70);
PostOutputArray VLsuppressed1000P(70);
PostOutputArray VLsuppressed1000FSW(70);
PostOutputArray VLsuppressed1000MSM(70);
PostOutputArray VLsuppressed1000PWID(70);
PostOutputArray VLsuppressed15to24(70);
PostOutputArray VLsuppressed15to24M(70);
PostOutputArray VLsuppressed15to24F(70);
PostOutputArray VLsuppressed25to49(70);
PostOutputArray VLsuppressed25to49M(70);
PostOutputArray VLsuppressed25to49F(70);
PostOutputArray VLsuppressed50plus(70);
PostOutputArray VLsuppressed50plusM(70);
PostOutputArray VLsuppressed50plusF(70);
PostOutputArray VLsuppressed50(70);
PostOutputArray VLsuppressed50M(70);
PostOutputArray VLsuppressed50F(70);
PostOutputArray VLsuppressed50P(70);
PostOutputArray ARTerror(1);
PostOutputArray CumARTtot(70);
PostOutputArray CumART15F(70);
PostOutputArray CumART15M(70);
PostOutputArray CumARTunder15(70);
PostOutputArray PreARTunder200M(70);
PostOutputArray PreART200to349M(70);
PostOutputArray PreART350to499M(70);
PostOutputArray PreARTover500M(70);
PostOutputArray PreARTunder200F(70);
PostOutputArray PreART200to349F(70);
PostOutputArray PreART350to499F(70);
PostOutputArray PreARTover500F(70);
PostOutputArray OnARTcurrUnder200(70);
PostOutputArray OnARTcurr200to349(70);
PostOutputArray OnARTcurr350to499(70);
PostOutputArray OnARTcurrOver500(70);
PostOutputArray DiscontinuedART_M(70);
PostOutputArray DiscontinuedART_F(70);
PostOutputArray TotNewNeed500M(70);
PostOutputArray TotNewNeed500F(70);
PostOutputArray ARTcoverage(70);
PostOutputArray ARTcoverage15M(70);
PostOutputArray ARTcoverage15F(70);
PostOutputArray ARTcoverageAdult(70);
PostOutputArray ARTcoverageU15(70);
PostOutputArray ARTcoverage15to24(70);
PostOutputArray ARTcoverage15to24M(70);
PostOutputArray ARTcoverage15to24F(70);
PostOutputArray ARTcoverageFSW(70);
PostOutputArray ARTcoverageClients(70);
PostOutputArray ARTcoverageMSM(70);
PostOutputArray ARTcoveragePWID(70);
PostOutputArray AdultRootM(70);
PostOutputArray AdultRootF(70);
PostOutputArray ChildRoot(70);
PostOutputArray EnrolmentRatio(70);
PostOutputArray EnrolmentRatio15M(70);
PostOutputArray EnrolmentRatio15F(70);
PostOutputArray EnrolmentRatioU15(70);
PostOutputArray ARTcoverageDiag(70);
PostOutputArray ARTcoverageDiagM(70);
PostOutputArray ARTcoverageDiagF(70);
PostOutputArray ARTcoverageDiagU15(70);
PostOutputArray VLsuppressedAllHIV(70);
PostOutputArray VLsuppressedAllM(70);
PostOutputArray VLsuppressedAllF(70);
PostOutputArray VLsuppressedAllU15(70);
PostOutputArray VLsuppressedAll1000(70);
PostOutputArray VLsuppressedAllM1000(70);
PostOutputArray VLsuppressedAllF1000(70);
PostOutputArray VLsuppressedAllP1000(70);
PostOutputArray LowVLallHIV(70);
PostOutputArray LowVLallHIV_M(70);
PostOutputArray LowVLallHIV_F(70);
PostOutputArray LowVLallHIV_P(70);
PostOutputArray LowVLuntreatedHIV(70);
PostOutputArray LowVLuntreatedHIV_M(70);
PostOutputArray LowVLuntreatedHIV_F(70);
PostOutputArray LowVLuntreatedHIV_P(70);
PostOutputArray AdultARTinterrupters(70);
PostOutputArray AdultInterruptPropn(70);
PostOutputArray ChildARTinterrupters(70);
PostOutputArray ChildInterruptPropn(70);
PostOutputArray ARTresumptionRateM(70);
PostOutputArray ARTresumptionRateF(70);
PostOutputArray TotalART15F2L(70);
PostOutputArray TotalART15M2L(70);
PostOutputArray TotalARTunder15_2L(70);
PostOutputArray AgeDbnOnART_M(70);
PostOutputArray AgeDbnOnART_F(70);

///< Other prevention/cascade indicators
PostOutputArray TotBirthsHIV(70);
PostOutputArray TotBirthsART(70);
PostOutputArray TotBirthsARTconcep(70);
PostOutputArray EverARTpreConcep(70);
PostOutputArray ARTpreConcep15(70);
PostOutputArray ARTpreConcep20(70);
PostOutputArray ARTpreConcep25(70);
PostOutputArray ARTpreConcep30(70);
PostOutputArray ARTpreConcep35(70);
PostOutputArray FSWcondomUse(31);
PostOutputArray CondomUse15to24F(70);
PostOutputArray CondomUse25to49F(70);
PostOutputArray PrevTested05(20);
PostOutputArray PrevTested08(20);
PostOutputArray PrevTested12(20);
PostOutputArray PrevTested17(20);
PostOutputArray PrevTested22(20);
PostOutputArray PrevTested16(16);
PostOutputArray PrevTested09(16);
PostOutputArray MMC10to14(70);
PostOutputArray MMC15to19(70);
PostOutputArray MMC20to24(70);
PostOutputArray MMC25to49(70);
PostOutputArray MMCover50(70);
PostOutputArray Circumcised15to49(70);
PostOutputArray Circumcised15to24(70);
PostOutputArray Circumcised15plus(70);
PostOutputArray NeonatalMMCops(70);
PostOutputArray MMCprob10to14(70);
PostOutputArray AdultsEverTestedM(70);
PostOutputArray AdultsEverTestedF(70);
PostOutputArray AdultsEverTested(70);
//PostOutputArray TestingBias(2);
PostOutputArray TotalHIVtests(70); ///< Adults
PostOutputArray TotalHIVtestsU15(70);
PostOutputArray TotalHIVtests15to24M(70);
PostOutputArray TotalHIVtests15to24F(70);
PostOutputArray TotalHIVtests25to49M(70);
PostOutputArray TotalHIVtests25to49F(70);
PostOutputArray TotalHIVtests50plusM(70);
PostOutputArray TotalHIVtests50plusF(70);
PostOutputArray PregTests15to24(70);
PostOutputArray PregTests25to49(70);
PostOutputArray HIVtestsPos(70);
PostOutputArray HIVtestsPosU15(70);
PostOutputArray HIVtestsPos18mo(70);
PostOutputArray HIVtestsPos19to59mo(70);
PostOutputArray HIVtestsPos5to14(70);
PostOutputArray PosHIVtests15to24M(70);
PostOutputArray PosHIVtests15to24F(70);
PostOutputArray PosHIVtests25to49M(70);
PostOutputArray PosHIVtests25to49F(70);
PostOutputArray PosHIVtests50plusM(70);
PostOutputArray PosHIVtests50plusF(70);
PostOutputArray PregDiag15to24(70);
PostOutputArray PregDiag25to49(70);
PostOutputArray FalseNegPropn(70);
PostOutputArray FirstHIVtestsPos(70);
PostOutputArray NewDiagAtBirth(70);
PostOutputArray NewDiagInfants(70);
PostOutputArray NewDiag1yrOlds(70);
PostOutputArray NewDiagnosesPregnancy(70);
PostOutputArray TotSTestANC(70);
PostOutputArray TotSTestIndex(70);
PostOutputArray TotSTestTaxi(70);
PostOutputArray TotSTestFixedPoint(70);
PostOutputArray TotSTestWork1(70);
PostOutputArray TotSTestWork2(70);
PostOutputArray PosSTestANC(70);
PostOutputArray PosSTestIndex(70);
PostOutputArray PosSTestTaxi(70);
PostOutputArray PosSTestFixedPoint(70);
PostOutputArray PosSTestWork1(70);
PostOutputArray PosSTestWork2(70);
PostOutputArray STtoART_ANC(70);
PostOutputArray STtoARTindex(70);
PostOutputArray STtoARTtaxi(70);
PostOutputArray STtoARTfixedPoint(70);
PostOutputArray STtoARTwork1(70);
PostOutputArray STtoARTwork2(70);
PostOutputArray STuptakeByYr(18);
PostOutputArray HIVtestUptakeF25(70);
PostOutputArray OItestingRate(70);
PostOutputArray RelativeTestingVirgins(70);
PostOutputArray ProbTestedNextYr(41);
PostOutputArray DiagnosedHIVtot(70);
PostOutputArray DiagnosedHIV_M(70);
PostOutputArray DiagnosedHIV_F(70);
PostOutputArray DiagnosedHIV_U15(70);
PostOutputArray DiagnosedHIV_FSW(70);
PostOutputArray DiagnosedHIV_MSM(70);
PostOutputArray DiagnosedHIV_PWID(70);
PostOutputArray UndiagnosedHIV_M(70);
PostOutputArray UndiagnosedHIV_F(70);
PostOutputArray UndiagnosedHIV_U15(70);
PostOutputArray DiagnosedPropnM(70);
PostOutputArray DiagnosedPropnF(70);
PostOutputArray DiagnosedPropnAdult(70);
PostOutputArray DiagnosedPropnU15(70);
PostOutputArray DiagnosedPropn(70);
PostOutputArray DiagnosedPropn15to24(70);
PostOutputArray DiagnosedPropn15to24M(70);
PostOutputArray DiagnosedPropn15to24F(70);
PostOutputArray Undiagnosed2012(20); ///< By sex and age
PostOutputArray DiagnosedUntreated2012(20);
PostOutputArray Treated2012(20);
PostOutputArray UntreatedByCD4_2012(8); ///< By diagnosis and CD4 stage
PostOutputArray PaedCascade2018(45); ///< By diagnosis and CD4 stage
PostOutputArray OutRRdiagDeathsPIP(2);
PostOutputArray MenOnPrEP(70);
PostOutputArray WomenOnPrEP(70);
PostOutputArray TotOnPrEP(70);
PostOutputArray FSWonPrEP(70);
PostOutputArray MSMonPrEP(70);
PostOutputArray PWIDonPrEP(70);
PostOutputArray AGYWonPrEP(70);
PostOutputArray MenOnCABLA(70);
PostOutputArray WomenOnCABLA(70);
PostOutputArray TotOnCABLA(70);
PostOutputArray FSWonCABLA(70);
PostOutputArray MSMonCABLA(70);
PostOutputArray PWIDonCABLA(70);
PostOutputArray AGYWonCABLA(70);
PostOutputArray NewPrEP_M(70);
PostOutputArray NewPrEP_F(70);
PostOutputArray NewPrEPinAGYW(70);
PostOutputArray NewPrEPinFSW(70);
PostOutputArray NewPrEPinMSM(70);
PostOutputArray NewPrEPinPWID(70);
PostOutputArray NewPrEPrateFSW(70);
PostOutputArray NewCABLA_M(70);
PostOutputArray NewCABLA_F(70);
PostOutputArray NewCABLAinAGYW(70);
PostOutputArray NewCABLAinFSW(70);
PostOutputArray NewCABLAinMSM(70);
PostOutputArray NewCABLAinPWID(70);
PostOutputArray NewCABLArateFSW(70);
PostOutputArray PrEPcoverageFSW(70);
PostOutputArray PrEPcoverageMSM(70);
PostOutputArray PrEPcoveragePWID(70);
PostOutputArray PrEPcoverageAGYW(70);
PostOutputArray PrEPcoverageAllM(70);
PostOutputArray PrEPcoverageAllF(70);
PostOutputArray PrEPcoverageAll(70);
PostOutputArray AdolescOnPrEP(70);
PostOutputArray WomenOnVM(70);
PostOutputArray NewAIDSdiagTrend(5);
PostOutputArray NewAIDSdiagAge(20);
PostOutputArray MSMpropn18to24(70);
PostOutputArray MultPartners15to24M(70);
PostOutputArray MultPartners15to24F(70);
PostOutputArray MultPartners25to49M(70);
PostOutputArray MultPartners25to49F(70);

///< HIV-negative populations 
PostOutputArray TotNegPop(70);
PostOutputArray NegChildrenU15(70);
PostOutputArray Neg15to49(70);
PostOutputArray Neg15to49M(70);
PostOutputArray Neg15to49F(70);
PostOutputArray Neg15to24(70);
PostOutputArray Neg15to24F(70);
PostOutputArray Neg15to24M(70);
PostOutputArray Neg25to49F(70);
PostOutputArray Neg25to49M(70);
PostOutputArray Neg50(70);
PostOutputArray Neg50M(70);
PostOutputArray Neg50F(70);
PostOutputArray NegFSW(70);
PostOutputArray NegClients1(70);
PostOutputArray NegMSM(70);
PostOutputArray NegPWID(70);

///< New infection total
PostOutputArray NewHIVU15(70);
PostOutputArray NewHIV15M(70);
PostOutputArray NewHIV15F(70);
PostOutputArray NewHIV15to49(70);
PostOutputArray NewHIV15to49M(70);
PostOutputArray NewHIV15to49F(70);
PostOutputArray NewHIV15to24(70);
PostOutputArray NewHIV15to24F(70);
PostOutputArray NewHIV15to24M(70);
PostOutputArray NewHIV25to49(70);
PostOutputArray NewHIV25to49F(70);
PostOutputArray NewHIV25to49M(70);
PostOutputArray NewHIV50(70);
PostOutputArray NewHIV50M(70);
PostOutputArray NewHIV50F(70);

///< TB outputs : incidence
PostOutputArray NewActiveTBadult(70);
PostOutputArray NewActiveTBadultM(70);
PostOutputArray NewActiveTBadultF(70);
PostOutputArray NewActiveTB_HIVpos(70);
PostOutputArray NewActiveTBonART(70);
PostOutputArray NewActiveTBprevTB(70);
PostOutputArray NewActiveTBprevTBpropn(70);
PostOutputArray NewTBrateAdult(70);
PostOutputArray NewTBrateAdultM(70);
PostOutputArray NewTBrateAdultF(70);
PostOutputArray PropnTBreactivation(70);
PostOutputArray TBincFastProg(70);
PostOutputArray TBincReactivation(70);
PostOutputArray AnnMTBriskPaed(70);

///< TB outputs : prevalence
PostOutputArray AdultLTBIprev(70);
PostOutputArray AdultTBprev(70);
PostOutputArray AdultTBprevM(70);
PostOutputArray AdultTBprevF(70);
PostOutputArray AdultTBprevN(70);
PostOutputArray AdultPTBprev(70);
PostOutputArray AdultPTBprevM(70);
PostOutputArray AdultPTBprevF(70);
PostOutputArray AdultTBprevHIVpos(70);
PostOutputArray AdultTBprevHIVneg(70);
PostOutputArray OR_TB_HIVassociation(70);
PostOutputArray AdultTBprevART(70);
PostOutputArray AdultTBprevARTover500(70);
PostOutputArray AdultTBprevART500(70);
PostOutputArray AdultTBprevART350(70);
PostOutputArray AdultTBprevART200(70);
PostOutputArray TotTBadult(70);
PostOutputArray TotTBadultM(70);
PostOutputArray TotTBadultF(70);
PostOutputArray TotTBadultHIVpos(70);
PostOutputArray TotTBadultHIVneg(70);
PostOutputArray DurTBadult(70);
PostOutputArray DurTBadultM(70);
PostOutputArray DurTBadultF(70);
PostOutputArray DurTBadultHIVpos(70);
PostOutputArray DurTBadultHIVneg(70);
PostOutputArray EverTBtreatedM(70);
PostOutputArray EverTBtreatedF(70);
PostOutputArray UntreatedTBprev(70);
PostOutputArray UntreatedTBprevM(70);
PostOutputArray UntreatedTBprevF(70);

///< TB outputs: diagnosis and treatment (active + passive case finding combined)
PostOutputArray TotLabDiagAllTBscreening(70);
PostOutputArray TotLabDiagAdultFalsePos(70);
PostOutputArray TotNewRxAdultTB(70);
PostOutputArray TotNewRxAdultTBfalsePos(70);
PostOutputArray TotNewRxAdultTBsmPos(70);
PostOutputArray TBempiricRxAdults(70);
PostOutputArray TBempiricRxNoLab(70);
PostOutputArray TBempiricRxNegLab(70);
PostOutputArray TotLabTestedAllScreening(70);
PostOutputArray DiagnosisDelay(70);
PostOutputArray TreatedTBcurr(70);
PostOutputArray UntreatedTB(70);
PostOutputArray UntreatedTBsmPos(70);
PostOutputArray PropnUntreatedSmPos(70);
PostOutputArray TotNewRxAdultTB_HIV(70);
PostOutputArray HIVprevNewRxAdultTB(70);
PostOutputArray HIVprevNewRxTB_M(70);
PostOutputArray HIVprevNewRxTB_F(70);
PostOutputArray CaseDetectionRatioT(70);
PostOutputArray CaseDetectionRatioR(70);
PostOutputArray LagAdjCaseDetectionRatio(70);
PostOutputArray TBRxCompletion(70);
PostOutputArray TBtestingYield(70);
PostOutputArray ETRbias(5);
PostOutputArray VRbiasTB(1);
PostOutputArray TBlogL(10);

///< TB outputs: diagnosis and treatment through passive case finding (symptomatic)
PostOutputArray LabDiagAdultTB(70);
PostOutputArray LabDiagAdultTBfalsePos(70);
PostOutputArray NewRxAdultTB(70);
PostOutputArray NewRxAdultTBfalsePos(70);
PostOutputArray NewRxAdultTBsmPos(70);
PostOutputArray NewRxAdultTB_M(70);
PostOutputArray NewRxAdultTB_F(70);
PostOutputArray TreatedTB15to24(70);
PostOutputArray TotTBsymptomChecks(70);
PostOutputArray TotTBsymptomChecksART(70);
PostOutputArray TotalScreens(70);
PostOutputArray CultureConfirmTests(70);
PostOutputArray PropnScreened(70);
PostOutputArray PropnScreened2(70);
PostOutputArray NewRxAdultTB_HIV(70);

///< TB outputs: drug-resistant TB
PostOutputArray PropnPrevTreated(70);
PostOutputArray PropnPrevTreatedRR(70);
PostOutputArray PropnPrevTreatedRS(70);
PostOutputArray TotRifResTB(70);
PostOutputArray RifResAllTB(70);
PostOutputArray RifResPrevTB(70);
PostOutputArray RifResNewTB(70);
PostOutputArray MDRprevAllTB(70);
PostOutputArray NewRifResAcquired(70);
PostOutputArray CultureLPAtestsFailing(70);
PostOutputArray RifResDetected(70);
PostOutputArray RifResDetectedFailing(70);
PostOutputArray New2ndRxAdultTB(70);
PostOutputArray New2ndRxFailing1st(70);
PostOutputArray TreatedTBcurr2nd(70);
PostOutputArray TBRx2Completion(70);

///< TB outputs: active case finding approaches and TUTT
PostOutputArray TotalScreensACF(70);
PostOutputArray TotalXpertScreensACF(70);
PostOutputArray NewRxAdultTB_ACF(70);
PostOutputArray TotalScreensART_ICF(70);
PostOutputArray TotalXpertScreensART_ICF(70);
PostOutputArray NewRxAdultTB_ART_ICF(70);
PostOutputArray TotalScreensPrevTB(70);
PostOutputArray TotalXpertScreensPrevTB(70);
PostOutputArray NewRxAdultTBscreenPrev(70);
PostOutputArray TotalScreensD2D(70);
PostOutputArray Total_dCXRscreensD2D(70);
PostOutputArray TotalXpertScreensD2D(70);
PostOutputArray TotTongueSwabsD2D(70);
PostOutputArray NewRxAdultTBscreenD2D(70);

///< TB outputs: TPT and prevention
PostOutputArray NewIPTlatent(70);
PostOutputArray NewTPTinHHcontacts(70);
PostOutputArray IPTstartRate(70);
PostOutputArray IPTcoverage(70);

///< TB outputs: mortality
PostOutputArray TotTBdeathsAdult(70);
PostOutputArray TotTBdeathsM(70);
PostOutputArray TotTBdeathsF(70);
PostOutputArray TotTBmortRate(70);
PostOutputArray TotTBmortRateM(70);
PostOutputArray TotTBmortRateF(70);
PostOutputArray TBdeathsOnRx(70);
PostOutputArray TBdeathsOnRxM(70);
PostOutputArray TBdeathsOnRxF(70);
PostOutputArray MortRateTB_RxM(70);
PostOutputArray MortRateTB_RxF(70);
PostOutputArray TBdeathsHIV(70);
PostOutputArray CaseFatalityRatioA(70);
PostOutputArray CaseFatalityRatioT(70);
PostOutputArray AdultLYlostTB(70);

///< Other outputs
PostOutputArray MarriedM15to49(70);
PostOutputArray MarriedF15to49(70);
PostOutputArray MarriedM50(70);
PostOutputArray MarriedF50(70);
PostOutputArray MarriedPropnAll(70);
PostOutputArray MarriedPropn15_49(70);
PostOutputArray MarriedPropn50plus(70);
PostOutputArray MarriedPropnAllM(70);
PostOutputArray MarriedPropn15_49M(70);
PostOutputArray MarriedPropn50plusM(70);
PostOutputArray MarriedPropnAllF(70);
PostOutputArray MarriedPropn15_49F(70);
PostOutputArray MarriedPropn50plusF(70);
PostOutputArray MarriedMSM(70);
PostOutputArray MarriedPropnAllMSM(70);
PostOutputArray PropnMarriedM_MSM(70);
PostOutputArray NewARTunder200F(70);
PostOutputArray NewART200to349F(70);
PostOutputArray NewART350to499F(70);
PostOutputArray NewARTover500F(70);
PostOutputArray StartingART1to2(70);
PostOutputArray StartingART3to5(70);
PostOutputArray StartingART6to13(70);
PostOutputArray TotLateUnder15(70);
PostOutputArray TotEarlyInfants(70);
PostOutputArray TotEarly1to4(70);
PostOutputArray TotSexActs(70);
PostOutputArray TotProtSexActs(70);
PostOutputArray TotProtSexActs18(70);
PostOutputArray BirthsDiagHIV(70);
PostOutputArray BirthsOver500(70);
PostOutputArray Births350to499(70);
PostOutputArray Births200to349(70);
PostOutputArray BirthsUnder200(70);
PostOutputArray SWsexActs(70);
PostOutputArray SWsexActsProt(70);
PostOutputArray FSWonART(70);
PostOutputArray DiscordantARTelig(70);
PostOutputArray DiscordantPrEPelig(70);
PostOutputArray OnARTover500(70);
PostOutputArray OnART350to499(70);
PostOutputArray OnART200to349(70);
PostOutputArray OnARTunder200(70);
PostOutputArray DiscARTover500(70);
PostOutputArray DiscART350to499(70);
PostOutputArray DiscART200to349(70);
PostOutputArray DiscARTunder200(70);
PostOutputArray ChildrenOnExtNVP(70);
PostOutputArray TotBirthDiagnosed(70);

///< Age-specific output tables: HIV
OutputByAge MalePopAS(91, 56);
OutputByAge FemPopAS(91, 56);
OutputByAge MaleIncAS(81, 56);
OutputByAge FemIncAS(81, 56);
OutputByAge MalePrevAS(91, 56);
OutputByAge FemPrevAS(91, 56);
OutputByAge MaleMortAS(91, 56);
OutputByAge FemMortAS(91, 56);
OutputByAge MaleDiagAS(91, 56);
OutputByAge FemDiagAS(91, 56);
OutputByAge MaleART_AS(91, 56);
OutputByAge FemART_AS(91, 56);
OutputByAge MaleAIDSdeathsAS(92, 56);
OutputByAge FemAIDSdeathsAS(92, 56);
OutputByAge BirthsPosMomsAS(36, 56);
OutputByAge NonAIDSdeathsPosM(91, 56);
OutputByAge NonAIDSdeathsPosF(91, 56);
OutputByAge NonAIDSdeathsNegM(91, 56);
OutputByAge NonAIDSdeathsNegF(91, 56);
OutputByAge NetMigrantsPosM(91, 56);
OutputByAge NetMigrantsPosF(91, 56);
OutputByAge NetMigrantsNegM(91, 56);
OutputByAge NetMigrantsNegF(91, 56);
OutputByAge NewHIVmen(81, 56);
OutputByAge NewHIVwomen(81, 56);
///< Inputs for condom model
/*OutputByAge SexExpUnmarriedF(81, 56);
OutputByAge SexExpMarriedF(81, 56);
OutputByAge SexExpUnmarriedDiagF(81, 56);
OutputByAge SexExpMarriedDiagF(81, 56);
OutputByAge SexExpUnmarriedART_F(81, 56);
OutputByAge SexExpMarriedART_F(81, 56);*/

///< Age-specific output tables: TB
OutputByAge MaleTBdeathsAS(16, 56);
OutputByAge FemTBdeathsAS(16, 56);
OutputByAge MaleTBtreatAS(16, 56);
OutputByAge FemTBtreatAS(16, 56);


//************************************************************** ADDITIONAL OUTPUTS FOR TB-IC ****************************************************************************
//******************************************************************************************************************************************************
//Additional outputs MK added 
//PostOutputArray TotLabDiagAllTBscreening(56); // Added from LJ
PostOutputArray TotRxInitAllTBscreening(56); // Added by MK
PostOutputArray Diagnosed_LinkedIN(56); 
PostOutputArray PropnSymptomCheck1(56);
PostOutputArray PropnSymptomCheck2(56); 

PostOutputArray NumberTBContacts(56);

PostOutputArray TotalScreensTargettedD2D(56); 
PostOutputArray Total_dCXRscreensD2DPort(56); 
PostOutputArray TotTSwabScreensPHC(56); 									   
PostOutputArray DiagnosedDrugSuscTest(56); // to be able to cost those follow-up for 
										   // drug susceptibility 
PostOutputArray LinkedToTreatment(56); 
PostOutputArray FollowupTreat(56); // those diagnosed and started on treatment 

//IPT
//added by MK
PostOutputArray TPTdenominator(56); //MK-added
PostOutputArray NumberPreviousTB(56); //MK-added 
PostOutputArray IPTforPLHIV(56); 
PostOutputArray TPT3HPforPLHIV(56);
PostOutputArray IPTforHH(56);
PostOutputArray TPT3HPforHH(56);

//DALY
PostOutputArray AdultYLdisabilityTB(56);//MK - Years Lived with Disability 
//PostOutputArray AdultYLdisabilityTB(56);//MK - Years Lived with Disability 
PostOutputArray AdultTBDALYs(56); //MK - DALYS 

//DALY additional for post-TB
PostOutputArray PostTB_HIVneg(56);
PostOutputArray PostTB_HIVpos(56);
PostOutputArray AdultYLdisabilityPostTB(56);
PostOutputArray AdultLYlostPostTB(56);
PostOutputArray AdultPostTBDALYs(56);
PostOutputArray AdultEpisodePostTBDALYS(56);

PostOutputArray LYlostAIDSTB(70); //LJam
PostOutputArray AdultLYlostTB_HIVpos(70); //LJam
PostOutputArray AdultLYlostTB_HIVneg(70); 



// ****** TB-IC COST-MODEL *******
//NB: Nov 2024. In void RunSample() ensure that for running the for TB-IC, ReadAllFiles() is called at each re-sample.
//Weights for TB DALYS and post-TB DALYS added July 2026
double DWHIVpos = 0.408; // source: GBD
double DWHIVneg = 0.33; // source: GBD
//Borrowed from Nick Menzies 
double DWpostTB_HIVneg = 0.089; // South Africa, country-specific (95% UI 0.040-0.151)
double DWpostTB_HIVpos = 0.089; // same - source doesn't split by HIV status
//double MortRR_postTB_HIVneg = 1.351; // South Africa, country-specific (95% UI 1.167-1.647)
//double MortRR_postTB_HIVpos = 1.351;

double DWpostTB = 0.089;
double MortRR_postTB = 1.351;

double AvgAIDSmortHIVpos[2] = { 0.0240, 0.0184 };  // male, female
// TODO: unweighted average across AnnHIVmortART cells - likely overstates true rate;
// also excludes not-yet-on-ART HIV+ individuals. Replace with population-weighted
// version once ART-duration/CD4 population shares are available.

// Functions
//void SetupCosts();
//void SimInvestmentCase();
//void CalcCostModel();
//void ImportTBParms();

//Additional screeing 
double p = 0.01;  // Example prevalence of TB in high-prevalence communities (1%)
double SeScreenTool1; // Sensitivity of the TB screen (e.g., dCXR or Tongue swab)
double SpScreenTool1; // Specificity of the TB screen
double SeTestTool2; // Sensitivity of a secondary TB screen (if applicable)
double SpTestTool2; // Specificity of the secondary TB screen (if applicable)
double x2Prev = 2 * p; // Prevalence in a high-prevalence communities
//double SpTB_dCXR;


//Adding dcXR at PHC MK 30.12.2024
double CurrSeTB_PHCdXCR[2];
//Total_PHCdCXRscreensD2D.out[CurrSim - 1][iy]
//CurrSeTB_dCXRPHC[0] = 0;
//CurrSeTB_dCXRPHC[1] = 1;
double seDCXR = 0.83;

// Variables
//string costingl[100]; //labels for imported costs
//double costing[100];  //values for imported costs
//int cc;

//string costpopl[100]; //labels for cost population, to export

//double costpop[100][86]; //values for cost population, to export, array denote types and year //MK changed it to double
double BaselineCost[86];
double BaselineImpactNewTB[86];

const int ROWS_TBOpt = 1024;//80;//384; //row[0] = labels;  row[1 to 16384] = coverage values
const int COLS_TBOpt = 3; //17; //different intervention parameters 
const int TBOptInd = 0; //indicator for when applying optimisation
const int NumImportedParms = ROWS_TBOpt; //what ever the number is, shoud be plus 1

int TBOptCounter = 0; //global counter
int TBOptCounterMax = 0;
double TBOptmiseParms[ROWS_TBOpt][COLS_TBOpt];

//double unitcost2[100]; //used in output of total costs
//string totalcostl[100];//labels for total cost, to export
//string unitlabel[100];//units for cost, to export

//long long totalcost[100][54]; //values for total cost, to export, array denote types and year
//long long TotalCost[ResampleSize]; //Totalcost over 20 years

int ILTFU_indi; //indicator to activate intervention to reduce ILTFU
//double Diagnosed_LinkedIN[100][86];


//***************************************************************************Added by Lise for HIV IC
#include <sstream>


//******************************************************************************************Parameters
int Optimise = 0; //0=no optimisation, 1=optimisation for HIV/TB IC, 2= for calibrating/identifying parameter values
const int intercount = 96 + 56; //How many additional interventions to run //MK added +56 slack for TB levers (14 scenarios x ~4 levels avg)
const int maxinter = 96 + 56; //use to make sure arrays are large enough for additional testing

const int ICstart = 2027 - 1985;  //should be 2027 for HIV IC
const int timehorizon = 30;  //NB should be 20 years.

double pvtsector = 0.058; //proportion of population getting HIV testing and care in private sector

//int Zero2030 = 0; //indicator to run analysis where several interventions get reduced to 0%

double PropMessaging = 0.0; //U=U messaging, assumed baseline coverage 0%

double RetentionOR_PN = 1.78; //Peer Nav
double PropWithPN = 0.0;   //Peer Nav coverage- ultimate
double prop_peernav = 0.0;   //Peer Nav coverage- running coverage for scale up

double OriginalIedeaEffect = 0.0; //for POC VL testing intervention
double PropWithPOCVL = 0.0; //POC VL coverage- ultimate
double prop_pocvl = 0.0;  //POC VL - running coverage for scale up
double RetentionRR_POCVL = 1.06; //POC VL retention impact





//const int CEAstart = 2015, CEAstop = 2034;
string effectmeasure = "LYL"; //Choose effective measure to be used in ICER calculation: LYL, HIV, DALY
int newint, newnegint, NWnewint; //values for number of interventions in pool to be considered (excl those which were excluded)
string InterventionName[ResampleSize][maxinter]; //Names for all interventions
int InterventionExclude[ResampleSize][maxinter]; //Which interventions to exclude because they fall in the NW quandrant

int RunIntervention; //to loop through different interventions
string IntName = "";
int CountInt[ResampleSize]; //Running counter for interventions added to baseline
int FlagNegICER[ResampleSize]; //used to flag number of negative ICERS - different algorithm followed if there are 2 or more negative

int calcICER[ResampleSize]; //used to flag whether an icer should be calculated or not
int BaseIntOrder[maxinter + 1]; //Running order of interventions as they get assigned to the baseline scenario. Used to keep track of what has happened
//as interventions get added so we can adjust for compounding effects between interventions
int NoNonNWleft[ResampleSize]; //Loop criteria: For each set, whether there are any non-NW quandrant interventions left 0=Yes there are, 1=No more left

string BaseIntName[ResampleSize][maxinter]; //Baseline Interventions - corresponds to BaseIntToggle with names added
long long BaseIntCost[ResampleSize][maxinter]; //Total Cost of baseline interventions
long long BaseIntEffect[ResampleSize][maxinter]; //Effect of baseline interventions
double BaseIntICER[ResampleSize][maxinter]; //ICER of baseline interventions

int BaseIntToggle[ResampleSize][maxinter]; //Baseline Intervention toggle - indicates which of the interventions are included in new baseline. Where second
//part of array indicates the no. of the intervention applied to baseline, in order.
//i.e. 0 = 1st intervention, 1 = 2nd, 2 = 3rd, etc. Order is important
int BaseInt[ResampleSize][maxinter]; //Baseline Intervention order - array to record the order of interventions where second part of array references
//intervention number, eg. 0=Condom 90%, 1=Condom 30%, etc.
int DelayConsider[ResampleSize][maxinter]; //An array that indicates which interventions should be delayed until the very next time an intervention
//gets considered. We use this when there is a specific pattern related to defaulting an intervention
int IntAllow[ResampleSize][maxinter]; //Like delay consider but works in absolute 0=No, 1=Yes terms - for very specific scenarios
int IntDefault[ResampleSize][maxinter]; //0=No, 1=Yes corresponding with the interventions to show which are defaults. used for new algorithm
int IntNWquad[ResampleSize][maxinter]; //Records whether the interventions have a NW ICER - used to end while loop
int OutPool[ResampleSize][maxinter]; //Checks whether an intervention is out of the pool during runsample, to be used to break loop; resets before each set
int reduceCountInt[ResampleSize]; //flag to reduce CountInt after best intervention is not added to baseline interventions;
const int StopLoopForBudget = 0; //Trigger to tell program to stop loop if budget constraints are hit in 2016/17/18; 0=No, 1=Yes
int BudgetReached[ResampleSize]; //Loop criteria: For each set, whether the budget has been reached 0=No, 1=Yes

long long IntIncEffRrollover[ResampleSize][maxinter];
long long IntIncCostRrollover[ResampleSize][maxinter];
double InterventionICERrollover[ResampleSize][maxinter]; //this array never gets cleared - it stores the last ICER from the previous runs and 
//only gets updated when a new ICER is calculated for the corresponding intervention
//used in defaulting algorithm

long long InitialBaseCost[ResampleSize]; //Baseline cost before any interventions added
long long InitialBaseEff[ResampleSize]; //Baseline effect before any interventions added


long long InterventionTotCost[ResampleSize][maxinter]; //Total cost for intervention
long long InterventionEffect[ResampleSize][maxinter]; //Effect for intervention
long long InterventionIncCost[ResampleSize][maxinter]; //Incremental costs for all interventions
long long InterventionEff[ResampleSize][maxinter]; //Incremental effect for all interventions
double InterventionICER[ResampleSize][maxinter]; //ICERs for all interventions
long long ICERranking[ResampleSize][maxinter][4]; //used to store ranked ICERs, minus excluded interventions; index for ResampleSize,interventions to be sorted; storing [][][0] ICER and [][][1] inter number
long long ICERrankingneg[ResampleSize][maxinter][7]; //used to store ranked negative ICERs, minus excluded interventions; index for ResampleSize,interventions to be sorted; storing [][][0] ICER and [][][1] inter number
//5th element score Cost, 6th effect, 7th final

double ICERranking_d[ResampleSize][maxinter]; //used for ranking, but double type so we can see the decimals points of ICER
double ICERrankingneg_d[ResampleSize][maxinter]; //used for ranking, but double type so we can see the decimals points of ICER
long long ICERNW[ResampleSize][maxinter][4]; //used to store NW ICERs, 0=ICER; 1=intervention number; 2=Cost; 3=Effect

string inter[100][5];
//string costlitl[150]; //labels for literature costs
//double costlit[150];  //values for literature costs
string costingl[250]; //labels for ingredient costs
double costing[250];  //values for ingredient costs
//string NACMl[47][2];
//double NACM[47][7];

//double NACMCD4[20][4]; //values for CD4 distribution per year. array of 20: 2016, 2017,... etc / array of 4: <200,200-349,350-499,500. 
//double rocmAFLF[6], rocmASLF[6], rocmASL[6], rocmATL[6], rocfAFLF[6], rocfASLF[6], rocfASL[6], rocfATL[6]; //used to calculate rate of change from 2016 - 2021
//double rocCFLF[6], rocCSL[6]; //used to calculate rate of change from 2016 - 2021

int costpopsize;
string costpopl[250]; //labels for cost population
long long costpop[250][93]; //values for cost population, array denote types and year, 55+1 to adjust for flow variables
string unitcostl[250][5]; //labels for unit cost - (0) Intervention (1) Ingredient / Literature (2) IN/OUT (3) TE/INT (4) programme area
double unitcost[250];
string totalcostl[250];//labels for total cost
double unitcost2[250]; //used in output of total costs
long long totalcost[250][54]; //values for total cost, array denote types and year
long long CostforICER[ResampleSize][maxinter + 1];
long long TotalCost[ResampleSize]; //Totalcost

double LYLforICER[ResampleSize]; //LYL for ICER  - changed from long long to double 20 jan 16
double DALYforICER[ResampleSize]; //DALY for ICER
long long HIVforICER[ResampleSize]; //HIV infections for ICER&&
long long baselinecost[ResampleSize]; //Baseline TotalCost
double baselineEff[ResampleSize]; //Effectiveness measure for baseline - changed from long long to double 20 jan 16

// TB ICER outputs
double TBLYLforICER[ResampleSize];     // TB life-years lost
double TBDALYforICER[ResampleSize];    // TB DALYs, summed over the investment-case horizon
long long TBCasesforICER[ResampleSize];// TB cases averted proxy (NewActiveTBadult)
double CombinedLYLforICER[ResampleSize];  // = LYLforICER + TBLYLforICER  (HIV/TB joint LYL)
double CombinedDALYforICER[ResampleSize]; // = DALYforICER + TBDALYforICER 


int UTTretention = 0;
double RetIntCost = 0;
int CABlong = 0;
int LENlong = 0;
int LENmodel = 0;
int CABmodel = 0;

string LENdur = "NA";
string CABdur = "NA";


int flagcount = 0;
double ParmsA[intercount + 1][30]; //parameters not time-dependent, +1 for baseline
double ParmsB[intercount + 1][30][timehorizon]; //parameters time-dependent, +1 for baseline

long long CostforBudget1[maxinter + 1][ResampleSize];
long long CostforBudget2[maxinter + 1][ResampleSize];
long long CostforBudget3[maxinter + 1][ResampleSize];
long long MaxBudget1, MaxBudget2, MaxBudget3;
double BudgetFraction = 1.0;

long long CostforBudget1_NoOpt[ResampleSize];
long long CostforBudget2_NoOpt[ResampleSize];
long long CostforBudget3_NoOpt[ResampleSize];
long long budget[10][3]; //budget for SA and national


//LJ: Variables to save default parameter estimates when using function GetDefaultAssump()
double OnARThalfIntDur_def[6][2];
double HCT_ARTuptake_def[93];
double HCT1stTimeF25_def[93];
double NeonatalMMC_def[93];
double RR_MMCpromo10_def[93]; // RR of MMC promotion at ages 10-14
double RR_MMCpromo15_def[93]; // RR of MMC promotion at ages 15-19
double RR_MMCpromo20_def[93]; // RR of MMC promotion at ages 20-24
double RR_MMCpromo25_def[93]; // RR of MMC promotion at ages 25-49
double RR_MMCpromo50_def[93]; // RR of MMC promotion at ages 50+

double RR_ARTinterruption_def[93];

double ORcondomModel2_FSW_def[93]; // ratio of odds of condom use in model 2 to model 1 (FSW)
double ORcondomModel2_ST_def[93]; // ratio of odds of condom use in model 2 to model 1 (ST)
double ORcondomModel2_LT_def[93]; // ratio of odds of condom use in model 2 to model 1 (LT)

double UltPrEPrateFSW_def;
double UltCABLArateFSW_def;
double RR_PrEPstartMSM_def[93];
double RR_PrEPstartF20_def[93];
double CABLApregnant_def[93];
double PrEPpregnant_def[93];
double MatARTuptake_def[93];
double PCR6week_def[93];
double PCR6month_def[93];


int LastAdolTest;
int LastMMC;
string LastHCT, LastSTpack, LastOralPrEP;
double AdolHCTMultiplier = 1; //used to adjust testing rates for adolescents
double AdolHCTMultiplierPM = 1; //used to adjust testing rates for adolescents

double YAHCTMultiplier = 1; //used to adjust testing rates for 20-24 year olds
double NewlyTestedNeg15_19; // Adolescents who tested negative through HCT in current year (by sex)
double NewlyTestedPos15_19;
double NewlyTestedNeg20_24; // Adolescents who tested negative through HCT in current year (by sex)
double NewlyTestedPos20_24;

double NewlyTestedNeg15_24F; // AGYW through HCT in current year (by sex)
double NewlyTestedPos15_24F;


double LastCondomMultiplier;
double LastCondomAdjMultiplier;
double LastCondomPerc;
double TempNeg15_19, TempPos15_19;
double TempNeg15_24F, TempPos15_24F;

double NewCABLA_nonMSM;
double NewCABLA_nonFSW;
double NewPrEP_nonMSM;
double NewPrEP_nonFSW;



//*************************************************************Functions
void SimInvestmentCase();
void SimInvestmentCaseOpt();
void SetSQ();
void SaveParmNormal(); //save key parameters in a normal run
void RecordParameters(int chosen); //Used to save all parameters used for particular optimisation set, from 2015 onwards only.
void GetDefaultAssump(); //Get default parameter asfsumptions at start of program and save them for later use (when reverting to default interventions
void EliminateLowerCoverage(int iy); //Eliminate lower coverage for previous intervention, argument is simulation (Resamplesize) number
void EliminateCurrentDefault(int iy); //Eliminate current default as previous intervention will become the new default
void ReleaseBaseInt(int Best, int iy); //Releasing BaseInt values after a reversion won, arguments BestIntervention/NextBest and simulation (Resamplesize) number
void AssessBudget(int chosen, int iy); //Determines whether budget has been reached, given chosen intervention and simulation (Resamplesize)
int IsNextDefault(int chosen, int iy);
int IsNextNotDefault(int chosen, int iy);
int IsNextNotLowerCov(int chosen, int iy);
int IsNextLowerCov(int chosen, int iy);

int DontRunModel();
int IsLowerNotDefault(int arrint, int iy); //for looping through icer ranking for finding next best intervention
double NewlyTestedNeg_PrEP[2];

void SetupCosts();
void CalcCostModel();
void CalcEffect();

void InitializeBudget();

void Int_MMCBm2();
void Int_MMCBm1();
void Int_MMCDefault();
void Int_MMCBp1();
void Int_MMCBp2();
void Int_MMCBp3();

void Int_MMCMax();
void Int_EIMCBm2();
void Int_EIMCBm1();
void Int_EIMCDefault();
void Int_EIMCBp1();
void Int_EIMCBp2();
void Int_EIMCBp3();
void Int_EIMCMax();
void Int_CondomSupplyBm2();
void Int_CondomSupplyBm1();
void Int_CondomSupplyDefault();
void Int_CondomSupplyBp1();
void Int_CondomSupplyBp2();
void Int_CondomSupplyBp3();
void Int_CondomSupplyMax();
void Int_Test6monthsBm2();
void Int_Test6monthsBm1();
void Int_Test6monthsDefault();
void Int_Test6monthsBp1();
void Int_Test6monthsBp2();
void Int_Test6monthsBp3();
void Int_Test6monthsMax();
void Int_Test10weeksBm2();
void Int_Test10weeksBm1();
void Int_Test10weeksDefault();
void Int_Test10weeksBp1();
void Int_Test10weeksBp2();
void Int_Test10weeksBp3();
void Int_Test10weeksMax();

/*
void Int_OralPrepMedium();
void Int_OralPrepHigh();
void Int_OralPrepPregDefault();
void Int_OralPrepPregBp1();
void Int_OralPrepPregBp2();
void Int_OralPrepPregBp3();
void Int_OralPrepPregMax();*/

void Int_OralPrepBm2();
void Int_OralPrepBm1();
void Int_OralPrepDefault();
void Int_OralPrepBp1();
void Int_OralPrepBp2();
void Int_OralPrepBp3();
void Int_OralPrepMax();

void Int_OralPrepPWIDBm2();
void Int_OralPrepPWIDBm1();
void Int_OralPrepPWIDDefault();
void Int_OralPrepPWIDBp1();
void Int_OralPrepPWIDBp2();
void Int_OralPrepPWIDBp3();
void Int_OralPrepPWIDMax();




void Int_LENndohBm2();
void Int_LENndohBm1();
void Int_LENndohDefault();
void Int_LENndohBp1();
void Int_LENndohBp2();
void Int_LENndohBp3();
void Int_LENndohMax();

void Int_LENPWIDndohBm2();
void Int_LENPWIDndohBm1();
void Int_LENPWIDndohDefault();
void Int_LENPWIDndohBp1();
void Int_LENPWIDndohBp2();
void Int_LENPWIDndohBp3();
void Int_LENPWIDndohMax();



void Int_LENOptDefault();
void Int_LENOptBp0();
void Int_LENOptBp1();
void Int_LENOptBp2();
void Int_LENOptBp3();
void Int_LENOptMax();


void Int_CABLAPregDefault();
void Int_CABLAPregBp1();
void Int_CABLAPregBp2();
void Int_CABLAPregBp3();
void Int_CABLAPregMax();
void Int_TestAdolDefault();
void Int_TestAdolBp1();
void Int_TestAdolBp2();
void Int_TestAdolBp3();
void Int_TestAdolMax();
void Int_HCTBm2();
void Int_HCTBm1();
void Int_HCTDefault();
void Int_HCTBp1();
void Int_HCTBp2();
void Int_HCTBp3();
void Int_HCTMax();
void Int_ARTuniversalBm2();
void Int_ARTuniversalBm1();
void Int_ARTuniversalDefault();
void Int_ARTuniversalBp1();
void Int_ARTuniversalBp2();
void Int_ARTuniversalBp3();
void Int_ARTuniversalBp4();
void Int_ARTuniversalBp5();
void Int_ARTuniversalBp6();

void Int_ARTuniversalMax();
void Int_STpackDefault();
void Int_STpackBp1();
void Int_STpackBp2();
void Int_STpackBp3();
void Int_STpackMax();
void Int_Test18monthsBm2();
void Int_Test18monthsBm1();
void Int_Test18monthsDefault();
void Int_Test18monthsBp1();
void Int_Test18monthsBp2();
void Int_Test18monthsBp3();
void Int_Test18monthsMax();
void Int_POCVL_Inactive();
void Int_POCVL_Active();
void Int_UU_Inactive();
void Int_UU_Active();
void Int_MensClinics_Inactive();
void Int_MensClinics_Active();
void Int_PeerNav_Inactive();
void Int_PeerNav_Active();


void RecordOutputOpt();

//Outputs
PostOutputArray TotOnCABLA_M(67);
PostOutputArray TotOnCABLA_F(67);
PostOutputArray F25_34onCABLA(67);


double CABLAeligOtherG[93][2]; // Proportion of other groups eligible to initiate PrEP by sex
double PrEPeligOtherG[93][2]; // Proportion of other groups eligible to initiate PrEP by sex

double RR_ARTinit[93]; //reduce ART initation rates in adults, annual by sex
double RR_ARTinitSex[93][2]; //reduce ART initation rates in adults, annual by sex


//double RR_ARTinitP[21]; //reduce ART initation rates in children, annual
int RR_ARTinityr = ICstart + 1985; //starting point where RR are applied

PostOutputArray PrEPcoverageNonMSM(92);
PostOutputArray CABLAcoverageMSM(67);
PostOutputArray CABLAcoverageNonMSM(67);
PostOutputArray CABLAcoverageFSW(67);
PostOutputArray CABLAcoverageAGYW(67);
PostOutputArray CABLAcoverageAllF(67);
PostOutputArray CABLAcoverageAllM(67);

PostOutputArray CondomUsageAdjFactor(92);
PostOutputArray CondomUsageAdjFactor_def(92);
PostOutputArray CovNeonatalCirc(92);
PostOutputArray CovNeonatalCirc_def(92);
PostOutputArray TotSTestprimaryPHC(92);
PostOutputArray CovPregWomenTest(92);
PostOutputArray TotalHIVtestsPrEP(92);
PostOutputArray HIVtestsPosNoPrEP(92);

PostOutputArray CovPCR10weeks(92);
PostOutputArray CovPCR6months(92);
PostOutputArray CovBirthTest(92);

PostOutputArray TotalHIVtests15_19(92);
PostOutputArray TotalHIVtests15_24F(92);

PostOutputArray TotalHIVtestsNeg15_19(92);
PostOutputArray TotalHIVtestsPos15_19(92);

PostOutputArray Total15_19(92);

PostOutputArray TotalART1to2(92);
PostOutputArray TotalART3to5(92);
PostOutputArray TotalART6to9(92);
PostOutputArray TotalART10to14(92);
PostOutputArray StartingART6to9(92);
PostOutputArray StartingART10to14(92);

PostOutputArray NewCABLAinNonMSM(92);
PostOutputArray NewCABLAinNonFSW(92);

PostOutputArray NewPrEPinNonMSM(92);
PostOutputArray NewPrEPinNonFSW(92);

PostOutputArray NonMSMonPrEP(92);
PostOutputArray NonMSMonCABLA(92);

double TotARTbase[20];

int bl;  //0=old baseline, 1=baseline+LEN GF, 2=PEPFAR minimum scenario

//for HIV IC calibration of parameters

double ptest;// , pbase; //for calibration for HIV IC
int yrtest;
const int tnum = 8; //number of target values
int target_curr;
const int yr = 2; //from 2027-2028
double parmyear[tnum][yr]; //to capture all parameters from 2028, initalized to zero, (we know the 2026 and 27 parms)
int styr = 2027; //starting year

const int fswnum = 9; //number of targets for fsw
int fsw_curr;
double parmSETFSWyear[2][fswnum]; //to parmaterize FSW LEN by year (2026 and 2027) for each target for fsw

double VLsuppOR = 1;