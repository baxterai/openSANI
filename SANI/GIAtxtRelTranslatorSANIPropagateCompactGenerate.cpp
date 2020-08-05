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
 * File Name: GIAtxtRelTranslatorSANIPropagateCompactGenerate.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2020 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 3k1a 05-March-2020
 * Requirements: 
 * Description: Textual Relation Translator SANI (Sequentially Activated Neuronal Input neural network) Propagate Compact - unsupervised training of sequence grammar parse network
 * /
 *******************************************************************************/


#include "GIAtxtRelTranslatorSANIPropagateCompactGenerate.hpp"
#include "SHAREDvars.hpp"


#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR

//static int newNeuronIndex;

#ifdef GIA_TXT_REL_TRANSLATOR_SANI_FREE_MEMORY
static vector<GIAtxtRelTranslatorRulesGroupParseTree*>* parseTreeGroupListPointer;
#endif


/*
bool GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::formTxtRelTranslatorNeuralNetworkSequenceGrammarInput(GIAtranslatorVariablesClass* translatorVariables)
{

}
*/


bool GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::executeTxtRelTranslatorNeuralNetwork(GIAtranslatorVariablesClass* translatorVariables, vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes, vector<GIApreprocessorPlainTextWord*>* sentenceContents, const bool createNewConnections)
{
	GIAtxtRelTranslatorRulesGroupParseTree* topLevelParseTreeGroup = NULL; 
	bool parseIsolatedSubreferenceSets = false;
	bool parserEnabled = false;
	int performance = 0;
	return executeTxtRelTranslatorNeuralNetwork(translatorVariables, GIAtxtRelTranslatorRulesGroupTypes, sentenceContents, &topLevelParseTreeGroup, parseIsolatedSubreferenceSets, parserEnabled, &performance, createNewConnections);
}

bool GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::executeTxtRelTranslatorNeuralNetwork(GIAtranslatorVariablesClass* translatorVariables, vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes, vector<GIApreprocessorPlainTextWord*>* sentenceContents, GIAtxtRelTranslatorRulesGroupParseTree** topLevelParseTreeGroup, const bool parseIsolatedSubreferenceSets, const bool parserEnabled, int* performance, const bool createNewConnections)
{
	bool result = false;
	
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_FREE_MEMORY
	parseTreeGroupListPointer = GIAtxtRelTranslatorSANIPropagateCompact.getParseTreeGroupList();
	#endif

	GIAtxtRelTranslatorSANIForwardPropogationSentenceData forwardPropogationSentenceData;
	forwardPropogationSentenceData.sentenceContents = sentenceContents;

	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG
	cout << "\n\n\n\n\nGIAtxtRelTranslatorSANIPropagateCompactGenerateClass::executeTxtRelTranslatorNeuralNetwork 1" << endl;
	#endif
	
	bool toplevelGroupActivationFound = GIAtxtRelTranslatorSANIPropagateCompact.executeTxtRelTranslatorNeuralNetworkPart1(translatorVariables, GIAtxtRelTranslatorRulesGroupTypes, &forwardPropogationSentenceData, topLevelParseTreeGroup, parseIsolatedSubreferenceSets, parserEnabled, performance);
	
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG
	cout << "GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::executeTxtRelTranslatorNeuralNetwork 2" << endl;
	#endif
	
	if(!toplevelGroupActivationFound)
	{
		if(createNewConnections)
		{
			findAndReconcileVariation(translatorVariables, GIAtxtRelTranslatorRulesGroupTypes, &forwardPropogationSentenceData);
		}
	}
	
	GIAtxtRelTranslatorSANIPropagateCompact.executeTxtRelTranslatorNeuralNetworkPart2(translatorVariables, GIAtxtRelTranslatorRulesGroupTypes, &forwardPropogationSentenceData, topLevelParseTreeGroup, parseIsolatedSubreferenceSets, parserEnabled, performance);
		
	return toplevelGroupActivationFound;
}


bool GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::findAndReconcileVariation(GIAtranslatorVariablesClass* translatorVariables, vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes, GIAtxtRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData)
{
	bool result = true;
	
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_TEST_VERIFICATION_AFTER_GENERATION
	if(translatorVariables->currentPreprocessorSentenceInList->sentenceIndexOriginal <= translatorVariables->maxNumberSentences/2)
	{
	#endif
		bool foundAndReconciledMissingOrDifferentIncrementalNeurons = findAndReconcileIncrementalVariation(translatorVariables, GIAtxtRelTranslatorRulesGroupTypes, forwardPropogationSentenceData);

	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_TEST_VERIFICATION_AFTER_GENERATION
	}
	#endif
	
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG
	cout << "\n\n\n\n\nGIAtxtRelTranslatorSANIPropagateCompactGenerateClass::executeTxtRelTranslatorNeuralNetwork 3" << endl;
	#endif
	
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_VERIFICATION
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_WORDCONNECTIVITY_VERIFICATION
	cout << "GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_VERIFICATION: performPropagationTest:" << endl;
	#endif
	if(!GIAtxtRelTranslatorSANIPropagateCompact.performPropagationTest(translatorVariables, GIAtxtRelTranslatorRulesGroupTypes, forwardPropogationSentenceData))
	{
		cerr << "GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::findAndReconcileVariation fail: !performPropagationTest verification" << endl;
		exit(EXIT_ERROR);
		result = false;
	}	
	#endif
	
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG
	cout << "GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::executeTxtRelTranslatorNeuralNetwork 4" << endl;
	#endif

	return result;
}

	



