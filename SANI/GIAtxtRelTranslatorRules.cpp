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
 * File Name: GIAtxtRelTranslatorRules.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2019 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 3h4c 25-April-2019
 * Requirements: requires plain text file
 * Description: Textual Relation Translator Rules
 * /
 *******************************************************************************/



#include "GIAtxtRelTranslatorRules.hpp"
#include "XMLrulesClass.hpp"


#ifdef GIA_TXT_REL_TRANSLATOR_RULES

vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypesGlobal;
vector<XMLparserTag*>* GIAtxtRelTranslatorRulesTokenLayersGlobal;

vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesClass::getGIAtxtRelTranslatorRulesGroupTypesGlobal()
{
	return GIAtxtRelTranslatorRulesGroupTypesGlobal;
}
vector<XMLparserTag*>* GIAtxtRelTranslatorRulesClass::getGIAtxtRelTranslatorRulesTokenLayersGlobal()
{
	return GIAtxtRelTranslatorRulesTokenLayersGlobal;
}

bool GIAtxtRelTranslatorRulesClass::extractGIAtxtRelTranslatorRulesGroups(vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes)
{
	bool result = true;
	
	#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_ANN
	for(int i=0; i<GIAtxtRelTranslatorRulesGroupTypes->size(); i++)
	{
		GIAtxtRelTranslatorRulesGroupType* groupType = GIAtxtRelTranslatorRulesGroupTypes->at(i);
		for(int j=0; j<(groupType->groups).size(); j++)
		{
			GIAtxtRelTranslatorRulesGroupNeuralNetwork* group = (groupType->groups)[j];
			delete group->neuronReference;
		}
	}
	#endif

	XMLparserTag* firstTagInRulesTag = XMLparserClass.parseTagDownALevel(GIAtxtRelTranslatorFirstTagInXMLfile, RULES_XML_TAG_rules, &result);
	if(result)
	{
		XMLparserTag* currentTag = firstTagInRulesTag;
		bool foundTxtRelTranslatorTag = false;
		XMLparserTag* firstTagInTxtRelTranslatorTag = NULL;
		while((currentTag->nextTag != NULL) && !foundTxtRelTranslatorTag)
		{
			if(currentTag->name == GIA_TXT_REL_TRANSLATOR_RULES_TAG_txtRelTranslator)
			{
				foundTxtRelTranslatorTag = true;
				firstTagInTxtRelTranslatorTag = XMLparserClass.parseTagDownALevel(currentTag, GIA_TXT_REL_TRANSLATOR_RULES_TAG_txtRelTranslator, &result);
			}
			currentTag = currentTag->nextTag;
		}
				
		if(foundTxtRelTranslatorTag)
		{
			XMLparserTag* currentTagInTxtRelTranslator = firstTagInTxtRelTranslatorTag;
			
			bool foundTxtRelTranslatorGroupsTag = false;
			XMLparserTag* firstTagInTxtRelTranslatorGroupsTag = NULL;
			while((currentTagInTxtRelTranslator->nextTag != NULL) && !foundTxtRelTranslatorGroupsTag)
			{
				if(currentTagInTxtRelTranslator->name == GIA_TXT_REL_TRANSLATOR_RULES_TAG_groups)
				{
					foundTxtRelTranslatorGroupsTag = true;
					firstTagInTxtRelTranslatorGroupsTag = XMLparserClass.parseTagDownALevel(currentTagInTxtRelTranslator, GIA_TXT_REL_TRANSLATOR_RULES_TAG_groups, &result);
				}
				currentTagInTxtRelTranslator = currentTagInTxtRelTranslator->nextTag;
			}
						
			if(foundTxtRelTranslatorGroupsTag)
			{
				XMLparserTag* currentTagInGroupsTag = firstTagInTxtRelTranslatorGroupsTag;
				bool foundTxtRelTranslatorGroupTypeTag = false;	//NOTUSED
				while(currentTagInGroupsTag->nextTag != NULL)
				{
					if(currentTagInGroupsTag->name == GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_TAG_groupType)
					{
						foundTxtRelTranslatorGroupTypeTag = true;
												
						string groupTypeName = "";
						string referenceSetType = GIAtxtRelTranslatorRulesGroupsComponentReferenceSetTypes[GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_REFERENCE_SET_TYPE_UNKNOWN];
						if(!XMLparserClass.getAttribute(currentTagInGroupsTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUPTYPE_ATTRIBUTE_groupTypeName, &groupTypeName))
						{
							cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInGroupsTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUPTYPE_ATTRIBUTE_groupTypeName, &groupTypeName)" << endl;
							exit(EXIT_ERROR);
						}
						if(!XMLparserClass.getAttribute(currentTagInGroupsTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUPTYPE_ATTRIBUTE_referenceSetType, &referenceSetType))
						{
							cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInGroupsTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUPTYPE_ATTRIBUTE_referenceSetType, &referenceSetType)" << endl;
							exit(EXIT_ERROR);
						}
					
						int referenceSetTypeInt = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_REFERENCE_SET_TYPE_UNKNOWN;
						if(!SHAREDvars.textInTextArray(referenceSetType, GIAtxtRelTranslatorRulesGroupsComponentReferenceSetTypes, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_REFERENCE_SET_TYPE_NUMBER_OF_TYPES, &referenceSetTypeInt))
						{
							cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: componentType unknown; referenceSetType = " << referenceSetType << endl;
							exit(EXIT_ERROR);
						}
								
						GIAtxtRelTranslatorRulesGroupType* groupType = new GIAtxtRelTranslatorRulesGroupType();
						groupType->groupTypeName = groupTypeName;
						groupType->referenceSetType = referenceSetTypeInt;
						GIAtxtRelTranslatorRulesGroupTypes->push_back(groupType);
						//cout << "groupType->groupTypeName = " << groupType->groupTypeName << endl;
						
						XMLparserTag* firstTagInTxtRelTranslatorGroupTypeTag = XMLparserClass.parseTagDownALevel(currentTagInGroupsTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_TAG_groupType, &result);

						XMLparserTag* currentTagInTxtRelTranslatorGroupTypeTag = firstTagInTxtRelTranslatorGroupTypeTag;
						bool foundTxtRelTranslatorGroupTag = false;	//NOTUSED
						while(currentTagInTxtRelTranslatorGroupTypeTag->nextTag != NULL)
						{
							if(currentTagInTxtRelTranslatorGroupTypeTag->name == GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUPTYPE_TAG_group)
							{								
								vector<string> semanticRelationFunctionName(GIA_TXT_REL_TRANSLATOR_MAX_NUMBER_OF_SEMANTIC_FUNCTIONS_EXECUTED_PER_GROUP);
								#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_NEW_CONDITIONS
								string semanticRelationFunctionConditionNewName = "";
								#endif
								string groupName = "";
								#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_GROUP_PREVIOUS_WORD_POS_TYPE
								string previousWordPOStype = "";
								#endif
								#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_GROUP_EXISTS_PRECEEDING_WORD_POS_TYPE
								string existsPreceedingWordPOStype = "";
								#endif
								#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_TAKE_LAST_SUCCESSFUL_PARSE_LIMIT_ITERATIONS_PREFERENCE_WEIGHT
								string groupWeight = "";
								int groupWeightInt = 0;
								#endif
								if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTypeTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUP_ATTRIBUTE_semanticRelationFunctionName, &(semanticRelationFunctionName[0])))
								{
									//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} warning: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTypeTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUP_ATTRIBUTE_semanticRelationFunctionName, &(semanticRelationFunctionName[2]))" << endl;
								}
								if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTypeTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUP_ATTRIBUTE_semanticRelationFunctionName2, &(semanticRelationFunctionName[1])))
								{
									//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} warning: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTypeTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUP_ATTRIBUTE_semanticRelationFunctionName2, &(semanticRelationFunctionName2[1]))" << endl;
								}
								#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_NEW_CONDITIONS
								if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTypeTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUP_ATTRIBUTE_semanticRelationFunctionConditionNewName, &semanticRelationFunctionConditionNewName))
								{
									//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} warning: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTypeTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUP_ATTRIBUTE_semanticRelationFunctionConditionNewName, &(semanticRelationFunctionConditionNewName[2]))" << endl;
								}
								#endif
								if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTypeTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUP_ATTRIBUTE_groupName, &groupName))
								{
									//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} warning: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTypeTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUP_ATTRIBUTE_groupName, &groupName)" << endl;
								}
								#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_GROUP_PREVIOUS_WORD_POS_TYPE
								if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTypeTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUP_ATTRIBUTE_previousWordPOStype, &previousWordPOStype))
								{
									//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} warning: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTypeTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUP_ATTRIBUTE_previousWordPOStype, &previousWordPOStype)" << endl;
								}
								#endif
								#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_GROUP_EXISTS_PRECEEDING_WORD_POS_TYPE
								if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTypeTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUP_ATTRIBUTE_existsPreceedingWordPOStype, &existsPreceedingWordPOStype))
								{
									//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} warning: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTypeTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUP_ATTRIBUTE_existsPreceedingWordPOStype, &existsPreceedingWordPOStype)" << endl;
								}
								#endif
								#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_TAKE_LAST_SUCCESSFUL_PARSE_LIMIT_ITERATIONS_PREFERENCE_WEIGHT
								if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTypeTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUP_ATTRIBUTE_groupWeight, &groupWeight))
								{
									//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} warning: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTypeTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUP_ATTRIBUTE_groupWeight, &groupWeight)" << endl;
								}
								else
								{
									groupWeightInt = SHAREDvars.convertStringToInt(groupWeight);
								}
								#endif
								
								bool passGroupNameRequirements = true;
								bool GIAwithNoExternalProcessingFunctionFound = false;
								bool GIAwithExternalProcessingFunctionFound = false;
								if(SHAREDvars.textInTextArray(groupName, GIAtxtRelWithNoExternalProcessingGroupNameArray, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_WITH_NO_EXTERNAL_PROCESSING_NUMBER_OF_TYPES))
								{
									GIAwithNoExternalProcessingFunctionFound = true;
								}	
								if(SHAREDvars.textInTextArray(groupName, GIAtxtRelWithExternalProcessingGroupNameArray, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_WITH_EXTERNAL_PROCESSING_NUMBER_OF_TYPES))
								{
									GIAwithExternalProcessingFunctionFound = true;
								}
								#ifdef GIA_EXTERNAL_PROCESSING
								if(GIAwithNoExternalProcessingFunctionFound)
								{
									passGroupNameRequirements = false;
								}
								#else
								if(GIAwithExternalProcessingFunctionFound)
								{
									passGroupNameRequirements = false;
								}
								#endif
								if(passGroupNameRequirements)
								{
									GIAtxtRelTranslatorRulesGroupNeuralNetwork* group = new GIAtxtRelTranslatorRulesGroupNeuralNetwork();	
									group->semanticRelationFunctionName = semanticRelationFunctionName;
									#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_NEW_CONDITIONS
									group->semanticRelationFunctionConditionNewName = semanticRelationFunctionConditionNewName;
									//cout << "semanticRelationFunctionConditionNewName = " << semanticRelationFunctionConditionNewName << endl;
									#endif
									group->groupName = groupName;
									#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_GROUP_PREVIOUS_WORD_POS_TYPE
									group->previousWordPOStype = previousWordPOStype;
									#endif
									#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_GROUP_EXISTS_PRECEEDING_WORD_POS_TYPE
									group->existsPreceedingWordPOStype = existsPreceedingWordPOStype;
									#endif
									#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_TAKE_LAST_SUCCESSFUL_PARSE_LIMIT_ITERATIONS_PREFERENCE_WEIGHT
									group->groupWeight = groupWeightInt;
									#endif
									
									#ifdef GIA_TXT_REL_TRANSLATOR_RULES_DEFINE_GROUP_TYPE_BACKUP_AT_START
									group->groupTypeName = groupType->groupTypeName;
									group->groupTypeReferenceSetType = groupType->referenceSetType;
									#endif
									
									/*
									#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_LIGHT_NEW
									group->currentParseTreeGroupTemp = new GIAtxtRelTranslatorRulesGroupNeuralNetwork(*group);
									#endif
									*/
									
									groupType->groups.push_back(group);

									XMLparserTag* firstTagInTxtRelTranslatorGroupTag = XMLparserClass.parseTagDownALevel(currentTagInTxtRelTranslatorGroupTypeTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUPTYPE_TAG_group, &result);

									if(!parseComponents(firstTagInTxtRelTranslatorGroupTag, group, &(group->components), false, NULL))
									{
										cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !parseComponents(firstTagInTxtRelTranslatorGroupTag, &(group->components), false))" << endl;
										exit(EXIT_ERROR);			
									}
								}
							}
							else
							{
								cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !(currentTagInGroups->name == GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUPSTYPE_TAG_group)" << endl;
								exit(EXIT_ERROR);					
							}

							currentTagInTxtRelTranslatorGroupTypeTag = currentTagInTxtRelTranslatorGroupTypeTag->nextTag;
						}
					}
					else
					{
						cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !(currentTagInGroups->name == GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUPS_TAG_groupType)" << endl;
						exit(EXIT_ERROR);					
					}
					
					currentTagInGroupsTag = currentTagInGroupsTag->nextTag;
				}
			}
		}
	}

	#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_REMOVE_LAST_OPTIONAL_COMPONENTS
	if(!removeLastOptionalComponents(GIAtxtRelTranslatorRulesGroupTypes))
	{
		result = false;
	}	
	#endif
		
	if(!connectGroupsReferences(GIAtxtRelTranslatorRulesGroupTypes))
	{
		result = false;
	}
	
	GIAtxtRelTranslatorRulesGroupTypesGlobal = GIAtxtRelTranslatorRulesGroupTypes;
	
	return result;
}


