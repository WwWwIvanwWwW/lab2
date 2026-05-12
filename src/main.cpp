#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

#include "Bit.hpp"
#include "BitSequence.hpp"
#include "ImmutableArraySequence.hpp"
#include "ImmutableListSequence.hpp"
#include "MutableArraySequence.hpp"
#include "MutableListSequence.hpp"

using IntSequenceVariant =
	std::variant<std::unique_ptr<MutableArraySequence<int>>,
				 std::unique_ptr<ImmutableArraySequence<int>>,
				 std::unique_ptr<MutableListSequence<int>>,
				 std::unique_ptr<ImmutableListSequence<int>>>;

struct SequenceState {
	IntSequenceVariant intSeq;
	std::unique_ptr<BitSequence> bitSeq;
	bool isBitSequence = false;
};

Sequence<int> *GetIntSequencePtr(IntSequenceVariant &var)
{
	struct visitor {
		Sequence<int> *
		operator()(std::unique_ptr<MutableArraySequence<int>> &ptr)
		{
			return ptr.get();
		}
		Sequence<int> *
		operator()(std::unique_ptr<ImmutableArraySequence<int>> &ptr)
		{
			return ptr.get();
		}
		Sequence<int> *
		operator()(std::unique_ptr<MutableListSequence<int>> &ptr)
		{
			return ptr.get();
		}
		Sequence<int> *
		operator()(std::unique_ptr<ImmutableListSequence<int>> &ptr)
		{
			return ptr.get();
		}
	};
	return std::visit(visitor{}, var);
}

std::string IntSequenceToString(Sequence<int> *seq)
{
	if (!seq || seq->GetLength() == 0)
		return "[ ]";
	std::string result = "[ ";
	for (int i = 0; i < seq->GetLength(); ++i) {
		result += std::to_string(seq->Get(i));
		if (i + 1 < seq->GetLength())
			result += ", ";
	}
	result += " ]";
	return result;
}

std::string BitSequenceToString(BitSequence *seq)
{
	if (!seq || seq->GetLength() == 0)
		return "[ ]";
	std::string result = "[ ";
	for (int i = 0; i < seq->GetLength(); ++i) {
		result += (seq->Get(i).GetValue() ? "1" : "0");
		if (i + 1 < seq->GetLength())
			result += ", ";
	}
	result += " ]";
	return result;
}

void CreateNewMutableArray(IntSequenceVariant &target)
{
	target = std::make_unique<MutableArraySequence<int>>();
}
void CreateNewImmutableArray(IntSequenceVariant &target)
{
	target = std::make_unique<ImmutableArraySequence<int>>();
}
void CreateNewMutableList(IntSequenceVariant &target)
{
	target = std::make_unique<MutableListSequence<int>>();
}
void CreateNewImmutableList(IntSequenceVariant &target)
{
	target = std::make_unique<ImmutableListSequence<int>>();
}