bool GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::findAndReconcileIncrementalVariation(GIAtranslatorVariablesClass* translatorVariables, vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes, GIAtxtRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData)
{
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_PRINT_GROUP_INDICES
	cout << "GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::findAndReconcileIncrementalVariation" << endl;
	#endif
		
	bool foundAndReconciledMissingOrDifferentIncrementalNeurons = false;
	
	
	//if GIA_TXT_REL_TRANSLATOR_SANI_PROPAGATE_ALL_POS_VALUES_SIMULTANEOUSLY, first layer contains firstPOS neuron for each wordIndex only
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_PROPAGATE_ALL_POS_VALUES_SIMULTANEOUSLY
	vector<vector<GIAtxtRelTranslatorRulesGroupNeuralNetwork*>*> firstLayer;
	for(int i=0; i<forwardPropogationSentenceData->sentenceContents.size(); i++)
	{
		firstLayer.push_back(new vector<GIAtxtRelTranslatorRulesGroupNeuralNetwork*>);
	}
	#else
	vector<GIAtxtRelTranslatorRulesGroupNeuralNetwork*> firstLayer;
	#endif
	forwardPropogationSentenceData->firstLayer = &firstLayer;
	GIAtxtRelTranslatorSANIPropagateCompact.defineFirstLayer(translatorVariables, forwardPropogationSentenceData);
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_COMPONENT_SUPPORT_VARIABLE_FIRST_COMPONENTS
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_PREVENT_INTRASENTENCE_MATCHING
	forwardPropogationSentenceData->listOfHighLevelNeuronsCompleteHistory.clear();
	#endif
	#endif
	
	/*
	algorithm2;
	let l be the first word in the sentence word sequence
	for every input neuron in sentence word sequence starting at l*
		propagate its input through the network
			ensure word index is contiguous during forward prop (GIA_TXT_REL_TRANSLATOR_SANI_ENFORCE_WORD_CONNECTIVITY_BETWEEN_PREVIOUS_ACTIVE_COMPONENTS_AND_NEWLY_ACTIVATED_COMPONENT: GIAtxtRelTranslatorSANIPropagateOperations.componentWordConnectivityTestsWrapper)
			mark all hidden neurons that fire (these are candidates)
			mark all hidden neurons that are only partially activated
				these become candidates for splitting
				never split a neuron below 2 components
			take the hidden neuron that support the most words in the sentence from l (whether it is fully activated or partially activated)
				if necessary (it is partially activated) split the neuron;
					b) take its components and forge a new neuron
					add to vector q
				c) if it is fully activated add to vector q
				then repeat* from last word index (l)
		if no appropriate hidden neuron is found create a a) new hidden neuron containing the first input in the current part of the sentence word sequence*
			add to vector q
			OLD: how to determine whether to use this new neuron or just connect its first input to..
			then repeat* from last word index (l)
	combine all the a) new, b) splitted, or c) fully activated neurons into a d) new neuron on a higher layer
		this new higher layer neuron d) represents a successfully parsed sentence m
			OPTIONAL: add this neuron to the highest level full gramatical sentence neuron
	issue with this algorithm is that it cannot reuse groups for embeded optional components eg rcmod;
		1 the dog barks
		2 the dog that is near the house barks
		will create 2 independent top level groups (the dog barks group will not be reused by 2)
		possibly look for and catch recursive group connectivity and ensure that groups can only support varied word index ranges when they refer to recursive (optional) groups
	*/
	
	GIAtxtRelTranslatorSANIPropagateOperations.setParseSentenceReverse(true, forwardPropogationSentenceData);
	//GIAtxtRelTranslatorRulesGroupNeuralNetwork* firstLayerNeuronGroupStart = NULL;
	
	int indexInSequence = 0;
	bool stillIdentifyingHighLevelNeurons = true;
	bool toplevelGroupActivationFound = false;

	vector<GIAtxtRelTranslatorRulesGroupNeuralNetwork*> listOfHighLevelNeurons1;	//vectorQ
	vector<GIAtxtRelTranslatorRulesGroupNeuralNetwork*>* listOfHighLevelNeuronsCurrent = &listOfHighLevelNeurons1;
	bool creatingNewNeuronSequence1 = false;	//this is used to ensure that only a single neuron is created to store the unrecognised sequence (not 1 neuron per word of the sequence)
	int neuronSequenceIndex1 = 0;
	GIAtxtRelTranslatorRulesGroupNeuralNetwork* newNeuronSequenceGroup1 = NULL;

	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_COMPONENT_DETECT_LOCAL_VARATION
	bool findingCandidateComponent1 = true;
	bool findingCandidateComponent2 = false;
	bool findingCentralVariation = false;
	int activatedNeuronWithMaxWordIndexCoverageFirstWordIndexAllowed = INT_DEFAULT_VALUE;	//for central variation detection only
	int activatedNeuronWithMaxWordIndexCoverageLastWordIndexAllowed = INT_DEFAULT_VALUE;	//for central variation detection only
	GIAtxtRelTranslatorRulesGroupParseTree* candidateNeuronBaseParseTree = NULL;
	vector<GIAtxtRelTranslatorRulesGroupNeuralNetwork*> listOfHighLevelNeuronsCentralVariation;
	#endif
			
	int loopIndex = 0;
	
	while(stillIdentifyingHighLevelNeurons)
	{		
		int currentFirstInputNeuronIndexInSequence;
		if(forwardPropogationSentenceData->parseSentenceReverse)
		{
			currentFirstInputNeuronIndexInSequence = forwardPropogationSentenceData->sentenceContents->size()-1-indexInSequence;
		}
		else
		{
			currentFirstInputNeuronIndexInSequence = indexInSequence;
		}

		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_BASIC
		cout << "\e[35m \n** loopIndex = " << loopIndex << ", indexInSequence = " << indexInSequence << ", word = " << (forwardPropogationSentenceData->sentenceContents)->at(currentFirstInputNeuronIndexInSequence)->tagName << " \e[0m" << endl;
		#endif

		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_PROPAGATE_ALL_POS_VALUES_SIMULTANEOUSLY
		//if GIA_TXT_REL_TRANSLATOR_SANI_PROPAGATE_ALL_POS_VALUES_SIMULTANEOUSLY, first layer contains firstPOS neuron for each wordIndex only
		cerr << "GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::findAndReconcileIncrementalVariation hasnt yet been coded for GIA_TXT_REL_TRANSLATOR_SANI_PROPAGATE_ALL_POS_VALUES_SIMULTANEOUSLY" << endl;
		exit(EXIT_ERROR);
		#else
		GIAtxtRelTranslatorRulesGroupNeuralNetwork* currentLayerNeuronGroupStart = (firstLayer)[currentFirstInputNeuronIndexInSequence];
		#endif
		
		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG
		cout << "GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::stillIdentifyingHighLevelNeurons" << endl;
		#endif
		
		forwardPropogationSentenceData->toplevelGroupActivationFound = false;

		forwardPropogationSentenceData->recordActivatedNeuronWithMaxWordIndexCoverage = true;
		forwardPropogationSentenceData->activatedNeuronWithMaxWordIndexCoverage = NULL;
		forwardPropogationSentenceData->activatedNeuronWithMaxWordIndexCoveragePartial = false;
		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_COMPONENT_SUPPORT_VARIABLE_FIRST_COMPONENTS
		forwardPropogationSentenceData->activatedNeuronWithMaxWordIndexCoverageVariable = false;
		#endif
		
		//cout << "indexInSequence = " << indexInSequence << endl;
		
		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_COMPONENT_DETECT_LOCAL_VARATION
		if(findingCentralVariation)
		{
			if(GIAtxtRelTranslatorSANIPropagateCompact.performPropagation(translatorVariables, GIAtxtRelTranslatorRulesGroupTypes, forwardPropogationSentenceData, false, indexInSequence, activatedNeuronWithMaxWordIndexCoverageFirstWordIndexAllowed, activatedNeuronWithMaxWordIndexCoverageLastWordIndexAllowed))
			{
				toplevelGroupActivationFound = true;	//note this will only be set true if the entire sentence word indices have been covered (ie only when currentFirstInputNeuronIndexInSequence=start)
			}
		}
		else
		{
		#endif			
			if(GIAtxtRelTranslatorSANIPropagateCompact.performPropagation(translatorVariables, GIAtxtRelTranslatorRulesGroupTypes, forwardPropogationSentenceData, false, indexInSequence))
			{
				toplevelGroupActivationFound = true;	//note this will only be set true if the entire sentence word indices have been covered (ie only when currentFirstInputNeuronIndexInSequence=start)
			}
		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_COMPONENT_DETECT_LOCAL_VARATION
		}
		#endif
		
		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_COMPONENT_DETECT_LOCAL_VARATION
		if(findingCandidateComponent2)
		{
			findingCandidateComponent2 = false;
			
			if(forwardPropogationSentenceData->foundCandidateComponent2)
			{
				listOfHighLevelNeuronsCurrent->push_back(candidateNeuronBaseParseTree->groupRef);

				GIAtxtRelTranslatorRulesGroupParseTree* candidateComponent2sourceParseTreeGroup = forwardPropogationSentenceData->candidateComponent2sourceParseTreeGroup;

				if(forwardPropogationSentenceData->parseSentenceReverse)
				{
					activatedNeuronWithMaxWordIndexCoverageFirstWordIndexAllowed = candidateNeuronBaseParseTree->parseTreeMinWordIndex-1;
					activatedNeuronWithMaxWordIndexCoverageLastWordIndexAllowed = candidateComponent2sourceParseTreeGroup->parseTreeMaxWordIndex+1;
				}
				else
				{
					activatedNeuronWithMaxWordIndexCoverageFirstWordIndexAllowed = candidateNeuronBaseParseTree->parseTreeMaxWordIndex+1;
					activatedNeuronWithMaxWordIndexCoverageLastWordIndexAllowed = candidateComponent2sourceParseTreeGroup->parseTreeMinWordIndex-1;
				}
				
				if(activatedNeuronWithMaxWordIndexCoverageFirstWordIndexAllowed == activatedNeuronWithMaxWordIndexCoverageLastWordIndexAllowed)
				{
					//perfect match detected between activated section of candidateNeuronBaseParseTree and candidateComponent2sourceParseTreeGroup, set component2 of candidateNeuronBase as optional
				}
				else
				{
					findingCentralVariation = true;
					listOfHighLevelNeuronsCurrent = &listOfHighLevelNeuronsCentralVariation;
				}
			}
			else
			{
				GIAtxtRelTranslatorRulesGroupNeuralNetwork* newNeuron = splitNeuron(GIAtxtRelTranslatorRulesGroupTypes, forwardPropogationSentenceData, candidateNeuronBaseParseTree);	//listOfHighLevelNeuronsCurrent CHECKTHIS
				listOfHighLevelNeuronsCurrent->push_back(newNeuron);
								
				//go back to standard findAndReconcileIncrementalVariation routine
			}
			
			forwardPropogationSentenceData->findingCandidateComponent2 = false;
			forwardPropogationSentenceData->candidateComponent2ToFind = NULL;
			candidateNeuronBaseParseTree = NULL;
		}
		else
		{
		#endif
			#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_LIMIT_NUM_COMPONENTS
			if(!(GIAtxtRelTranslatorSANIPropagateCompact.verifyActivatedNeuronsAtLeastOneBasic(forwardPropogationSentenceData, forwardPropogationSentenceData->activatedNeuronWithMaxWordIndexCoverage) && (!forwardPropogationSentenceData->activatedNeuronWithMaxWordIndexCoveragePartial)))		//(!forwardPropogationSentenceData->activatedNeuronWithMaxWordIndexCoveragePartial) should be enforced via GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_IGNORE_PARTIAL_DETECTIONS
			#else
			if(!GIAtxtRelTranslatorSANIPropagateCompact.verifyActivatedNeuronsAtLeastOne(forwardPropogationSentenceData, forwardPropogationSentenceData->activatedNeuronWithMaxWordIndexCoverage, newNeuronSequenceGroup1))
			#endif
			{
				//case a			
				#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_BASIC
				cout << "A createOrAppendFirstLevelHiddenLayerGroup" << endl;
				#endif
				foundAndReconciledMissingOrDifferentIncrementalNeurons = true;

				createOrAppendFirstLevelHiddenLayerGroup(GIAtxtRelTranslatorRulesGroupTypes, forwardPropogationSentenceData, currentLayerNeuronGroupStart, &creatingNewNeuronSequence1, &neuronSequenceIndex1, &newNeuronSequenceGroup1, listOfHighLevelNeuronsCurrent);

				indexInSequence++;
			}
			else
			{
				creatingNewNeuronSequence1 = false;
				neuronSequenceIndex1 = 0;
				foundAndReconciledMissingOrDifferentIncrementalNeurons = true;

				#ifndef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_LIMIT_NUM_COMPONENTS
				if(!(forwardPropogationSentenceData->activatedNeuronWithMaxWordIndexCoveragePartial))
				{	
				#endif
					//case c
					#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_BASIC
					cout << "B addNeuronToList, forwardPropogationSentenceData->activatedNeuronWithMaxWordIndexCoverage->groupRef->groupIndex = " << forwardPropogationSentenceData->activatedNeuronWithMaxWordIndexCoverage->groupRef->groupIndex << endl;
					#endif
					//fully activated group coverage+weight is > partially activated group coverage+weight
					
					addNeuronToList(GIAtxtRelTranslatorRulesGroupTypes, forwardPropogationSentenceData, listOfHighLevelNeuronsCurrent, forwardPropogationSentenceData->activatedNeuronWithMaxWordIndexCoverage->groupRef, &indexInSequence);
				#ifndef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_LIMIT_NUM_COMPONENTS
				}
				else
				{
					//case b
					#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_BASIC
					cout << "C splitGroupAtLastActivatedComponent + addNeuronToList, forwardPropogationSentenceData->activatedNeuronWithMaxWordIndexCoverage->groupRef->groupIndex = " << forwardPropogationSentenceData->activatedNeuronWithMaxWordIndexCoverage->groupRef->groupIndex << endl;
					#endif
					//partially activated group coverage+weight is > fully activated group coverage+weight
						
					#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_COMPONENT_DETECT_LOCAL_VARATION
					bool foundLocalVariationCandidate = false;
					if(findingCandidateComponent1)
					{
						GIAtxtRelTranslatorRulesComponentNeuralNetwork* candidateComponent2 = NULL; 
						candidateNeuronBaseParseTree = forwardPropogationSentenceData->activatedNeuronWithMaxWordIndexCoverage;
						if(verifyAndMarkNeuronAsCandidateWrapper(forwardPropogationSentenceData, candidateNeuronBaseParseTree, &candidateComponent2))
						{
							foundLocalVariationCandidate = true;
							findingCandidateComponent1 = false;
							findingCandidateComponent2 = true;
							forwardPropogationSentenceData->findingCandidateComponent2 = true;
							forwardPropogationSentenceData->candidateComponent2ToFind = candidateComponent2;
						}
					}
					if(!foundLocalVariationCandidate)
					{
					#endif
						GIAtxtRelTranslatorRulesGroupNeuralNetwork* newNeuron = splitNeuron(GIAtxtRelTranslatorRulesGroupTypes, forwardPropogationSentenceData, forwardPropogationSentenceData->activatedNeuronWithMaxWordIndexCoverage);
	
						addNeuronToList(GIAtxtRelTranslatorRulesGroupTypes, forwardPropogationSentenceData, listOfHighLevelNeuronsCurrent, newNeuron, &indexInSequence);

					#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_COMPONENT_DETECT_LOCAL_VARATION
					}
					#endif
				}
				#endif
			}			

			#ifdef GIA_TXT_REL_TRANSLATOR_SANI_FREE_MEMORY
			GIAtxtRelTranslatorSANIPropagateOperations.deinitialiseParseTreeGroupList(GIAtxtRelTranslatorRulesGroupTypes, parseTreeGroupListPointer);
			#endif
			
			#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_COMPONENT_DETECT_LOCAL_VARATION
			if(findingCentralVariation)
			{
				if(currentFirstInputNeuronIndexInSequence == activatedNeuronWithMaxWordIndexCoverageLastWordIndexAllowed)
				{
					GIAtxtRelTranslatorRulesGroupNeuralNetwork* grammaticalSentenceNeuron = NULL;
					if(connectListOfHighLevelNeuronsToNewNeuron(GIAtxtRelTranslatorRulesGroupTypes, forwardPropogationSentenceData, listOfHighLevelNeuronsCurrent, &grammaticalSentenceNeuron, false))
					{
						listOfHighLevelNeurons1.push_back(grammaticalSentenceNeuron);
					}
					findingCentralVariation = false;
					findingCandidateComponent1 = true;
					listOfHighLevelNeuronsCurrent = &listOfHighLevelNeurons1;
					activatedNeuronWithMaxWordIndexCoverageFirstWordIndexAllowed = INT_DEFAULT_VALUE;
					activatedNeuronWithMaxWordIndexCoverageLastWordIndexAllowed = INT_DEFAULT_VALUE;
					//candidateNeuronBaseParseTree = NULL;	//already done
				}
			}
			#endif

		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_COMPONENT_DETECT_LOCAL_VARATION
		}
		#endif
		
		if(indexInSequence < forwardPropogationSentenceData->sentenceContents->size())
		{
			stillIdentifyingHighLevelNeurons = true;	
			//see how many words successfully propagated through the next time
		}
		else
		{
			stillIdentifyingHighLevelNeurons = false;
		}	
		
		loopIndex++;
	}

	GIAtxtRelTranslatorRulesGroupNeuralNetwork* grammaticalSentenceNeuron = NULL;
	connectListOfHighLevelNeuronsToNewNeuron(GIAtxtRelTranslatorRulesGroupTypes, forwardPropogationSentenceData, &listOfHighLevelNeurons1, &grammaticalSentenceNeuron, true);
	
	return foundAndReconciledMissingOrDifferentIncrementalNeurons;
}