bool GIAtxtRelTranslatorRulesClass::parseComponents(XMLparserTag* firstTxtRelTranslatorRulesFirstComponentTag, GIAtxtRelTranslatorRulesGroupNeuralNetwork* groupOwner, vector<GIAtxtRelTranslatorRulesComponentNeuralNetwork*>* componentsList, const bool parseSubcomponent, GIAtxtRelTranslatorRulesComponentNeuralNetwork* subComponentOwner)
{
	bool result = true;
	
	XMLparserTag* currentTagInTxtRelTranslatorGroupTag = firstTxtRelTranslatorRulesFirstComponentTag;
	bool foundTxtRelTranslatorGroupTag = false;	//NOTUSED
	int componentIndex = GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_COMPONENT_INDEX_FIRST;
	while(currentTagInTxtRelTranslatorGroupTag->nextTag != NULL)
	{
		if(currentTagInTxtRelTranslatorGroupTag->name == GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUP_TAG_example)
		{
			//ignore
		}
		else if(currentTagInTxtRelTranslatorGroupTag->name == GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUP_TAG_component)
		{			
			#ifdef GIA_TXT_REL_TRANSLATOR_HYBRID
			string referenceSetTypeHybrid = GIAtxtRelTranslatorRulesGroupsComponentReferenceSetTypeHybridTypes[GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_REFERENCE_SET_TYPE_HYBRID_UNKNOWN];
			#endif
			string componentType = GIAtxtRelTranslatorRulesGroupsComponentTypes[GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_UNKNOWN];
			int componentTypeInt = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_UNKNOWN;
			string groupTypeRefName = "";
			string groupRefName = "";
			string stringType = GIAtxtRelTranslatorRulesGroupsComponentStringTypes[GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_STRINGTYPE_UNKNOWN];
			int stringTypeInt = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_STRINGTYPE_UNKNOWN;
			string word = "";
			string wordPOStype = "";
			string tokenLayer = "";
			string tokenClass = "";
			string tokenType = "";
			#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_COMPONENT_MISSING
			string missing = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_VALUE_false;
			#endif
			#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_ADD_EXPLICIT_WORD_REFERENCES_AS_INDEPENDENT_POS_PERMUTATIONS_EFFICIENT
			string addToExplicitWordTempPOS = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_VALUE_false;
			#endif
			vector<string> semanticRelationIndexType(GIA_TXT_REL_TRANSLATOR_MAX_NUMBER_OF_SEMANTIC_FUNCTIONS_EXECUTED_PER_GROUP);
			vector<int> semanticRelationIndexTypeInt(GIA_TXT_REL_TRANSLATOR_MAX_NUMBER_OF_SEMANTIC_FUNCTIONS_EXECUTED_PER_GROUP);
			for(int i=0; i<GIA_TXT_REL_TRANSLATOR_MAX_NUMBER_OF_SEMANTIC_FUNCTIONS_EXECUTED_PER_GROUP; i++)
			{
				semanticRelationIndexType[i] = GIAtxtRelTranslatorRulesGroupsComponentSemanticRelationIndexTypes[GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_SEMANTIC_RELATION_INDEX_TYPE_UNKNOWN];
			}
			string semanticRelationReturnEntity = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_VALUE_false;
			string semanticRelationReturnFunctionName = "";
			string semanticRelationReturnFunctionNameIndexType = GIAtxtRelTranslatorRulesGroupsComponentSemanticRelationIndexTypes[GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_SEMANTIC_RELATION_INDEX_TYPE_UNKNOWN];
			int semanticRelationReturnFunctionNameIndexTypeInt = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_SEMANTIC_RELATION_INDEX_TYPE_UNKNOWN;
			string semanticRelationRecord = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_VALUE_false;
			string semanticRelationConnect = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_VALUE_false;
			string optional = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_VALUE_false;
			
			#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_COMPONENT_QUERY
			string queryComparisonVariable = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_VALUE_false;
			string isAuxiliaryQuery = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_VALUE_false;
			string isWhichOrEquivalentWhatQuery = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_VALUE_false;
			#endif
			#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_ALIASES
			string isNameQuery = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_VALUE_false;
			string isName = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_VALUE_false;
			#endif
			#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_NUMBER_OF
			string isNumberOf = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_VALUE_false;
			#endif
			#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_COMPONENT_WORD_NOUN_VERB_VARIANT
			string wordVerbVariantType = GIApreprocessorMultiwordReductionVerbDatabaseTagBaseTenseFormArray[GIA_PREPROCESSOR_WORD_VERB_DATABASE_TAG_BASE_TENSE_FORM_UNKNOWN];
			int wordVerbVariantTypeInt = GIA_PREPROCESSOR_WORD_VERB_DATABASE_TAG_BASE_TENSE_FORM_UNKNOWN;
			string wordNounVariantType = GIApreprocessorMultiwordReductionNounDatabaseTagBaseTenseFormArray[GIA_PREPROCESSOR_WORD_NOUN_DATABASE_TAG_BASE_TENSE_FORM_UNKNOWN];
			int wordNounVariantTypeInt = GIA_PREPROCESSOR_WORD_NOUN_DATABASE_TAG_BASE_TENSE_FORM_UNKNOWN;
			#endif
			#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_NUMBER_EXPLETIVES
			string isExpletive = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_VALUE_false;
			#endif

			#ifdef GIA_TXT_REL_TRANSLATOR_HYBRID
			int referenceSetTypeHybridInt = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_REFERENCE_SET_TYPE_HYBRID_UNKNOWN;
			if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_referenceSetTypeHybrid, &referenceSetTypeHybrid))
			{
				cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_referenceSetTypeHybrid, &referenceSetTypeHybrid)" << endl;
				exit(EXIT_ERROR);
			}
			if(!SHAREDvars.textInTextArray(referenceSetTypeHybrid, GIAtxtRelTranslatorRulesGroupsComponentReferenceSetTypeHybridTypes, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_REFERENCE_SET_TYPE_HYBRID_NUMBER_OF_TYPES, &referenceSetTypeHybridInt))
			{
				//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: referenceSetTypeHybrid unknown; componentType = " << referenceSetTypeHybrid << endl;
			}			
			#endif
			
			if(XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_componentType, &componentType))
			{
				if(!SHAREDvars.textInTextArray(componentType, GIAtxtRelTranslatorRulesGroupsComponentTypes, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_NUMBER_OF_TYPES, &componentTypeInt))
				{
					cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: componentType unknown; componentType = " << componentType << endl;
					exit(EXIT_ERROR);
				}
				if(componentTypeInt == GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_GROUP)
				{
					if(XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_groupTypeNameRef, &groupTypeRefName))
					{

					}
					else 
					{
						cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: (componentTypeInt == GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_GROUP) && groupTypeName not specified" << endl;
						exit(EXIT_ERROR);
					}
					if(XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_groupNameRef, &groupRefName))
					{

					}
				}
				else if(componentTypeInt == GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_STRING)
				{
					if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_stringType, &stringType))
					{
						cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_stringType, &groupRefName)" << endl;
						exit(EXIT_ERROR);
					}
					if(!SHAREDvars.textInTextArray(stringType, GIAtxtRelTranslatorRulesGroupsComponentStringTypes, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_STRINGTYPE_NUMBER_OF_TYPES, &stringTypeInt))
					{
						cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: stringType unknown; stringType = " << stringType << endl;
						cout << "currentTagInTxtRelTranslatorGroupTag->lineCount = " << currentTagInTxtRelTranslatorGroupTag->lineCount << endl;
						exit(EXIT_ERROR);
					}
					if(stringTypeInt == GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_STRINGTYPE_LRPEXTERNALWORDLISTS)
					{
						if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_wordPOStype, &wordPOStype))
						{
							cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_wordPOStype, &groupRefName)" << endl;
							exit(EXIT_ERROR);
						}
					}
					else if(stringTypeInt == GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_STRINGTYPE_EXPLICIT)
					{
						if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_word, &word))
						{
							cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_word, &groupRefName)" << endl;
							exit(EXIT_ERROR);
						}	
					}
					else if(stringTypeInt == GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_STRINGTYPE_TOKENS)
					{
						if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_tokenLayer, &tokenLayer))
						{
							cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_tokenLayer, &groupRefName)" << endl;
							exit(EXIT_ERROR);
						}		
						if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_tokenClass, &tokenClass))
						{
							cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_tokenClass, &groupRefName)" << endl;
							exit(EXIT_ERROR);
						}
						if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_tokenType, &tokenType))
						{
							//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_tokenType, &groupRefName)" << endl;
						}
					}
					else
					{
						cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: stringType unknown; stringType = " << stringType << ", stringTypeInt = " << stringTypeInt << endl;
						exit(EXIT_ERROR);	
					}
				}
				else
				{
					cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: componentType unknown, componentTypeInt = " << componentTypeInt << endl;
					exit(EXIT_ERROR);	
				}
			}
			else
			{
				cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_componentType, &componentType)" << endl;
				cout << "currentTagInTxtRelTranslatorGroupTag->lineCount = " << currentTagInTxtRelTranslatorGroupTag->lineCount << endl;
				exit(EXIT_ERROR);			
			}

			
			#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_COMPONENT_MISSING
			if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_missing, &missing))
			{
				cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_missing, &groupRefName)" << endl;
				exit(EXIT_ERROR);
			}
			#endif
			#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_ADD_EXPLICIT_WORD_REFERENCES_AS_INDEPENDENT_POS_PERMUTATIONS_EFFICIENT
			if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_addToExplicitWordTempPOS, &addToExplicitWordTempPOS))
			{
				//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_addToExplicitWordTempPOS, &groupRefName)" << endl;
			}
			#endif
			
			if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_semanticRelationIndexType, &(semanticRelationIndexType[0])))
			{
				//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_semanticRelationIndexType, &(semanticRelationIndexType[0]))" << endl;
			}
			if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_semanticRelationIndexType2, &(semanticRelationIndexType[1])))
			{
				//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_semanticRelationIndexType2, &(semanticRelationIndexType[1]))" << endl;
			}
			for(int i=0; i<GIA_TXT_REL_TRANSLATOR_MAX_NUMBER_OF_SEMANTIC_FUNCTIONS_EXECUTED_PER_GROUP; i++)
			{
				if(!SHAREDvars.textInTextArray(semanticRelationIndexType[i], GIAtxtRelTranslatorRulesGroupsComponentSemanticRelationIndexTypes, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_SEMANTIC_RELATION_INDEX_NUMBER_OF_TYPES, &(semanticRelationIndexTypeInt[i])))
				{
					cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: semanticRelationIndexType unknown; semanticRelationIndexType[i] = " << semanticRelationIndexType[i] << endl;
					exit(EXIT_ERROR);
				}
			}	
			if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_semanticRelationReturnEntity, &semanticRelationReturnEntity))
			{
				//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_semanticRelationReturnEntity, &semanticRelationReturnEntity)" << endl;
			}
			if(XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_semanticRelationReturnFunctionName, &semanticRelationReturnFunctionName))
			{
				if(XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_semanticRelationReturnFunctionNameIndexType, &semanticRelationReturnFunctionNameIndexType))
				{
					if(!SHAREDvars.textInTextArray(semanticRelationReturnFunctionNameIndexType, GIAtxtRelTranslatorRulesGroupsComponentSemanticRelationIndexTypes, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_SEMANTIC_RELATION_INDEX_NUMBER_OF_TYPES, &semanticRelationReturnFunctionNameIndexTypeInt))
					{
						cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: semanticRelationReturnFunctionNameIndexType unknown; semanticRelationReturnFunctionNameIndexType = " << semanticRelationReturnFunctionNameIndexType << endl;
						exit(EXIT_ERROR);
					}
				}
				else
				{
					cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_semanticRelationReturnFunctionNameIndexType, &semanticRelationReturnFunctionNameIndexType)" << endl;
				}
			}
			else
			{
				//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_semanticRelationReturnFunctionName, &semanticRelationReturnFunctionName)" << endl;
			}

			if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_semanticRelationRecord, &semanticRelationRecord))
			{
				//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_semanticRelationRecord, &semanticRelationRecord)" << endl;
			}
			if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_semanticRelationConnect, &semanticRelationConnect))
			{
				//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_semanticRelationConnect, &semanticRelationConnect)" << endl;
			}
			if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_optional, &optional))
			{
				//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} warning: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_optional, &optional)" << endl;
			}
			
			#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_COMPONENT_QUERY
			if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_queryComparisonVariable, &queryComparisonVariable))
			{
				//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_queryComparisonVariable, &queryComparisonVariable)" << endl;
			}
			if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_isAuxiliaryQuery, &isAuxiliaryQuery))
			{
				//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_isAuxiliaryQuery, &isAuxiliaryQuery)" << endl;
			}
			if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_isWhichOrEquivalentWhatQuery, &isWhichOrEquivalentWhatQuery))
			{
				//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_isWhichOrEquivalentWhatQuery, &isWhichOrEquivalentWhatQuery)" << endl;
			}
			#endif	
			#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_ALIASES
			if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_isNameQuery, &isNameQuery))
			{
				//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_isNameQuery, &isNameQuery)" << endl;
			}
			if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_isName, &isName))
			{
				//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_isName, &isName)" << endl;
			}
			#endif
			#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_NUMBER_OF
			if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_isNumberOf, &isNumberOf))
			{
				//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_isNumberOf, &isNumberOf)" << endl;
			}
			#endif
			#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_COMPONENT_WORD_NOUN_VERB_VARIANT
			if(XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_wordVerbVariantType, &wordVerbVariantType))
			{
				if(!SHAREDvars.textInTextArray(wordVerbVariantType, GIApreprocessorMultiwordReductionVerbDatabaseTagBaseTenseFormArray, GIA_PREPROCESSOR_WORD_VERB_DATABASE_TAG_BASE_TENSE_FORM_NUMBER_OF_TYPES, &wordVerbVariantTypeInt))
				{
					cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: semanticRelationReturnFunctionNameIndexType unknown; wordVerbVariantType = " << wordVerbVariantType << endl;
					exit(EXIT_ERROR);
				}
			}
			if(XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_wordNounVariantType, &wordNounVariantType))
			{
				if(!SHAREDvars.textInTextArray(wordNounVariantType, GIApreprocessorMultiwordReductionNounDatabaseTagBaseTenseFormArray, GIA_PREPROCESSOR_WORD_NOUN_DATABASE_TAG_BASE_TENSE_FORM_NUMBER_OF_TYPES, &wordNounVariantTypeInt))
				{
					cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: semanticRelationReturnFunctionNameIndexType unknown; wordNounVariantType = " << wordNounVariantType << endl;
					exit(EXIT_ERROR);
				}		
			}						
			#endif			
			#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_NUMBER_EXPLETIVES
			if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_isExpletive, &isExpletive))
			{
				//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_isExpletive, &isExpletive)" << endl;
			}
			#endif
			
			GIAtxtRelTranslatorRulesComponentNeuralNetwork* component = new GIAtxtRelTranslatorRulesComponentNeuralNetwork();
			component->componentIndex = componentIndex;
			#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK
			component->ownerGroup = groupOwner;	//enables reverse lookup for ANN
			if(parseSubcomponent)
			{
				component->isSubcomponent = true;
				component->ownerComponent = subComponentOwner;
			}
			#endif
			#ifdef GIA_TXT_REL_TRANSLATOR_HYBRID
			component->referenceSetTypeHybrid = referenceSetTypeHybridInt;
			#endif
			component->componentType = componentTypeInt;
			component->groupTypeRefName = groupTypeRefName;
			component->groupRefName = groupRefName;
			component->stringType = stringTypeInt;
			component->word = word;
			component->wordPOStype = wordPOStype;
			component->tokenLayer = tokenLayer;
			component->tokenClass = tokenClass;
			component->tokenType = tokenType;
			#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_COMPONENT_MISSING
			component->missing = SHAREDvars.convertStringToBool(missing);
			#endif
			#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_ADD_EXPLICIT_WORD_REFERENCES_AS_INDEPENDENT_POS_PERMUTATIONS_EFFICIENT
			component->stringTypeExplicitAddToExplicitWordTempPOS = SHAREDvars.convertStringToBool(addToExplicitWordTempPOS);
			#endif
			component->semanticRelationIndexType = semanticRelationIndexTypeInt;
			component->semanticRelationReturnEntity = SHAREDvars.convertStringToBool(semanticRelationReturnEntity);
			component->semanticRelationReturnFunctionName = semanticRelationReturnFunctionName;
			component->semanticRelationReturnFunctionNameIndexType = semanticRelationReturnFunctionNameIndexTypeInt;
			component->semanticRelationRecord = SHAREDvars.convertStringToBool(semanticRelationRecord);
			component->semanticRelationConnect = SHAREDvars.convertStringToBool(semanticRelationConnect);
			component->optional = SHAREDvars.convertStringToBool(optional);
			#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_COMPONENT_QUERY
			component->queryComparisonVariable = SHAREDvars.convertStringToBool(queryComparisonVariable);
			component->isAuxiliaryQuery = SHAREDvars.convertStringToBool(isAuxiliaryQuery);
			component->isWhichOrEquivalentWhatQuery = SHAREDvars.convertStringToBool(isWhichOrEquivalentWhatQuery);
			#endif
			#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_ALIASES
			component->isNameQuery = SHAREDvars.convertStringToBool(isNameQuery);
			component->isName = SHAREDvars.convertStringToBool(isName);
			#endif
			#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_NUMBER_OF
			component->isNumberOf = SHAREDvars.convertStringToBool(isNumberOf);
			#endif
			#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_COMPONENT_WORD_NOUN_VERB_VARIANT
			component->wordVerbVariantType = wordVerbVariantTypeInt;
			component->wordNounVariantType = wordNounVariantTypeInt;
			//cout << "wordNounVariantTypeInt = " << wordNounVariantTypeInt << endl;
			#endif				
			#ifdef GIA_TXT_REL_TRANSLATOR_RULES_CODE_NUMBER_EXPLETIVES
			component->isExpletive = SHAREDvars.convertStringToBool(isExpletive);
			#endif
			
			componentsList->push_back(component);
			
			componentIndex++;
			
			//XMLparserTag* firstTagInTxtRelTranslatorComponentTag = XMLparserClass.parseTagDownALevel(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUP_TAG_component, &result);
		}
		else if(currentTagInTxtRelTranslatorGroupTag->name == GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUP_TAG_or)
		{
			if(parseSubcomponent)
			{
				cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error:(currentTagInTxtRelTranslatorGroupTag->name == GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUP_TAG_or) && parseSubcomponent" << endl;
				exit(EXIT_ERROR);
			}
			
			GIAtxtRelTranslatorRulesComponentNeuralNetwork* component = new GIAtxtRelTranslatorRulesComponentNeuralNetwork();
			component->componentIndex = componentIndex;
			#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK
			component->ownerGroup = groupOwner;	//enables reverse lookup for ANN
			#endif
			component->componentType = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_OR;
			componentsList->push_back(component);

			XMLparserTag* firstTagInTxtRelTranslatorOrTag = XMLparserClass.parseTagDownALevel(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUP_TAG_or, &result);

			if(!parseComponents(firstTagInTxtRelTranslatorOrTag, groupOwner, &(component->subComponents), true, component))
			{
				cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !parseComponents(firstTagInTxtRelTranslatorOrTag, &(component->components))" << endl;
				exit(EXIT_ERROR);			
			}
			
			componentIndex++;
		}
		else if(!parseSubcomponent && currentTagInTxtRelTranslatorGroupTag->name == GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUP_TAG_repeat)
		{	
			if(parseSubcomponent)
			{
				cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error:(currentTagInTxtRelTranslatorGroupTag->name == GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUP_TAG_repeat) && parseSubcomponent" << endl;
				exit(EXIT_ERROR);
			}
					
			string optional = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_VALUE_false;
			if(!XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_optional, &optional))
			{
				//cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !XMLparserClass.getAttribute(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_ATTRIBUTE_optional, &optional)" << endl;
			}
			
			GIAtxtRelTranslatorRulesComponentNeuralNetwork* component = new GIAtxtRelTranslatorRulesComponentNeuralNetwork();
			component->componentIndex = componentIndex;
			#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK
			component->ownerGroup = groupOwner;	//enables reverse lookup for ANN
			#endif
			component->componentType = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_REPEAT;
			component->optional = SHAREDvars.convertStringToBool(optional);
			componentsList->push_back(component);

			XMLparserTag* firstTagInTxtRelTranslatorRepeatTag = XMLparserClass.parseTagDownALevel(currentTagInTxtRelTranslatorGroupTag, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUP_TAG_repeat, &result);

			if(!parseComponents(firstTagInTxtRelTranslatorRepeatTag, groupOwner, &(component->subComponents), true, component))
			{
				cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !parseComponents(firstTagInTxtRelTranslatorRepeatTag, &(component->components))" << endl;
				exit(EXIT_ERROR);			
			}
			
			componentIndex++;
		}
		else
		{
			cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: !(currentTagInTxtRelTranslatorGroupTag->name == GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_GROUP_TAG_component); currentTagInTxtRelTranslatorGroupTag->name = " << currentTagInTxtRelTranslatorGroupTag->name << endl;
			exit(EXIT_ERROR);					
		}

		currentTagInTxtRelTranslatorGroupTag = currentTagInTxtRelTranslatorGroupTag->nextTag;
	}
	
	return result;
}


