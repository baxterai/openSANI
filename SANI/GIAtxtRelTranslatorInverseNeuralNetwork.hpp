/*******************************************************************************
 *
 * No License
 * 
 * This work is under exclusive copyright (c) Baxter AI (baxterai.com). 
 * Nobody else can use, copy, distribute, or modify this work without being 
 * at risk of take-downs, shake-downs, or litigation. 
 * 
 * By publishing this source code in a public repository on GitHub, Terms of 
 * Service have been accepted by which Baxter AI have allowed others to view 
 * and fork their repository.
 * 
 * If you find software that doesn't have a license, that generally means you 
 * have no permission from the creators of the software to use, modify, or 
 * share the software. Although a code host such as GitHub may allow you to 
 * view and fork the code, this does not imply that you are permitted to use, 
 * modify, or share the software for any purpose.
 *
 * This notice has been derived from https://choosealicense.com/no-permission 
 * (https://web.archive.org/web/20180312144938/https://choosealicense.com/no-permission)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: GIAtxtRelTranslatorInverseNeuralNetwork.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 3g1f 24-April-2018
 * Requirements: requires plain text file
 * Description: Textual Relation Translator Inverse Neural Network
 * /
 *******************************************************************************/


#ifndef HEADER_GIA_TXT_REL_TRANSLATOR_INVERSE_NEURAL_NETWORK
#define HEADER_GIA_TXT_REL_TRANSLATOR_INVERSE_NEURAL_NETWORK

#include "GIAglobalDefs.hpp"

#ifdef GIA_TXT_REL_TRANSLATOR_RULES_GIA3

#include "GIAtranslatorOperations.hpp"
#include "GIAtxtRelTranslatorRules.hpp"
#include "GIAtxtRelTranslatorRulesGroupClass.hpp"
#include "GIAtxtRelTranslatorRulesComponentClass.hpp"
#include "GIApreprocessorPOStagger.hpp"
#include "GIApreprocessorWordClass.hpp"
#include "GIApreprocessorSentenceClass.hpp"
#include "SHAREDvars.hpp"

class GIAtxtRelTranslatorInverseNeuralNetworkClass
{
	private: GIAtranslatorOperationsClass GIAtranslatorOperations;
	private: GIAtxtRelTranslatorRulesGroupClass GIAtxtRelTranslatorRulesGroupClassObject;
	private: GIAtxtRelTranslatorRulesComponentClass GIAtxtRelTranslatorRulesComponentClassObject;
	private: GIAtxtRelTranslatorRulesClass GIAtxtRelTranslatorRules;
	private: GIApreprocessorPOStaggerClass GIApreprocessorPOStagger;
	private: GIApreprocessorWordClassClass GIApreprocessorWordClassObject;
	private: GIApreprocessorSentenceClass GIApreprocessorSentenceClassObject;
	private: SHAREDvarsClass SHAREDvars;