#ifndef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_LIMIT_NUM_COMPONENTS
GIAtxtRelTranslatorRulesGroupNeuralNetwork* GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::splitNeuron(vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes, GIAtxtRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, GIAtxtRelTranslatorRulesGroupParseTree* partiallyActivatedNeuronWithMaxWordIndexCoverage)
{	
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_SUPPORT_PARTIAL_SENTENCE_PROPAGATION
	int indexToSplitVector1 = INT_DEFAULT_VALUE;
	int indexToSplitVector2 = INT_DEFAULT_VALUE;			
	GIAtxtRelTranslatorSANIPropagateCompact.identifyComponentIndexFirstAndLastActivatedIndexUnordered(forwardPropogationSentenceData, partiallyActivatedNeuronWithMaxWordIndexCoverage, &indexToSplitVector1, &indexToSplitVector2);
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_COMPONENT_SUPPORT_VARIABLE_FIRST_COMPONENTS
	if(forwardPropogationSentenceData->activatedNeuronWithMaxWordIndexCoverageVariable)
	{
		//ensure not to split off the first variable component (keep it in the group)
		if(forwardPropogationSentenceData->parseSentenceReverse)
		{
			indexToSplitVector2 = partiallyActivatedNeuronWithMaxWordIndexCoverage->groupRef->components.size()-1;
		}
		else
		{
			indexToSplitVector1 = 0;
		}
	}
	#endif
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_PRINT_GROUP_INDICES
	cout << "indexToSplitVector1 = " << indexToSplitVector1 << endl;
	cout << "indexToSplitVector2 = " << indexToSplitVector2 << endl;				
	#endif				
	GIAtxtRelTranslatorRulesGroupNeuralNetwork* newNeuron = splitGroupAtLastActivatedComponentUnordered(forwardPropogationSentenceData, GIAtxtRelTranslatorRulesGroupTypes, partiallyActivatedNeuronWithMaxWordIndexCoverage->groupRef, indexToSplitVector1, indexToSplitVector2);	//note passing partiallyActivatedNeuronWithMaxWordIndexCoverage instead of partiallyActivatedNeuronWithMaxWordIndexCoverage->groupRef because groupRef's activations may have been overwritten if the neuron was reset after being saved to partiallyActivatedNeuronWithMaxWordIndexCoverage
	#else
	int indexToSplitVector = INT_DEFAULT_VALUE;
	GIAtxtRelTranslatorSANIPropagateCompact.identifyComponentIndexLastActivatedIndex(forwardPropogationSentenceData, partiallyActivatedNeuronWithMaxWordIndexCoverage, &indexToSplitVector);
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_PRINT_GROUP_INDICES
	cout << "indexToSplitVector = " << indexToSplitVector << endl;				
	#endif
	GIAtxtRelTranslatorRulesGroupNeuralNetwork* newNeuron = splitGroupAtLastActivatedComponent(forwardPropogationSentenceData, GIAtxtRelTranslatorRulesGroupTypes, partiallyActivatedNeuronWithMaxWordIndexCoverage->groupRef, indexToSplitVector);	//note passing partiallyActivatedNeuronWithMaxWordIndexCoverage instead of partiallyActivatedNeuronWithMaxWordIndexCoverage->groupRef because groupRef's activations may have been overwritten if the neuron was reset after being saved to partiallyActivatedNeuronWithMaxWordIndexCoverage
	#endif
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_PRINT_GROUP_INDICES
	cout << "partiallyActivatedNeuronWithMaxWordIndexCoverage->parseTreeMaxWordIndex = " << partiallyActivatedNeuronWithMaxWordIndexCoverage->parseTreeMaxWordIndex << endl;
	cout << "partiallyActivatedNeuronWithMaxWordIndexCoverage->parseTreeMinWordIndex = " << partiallyActivatedNeuronWithMaxWordIndexCoverage->parseTreeMinWordIndex << endl;
	//cout << "indexInSequence = " << indexInSequence << endl;
	#endif				
	
	return newNeuron;
}
#endif