bool GIAtxtRelTranslatorRulesClass::connectGroupsReferences(vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes)
{
	bool result = true;
	for(int i=0; i<GIAtxtRelTranslatorRulesGroupTypes->size(); i++)
	{
		GIAtxtRelTranslatorRulesGroupType* groupType = GIAtxtRelTranslatorRulesGroupTypes->at(i);
		for(int j=0; j<(groupType->groups).size(); j++)
		{
			GIAtxtRelTranslatorRulesGroupNeuralNetwork* group = (groupType->groups)[j];

			#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_ANN
			group->initiateANNneuron(group->groupTypeName + ":" + group->groupName);
			#endif
									
			#ifdef GIA_DEBUG_TXT_REL_TRANSLATOR_NEURAL_NETWORK_PROPAGATE_EXTRA8
			cout << "GIAtxtRelTranslatorRulesClass::connectGroupsReferences{}: group->groupName = " << group->groupName << endl;
			#endif
			//cout << "GIAtxtRelTranslatorRulesClass::connectGroupsReferences{}: group->groupName = " << group->groupName << endl;
			if(!connectComponentsReferences(GIAtxtRelTranslatorRulesGroupTypes, &(group->components), false))
			{
				result = false;
			}
		}
	}
	return result;
}
bool GIAtxtRelTranslatorRulesClass::connectComponentsReferences(vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes, vector<GIAtxtRelTranslatorRulesComponentNeuralNetwork*>* components, bool subcomponents)
{
	bool result = true;
	for(int j=0; j<components->size(); j++)
	{
		GIAtxtRelTranslatorRulesComponentNeuralNetwork* component = (*components)[j];
		if(component->componentType == GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_GROUP)
		{
			if(component->groupTypeRefName != "")
			{
				if(component->groupRefName != "")
				{	
					#ifdef GIA_DEBUG_TXT_REL_TRANSLATOR_NEURAL_NETWORK_PROPAGATE_EXTRA8
					cout << "\tGIAtxtRelTranslatorRulesClass::connectComponentsReferences{}: component->groupTypeRefName = " << component->groupTypeRefName << ", component->groupRefName = " << component->groupRefName <<endl;
					#endif
					if(!findGroup(GIAtxtRelTranslatorRulesGroupTypes, component->groupTypeRefName, component->groupRefName, &(component->groupTypeRef), &(component->groupRef)))
					{
						result = false;
						cerr << "GIAtxtRelTranslatorRulesClass::connectComponentsReferences{} error: !findGroup(), component->groupTypeRefName = " << component->groupTypeRefName << ", component->groupRefName = " << component->groupRefName <<endl;
						exit(EXIT_ERROR);
					}
				}
				else
				{
					if(!findGroupType(GIAtxtRelTranslatorRulesGroupTypes, component->groupTypeRefName, &(component->groupTypeRef)))
					{
						result = false;
						cerr << "GIAtxtRelTranslatorRulesClass::connectComponentsReferences{} error: !findGroupType(), component->groupTypeRefName = " << component->groupTypeRefName << endl;
						exit(EXIT_ERROR);
					}
					//cout << "\tcomponent->groupTypeRef->groupTypeName = " << component->groupTypeRef->groupTypeName << endl;					
				}
			}
		}
		else if((component->componentType == GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_OR) || (component->componentType == GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_REPEAT))
		{
			if(subcomponents)
			{
				result = false;
				cerr << "GIAtxtRelTranslatorRulesClass::connectComponentsReferences{} error: (component->componentType == GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_OR/REPEAT) && subcomponents" << endl;
				exit(EXIT_ERROR);	
			}
			if(!connectComponentsReferences(GIAtxtRelTranslatorRulesGroupTypes, &(component->subComponents), true))
			{
				result = false;
				cerr << "GIAtxtRelTranslatorRulesClass::connectComponentsReferences{} error: !connectComponentsReferences()" << endl;
				exit(EXIT_ERROR);			
			}
		}
	}
	return result;
}
bool GIAtxtRelTranslatorRulesClass::findGroupType(vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes, const string groupTypeName, GIAtxtRelTranslatorRulesGroupType** groupTypeFound)
{
	bool result = false;
	for(int i=0; i<GIAtxtRelTranslatorRulesGroupTypes->size(); i++)
	{
		GIAtxtRelTranslatorRulesGroupType* groupType = GIAtxtRelTranslatorRulesGroupTypes->at(i);
		//cout << "groupType->groupTypeName = " << groupType->groupTypeName << endl;
		if(groupType->groupTypeName == groupTypeName)
		{
			*groupTypeFound = groupType;
			result = true;
		}
	}
	return result;
}
bool GIAtxtRelTranslatorRulesClass::findGroup(vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes, const string groupTypeName, const string groupName, GIAtxtRelTranslatorRulesGroupType** groupTypeFound, GIAtxtRelTranslatorRulesGroupNeuralNetwork** groupFound)
{
	bool result = false;
	for(int i=0; i<GIAtxtRelTranslatorRulesGroupTypes->size(); i++)
	{
		GIAtxtRelTranslatorRulesGroupType* groupType = GIAtxtRelTranslatorRulesGroupTypes->at(i);
		if(groupType->groupTypeName == groupTypeName)
		{
			*groupTypeFound = groupType;
			for(int j=0; j<groupType->groups.size(); j++)
			{
				GIAtxtRelTranslatorRulesGroupNeuralNetwork* group = (groupType->groups)[j];
				if(group->groupName == groupName)
				{
					*groupFound = group;
					result = true;
				}
			}
		}
	}
	return result;
}