	private: bool generateParseTreeIntro(vector<XMLparserTag*>* GIAtxtRelTranslatorRulesTokenLayers, vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes, vector<GIApreprocessorPlainTextWord*>* sentenceContents, GIAtxtRelTranslatorRulesGroup* firstParseTreeGroup, int* performance, const bool parseIsolatedSubreferenceSets);
		private: bool generateParseTreeGroupType(vector<XMLparserTag*>* GIAtxtRelTranslatorRulesTokenLayers, GIAtxtRelTranslatorRulesGroupType* groupType, vector<GIApreprocessorPlainTextWord*>* sentenceContentsSubset, GIAtxtRelTranslatorRulesGroup* currentParseTreeGroup, int* performance, int layer, string previousGroupType, int numberOfConsecutiveTimesPreviousGroupType, GIAtxtRelTranslatorRulesComponent* previousParseTreeComponent);
			private: bool generateParseTreeGroup(vector<XMLparserTag*>* GIAtxtRelTranslatorRulesTokenLayers, GIAtxtRelTranslatorRulesGroup* group, vector<GIApreprocessorPlainTextWord*>* sentenceContentsSubset, GIAtxtRelTranslatorRulesGroup* currentParseTreeGroup, int* performance, int layer, string previousGroupType, int numberOfConsecutiveTimesPreviousGroupType);
				private: bool generateRulesGroupTreeComponents(vector<XMLparserTag*>* GIAtxtRelTranslatorRulesTokenLayers, vector<GIAtxtRelTranslatorRulesComponent*>* components, vector<GIApreprocessorPlainTextWord*>* sentenceContentsSubset, GIAtxtRelTranslatorRulesGroup* currentParseTreeGroup, int* performance, bool subcomponents, int subcomponentsType, bool subcomponentsOptional, int layer, string previousGroupType, int numberOfConsecutiveTimesPreviousGroupType);
					private: bool generateRulesGroupTreeComponent(vector<XMLparserTag*>* GIAtxtRelTranslatorRulesTokenLayers, GIAtxtRelTranslatorRulesComponent* component, vector<GIApreprocessorPlainTextWord*>* sentenceContentsSubset, GIAtxtRelTranslatorRulesComponent* currentParseTreeComponent, int* performance, int layer, string previousGroupType, int numberOfConsecutiveTimesPreviousGroupType);
		#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_COMPONENT_WORD_NOUN_VERB_VARIANT
		private: bool forwardNounVerbVariantRequirementsComponentToGroup(GIAtxtRelTranslatorRulesComponent* component, GIAtxtRelTranslatorRulesGroup* newParseGroup);
		private: bool forwardNounVerbVariantRequirementsGroupToComponent(GIAtxtRelTranslatorRulesGroup* currentParseGroup, GIAtxtRelTranslatorRulesComponent* currentComponent);
		#endif
		private: bool findStringMatch(vector<XMLparserTag*>* GIAtxtRelTranslatorRulesTokenLayers, GIAtxtRelTranslatorRulesComponent* component, GIApreprocessorPlainTextWord* currentWord, GIAtxtRelTranslatorRulesComponent* currentParseTreeComponent);
		private: bool verifyPOStype(GIApreprocessorPlainTextWord* currentWord, unsigned char wordPOStype);
		private: bool updatePerformance(const int performanceTemp, int* performance, GIAtxtRelTranslatorRulesGroup* currentParseTreeGroup, GIAtxtRelTranslatorRulesGroup* currentParseTreeGroupTemp, const bool passedTemp, int* minIndexOfMatchesFoundBackupOptimum, vector<GIApreprocessorPlainTextWord*>* sentenceContentsSubset, const int minIndexOfMatchesFoundBackup, GIAtxtRelTranslatorRulesComponent* previousParseTreeComponent);
			private: bool deleteAllSubgroupsRecurse(GIAtxtRelTranslatorRulesGroup* currentParseTreeGroup, int layer);
			private: bool deleteParseComponent(GIAtxtRelTranslatorRulesComponent* currentParseTreeComponent);
		public: int calculateMinIndexOfMatchesFound(vector<GIApreprocessorPlainTextWord*>* sentenceContentsSubset);
		private: void clearAllWordsAlreadyFoundMatchInComponent(vector<GIApreprocessorPlainTextWord*>* sentenceContentsSubset, const int minIndexOfMatchesFoundBackup);
		private: void restoreAllWordsAlreadyFoundMatchInComponent(vector<GIApreprocessorPlainTextWord*>* sentenceContentsSubset, const int minIndexOfMatchesFoundNew);
	private: void defineSubstancesBasedOnNetworkAndDeterminerInfo(GIAtranslatorVariablesClass* translatorVariables);
	private: int getEntityArrayMaxIndex(GIAtranslatorVariablesClass* translatorVariables);

	private: bool transferParseTreePOStypeInferredToWordList(GIAtranslatorVariablesClass* translatorVariables);
	private: bool transferParseTreePOStypeInferredToWordList(GIAtxtRelTranslatorRulesGroup* currentParseTreeGroup, int layer);
	private: bool printParseTreeDebugIndentation(int layer);

};
#endif




#endif