bool GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::addNeuronToList(vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes, GIAtxtRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, vector<GIAtxtRelTranslatorRulesGroupNeuralNetwork*>* listOfHighLevelNeurons, GIAtxtRelTranslatorRulesGroupNeuralNetwork* neuron, int* indexInSequence)
{	
	bool result = true;
	
	if(forwardPropogationSentenceData->parseSentenceReverse)
	{
		*indexInSequence = forwardPropogationSentenceData->sentenceContents->size()-1 - (forwardPropogationSentenceData->activatedNeuronWithMaxWordIndexCoverage->parseTreeMinWordIndex - 1);	//CHECKTHIS
	}
	else
	{
		*indexInSequence = forwardPropogationSentenceData->activatedNeuronWithMaxWordIndexCoverage->parseTreeMaxWordIndex + 1;
	}
				
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_COMPONENT_SUPPORT_VARIABLE_FIRST_COMPONENTS
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_PREVENT_INTRASENTENCE_MATCHING
	addSubneuronsToList(&(forwardPropogationSentenceData->listOfHighLevelNeuronsCompleteHistory), neuron);	//add subneurons to listOfHighLevelNeuronsCompleteHistory before connecting its first component to listOfHighLevelNeurons heirachy
	#endif
	
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_LIMIT_NUM_COMPONENTS
	//why doesnt the following "if(forwardPropogationSentenceData->activatedNeuronWithMaxWordIndexCoverageVariable)" code work?
	#else
	if(forwardPropogationSentenceData->activatedNeuronWithMaxWordIndexCoverageVariable)
	{
		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_BASIC
		cout << "(forwardPropogationSentenceData->activatedNeuronWithMaxWordIndexCoverageVariable)" << endl;
		#endif
		
		int variableComponentInGroup = 0;
		if(forwardPropogationSentenceData->parseSentenceReverse)
		{
			variableComponentInGroup = neuron->components.size() - 1;
		}
		else
		{
			variableComponentInGroup = 0;
		}
		GIAtxtRelTranslatorRulesComponentNeuralNetwork* variableComponent = neuron->components[variableComponentInGroup];
		
		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_BASIC
		for(int l=0; l<variableComponent->ANNbackGroupConnectionList.size(); l++)
		{
			GIAtxtRelTranslatorRulesGroupNeuralNetwork* groupSource = variableComponent->ANNbackGroupConnectionList[l];
			if(groupSource->groupTypeIsString)
			{
				cout << "variableComponent groupSource->wordPOStype = " << groupSource->wordPOStype << endl;
			}
			else
			{
				cout << "variableComponent groupSource->groupIndex = " << groupSource->groupIndex << endl;
			}
		}
		#endif
		
		
		GIAtxtRelTranslatorRulesGroupNeuralNetwork* grammaticalSentenceNeuron = NULL;
		if(connectListOfHighLevelNeuronsToNewNeuron(GIAtxtRelTranslatorRulesGroupTypes, forwardPropogationSentenceData, listOfHighLevelNeurons, &grammaticalSentenceNeuron, false))
		{
			listOfHighLevelNeurons->clear();
			addComponentToGroup(forwardPropogationSentenceData, grammaticalSentenceNeuron, variableComponent);
		}
	}
	#endif
	
	#endif

	listOfHighLevelNeurons->push_back(neuron);
	

	
	return result;
}

bool GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::connectListOfHighLevelNeuronsToNewNeuron(vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes, GIAtxtRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, vector<GIAtxtRelTranslatorRulesGroupNeuralNetwork*>* listOfHighLevelNeurons, GIAtxtRelTranslatorRulesGroupNeuralNetwork** grammaticalSentenceNeuron, const bool createTopLevelNeuron)
{
	bool result = false;
	
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_TRACE
	cout << "connectListOfHighLevelNeuronsToNewNeuron" << endl;
	cout << "listOfHighLevelNeurons->size() = " << listOfHighLevelNeurons->size() << endl;
	#endif
	
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_PREVENT_TOP_LEVEL_NEURON_DUPLICATION
	if(listOfHighLevelNeurons->size() > 1)
	{
	#endif
		result = true;
		
		GIAtxtRelTranslatorRulesGroupNeuralNetwork* grammaticalSentenceNeuronSub = createNewHiddenLayerGroup(forwardPropogationSentenceData, GIAtxtRelTranslatorRulesGroupTypes);
		#ifdef GIA_DEBUG_TXT_REL_TRANSLATOR_SANI_FORMATION
		cout << "\t\t GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::connectListOfHighLevelNeuronsToNewNeuron: grammaticalSentenceNeuronSub->groupIndex = " << grammaticalSentenceNeuronSub->groupIndex << endl;
		#endif
		
		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_LIMIT_NUM_COMPONENTS
		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_ADD_NEW_NEURONS_TO_SYMMETRICAL_TREE
		int newTreeNumLayers = listOfHighLevelNeurons->size()/GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_MAX_NUM_COMPONENTS;
		bool oddNumHighLevNeurons = bool(listOfHighLevelNeurons->size()%GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_MAX_NUM_COMPONENTS);
		vector<GIAtxtRelTranslatorRulesGroupNeuralNetwork*> listOfHighLevelNeuronsSub = *listOfHighLevelNeurons;	//first layer in symmetrical tree is identical to listOfHighLevelNeurons
		//cout << "newTreeNumLayers = " << newTreeNumLayers << endl;
		if(oddNumHighLevNeurons)
		{
			//cout << "oddNumHighLevNeurons" << endl;
			listOfHighLevelNeuronsSub.pop_back();	//remove final odd neuron from list (will be added later)
			newTreeNumLayers++;	//require an additional (elongated) layer to add the final odd neuron in high level list
		}
		for(int l=0; l<newTreeNumLayers; l++)
		{
			vector<GIAtxtRelTranslatorRulesGroupNeuralNetwork*> listOfHighLevelNeuronsSubNew;
			listOfHighLevelNeuronsSubNew.push_back(grammaticalSentenceNeuronSub);
			
			for(int k=0; k<listOfHighLevelNeuronsSub.size(); k++)
			{
				GIAtxtRelTranslatorRulesGroupNeuralNetwork* singleComponentNeuronCandidate = listOfHighLevelNeuronsSub[k];
				
				int componentType = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_GROUP;
				if(singleComponentNeuronCandidate->inputLayerNeuron)
				{
					componentType = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_STRING;
				}
				addComponentToGroup(forwardPropogationSentenceData, singleComponentNeuronCandidate, grammaticalSentenceNeuronSub, componentType, false);
				
				//add new higher level group in layer
				if(k%GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_MAX_NUM_COMPONENTS != 0)
				{
					GIAtxtRelTranslatorRules.updateComponentsOwnerGroupAndIndexes(grammaticalSentenceNeuronSub, &(grammaticalSentenceNeuronSub->components), false, NULL);

					//there is still another neuron in listOfHighLevelNeuronsSub to be added to the tree

					if(!((k == listOfHighLevelNeuronsSub.size()-1) && (l == newTreeNumLayers-1)))
					{//not last neuron of last layer:
						GIAtxtRelTranslatorRulesGroupNeuralNetwork* grammaticalSentenceNeuronSubNew = createNewHiddenLayerGroup(forwardPropogationSentenceData, GIAtxtRelTranslatorRulesGroupTypes);
						grammaticalSentenceNeuronSub = grammaticalSentenceNeuronSubNew;
					}
					
					if(k != listOfHighLevelNeuronsSub.size()-1)
					{//not last neuron:
						listOfHighLevelNeuronsSubNew.push_back(grammaticalSentenceNeuronSub);
					}
				}
			}
		
			listOfHighLevelNeuronsSub.clear();
			listOfHighLevelNeuronsSub = listOfHighLevelNeuronsSubNew;
			
			if(oddNumHighLevNeurons && (l == newTreeNumLayers-2))
			{
				//prepare for last layer (ensure top layer list has 2 neurons to be added)
				listOfHighLevelNeuronsSub.push_back(listOfHighLevelNeurons->back());	//add final odd neuron to list 
			}
		}
		#else	//GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_ADD_NEW_NEURONS_TO_ELONGATED_TREE
		for(int k=0; k<listOfHighLevelNeurons->size(); k++)
		{
			GIAtxtRelTranslatorRulesGroupNeuralNetwork* singleComponentNeuronCandidate = (*listOfHighLevelNeurons)[k];
			
			int componentType = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_GROUP;
			if(singleComponentNeuronCandidate->inputLayerNeuron)
			{
				componentType = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_STRING;
			}
			addComponentToGroup(forwardPropogationSentenceData, singleComponentNeuronCandidate, grammaticalSentenceNeuronSub, componentType, false);
			
			//add new higher level group in elongated tree
			if(k>0 && k<listOfHighLevelNeurons->size()-1)
			{//there is still another neuron in listOfHighLevelNeurons to be added to the tree
			
				GIAtxtRelTranslatorRulesGroupNeuralNetwork* grammaticalSentenceNeuronSubHigher = createNewHiddenLayerGroup(forwardPropogationSentenceData, GIAtxtRelTranslatorRulesGroupTypes);
				#ifdef GIA_DEBUG_TXT_REL_TRANSLATOR_SANI_FORMATION
				cout << "\t\t GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::connectListOfHighLevelNeuronsToNewNeuron: grammaticalSentenceNeuronSubHigher->groupIndex = " << grammaticalSentenceNeuronSubHigher->groupIndex << endl;
				#endif

				addComponentToGroup(forwardPropogationSentenceData, grammaticalSentenceNeuronSub, grammaticalSentenceNeuronSubHigher, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_GROUP, false);
				
				GIAtxtRelTranslatorRules.updateComponentsOwnerGroupAndIndexes(grammaticalSentenceNeuronSub, &(grammaticalSentenceNeuronSub->components), false, NULL);
				
				grammaticalSentenceNeuronSub = grammaticalSentenceNeuronSubHigher;
			}
		}	
		#endif
		#else
		for(int k=0; k<listOfHighLevelNeurons->size(); k++)
		{
			GIAtxtRelTranslatorRulesGroupNeuralNetwork* singleComponentNeuronCandidate = (*listOfHighLevelNeurons)[k];
				
			#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_REQUIRE_NUM_COMPONENTS_ENFORCE_DURING_FIRST_HIDDEN_LAYER_GENERATION
			if(!directWireLowLevelPOSneuronToGrammaticalSentenceNeuron(GIAtxtRelTranslatorRulesGroupTypes, forwardPropogationSentenceData, singleComponentNeuronCandidate, grammaticalSentenceNeuronSub))
			{
			#endif
				addComponentToGroup(forwardPropogationSentenceData, singleComponentNeuronCandidate, grammaticalSentenceNeuronSub, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_GROUP, false);
			#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_REQUIRE_NUM_COMPONENTS_ENFORCE_DURING_FIRST_HIDDEN_LAYER_GENERATION
			}
			#endif
		}
		#endif
		
		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_PRINT_GROUP_INDICES
		cout << "GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::connectListOfHighLevelNeuronsToNewNeuron - assigning top level sentence neuron;" << endl;
		#endif
		(*grammaticalSentenceNeuron) = grammaticalSentenceNeuronSub;
		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_ANN_SEGREGATE_TOP_LAYER_NEURONS
		if(createTopLevelNeuron)
		{
			(*grammaticalSentenceNeuron)->topLevelSentenceNeuron = true;
		}
		#endif
		
		GIAtxtRelTranslatorRules.updateComponentsOwnerGroupAndIndexes((*grammaticalSentenceNeuron), &((*grammaticalSentenceNeuron)->components), false, NULL);

		if(createTopLevelNeuron)
		{
			#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_TRACE
			GIAtxtRelTranslatorSANIPropagateOperations.traceBackpropNeuralNetwork((*grammaticalSentenceNeuron), 0, -1, -1);
			#endif
		}
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_PREVENT_TOP_LEVEL_NEURON_DUPLICATION
	}
	else
	{
		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_REQUIRE_NUM_COMPONENTS_ENFORCE_DURING_FIRST_HIDDEN_LAYER_GENERATION
		if(listOfHighLevelNeurons->size() == 1)
		{
			result = true;
			
			*grammaticalSentenceNeuron = (*listOfHighLevelNeurons)[0];
			(*grammaticalSentenceNeuron)->firstHiddenLayerNeuron = false;
			
			if(createTopLevelNeuron)
			{			
				#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_TRACE
				GIAtxtRelTranslatorSANIPropagateOperations.traceBackpropNeuralNetwork((*grammaticalSentenceNeuron), 0, -1, -1);
				#endif
			}
		}
		#endif
	}
	#endif
	
	return result;
}

	
#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_COMPONENT_DETECT_LOCAL_VARATION
bool GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::verifyAndMarkNeuronAsCandidateWrapper(GIAtxtRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, GIAtxtRelTranslatorRulesGroupParseTree* candidateNeuronBaseParseTree, GIAtxtRelTranslatorRulesComponentNeuralNetwork** candidateComponent2)
{
	bool result = false;
	
	GIAtxtRelTranslatorRulesGroupNeuralNetwork* candidateNeuronBase = candidateNeuronBaseParseTree->groupRef;
		
	int lastActivatedIndex = INT_DEFAULT_VALUE;
	int firstUnactivatedIndex = INT_DEFAULT_VALUE;	
	GIAtxtRelTranslatorSANIPropagateCompact.identifyComponentIndexLastActivatedAndFirstUnactivatedIndex(forwardPropogationSentenceData, candidateNeuronBaseParseTree, &lastActivatedIndex, &firstUnactivatedIndex);
		
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_SUPPORT_PARTIAL_SENTENCE_PROPAGATION
	bool missingStartComponentsFound = false;
	int indexOfFirstComponent;
	if(forwardPropogationSentenceData->parseSentenceReverse)
	{
		indexOfFirstComponent = candidateNeuronBaseParseTree->components.size()-1;
		GIAtxtRelTranslatorRulesComponentParseTree* firstActiveComponent = candidateNeuronBaseParseTree->components[indexOfFirstComponent];
		if(firstActiveComponent->componentRef->componentIndex != candidateNeuronBase->components.size()-1)
		{
			missingStartComponentsFound = true;
		}
	}
	else
	{
		indexOfFirstComponent = 0;
		GIAtxtRelTranslatorRulesComponentParseTree* firstActiveComponent = candidateNeuronBaseParseTree->components[indexOfFirstComponent];
		if(firstActiveComponent->componentRef->componentIndex != 0)
		{
			missingStartComponentsFound = true;
		}
	}
	if(!missingStartComponentsFound)
	{
	#endif
		bool missingEndComponentsFound = false;
		int missingEndComponentsIndex;
		if(forwardPropogationSentenceData->parseSentenceReverse)
		{
			if(firstUnactivatedIndex > 0)
			{
				missingEndComponentsFound = true;
				missingEndComponentsIndex = firstUnactivatedIndex-1;
			}
		}
		else
		{
			if(firstUnactivatedIndex < candidateNeuronBase->components.size()-1)
			{
				missingEndComponentsFound = true;
				missingEndComponentsIndex = firstUnactivatedIndex+1;
			}
		}
		
		if(missingEndComponentsFound)
		{
			*candidateComponent2 = candidateNeuronBase->components[missingEndComponentsIndex];
			result = true;
		}
		else
		{
			if(verifyAndMarkNeuronAsCandidate(forwardPropogationSentenceData, candidateNeuronBase, candidateComponent2))
			{
				result = true;
			}
		}
		
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_SUPPORT_PARTIAL_SENTENCE_PROPAGATION
	}
	#endif

	return result;
}
	