bool GIAtxtRelTranslatorRulesClass::extractGIAtxtRelTranslatorRulesTokens(vector<XMLparserTag*>* GIAtxtRelTranslatorRulesTokenLayers)
{
	bool result = true;
	vector<string> logicReferenceInstanceList;

	XMLparserTag* firstTagInRulesTag = XMLparserClass.parseTagDownALevel(GIAtxtRelTranslatorFirstTagInXMLfile, RULES_XML_TAG_rules, &result);
	if(result)
	{
		XMLparserTag* currentTag = firstTagInRulesTag;
		bool foundTxtRelTranslatorTag = false;
		XMLparserTag* firstTagInTxtRelTranslatorTag = NULL;
		while((currentTag->nextTag != NULL) && !foundTxtRelTranslatorTag)
		{
			if(currentTag->name == GIA_TXT_REL_TRANSLATOR_RULES_TAG_txtRelTranslator)
			{
				foundTxtRelTranslatorTag = true;
				firstTagInTxtRelTranslatorTag = XMLparserClass.parseTagDownALevel(currentTag, GIA_TXT_REL_TRANSLATOR_RULES_TAG_txtRelTranslator, &result);
			}
			currentTag = currentTag->nextTag;
		}
		if(foundTxtRelTranslatorTag)
		{
			XMLparserTag* currentTagInTxtRelTranslator = firstTagInTxtRelTranslatorTag;
			
			bool foundTxtRelTranslatorTokensTag = false;
			XMLparserTag* firstTagInTxtRelTranslatorTokensTag = NULL;
			while((currentTagInTxtRelTranslator->nextTag != NULL) && !foundTxtRelTranslatorTokensTag)
			{
				if(currentTagInTxtRelTranslator->name == GIA_TXT_REL_TRANSLATOR_RULES_TAG_tokens)
				{
					foundTxtRelTranslatorTokensTag = true;
					firstTagInTxtRelTranslatorTokensTag = XMLparserClass.parseTagDownALevel(currentTagInTxtRelTranslator, GIA_TXT_REL_TRANSLATOR_RULES_TAG_tokens, &result);
				}
				currentTagInTxtRelTranslator = currentTagInTxtRelTranslator->nextTag;
			}
			
			if(foundTxtRelTranslatorTokensTag)
			{
				XMLparserTag* currentTagInTokens = firstTagInTxtRelTranslatorTokensTag;
				bool foundTxtRelTranslatorLogicReferenceTag = false;
				XMLparserTag* firstTagInTxtRelTranslatorLogicReferenceTag = NULL;
				while((currentTagInTokens->nextTag != NULL) && !foundTxtRelTranslatorLogicReferenceTag)
				{
					if(currentTagInTokens->name == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_layer)
					{
						GIAtxtRelTranslatorRulesTokenLayers->push_back(currentTagInTokens);
						
						//error checking only:
						if(currentTagInTokens->firstAttribute->name == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_ATTRIBUTE_name)
						{
							string layerName = currentTagInTokens->firstAttribute->value;
							if(layerName == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_LOGIC_REFERENCE_LAYER_NAME)
							{
								//cout << "DEBUG: (layerName == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_layer_logicReference)" << endl;
								foundTxtRelTranslatorLogicReferenceTag = true;	//only record the first 3 <layer> tags
								firstTagInTxtRelTranslatorLogicReferenceTag = XMLparserClass.parseTagDownALevel(currentTagInTokens, GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_layer, &result);
								//*firstTxtRelTranslatorRulesTokenFirstLogicReferenceTag = firstTagInTxtRelTranslatorLogicReferenceTag;
							}
						}
					}
					currentTagInTokens = currentTagInTokens->nextTag;
				}

				//error checking only:
				if(foundTxtRelTranslatorLogicReferenceTag)
				{
					XMLparserTag* currentTagInTxtRelTranslatorLogicReference = firstTagInTxtRelTranslatorLogicReferenceTag;
					while(currentTagInTxtRelTranslatorLogicReference->nextTag != NULL)
					{
						if(currentTagInTxtRelTranslatorLogicReference->name == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_class)
						{	
							bool foundClass = true;
							int logicReferenceClass = GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_LOGIC_REFERENCE_CLASS_UNDEFINED;
							if(currentTagInTxtRelTranslatorLogicReference->firstAttribute->name == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_ATTRIBUTE_name)
							{
								string className = currentTagInTxtRelTranslatorLogicReference->firstAttribute->value;
								if(className == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_LOGIC_REFERENCE_CLASS_undefined)
								{
									logicReferenceClass = GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_LOGIC_REFERENCE_CLASS_UNDEFINED;
								}
								else if(className == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_LOGIC_REFERENCE_CLASS_conjunction)
								{
									logicReferenceClass = GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_LOGIC_REFERENCE_CLASS_CONJUNCTION;
								}
								else if(className == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_LOGIC_REFERENCE_CLASS_verb)
								{
									logicReferenceClass = GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_LOGIC_REFERENCE_CLASS_VERB;
								}
								else if(className == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_LOGIC_REFERENCE_CLASS_preposition)
								{
									logicReferenceClass = GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_LOGIC_REFERENCE_CLASS_PREPOSITION;
								}
								else
								{
									cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: illegal class name = currentTagInTxtRelTranslatorLogicReference->firstAttribute->value = " << currentTagInTxtRelTranslatorLogicReference->firstAttribute->value << endl;
									exit(EXIT_ERROR);
								}
							}
							else
							{
								cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: illegal class name = currentTagInTxtRelTranslatorLogicReference->firstAttribute->name = " << currentTagInTxtRelTranslatorLogicReference->firstAttribute->name << ", expected: GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_ATTRIBUTE_name" << endl;
								exit(EXIT_ERROR);
							}

							if(foundClass)
							{
								XMLparserTag* firstTagInClassTag = XMLparserClass.parseTagDownALevel(currentTagInTxtRelTranslatorLogicReference, GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_class, &result);	
								XMLparserTag* currentTagInClass = firstTagInClassTag;
								while(currentTagInClass->nextTag != NULL)
								{
									if(currentTagInClass->name == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_type)
									{

										if(currentTagInClass->firstAttribute->name == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_ATTRIBUTE_name)
										{

										}
										else
										{
											cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: illegal type name = currentTagInClass->firstAttribute->name = " << currentTagInClass->firstAttribute->name << ", expected: GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_ATTRIBUTE_name" << endl;
											exit(EXIT_ERROR);
										}

										XMLparserTag* firstTagInTypeTag = XMLparserClass.parseTagDownALevel(currentTagInClass, GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_type, &result);
										XMLparserTag* currentTagInType = firstTagInTypeTag;
										while(currentTagInType->nextTag != NULL)
										{
											if(currentTagInType->name == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_instance)
											{

												if(currentTagInType->firstAttribute->name == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_ATTRIBUTE_name)
												{
													string instanceName = currentTagInType->firstAttribute->value;
													//logicReferenceInstanceList->push_back(instanceName);
												}
												else
												{
													cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: illegal instance name = currentTagInType->firstAttribute->name = " << currentTagInType->firstAttribute->name << ", expected: GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_ATTRIBUTE_name" << endl;
													exit(EXIT_ERROR);
												}
											}
											else
											{
												cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: illegal currentTagInType->name = " << currentTagInType->name << ", expected: GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_instance" << endl;
												exit(EXIT_ERROR);
											}
											currentTagInType = currentTagInType->nextTag;
										}
									}
									else
									{
										cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: illegal currentTagInClass->name = " << currentTagInClass->name << ", expected: GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_type" << endl;
										exit(EXIT_ERROR);
									}
									currentTagInClass = currentTagInClass->nextTag;
								}
							}
						}
						else
						{
							cerr << "GIAtxtRelTranslatorRules::extractGIAtxtRelTranslatorRulesGroups{} error: illegal currentTagInTxtRelTranslatorLogicReference->name = " << currentTagInTxtRelTranslatorLogicReference->name << ", expected: GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_class" << endl;
							exit(EXIT_ERROR);
						}
						currentTagInTxtRelTranslatorLogicReference = currentTagInTxtRelTranslatorLogicReference->nextTag;
					}
				}
			}
		}
	}
	
	GIAtxtRelTranslatorRulesTokenLayersGlobal = GIAtxtRelTranslatorRulesTokenLayers;

	return result;
}