int main(int, char **)
{
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow *window =
		glfwCreateWindow(1200, 800, "Sequence Tester", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	SequenceState state;
	CreateNewMutableArray(state.intSeq);
	state.isBitSequence = false;

	int currentTypeIndex = 0;
	const char *typeNames[] = {"MutableArraySequence<int>",
							   "ImmutableArraySequence<int>",
							   "MutableListSequence<int>",
							   "ImmutableListSequence<int>", "BitSequence"};

	int appendValue = 0;
	int prependValue = 0;
	int insertIndex = 0;
	int insertValue = 0;
	int getIndex = 0;
	int subStart = 0, subEnd = 0;

	int concatType = 0;
	SequenceState secondSeqForConcat;
	CreateNewMutableArray(secondSeqForConcat.intSeq);

	int bitwiseChoice = 0;
	SequenceState bitwiseOther;
	bitwiseOther.isBitSequence = true;
	bitwiseOther.bitSeq = std::make_unique<BitSequence>();

	bool showSecondSeqEditor = false;
	bool showBitwiseEditor = false;
	bool showConcatResult = false;
	bool showBitwiseResult = false;
	std::string concatResultStr;
	std::string bitwiseResultStr;
	std::string getResultMsg;
	std::string errorMsgStr;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Sequence Type Selector");
		if (ImGui::Combo("Type", &currentTypeIndex, typeNames,
						 IM_ARRAYSIZE(typeNames))) {
			if (currentTypeIndex == 4) {
				state.isBitSequence = true;
				state.bitSeq = std::make_unique<BitSequence>();
			} else {
				state.isBitSequence = false;
				switch (currentTypeIndex) {
				case 0:
					CreateNewMutableArray(state.intSeq);
					break;
				case 1:
					CreateNewImmutableArray(state.intSeq);
					break;
				case 2:
					CreateNewMutableList(state.intSeq);
					break;
				case 3:
					CreateNewImmutableList(state.intSeq);
					break;
				}
			}
		}
		ImGui::End();

		ImGui::Begin("Current Sequence State");
		if (state.isBitSequence) {
			ImGui::TextWrapped("%s",
							   BitSequenceToString(state.bitSeq.get()).c_str());
			ImGui::Text("Length: %d", state.bitSeq->GetLength());
		} else {
			Sequence<int> *seq = GetIntSequencePtr(state.intSeq);
			ImGui::TextWrapped("%s", IntSequenceToString(seq).c_str());
			ImGui::Text("Length: %d", seq->GetLength());
		}
		ImGui::End();

		ImGui::Begin("Operations");

		ImGui::InputInt("Append value", &appendValue);
		if (ImGui::Button("Append")) {
			try {
				if (state.isBitSequence) {
					state.bitSeq->Append(Bit(appendValue));
				} else {
					GetIntSequencePtr(state.intSeq)->Append(appendValue);
				}
			} catch (const std::exception &e) {
				errorMsgStr = e.what();
				ImGui::OpenPopup("Error");
			}
		}

		ImGui::InputInt("Prepend value", &prependValue);
		if (ImGui::Button("Prepend")) {
			try {
				if (state.isBitSequence) {
					state.bitSeq->Prepend(Bit(prependValue));
				} else {
					GetIntSequencePtr(state.intSeq)->Prepend(prependValue);
				}
			} catch (const std::exception &e) {
				errorMsgStr = e.what();
				ImGui::OpenPopup("Error");
			}
		}

		ImGui::InputInt("Insert index", &insertIndex);
		ImGui::InputInt("Insert value", &insertValue);
		if (ImGui::Button("InsertAt")) {
			try {
				if (state.isBitSequence) {
					state.bitSeq->InsertAt(Bit(insertValue), insertIndex);
				} else {
					GetIntSequencePtr(state.intSeq)
						->InsertAt(insertValue, insertIndex);
				}
			} catch (const std::exception &e) {
				errorMsgStr = e.what();
				ImGui::OpenPopup("Error");
			}
		}

		ImGui::InputInt("Get index", &getIndex);
		if (ImGui::Button("Get")) {
			try {
				if (state.isBitSequence) {
					Bit b = state.bitSeq->Get(getIndex);
					getResultMsg = "Value at index " +
								   std::to_string(getIndex) + ": " +
								   (b.GetValue() ? "1" : "0");
				} else {
					int val = GetIntSequencePtr(state.intSeq)->Get(getIndex);
					getResultMsg = "Value at index " +
								   std::to_string(getIndex) + ": " +
								   std::to_string(val);
				}
				ImGui::OpenPopup("GetResult");
			} catch (const std::exception &e) {
				errorMsgStr = e.what();
				ImGui::OpenPopup("Error");
			}
		}

		if (ImGui::Button("GetFirst")) {
			try {
				if (state.isBitSequence) {
					Bit b = state.bitSeq->GetFirst();
					getResultMsg =
						"First: " + std::string(b.GetValue() ? "1" : "0");
				} else {
					int val = GetIntSequencePtr(state.intSeq)->GetFirst();
					getResultMsg = "First: " + std::to_string(val);
				}
				ImGui::OpenPopup("GetResult");
			} catch (const std::exception &e) {
				errorMsgStr = e.what();
				ImGui::OpenPopup("Error");
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("GetLast")) {
			try {
				if (state.isBitSequence) {
					Bit b = state.bitSeq->GetLast();
					getResultMsg =
						"Last: " + std::string(b.GetValue() ? "1" : "0");
				} else {
					int val = GetIntSequencePtr(state.intSeq)->GetLast();
					getResultMsg = "Last: " + std::to_string(val);
				}
				ImGui::OpenPopup("GetResult");
			} catch (const std::exception &e) {
				errorMsgStr = e.what();
				ImGui::OpenPopup("Error");
			}
		}

		ImGui::InputInt("Subrange start", &subStart);
		ImGui::InputInt("Subrange end", &subEnd);
		if (ImGui::Button("GetSubsequence")) {
			try {
				if (state.isBitSequence) {
					auto sub = state.bitSeq->GetSubsequence(subStart, subEnd);
					auto *bitSub = dynamic_cast<BitSequence *>(sub.get());
					if (bitSub) {
						getResultMsg =
							"Subsequence: " + BitSequenceToString(bitSub);
					} else {
						getResultMsg = "Subsequence: [error]";
					}
				} else {
					auto sub = GetIntSequencePtr(state.intSeq)
								   ->GetSubsequence(subStart, subEnd);
					getResultMsg =
						"Subsequence: " + IntSequenceToString(sub.get());
				}
				ImGui::OpenPopup("GetResult");
			} catch (const std::exception &e) {
				errorMsgStr = e.what();
				ImGui::OpenPopup("Error");
			}
		}

		ImGui::SeparatorText("Concat");
		ImGui::Combo("Second sequence type", &concatType, typeNames,
					 IM_ARRAYSIZE(typeNames));
		if (ImGui::Button("Create/Edit second sequence")) {
			if (concatType == 4) {
				secondSeqForConcat.isBitSequence = true;
				secondSeqForConcat.bitSeq = std::make_unique<BitSequence>();
			} else {
				secondSeqForConcat.isBitSequence = false;
				switch (concatType) {
				case 0:
					CreateNewMutableArray(secondSeqForConcat.intSeq);
					break;
				case 1:
					CreateNewImmutableArray(secondSeqForConcat.intSeq);
					break;
				case 2:
					CreateNewMutableList(secondSeqForConcat.intSeq);
					break;
				case 3:
					CreateNewImmutableList(secondSeqForConcat.intSeq);
					break;
				}
			}
			showSecondSeqEditor = true;
		}

		if (showSecondSeqEditor) {
			ImGui::Begin("Second Sequence Editor", &showSecondSeqEditor);
			if (secondSeqForConcat.isBitSequence) {
				ImGui::Text("Content: %s",
							BitSequenceToString(secondSeqForConcat.bitSeq.get())
								.c_str());
				static int val = 0;
				ImGui::InputInt("Value", &val);
				if (ImGui::Button("Append to second"))
					secondSeqForConcat.bitSeq->Append(Bit(val));
			} else {
				Sequence<int> *seq =
					GetIntSequencePtr(secondSeqForConcat.intSeq);
				ImGui::Text("Content: %s", IntSequenceToString(seq).c_str());
				static int val = 0;
				ImGui::InputInt("Value", &val);
				if (ImGui::Button("Append to second"))
					seq->Append(val);
			}

			if (ImGui::Button("Concat current with second")) {
				try {
					if (state.isBitSequence &&
						secondSeqForConcat.isBitSequence) {
						auto result = state.bitSeq->Concat(
							secondSeqForConcat.bitSeq.get());
						BitSequence *bitResult =
							dynamic_cast<BitSequence *>(result.get());
						if (bitResult) {
							concatResultStr = BitSequenceToString(bitResult);
							showConcatResult = true;
						} else {
							throw std::runtime_error(
								"Concat result is not BitSequence");
						}
					} else if (!state.isBitSequence &&
							   !secondSeqForConcat.isBitSequence) {
						auto result = GetIntSequencePtr(state.intSeq)
										  ->Concat(GetIntSequencePtr(
											  secondSeqForConcat.intSeq));
						concatResultStr = IntSequenceToString(result.get());
						showConcatResult = true;
					} else {
						throw std::runtime_error(
							"Cannot concat different types (BitSequence vs int "
							"sequence)");
					}
				} catch (const std::exception &e) {
					errorMsgStr = e.what();
					ImGui::OpenPopup("Error");
				}
			}
			ImGui::End();
		}

		if (state.isBitSequence) {
			ImGui::SeparatorText("Bitwise Operations");
			ImGui::Combo("Bitwise op", &bitwiseChoice, "AND\0OR\0XOR\0NOT\0");
			if (ImGui::Button("Edit second operand")) {
				bitwiseOther.isBitSequence = true;
				bitwiseOther.bitSeq = std::make_unique<BitSequence>();
				showBitwiseEditor = true;
			}

			if (showBitwiseEditor) {
				ImGui::Begin("Bitwise Second Operand", &showBitwiseEditor);
				ImGui::Text(
					"Other: %s",
					BitSequenceToString(bitwiseOther.bitSeq.get()).c_str());
				static int bitVal = 0;
				ImGui::InputInt("Bit value", &bitVal);
				if (ImGui::Button("Append to other"))
					bitwiseOther.bitSeq->Append(Bit(bitVal));

				if (ImGui::Button("Apply bitwise")) {
					try {
						BitSequence result;
						switch (bitwiseChoice) {
						case 0:
							result = (*state.bitSeq) & (*bitwiseOther.bitSeq);
							break;
						case 1:
							result = (*state.bitSeq) | (*bitwiseOther.bitSeq);
							break;
						case 2:
							result = (*state.bitSeq) ^ (*bitwiseOther.bitSeq);
							break;
						case 3:
							result = ~(*state.bitSeq);
							break;
						}
						bitwiseResultStr = BitSequenceToString(&result);
						showBitwiseResult = true;
					} catch (const std::exception &e) {
						errorMsgStr = e.what();
						ImGui::OpenPopup("Error");
					}
				}
				ImGui::End();
			}
		}

		ImGui::SeparatorText("Utilities");
		if (ImGui::Button("Clear")) {
			try {
				if (state.isBitSequence) {
					state.bitSeq = std::make_unique<BitSequence>();
				} else {
					switch (currentTypeIndex) {
					case 0:
						CreateNewMutableArray(state.intSeq);
						break;
					case 1:
						CreateNewImmutableArray(state.intSeq);
						break;
					case 2:
						CreateNewMutableList(state.intSeq);
						break;
					case 3:
						CreateNewImmutableList(state.intSeq);
						break;
					}
				}
			} catch (const std::exception &e) {
				errorMsgStr = e.what();
				ImGui::OpenPopup("Error");
			}
		}

		if (ImGui::BeginPopupModal("GetResult", nullptr,
								   ImGuiWindowFlags_AlwaysAutoResize)) {
			ImGui::Text("%s", getResultMsg.c_str());
			if (ImGui::Button("OK"))
				ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
		}

		if (ImGui::BeginPopupModal("ConcatResult", nullptr,
								   ImGuiWindowFlags_AlwaysAutoResize)) {
			ImGui::Text("Concat result: %s", concatResultStr.c_str());
			if (ImGui::Button("OK")) {
				showConcatResult = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
		if (showConcatResult) {
			ImGui::OpenPopup("ConcatResult");
		}

		if (ImGui::BeginPopupModal("BitwiseResult", nullptr,
								   ImGuiWindowFlags_AlwaysAutoResize)) {
			ImGui::Text("Bitwise result: %s", bitwiseResultStr.c_str());
			if (ImGui::Button("OK")) {
				showBitwiseResult = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
		if (showBitwiseResult) {
			ImGui::OpenPopup("BitwiseResult");
		}

		if (ImGui::BeginPopupModal("Error", nullptr,
								   ImGuiWindowFlags_AlwaysAutoResize)) {
			ImGui::Text("Exception: %s", errorMsgStr.c_str());
			if (ImGui::Button("OK"))
				ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
		}

		ImGui::End();

		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}