bool GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::verifyAndMarkNeuronAsCandidate(GIAtxtRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, GIAtxtRelTranslatorRulesGroupNeuralNetwork* currentNeuron, GIAtxtRelTranslatorRulesComponentNeuralNetwork** candidateComponent2)
{
	bool result = false;
	
	for(int i=0; i<currentNeuron->ANNfrontComponentConnectionList.size(); i++)
	{
		GIAtxtRelTranslatorRulesComponentNeuralNetwork* currentComponent = (currentNeuron->ANNfrontComponentConnectionList)[i];
		GIAtxtRelTranslatorRulesGroupNeuralNetwork* higherLevelGroup = currentComponent->ownerGroup;
		//cout << "higherLevelGroup->groupIndex = " << higherLevelGroup->groupIndex << endl;
		
		//note this function currently relies on higherLevelGroup instead of higherLevelGroup->parseTreeTemp to detect component activations (neuronComponentConnectionActive); CHECKTHIS
		//GIAtxtRelTranslatorRulesGroupNeuralNetwork* higherLevelGroupParseTree = higherLevelGroup->parseTreeTemp;
		
		bool foundPriorComponent = false;
		bool foundPostComponent = false;
		bool foundCurrentComponent = false;
		bool allPriorComponentsActive = true;
		for(int j=0; j<higherLevelGroup->components.size(); j++)
		{
			int c;
			if(forwardPropogationSentenceData->parseSentenceReverse)
			{
				c = higherLevelGroup->components.size()-1-j;
			}
			else
			{
				c = j;
			}
				
			GIAtxtRelTranslatorRulesComponentNeuralNetwork* currentComponent2 = higherLevelGroup->components[c];
			if(foundCurrentComponent)
			{
				if(!foundPostComponent)
				{
					foundPostComponent = true;
					if(allPriorComponentsActive)
					{
						//record first post component
						*candidateComponent2 = currentComponent2;
						result = true;
					}
				}
			}
			else
			{
				if(c == currentComponent->componentIndex)
				{
					foundCurrentComponent = true;
				}
				else
				{
					foundPriorComponent = true;
					if(!(currentComponent2->neuronComponentConnectionActive))
					{
						allPriorComponentsActive = false;
					}
				}
			}
		}
		if(allPriorComponentsActive && !foundPostComponent)
		{
			if(verifyAndMarkNeuronAsCandidate(forwardPropogationSentenceData, higherLevelGroup, candidateComponent2))
			{
				result = true;
			}
		}
	}
	
	return result;
}
#endif
	