bool GIAtxtRelTranslatorRulesClass::isClassTagWrapper(string word, string layerNameToFind, string classNameToFind, string classTypeNameToFind, vector<XMLparserTag*>* GIAtxtRelTranslatorRulesTokenLayers)
{
	if(classTypeNameToFind == "")
	{
		string classTypeNameFound = "";
		return isClassTag(word, layerNameToFind, classNameToFind, &classTypeNameFound, GIAtxtRelTranslatorRulesTokenLayers);
	}
	else
	{
		return isClassTag(word, layerNameToFind, classNameToFind, classTypeNameToFind, GIAtxtRelTranslatorRulesTokenLayers);	
	}
}

bool GIAtxtRelTranslatorRulesClass::isClassTag(string word, string layerNameToFind, string classNameToFind, string* classTypeNameFound, vector<XMLparserTag*>* GIAtxtRelTranslatorRulesTokenLayers)
{
	bool classTagFound = false;
	bool result = false;

	for(int i=0; i<GIAtxtRelTranslatorRulesTokenLayers->size(); i++)
	{
		XMLparserTag* currentLayerTag = GIAtxtRelTranslatorRulesTokenLayers->at(i);
		string layerName;
		if(!XMLparserClass.getAttribute(currentLayerTag, GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_ATTRIBUTE_name, &layerName))
		{
			cerr << "GIAtxtRelTranslatorHybridClass::executeTxtRelTranslatorDepreciated{} error: (!XMLparserClass.getAttribute(currentLayerTag, GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_ATTRIBUTE_name, &layerName)" << endl;
			exit(EXIT_ERROR);
		}
		if(layerName == layerNameToFind)
		{
			XMLparserTag* firstXMLtagInLayer = XMLparserClass.parseTagDownALevel(currentLayerTag, GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_layer, &result);
			XMLparserTag* firstLogicReferenceClassTag = firstXMLtagInLayer;
			
			XMLparserTag* currentTagInLogicReferencePreprocessor = firstLogicReferenceClassTag;
			string wordLowerCase = SHAREDvars.convertStringToLowerCase(&word);

			while(currentTagInLogicReferencePreprocessor->nextTag != NULL)
			{
				if(currentTagInLogicReferencePreprocessor->name == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_class)
				{	
					bool sameClass = false;
					//vector<string>* logicReferenceClassVector = NULL;
					if(currentTagInLogicReferencePreprocessor->firstAttribute->name == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_ATTRIBUTE_name)
					{
						string className = currentTagInLogicReferencePreprocessor->firstAttribute->value;
						if(className == classNameToFind)
						{
							sameClass = true;	
						}
					}

					if(sameClass)
					{				
						XMLparserTag* firstTagInClass = XMLparserClass.parseTagDownALevel(currentTagInLogicReferencePreprocessor, GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_class, &result);
						XMLparserTag* currentTagInClass = firstTagInClass;
						#ifdef GIA_DEBUG_PREPROCESSOR_SENTENCE_LOGIC_REFERENCE
						//cout << "classNameToFind = " << classNameToFind << endl;
						#endif
						while(currentTagInClass->nextTag != NULL)
						{
							if(currentTagInClass->name == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_type)
							{
								#ifdef GIA_DEBUG_PREPROCESSOR_SENTENCE_LOGIC_REFERENCE
								//cout << "\tGIAtxtRelTranslatorRules::isClassTag{} debug: GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_type" << endl;
								#endif
								string classTypeName = "";
								if(currentTagInClass->firstAttribute->name == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_ATTRIBUTE_name)
								{
									classTypeName = currentTagInClass->firstAttribute->value;
								}


								XMLparserTag* firstTagInTypeTag = XMLparserClass.parseTagDownALevel(currentTagInClass, GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_type, &result);
								XMLparserTag* currentTagInType = firstTagInTypeTag;
								while(currentTagInType->nextTag != NULL)
								{
									if(currentTagInType->name == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_instance)
									{
										#ifdef GIA_DEBUG_PREPROCESSOR_SENTENCE_LOGIC_REFERENCE
										//cout << "\t\tGIAtxtRelTranslatorRules::isClassTag{} debug: GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_instance" << endl;
										#endif
										if(currentTagInType->firstAttribute->name == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_ATTRIBUTE_name)
										{
											string instanceName = currentTagInType->firstAttribute->value;

											if(instanceName == wordLowerCase)
											{
												classTagFound = true;
												*classTypeNameFound = classTypeName;
											}
										}
									}
									currentTagInType = currentTagInType->nextTag;
								}
							}

							currentTagInClass = currentTagInClass->nextTag;
						}
					}
				}

				currentTagInLogicReferencePreprocessor = currentTagInLogicReferencePreprocessor->nextTag;
			}
		}
	}

	return classTagFound;
}