bool GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::createOrAppendFirstLevelHiddenLayerGroup(vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes, GIAtxtRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, GIAtxtRelTranslatorRulesGroupNeuralNetwork* currentLayerNeuronGroupStart, bool* creatingNewNeuronSequence, int* neuronSequenceIndex, GIAtxtRelTranslatorRulesGroupNeuralNetwork** newNeuronSequenceGroup, vector<GIAtxtRelTranslatorRulesGroupNeuralNetwork*>* listOfHighLevelNeurons)
{
	bool result = true;
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_PRINT_GROUP_INDICES
	cout << "GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::createOrAppendFirstLevelHiddenLayerGroup" << endl;
	#endif
	
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_LIMIT_NUM_COMPONENTS
	listOfHighLevelNeurons->push_back(currentLayerNeuronGroupStart);
	currentLayerNeuronGroupStart->inputLayerNeuron = true;
	#else
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_LIMIT_NUM_COMPONENTS_ORIG
	if(*neuronSequenceIndex >= GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_MAX_NUMBER_COMPONENTS)
	{
		*creatingNewNeuronSequence = false;
		*neuronSequenceIndex = 0;
	}
	#endif

	if(*creatingNewNeuronSequence)
	{
		addComponentToFirstLevelHiddenLayerGroup(forwardPropogationSentenceData, currentLayerNeuronGroupStart, *newNeuronSequenceGroup);
		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_BASIC
		cout << "creatingNewNeuronSequence: newNeuronSequenceGroup->groupIndex = " << (*newNeuronSequenceGroup)->groupIndex << endl;
		#endif
	}
	else
	{
		*neuronSequenceIndex = 0;
		*creatingNewNeuronSequence = true;
		GIAtxtRelTranslatorRulesGroupNeuralNetwork* newNeuron = createNewHiddenLayerGroup(forwardPropogationSentenceData, GIAtxtRelTranslatorRulesGroupTypes);
		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_REQUIRE_NUM_COMPONENTS_ENFORCE_DURING_FIRST_HIDDEN_LAYER_GENERATION
		newNeuron->firstHiddenLayerNeuron = true;
		#endif
		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_BASIC
		cout << "!creatingNewNeuronSequence: newNeuron->groupIndex = " << newNeuron->groupIndex << endl;
		//cout << "currentLayerNeuronGroupStart->wordPOStype = " << currentLayerNeuronGroupStart->wordPOStype << endl;
		#endif
		addComponentToFirstLevelHiddenLayerGroup(forwardPropogationSentenceData, currentLayerNeuronGroupStart, newNeuron);
		listOfHighLevelNeurons->push_back(newNeuron);
		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_COMPONENT_SUPPORT_VARIABLE_FIRST_COMPONENTS
		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_PREVENT_INTRASENTENCE_MATCHING
		addSubneuronsToList(&(forwardPropogationSentenceData->listOfHighLevelNeuronsCompleteHistory), newNeuron);
		#endif	
		#endif
		*newNeuronSequenceGroup = newNeuron;
	}
	#endif

	*neuronSequenceIndex = *neuronSequenceIndex + 1;
	
	return result;
}		
			
#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_REQUIRE_NUM_COMPONENTS_ENFORCE_DURING_FIRST_HIDDEN_LAYER_GENERATION
bool GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::directWireLowLevelPOSneuronToGrammaticalSentenceNeuron(vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes, GIAtxtRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, GIAtxtRelTranslatorRulesGroupNeuralNetwork* singleComponentNeuronCandidate, GIAtxtRelTranslatorRulesGroupNeuralNetwork* grammaticalSentenceNeuron)
{
	bool directWire = false;
	if(singleComponentNeuronCandidate->firstHiddenLayerNeuron)
	{		
		if(singleComponentNeuronCandidate->components.size() == 1)
		{
			GIAtxtRelTranslatorRulesGroupNeuralNetwork* singleComponentNeuron = singleComponentNeuronCandidate;

			#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_BASIC
			cout << "GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::directWireLowLevelPOSneuronToGrammaticalSentenceNeuron: singleComponentNeuron->groupIndex = " << singleComponentNeuron->groupIndex << endl;
			#endif
			
			//direct wire low level POS neuron to grammaticalSentenceNeuron (dont ever create intermediary single component neuron)
			directWire = true;

			GIAtxtRelTranslatorRulesComponentNeuralNetwork* component = singleComponentNeuron->components[0];

			//doesnt seem to ever be required;
			for(int i=0; i<singleComponentNeuron->ANNfrontComponentConnectionList.size(); i++)
			{
				GIAtxtRelTranslatorRulesComponentNeuralNetwork* currentComponent = (singleComponentNeuron->ANNfrontComponentConnectionList)[i];
				GIAtxtRelTranslatorRulesGroupNeuralNetwork* higherLevelGroup = currentComponent->ownerGroup;
				//cout << "higherLevelGroup->groupIndex = " << higherLevelGroup->groupIndex << endl;

				/*
				//method1;
				for(int j=0; j<higherLevelGroup->components.size(); j++)
				{	
					GIAtxtRelTranslatorRulesComponentNeuralNetwork* currentComponent2 = (higherLevelGroup->components)[j];
					if(currentComponent2 == currentComponent)
					{
						higherLevelGroup->components.erase(higherLevelGroup->components.begin()+j);
						j--;
					}
				}
				GIAtxtRelTranslatorRules.updateComponentsOwnerGroupAndIndexes(higherLevelGroup, &(higherLevelGroup->components), false, NULL);	
				delete currentComponent;
				*/
				//method2;
				for(int j=0; j<currentComponent->ANNbackGroupConnectionList.size(); j++)
				{
					GIAtxtRelTranslatorRulesGroupNeuralNetwork* firstHiddenLayerGroup = (currentComponent->ANNbackGroupConnectionList)[j];
					if(firstHiddenLayerGroup == singleComponentNeuron)
					{
						currentComponent->ANNbackGroupConnectionList.erase(currentComponent->ANNbackGroupConnectionList.begin()+j);
						j--;
					}
				}
			}

			for(int i=0; i<component->ANNbackGroupConnectionList.size(); i++)
			{
				GIAtxtRelTranslatorRulesGroupNeuralNetwork* lowerLevelPOSgroup = (component->ANNbackGroupConnectionList)[i];
				//GIAtxtRelTranslatorSANIFormation.deleteGroupANNconnectionForward(lowerLevelPOSgroup, component);
				for(int j=0; j<lowerLevelPOSgroup->ANNfrontComponentConnectionList.size(); j++)
				{
					GIAtxtRelTranslatorRulesComponentNeuralNetwork* currentComponent = (lowerLevelPOSgroup->ANNfrontComponentConnectionList)[j];
					if(currentComponent == component)
					{
						lowerLevelPOSgroup->ANNfrontComponentConnectionList.erase(lowerLevelPOSgroup->ANNfrontComponentConnectionList.begin()+j);
						j--;
					}
				}

				addComponentToGroup(forwardPropogationSentenceData, lowerLevelPOSgroup, grammaticalSentenceNeuron, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_STRING, false);	//fixed GIA3j5aTEMP61 
			}


			/*
			cout << "\t GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_REQUIRE_NUM_COMPONENTS_ENFORCE_DURING_FIRST_HIDDEN_LAYER_GENERATION;" << endl;
			cout << "\tgrammaticalSentenceNeuron->groupIndex = " << grammaticalSentenceNeuron->groupIndex << endl;
			cout << "\tlowerLevelPOSgroup->groupIndex = " << lowerLevelPOSgroup->groupIndex << endl;
			cout << "\tlistOfHighLevelNeurons1[i]->groupIndex = " << singleComponentNeuron->groupIndex << endl;
			*/

			GIAtxtRelTranslatorRulesGroupType* groupType = GIAtxtRelTranslatorRules.getSequenceGrammarGroupTypeDefault(GIAtxtRelTranslatorRulesGroupTypes);
			//groupType->groups.erase(remove(groupType->groups.begin(), groupType->groups.end(), singleComponentNeuron), groupType->groups.end());
			for(int i2=0; i2<groupType->groups.size(); i2++)
			{
				GIAtxtRelTranslatorRulesGroupNeuralNetwork* group = (groupType->groups)[i2];
				if(group == singleComponentNeuron)
				{
					groupType->groups.erase(groupType->groups.begin()+i2);
        				i2--;
				}
			}

			/*
			//parseTreeGroup has already been removed by GIAtxtRelTranslatorSANIPropagateOperations.deinitialiseParseTreeGroupList;
			if(singleComponentNeuron->currentParseTreeGroupTemp != NULL)
			{
				GIAtxtRelTranslatorSANIPropagateOperations.deleteGroup(singleComponentNeuron->currentParseTreeGroupTemp);
				parseTreeGroupListPointer->erase(remove(parseTreeGroupListPointer->begin(), parseTreeGroupListPointer->end(), singleComponentNeuron->currentParseTreeGroupTemp), parseTreeGroupListPointer->end());
			}
			*/

			GIAtxtRelTranslatorSANIPropagateOperations.deleteGroup(singleComponentNeuron);	
		}
	}
	if(!directWire)
	{
		singleComponentNeuronCandidate->firstHiddenLayerNeuron = false;	//NOT REQUIRED? prevents parsing of future sentence from matching this neuron as activatedNeuronWithMaxWordIndexCoverage, and then treating it like firstHiddenLayerNeuron above
	}
	
	return directWire;
}
#endif









bool GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::addComponentToFirstLevelHiddenLayerGroup(GIAtxtRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, GIAtxtRelTranslatorRulesGroupNeuralNetwork* inputLayerPOSneuron, GIAtxtRelTranslatorRulesGroupNeuralNetwork* newNeuronSequenceGroup)
{
	bool result = true;

	addComponentToGroup(forwardPropogationSentenceData, inputLayerPOSneuron, newNeuronSequenceGroup, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_STRING, false);
	//GIAtxtRelTranslatorSANIFormation.createGroupANNconnection(group, higherLevelComponent);

	return result;
}

GIAtxtRelTranslatorRulesGroupNeuralNetwork* GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::createNewHiddenLayerGroup(GIAtxtRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes)
{
	bool result = true;
	
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_PRINT_GROUP_INDICES
	cout << "GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::createNewHiddenLayerGroup" << endl;
	#endif
		
	GIAtxtRelTranslatorRulesGroupNeuralNetwork* newNeuron = createNewGroup();	
	GIAtxtRelTranslatorRulesGroupType* groupType = GIAtxtRelTranslatorRules.getSequenceGrammarGroupTypeDefault(GIAtxtRelTranslatorRulesGroupTypes);	
	groupType->groups.push_back(newNeuron);

	return newNeuron;
}
/*
GIAtxtRelTranslatorRulesGroupNeuralNetwork* GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::createNewFirstLevelHiddenLayerGroup(GIAtxtRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes, GIAtxtRelTranslatorRulesGroupNeuralNetwork* inputLayerPOSneuron)
{
	bool result = true;
	
	GIAtxtRelTranslatorRulesGroupNeuralNetwork* newNeuronSequenceGroup = createNewGroup();	
	GIAtxtRelTranslatorRulesGroupType* groupType = GIAtxtRelTranslatorRules.getSequenceGrammarGroupTypeDefault(GIAtxtRelTranslatorRulesGroupTypes);	
	groupType->groups.push_back(newNeuronSequenceGroup);

	addComponentToFirstLevelHiddenLayerGroup(forwardPropogationSentenceData, inputLayerPOSneuron, newNeuronSequenceGroup);

	return newNeuronSequenceGroup;
}
*/

//NB indexToSplitVector = lastActivatedComponent (the last component index in the first part of component to be splitted) (do not assume normal order: "first" and "last" definitions respect (forwardPropogationSentenceData->parseSentenceReverse))
GIAtxtRelTranslatorRulesGroupNeuralNetwork* GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::splitGroupAtLastActivatedComponent(GIAtxtRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes, GIAtxtRelTranslatorRulesGroupNeuralNetwork* neuronToSplit, int indexToSplitVector)
{
	GIAtxtRelTranslatorRulesGroupNeuralNetwork* newHiddenLayerNeuron = createNewGroup();	
	GIAtxtRelTranslatorRulesGroupType* groupType = GIAtxtRelTranslatorRules.getSequenceGrammarGroupTypeDefault(GIAtxtRelTranslatorRulesGroupTypes);	
	groupType->groups.push_back(newHiddenLayerNeuron);
		
	vector<GIAtxtRelTranslatorRulesComponentNeuralNetwork*>* components = &(neuronToSplit->components);
	vector<GIAtxtRelTranslatorRulesComponentNeuralNetwork*> componentsPart1(components->begin(), components->begin() + indexToSplitVector+1);
        vector<GIAtxtRelTranslatorRulesComponentNeuralNetwork*> componentsPart2(components->begin() + indexToSplitVector+1, components->end());
	
	if(forwardPropogationSentenceData->parseSentenceReverse)
	{
		newHiddenLayerNeuron->components = componentsPart2;
		neuronToSplit->components = componentsPart1;
	}
	else
	{
		newHiddenLayerNeuron->components = componentsPart1;
		neuronToSplit->components = componentsPart2;
	}
	GIAtxtRelTranslatorRules.updateComponentsOwnerGroupAndIndexes(newHiddenLayerNeuron, &(newHiddenLayerNeuron->components), false, NULL);
	GIAtxtRelTranslatorRules.updateComponentsOwnerGroupAndIndexes(neuronToSplit, &(neuronToSplit->components), false, NULL);	
	
	addComponentToGroup(forwardPropogationSentenceData, newHiddenLayerNeuron, neuronToSplit, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_GROUP, true);	//CHECKTHIS	
		
	return newHiddenLayerNeuron;
}

#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_SUPPORT_PARTIAL_SENTENCE_PROPAGATION
//indexToSplitVector1 = firstActivatedComponent (unordered; always assume normal order: "first" and "last" definitions do not respect (forwardPropogationSentenceData->parseSentenceReverse))
//indexToSplitVector2 = lastActivatedComponent (unordered; always assume normal order: "first" and "last" definitions do not respect (forwardPropogationSentenceData->parseSentenceReverse))
GIAtxtRelTranslatorRulesGroupNeuralNetwork* GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::splitGroupAtLastActivatedComponentUnordered(GIAtxtRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes, GIAtxtRelTranslatorRulesGroupNeuralNetwork* neuronToSplit, int indexToSplitVector1, int indexToSplitVector2)
{
	GIAtxtRelTranslatorRulesGroupNeuralNetwork* newHiddenLayerNeuron = createNewGroup();	
	GIAtxtRelTranslatorRulesGroupType* groupType = GIAtxtRelTranslatorRules.getSequenceGrammarGroupTypeDefault(GIAtxtRelTranslatorRulesGroupTypes);	
	groupType->groups.push_back(newHiddenLayerNeuron);
				
	vector<GIAtxtRelTranslatorRulesComponentNeuralNetwork*>* components = &(neuronToSplit->components);
	
	if(indexToSplitVector1 == 0)
	{
		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_SPLIT
		cout << "split at right (indexToSplitVector2) only: newHiddenLayerNeuron->groupIndex = " << newHiddenLayerNeuron->groupIndex << ", neuronToSplit->groupIndex = " << neuronToSplit->groupIndex << endl;
		#endif
		//split at right of centre (indexToSplitVector2) only - there was no unmatched first section (from GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_SUPPORT_PARTIAL_SENTENCE_PROPAGATION)
		vector<GIAtxtRelTranslatorRulesComponentNeuralNetwork*> componentsPart1(components->begin(), components->begin()+indexToSplitVector2+1);
        	vector<GIAtxtRelTranslatorRulesComponentNeuralNetwork*> componentsPart2(components->begin()+indexToSplitVector2+1, components->end());

		newHiddenLayerNeuron->components = componentsPart1;
		neuronToSplit->components = componentsPart2;
		
		GIAtxtRelTranslatorRules.updateComponentsOwnerGroupAndIndexes(newHiddenLayerNeuron, &(newHiddenLayerNeuron->components), false, NULL);
		GIAtxtRelTranslatorRules.updateComponentsOwnerGroupAndIndexes(neuronToSplit, &(neuronToSplit->components), false, NULL);	

		bool insertAtStart = true;
		if(forwardPropogationSentenceData->parseSentenceReverse)
		{
			insertAtStart = false;	//compensate for addComponentToGroup specification limitation
		}
		addComponentToGroup(forwardPropogationSentenceData, newHiddenLayerNeuron, neuronToSplit, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_GROUP, insertAtStart);	//CHECKTHIS
	}
	else if(indexToSplitVector2 == components->size()-1)
	{
		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_SPLIT
		cout << "split at left (indexToSplitVector1) only: newHiddenLayerNeuron->groupIndex = " << newHiddenLayerNeuron->groupIndex << ", neuronToSplit->groupIndex = " << neuronToSplit->groupIndex << endl;
		#endif
		//split at left of centre (indexToSplitVector1) only - there was no unmatched last section
		vector<GIAtxtRelTranslatorRulesComponentNeuralNetwork*> componentsPart1(components->begin(), components->begin()+indexToSplitVector1);
		vector<GIAtxtRelTranslatorRulesComponentNeuralNetwork*> componentsPart2(components->begin()+indexToSplitVector1, components->end());
		
		newHiddenLayerNeuron->components = componentsPart2;
		neuronToSplit->components = componentsPart1;
		
		GIAtxtRelTranslatorRules.updateComponentsOwnerGroupAndIndexes(newHiddenLayerNeuron, &(newHiddenLayerNeuron->components), false, NULL);
		GIAtxtRelTranslatorRules.updateComponentsOwnerGroupAndIndexes(neuronToSplit, &(neuronToSplit->components), false, NULL);	

		bool insertAtStart = false;
		if(forwardPropogationSentenceData->parseSentenceReverse)
		{
			insertAtStart = true;	//compensate for addComponentToGroup specification limitation
		}
		addComponentToGroup(forwardPropogationSentenceData, newHiddenLayerNeuron, neuronToSplit, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_GROUP, insertAtStart);	//CHECKTHIS
	}
	else
	{
		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_SPLIT
		cout << "split middle: newHiddenLayerNeuron->groupIndex = " << newHiddenLayerNeuron->groupIndex << ", neuronToSplit->groupIndex = " << neuronToSplit->groupIndex << endl;
		#endif
		//split middle
		vector<GIAtxtRelTranslatorRulesComponentNeuralNetwork*> componentsPart1(components->begin(), components->begin()+indexToSplitVector1);
		vector<GIAtxtRelTranslatorRulesComponentNeuralNetwork*> componentsPart2(components->begin()+indexToSplitVector1, components->begin()+indexToSplitVector2+1);	
		vector<GIAtxtRelTranslatorRulesComponentNeuralNetwork*> componentsPart3(components->begin()+indexToSplitVector2+1, components->end());		
		
		newHiddenLayerNeuron->components = componentsPart2;
		GIAtxtRelTranslatorRules.updateComponentsOwnerGroupAndIndexes(newHiddenLayerNeuron, &(newHiddenLayerNeuron->components), false, NULL);

		//neuronToSplit->components = componentsPart1;
		neuronToSplit->components.clear();
		neuronToSplit->components.insert(neuronToSplit->components.end(), componentsPart1.begin(), componentsPart1.end());
		GIAtxtRelTranslatorRules.updateComponentsOwnerGroupAndIndexes(neuronToSplit, &(neuronToSplit->components), false, NULL);
		
		bool insertAtStart = false;
		if(forwardPropogationSentenceData->parseSentenceReverse)
		{
			insertAtStart = true;	//compensate for addComponentToGroup specification limitation
		}
		addComponentToGroup(forwardPropogationSentenceData, newHiddenLayerNeuron, neuronToSplit, GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_GROUP, insertAtStart);	//CHECKTHIS
		
		neuronToSplit->components.insert(neuronToSplit->components.end(), componentsPart3.begin(), componentsPart3.end());
		GIAtxtRelTranslatorRules.updateComponentsOwnerGroupAndIndexes(neuronToSplit, &(neuronToSplit->components), false, NULL);
	}

	/*
	cout << "neuronToSplit->components.size() = " << neuronToSplit->components.size() << endl;
	cout << "newHiddenLayerNeuron->components.size() = " << newHiddenLayerNeuron->components.size() << endl;
	*/
	
	return newHiddenLayerNeuron;
}
#endif




	
bool GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::addComponentToGroup(GIAtxtRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, GIAtxtRelTranslatorRulesGroupNeuralNetwork* group, GIAtxtRelTranslatorRulesGroupNeuralNetwork* higherLevelComponentGroupOwner, int componentType, bool insertAtStart)
{
	bool result = true;

	GIAtxtRelTranslatorRulesComponentNeuralNetwork* newComponent = new GIAtxtRelTranslatorRulesComponentNeuralNetwork();

	newComponent->ownerGroup = higherLevelComponentGroupOwner;
	
	if(forwardPropogationSentenceData->parseSentenceReverse)
	{
		insertAtStart = !insertAtStart;
	}
	if(insertAtStart)
	{
		int componentIndex = GIA_TXT_REL_TRANSLATOR_SANI_COMPONENT_INDEX_FIRST;
		newComponent->componentIndex = componentIndex;
		//higherLevelComponentGroupOwner->components.push_front(newComponent);
		higherLevelComponentGroupOwner->components.insert(higherLevelComponentGroupOwner->components.begin(), newComponent);
		GIAtxtRelTranslatorRules.updateComponentsOwnerGroupAndIndexes(higherLevelComponentGroupOwner, &(higherLevelComponentGroupOwner->components), false, NULL);
	}
	else
	{
		int componentIndex = GIA_TXT_REL_TRANSLATOR_SANI_COMPONENT_INDEX_FIRST+higherLevelComponentGroupOwner->components.size();
		newComponent->componentIndex = componentIndex;
		higherLevelComponentGroupOwner->components.push_back(newComponent);
	}
			
	newComponent->componentType = componentType;
	newComponent->groupRefName = group->groupName;
	newComponent->groupTypeRefName = group->groupTypeName;
	/*
	this is only for initialisation (GIAtxtRelTranslatorSANIFormation) and parseTreeGroup components?;
	newComponent->groupRef = group;
	newComponent->groupTypeRef = group->groupType;
	*/
	if(componentType == GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_GROUP)
	{
	
	}
	else if(componentType == GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_STRING)
	{
		newComponent->stringType = GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_STRINGTYPE_LRPEXTERNALWORDLISTS;
		newComponent->wordPOStype = group->wordPOStype;	
	}
	else
	{
		cerr << "GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::addComponentToGroup error: componentType != GIA_TXT_REL_TRANSLATOR_RULES_GROUPS_COMPONENT_COMPONENTTYPE_GROUP/STRING" << endl;
		exit(EXIT_ERROR);
	}

	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_PRINT_GROUP_INDICES
	cout << "GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::addComponentToGroup: higherLevelComponentGroupOwner->groupIndex = " << higherLevelComponentGroupOwner->groupIndex << ", newComponent->componentIndex = " << newComponent->componentIndex << endl;
	#endif
	
	GIAtxtRelTranslatorSANIFormation.createGroupANNconnection(group, newComponent);
	
	return result;
}