bool GIAtxtRelTranslatorRulesClass::isClassTag(string word, string layerNameToFind, string classNameToFind, string classTypeNameToFind, vector<XMLparserTag*>* GIAtxtRelTranslatorRulesTokenLayers)
{
	bool classTagFound = false;
	bool result = false;
	
	string wordLowerCase = SHAREDvars.convertStringToLowerCase(&word);

	for(int i=0; i<GIAtxtRelTranslatorRulesTokenLayers->size(); i++)
	{
		XMLparserTag* currentLayerTag = GIAtxtRelTranslatorRulesTokenLayers->at(i);
		string layerName;
		if(!XMLparserClass.getAttribute(currentLayerTag, GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_ATTRIBUTE_name, &layerName))
		{
			cerr << "GIAtxtRelTranslatorHybridClass::executeTxtRelTranslatorDepreciated{} error: (!XMLparserClass.getAttribute(currentLayerTag, GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_ATTRIBUTE_name, &layerName)" << endl;
			exit(EXIT_ERROR);
		}
		if(layerName == layerNameToFind)
		{
			XMLparserTag* firstXMLtagInLayer = XMLparserClass.parseTagDownALevel(currentLayerTag, GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_layer, &result);
			XMLparserTag* currentXMLtagInLayer = firstXMLtagInLayer;
			
			while(currentXMLtagInLayer->nextTag != NULL)
			{
				if(currentXMLtagInLayer->name == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_class)
				{	
					bool sameClass = false;
					//vector<string>* logicReferenceClassVector = NULL;
					if(currentXMLtagInLayer->firstAttribute->name == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_ATTRIBUTE_name)
					{
						string className = currentXMLtagInLayer->firstAttribute->value;
						if(className == classNameToFind)
						{
							sameClass = true;	
						}
					}

					if(sameClass)
					{				
						XMLparserTag* firstTagInClass = XMLparserClass.parseTagDownALevel(currentXMLtagInLayer, GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_class, &result);
						XMLparserTag* currentTagInClass = firstTagInClass;
						#ifdef GIA_DEBUG_PREPROCESSOR_SENTENCE_LOGIC_REFERENCE
						//cout << "classNameToFind = " << classNameToFind << endl;
						#endif
						while(currentTagInClass->nextTag != NULL)
						{
							if(currentTagInClass->name == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_type)
							{
								#ifdef GIA_DEBUG_PREPROCESSOR_SENTENCE_LOGIC_REFERENCE
								//cout << "\tGIAtxtRelTranslatorRules::isClassTag{} debug: GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_type" << endl;
								#endif
								string classTypeName = "";
								bool sameType = false;
								if(currentTagInClass->firstAttribute->name == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_ATTRIBUTE_name)
								{
									classTypeName = currentTagInClass->firstAttribute->value;
									if(classTypeNameToFind != "")
									{
										if(classTypeName == classTypeNameToFind)
										{
											sameType = true;	
										}
									}
									else
									{
										sameType = true;
									}
								}

								if(sameType)
								{
									XMLparserTag* firstTagInTypeTag = XMLparserClass.parseTagDownALevel(currentTagInClass, GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_type, &result);
									XMLparserTag* currentTagInType = firstTagInTypeTag;
									while(currentTagInType->nextTag != NULL)
									{
										if(currentTagInType->name == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_instance)
										{
											#ifdef GIA_DEBUG_PREPROCESSOR_SENTENCE_LOGIC_REFERENCE
											//cout << "\t\tGIAtxtRelTranslatorRules::isClassTag{} debug: GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_TAG_instance" << endl;
											#endif
											if(currentTagInType->firstAttribute->name == GIA_TXT_REL_TRANSLATOR_RULES_TOKENS_ATTRIBUTE_name)
											{
												string instanceName = currentTagInType->firstAttribute->value;

												if(instanceName == wordLowerCase)
												{
													classTagFound = true;
												}
											}
										}
										currentTagInType = currentTagInType->nextTag;
									}
								}
							}

							currentTagInClass = currentTagInClass->nextTag;
						}
					}
				}

				currentXMLtagInLayer = currentXMLtagInLayer->nextTag;
			}
		}
	}
	
	return classTagFound;
}