bool GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::addComponentToGroup(GIAtxtRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, GIAtxtRelTranslatorRulesGroupNeuralNetwork* group, GIAtxtRelTranslatorRulesComponentNeuralNetwork* higherLevelComponent)
{
	bool result = true;

	GIAtxtRelTranslatorSANIFormation.createGroupANNconnection(group, higherLevelComponent);
	
	return result;
}


GIAtxtRelTranslatorRulesGroupNeuralNetwork* GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::createNewGroup()
{
	GIAtxtRelTranslatorRulesGroupNeuralNetwork* newGroup = new GIAtxtRelTranslatorRulesGroupNeuralNetwork();
	newGroup->groupName = GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_GROUP_NAME;
	newGroup->groupTypeName = GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_GROUP_TYPE_NAME;
	
	int* newNeuronIndex = GIAtxtRelTranslatorRules.getNewGroupIndex();
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_DEBUG_PRINT_GROUP_INDICES
	cout << "GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::createNewGroup - groupIndex = " << *newNeuronIndex << endl;
	#endif
	#ifdef GIA_TXT_REL_TRANSLATOR_SANI_ANN
	newGroup->initiateANNneuron("groupIndex:" + SHAREDvars.convertIntToString(*newNeuronIndex));	//GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_NEURON_NAME	//newGroup->groupTypeName + ":" + newGroup->groupName
	#endif
	newGroup->groupIndex = *newNeuronIndex;
	*newNeuronIndex = *newNeuronIndex + 1;
	
	return newGroup;
}

bool GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::findGroupDirectlyAbove(GIAtxtRelTranslatorRulesGroupNeuralNetwork* group1, GIAtxtRelTranslatorRulesGroupNeuralNetwork* group2)
{
	bool result = false;
	
	for(int i=0; i<group1->ANNfrontComponentConnectionList.size(); i++)
	{
		GIAtxtRelTranslatorRulesComponentNeuralNetwork* currentComponent = (group1->ANNfrontComponentConnectionList)[i];

		GIAtxtRelTranslatorRulesGroupNeuralNetwork* ownerGroup = currentComponent->ownerGroup;	
		GIAtxtRelTranslatorRulesComponentNeuralNetwork* ownerComponent = currentComponent;	//not used by GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR (as subcomponents are never generated)
		int componentIndex = currentComponent->componentIndex;	
		int ownerComponentIndex = componentIndex;	//not used by GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR (as subcomponents are never generated)
	
		if(ownerGroup == group2)
		{
			result = true;
		}
	}
	
	return result;
}


bool GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::verifyLastWordIndex(GIAtxtRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, GIAtxtRelTranslatorRulesGroupParseTree* parseTreeGroup, int lastWordIndex, bool* adjacent)
{
	bool result = false;
	
	if(forwardPropogationSentenceData->parseSentenceReverse)
	{
		if(parseTreeGroup->parseTreeMinWordIndex >= lastWordIndex)
		{
			result = true;
		}
		if(parseTreeGroup->parseTreeMinWordIndex == lastWordIndex)
		{
			*adjacent = true;
		}
	}
	else
	{
		if(parseTreeGroup->parseTreeMaxWordIndex <= lastWordIndex)
		{
			result = true;
		}
		if(parseTreeGroup->parseTreeMaxWordIndex == lastWordIndex)
		{
			*adjacent = true;
		}
	}

	return result;
}

#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_PREVENT_INTRASENTENCE_MATCHING
bool GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::addSubneuronsToList(vector<GIAtxtRelTranslatorRulesGroupNeuralNetwork*>* listOfHighLevelNeuronsCompleteHistory, GIAtxtRelTranslatorRulesGroupNeuralNetwork* currentNeuron)
{
	bool result = true;
	
	if(!GIAtxtRelTranslatorSANIPropagateOperations.isNeuronString(currentNeuron))
	{
		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_VERIFY_NO_CIRCULAR
		if(currentNeuron->verified)
		{
			cout << "GIAtxtRelTranslatorSANIPropagateCompactGenerateClass::addSubneuronsToList error: currentNeuron has already been parsed (circular loop detected)" << endl;
			exit(EXIT_ERROR);
		}
		currentNeuron->verified = true;
		#endif
	
		listOfHighLevelNeuronsCompleteHistory->push_back(currentNeuron);
		
		for(int i=0; i<currentNeuron->components.size(); i++)
		{
			GIAtxtRelTranslatorRulesComponentNeuralNetwork* currentComponent = currentNeuron->components[i];
			for(int j=0; j<currentComponent->ANNbackGroupConnectionList.size(); j++)
			{
				GIAtxtRelTranslatorRulesGroupNeuralNetwork* subGroup = (currentComponent->ANNbackGroupConnectionList)[j];
				addSubneuronsToList(listOfHighLevelNeuronsCompleteHistory, subGroup);
			}
		}
		
		#ifdef GIA_TXT_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_VERIFY_NO_CIRCULAR
		currentNeuron->verified = false;
		#endif
	}
	
	return result;
}
#endif

#endif