#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_REMOVE_LAST_OPTIONAL_COMPONENTS
bool GIAtxtRelTranslatorRulesClass::removeLastOptionalComponents(vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes)
{
	bool result = true;
	
	for(int i=0; i<GIAtxtRelTranslatorRulesGroupTypes->size(); i++)
	{
		GIAtxtRelTranslatorRulesGroupType* groupType = GIAtxtRelTranslatorRulesGroupTypes->at(i);
		
		int groupTypeGroupsSizeOrig = (groupType->groups).size();
		for(int j=0; j<(groupType->groups).size(); j++)
		{
			GIAtxtRelTranslatorRulesGroupNeuralNetwork* group = (groupType->groups)[j];
			vector<GIAtxtRelTranslatorRulesComponentNeuralNetwork*>* components = &(group->components);
			
			GIAtxtRelTranslatorRulesGroupNeuralNetwork* optionalComponentsWrapperGroup = NULL;
			bool wrapperGroupAlreadyDefined = false;
			if(j >= groupTypeGroupsSizeOrig)
			{
				wrapperGroupAlreadyDefined = true;
				optionalComponentsWrapperGroup = group->optionalComponentsWrapperGroup;
				#ifdef GIA_DEBUG_TXT_REL_TRANSLATOR_NEURAL_NETWORK_PROPAGATE_EXTRA7
				cout << "passed test: (j >= groupTypeGroupsSizeOrig)" << endl;
				#endif
			}
							
			if(components->size() > 0)
			{
				#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_LIGHT_REVERSE
				GIAtxtRelTranslatorRulesComponentNeuralNetwork* lastComponent = (*components)[0];
				#else
				GIAtxtRelTranslatorRulesComponentNeuralNetwork* lastComponent = (*components)[components->size()-1];
				#endif
				if(components->size() == 1 && lastComponent->optional)
				{
					//group only contains one component and it is optional
					cerr << "GIAtxtRelTranslatorRulesClass::removeLastOptionalComponents{} warning: (components->size() == 1 && lastComponent->optional) - group only contains one component and it is optional" << endl;
				}
				if(lastComponent->optional)
				{

					#ifdef GIA_DEBUG_TXT_REL_TRANSLATOR_NEURAL_NETWORK_PROPAGATE_EXTRA7
					cout << "GIAtxtRelTranslatorRulesClass::removeLastOptionalComponents: remove last component from groupNew1" << endl;
					cout << "GIAtxtRelTranslatorRulesClass::removeLastOptionalComponents: set last component from groupNew1 to optional==false" << endl;
					#endif

					//create groupNew1
					GIAtxtRelTranslatorRulesGroupNeuralNetwork* groupNew1 = copyGroup(group);
					groupNew1->groupName = groupNew1->groupName + GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_REMOVE_LAST_OPTIONAL_COMPONENTS_ARTIFICIAL_GROUP_NAME_APPEND1;
					groupNew1->optionalComponentsWrapperGroup = group;
					//remove last component from groupNew1;
					vector<GIAtxtRelTranslatorRulesComponentNeuralNetwork*>* componentsNew1 = &(groupNew1->components);
					#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_LIGHT_REVERSE
					//componentsNew1.pop_front();
					componentsNew1->erase(componentsNew1->begin());
					#else
					componentsNew1->pop_back();
					#endif
					updateComponentsOwnerGroupAndIndexes(groupNew1, &(groupNew1->components));
					(groupType->groups).push_back(groupNew1);

					//create groupNew2
					GIAtxtRelTranslatorRulesGroupNeuralNetwork* groupNew2 = copyGroup(group);
					groupNew2->groupName = groupNew2->groupName + GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_REMOVE_LAST_OPTIONAL_COMPONENTS_ARTIFICIAL_GROUP_NAME_APPEND2;
					groupNew2->optionalComponentsWrapperGroup = group;
					//set last component to !optional;
					vector<GIAtxtRelTranslatorRulesComponentNeuralNetwork*>* componentsNew2 = &(groupNew2->components);
					#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_LIGHT_REVERSE
					GIAtxtRelTranslatorRulesComponentNeuralNetwork* lastComponentNew2 = (*componentsNew2)[0];
					#else
					GIAtxtRelTranslatorRulesComponentNeuralNetwork* lastComponentNew2 = (*componentsNew2)[components->size()-1];
					#endif
					lastComponentNew2->optional = false;
					updateComponentsOwnerGroupAndIndexes(groupNew2, &(groupNew2->components));
					(groupType->groups).push_back(groupNew2);

					GIAtxtRelTranslatorRulesComponentNeuralNetwork* artificialGroupOrComponent = NULL;
					if(wrapperGroupAlreadyDefined)
					{
						artificialGroupOrComponent = optionalComponentsWrapperGroup->components[0];
						
						//delete artifical group (reference) from groupTypes and artificialGroupOrComponent->components;
						(groupType->groups).erase((groupType->groups).begin() + j);
						j--;
						for(int q=0; q<artificialGroupOrComponent->subComponents.size(); q++)
						{	
							GIAtxtRelTranslatorRulesComponentNeuralNetwork* component = artificialGroupOrComponent->subComponents[q];
							if(component->groupRefName == group->groupName)
							{
								(artificialGroupOrComponent->subComponents).erase((artificialGroupOrComponent->subComponents).begin() + q);
								q--;
							}
						}
					}
					else
					{
						//turn group into a wrapper group with an or function pointing to both groups
						optionalComponentsWrapperGroup = group;
						artificialGroupOrComponent = new GIAtxtRelTranslatorRulesComponentNeuralNetwork();
						artificialGroupOrComponent->componentIndex = GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_COMPONENT_INDEX_FIRST;
						#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK
						artificialGroupOrComponent->ownerGroup = group;	//enables reverse lookup for ANN
						#endif
						artificialGroupOrComponent->componentType = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_OR;
						components->clear();
						components->push_back(artificialGroupOrComponent);
					}

					//add newly created artificial groups to wrapper group
					GIAtxtRelTranslatorRulesComponentNeuralNetwork* artificialGroupComponentNew1 = new GIAtxtRelTranslatorRulesComponentNeuralNetwork();
					artificialGroupComponentNew1->groupRefName = groupNew1->groupName;
					artificialGroupComponentNew1->groupTypeRefName = optionalComponentsWrapperGroup->groupTypeName;
					artificialGroupComponentNew1->componentType = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_GROUP;
					artificialGroupComponentNew1->componentIndex = artificialGroupOrComponent->subComponents.size();
					artificialGroupComponentNew1->ownerGroup = optionalComponentsWrapperGroup;
					artificialGroupComponentNew1->ownerComponent = artificialGroupOrComponent;
					artificialGroupComponentNew1->isSubcomponent = true;
					artificialGroupComponentNew1->semanticRelationReturnEntity = true;
					artificialGroupOrComponent->subComponents.push_back(artificialGroupComponentNew1);
					GIAtxtRelTranslatorRulesComponentNeuralNetwork* artificialGroupComponentNew2 = new GIAtxtRelTranslatorRulesComponentNeuralNetwork();
					artificialGroupComponentNew2->groupRefName = groupNew2->groupName;
					artificialGroupComponentNew2->groupTypeRefName = optionalComponentsWrapperGroup->groupTypeName;
					artificialGroupComponentNew2->componentType = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_GROUP;
					artificialGroupComponentNew2->componentIndex = artificialGroupOrComponent->subComponents.size();
					artificialGroupComponentNew2->ownerGroup = optionalComponentsWrapperGroup;
					artificialGroupComponentNew2->ownerComponent = artificialGroupOrComponent;
					artificialGroupComponentNew2->isSubcomponent = true;
					artificialGroupComponentNew2->semanticRelationReturnEntity = true;
					artificialGroupOrComponent->subComponents.push_back(artificialGroupComponentNew2);
					for(int c=GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_COMPONENT_INDEX_FIRST; c<artificialGroupOrComponent->subComponents.size(); c++)
					{
						GIAtxtRelTranslatorRulesComponentNeuralNetwork* subcomponent = artificialGroupOrComponent->subComponents[c];
						subcomponent->componentIndex = c;
					}
					
					#ifdef GIA_DEBUG_TXT_REL_TRANSLATOR_NEURAL_NETWORK_PROPAGATE_EXTRA8
					cout << "artificialGroupComponentNew1->groupRefName = " << artificialGroupComponentNew1->groupRefName << endl;
					cout << "artificialGroupComponentNew2->groupRefName = " << artificialGroupComponentNew2->groupRefName << endl;
					#endif
				}
			}
			else
			{
				cerr << "GIAtxtRelTranslatorRulesClass::removeLastOptionalComponents{} error: " << (components->size() == 0) << endl;
				exit(EXIT_ERROR);
			}
		}
	}
	
	#ifdef GIA_DEBUG_TXT_REL_TRANSLATOR_NEURAL_NETWORK_PROPAGATE_EXTRA7
	cout << "GIA_DEBUG_TXT_REL_TRANSLATOR_NEURAL_NETWORK_PROPAGATE_EXTRA7 exit" << endl;
	exit(EXIT_ERROR);
	#endif
	
	return result;
}	

#endif
	
GIAtxtRelTranslatorRulesGroupNeuralNetwork* GIAtxtRelTranslatorRulesClass::copyGroup(GIAtxtRelTranslatorRulesGroupNeuralNetwork* group)
{		
	GIAtxtRelTranslatorRulesGroupNeuralNetwork* newGroup = new GIAtxtRelTranslatorRulesGroupNeuralNetwork(*group);
	newGroup->components.clear();
	copyComponents(&(group->components), &(newGroup->components));

	return newGroup;
}
bool GIAtxtRelTranslatorRulesClass::copyComponents(vector<GIAtxtRelTranslatorRulesComponentNeuralNetwork*>* components, vector<GIAtxtRelTranslatorRulesComponentNeuralNetwork*>* componentsNew)
{	
	bool result = true;
	
	for(int i=0; i<components->size(); i++)
	{
		GIAtxtRelTranslatorRulesComponentNeuralNetwork* currentComponent = (*components)[i];
		GIAtxtRelTranslatorRulesComponentNeuralNetwork* newComponent = new GIAtxtRelTranslatorRulesComponentNeuralNetwork(*currentComponent);
		componentsNew->push_back(newComponent);
		if(GIAtxtRelTranslatorRulesComponentClassObject.componentHasSubcomponents(currentComponent))
		{
			newComponent->subComponents.clear();
			copyComponents(&(currentComponent->subComponents), &(newComponent->subComponents)); 
		}
	}
	
	return result;
}

GIAtxtRelTranslatorRulesGroupParseTree* GIAtxtRelTranslatorRulesClass::copyGroup(GIAtxtRelTranslatorRulesGroupParseTree* group)
{		
	GIAtxtRelTranslatorRulesGroupParseTree* newGroup = new GIAtxtRelTranslatorRulesGroupParseTree(*group);
	newGroup->components.clear();
	copyComponents(&(group->components), &(newGroup->components));

	return newGroup;
}
bool GIAtxtRelTranslatorRulesClass::copyComponents(vector<GIAtxtRelTranslatorRulesComponentParseTree*>* components, vector<GIAtxtRelTranslatorRulesComponentParseTree*>* componentsNew)
{	
	bool result = true;
	
	for(int i=0; i<components->size(); i++)
	{
		GIAtxtRelTranslatorRulesComponentParseTree* currentComponent = (*components)[i];
		GIAtxtRelTranslatorRulesComponentParseTree* newComponent = new GIAtxtRelTranslatorRulesComponentParseTree(*currentComponent);
		componentsNew->push_back(newComponent);
	}
	
	return result;
}

GIAtxtRelTranslatorRulesGroupActivationMemory* GIAtxtRelTranslatorRulesClass::copyGroup(GIAtxtRelTranslatorRulesGroupActivationMemory* group)
{		
	GIAtxtRelTranslatorRulesGroupActivationMemory* newGroup = new GIAtxtRelTranslatorRulesGroupActivationMemory(*group);
	newGroup->components.clear();
	copyComponents(&(group->components), &(newGroup->components));

	return newGroup;
}




#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_REMOVE_LAST_OPTIONAL_COMPONENTS
bool GIAtxtRelTranslatorRulesClass::updateComponentsOwnerGroupAndIndexes(GIAtxtRelTranslatorRulesGroupNeuralNetwork* group, vector<GIAtxtRelTranslatorRulesComponentNeuralNetwork*>* components)
{
	bool result = true;
	
	for(int c=GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_COMPONENT_INDEX_FIRST; c<components->size(); c++)
	{
		GIAtxtRelTranslatorRulesComponentNeuralNetwork* component = (*components)[c];
		component->componentIndex = c;
		component->ownerGroup = group;
		if(GIAtxtRelTranslatorRulesComponentClassObject.componentHasSubcomponents(component))
		{
			updateComponentsOwnerGroupAndIndexes(group, &(component->subComponents));
		}
	}
	
	return result;
}		
#endif			

#endif








