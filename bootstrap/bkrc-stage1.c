/* BUNKER_CAPABILITY_JSON: {"schema_version":"bunker.self_host.capability.v1","compiler":"bkrc-self-host-bootstrap","agent_contract_version":"bunker.agent.diagnostics.v1","self_hosting_stage":"bootstrap-self-hosted-reports","ai_agent_native_diagnostics":true,"production_language_ready":false,"requires_ci_validation":true,"source_byte_spans":true,"source_excerpts":true,"structured_repair_metadata":true,"structured_parse_diagnostics":true,"diagnostic_code_registry":true,"diagnostic_phase_field":true,"diagnostic_rule_ids":true,"diagnostic_severity":true,"diagnostic_severity_counts":true,"suggested_edit_envelope":true,"import_expansion":true,"import_graph_report":true,"import_duplicate_or_cycle_summary":true,"stage1_stage2_ci_gate":true,"type_graph_report":true,"symbol_table_report":true,"name_resolver_report":true,"typecheck_report":true,"real_typechecker":true,"full_subset_type_enforcement":true,"modular_c_codegen":true,"typed_c_emission":true,"cgen_state_ref_routing":true,"hygienic_temporaries":true,"gnu_statement_expressions_locked":true,"c99_standard_portability":true,"multi_target_backend_strategy":true,"deterministic_artifact_layout":true,"supported_backends":"c, cranelift, llvm","constant_folding":true,"dead_code_elimination":true,"incremental_compilation_cache":true,"debug_info_source_mapping":true,"source_line_directives":true,"closures":true,"lambdas":true,"closure_captures":true,"code_formatter":true,"static_linter":true,"test_runner":true,"doc_generator":true,"package_manager":true,"build_cache":true,"language_server":true,"watch_mode":true,"debugger_hooks":true,"profiler_hooks":true,"coverage_tooling":true,"benchmark_tooling":true,"fuzzing_harness":true,"differential_testing":true,"property_testing":true,"stress_testing":true,"cross_platform_ci":true,"versioning_rules":true,"package_registry":true,"stdlib_documentation":true,"construct_examples":true,"migration_guides":true,"contribution_guide":true,"spec_sync":true,"roadmap_ci_gates":true,"borrow_resource_checker":true,"shell_actor_runtime":true,"declarative_view_runtime":true,"contract_verification":true,"typed_ast":true,"real_module_resolver":true,"module_cycle_path_detection":true,"visibility_boundary_enforcement":true,"semantic_validation_passes":true,"loop_control_validation":true,"unreachable_code_detection":true,"return_path_validation":true,"real_generics":true,"user_defined_adts":true,"multi_error_recovery":true,"multi_error_parse_recovery":true,"parse_recovery_synchronization":true,"diagnostic_codes":[{"code":"BKR_SELF_PARSE","rule_id":"BKR_SELF_PARSE","phase":"parse","category":"syntax","description":"Parse error with expected and actual token details."},{"code":"BKR_SELF_IMPORT_PATH","rule_id":"BKR_SELF_IMPORT_PATH","phase":"import","category":"module","description":"Invalid normalized relative import path."},{"code":"BKR_SELF_IMPORT","rule_id":"BKR_SELF_IMPORT","phase":"import","category":"module","description":"Missing imported module."},{"code":"BKR_SELF_IMPORT_CYCLE","rule_id":"BKR_SELF_IMPORT_CYCLE","phase":"import","category":"module","description":"Cyclic dependency detected in import graph."},{"code":"BKR_SELF_VISIBILITY","rule_id":"BKR_SELF_VISIBILITY","phase":"resolver","category":"visibility","description":"Attempt to access private symbol across kernel or module boundaries."},{"code":"BKR_SELF_DUPLICATE_SYMBOL","rule_id":"BKR_SELF_DUPLICATE_SYMBOL","phase":"resolver","category":"name_resolution","description":"Duplicate declaration in a scope."},{"code":"BKR_SELF_UNRESOLVED_SYMBOL","rule_id":"BKR_SELF_UNRESOLVED_SYMBOL","phase":"resolver","category":"name_resolution","description":"Unresolved identifier, function, type, struct literal, or field reference."},{"code":"BKR_SELF_TYPE_MISMATCH","rule_id":"BKR_SELF_TYPE_MISMATCH","phase":"typecheck","category":"type_system","description":"Expected/found type mismatch."},{"code":"BKR_SELF_ARITY_MISMATCH","rule_id":"BKR_SELF_ARITY_MISMATCH","phase":"typecheck","category":"type_system","description":"Function call argument count mismatch."},{"code":"BKR_SELF_ASSIGNMENT_TARGET","rule_id":"BKR_SELF_ASSIGNMENT_TARGET","phase":"typecheck","category":"type_system","description":"Invalid non-assignable assignment target."},{"code":"BKR_SELF_CONTROL_FLOW","rule_id":"BKR_SELF_CONTROL_FLOW","phase":"typecheck","category":"control_flow","description":"Invalid break or continue outside a loop."},{"code":"BKR_SELF_RETURN_PATH","rule_id":"BKR_SELF_RETURN_PATH","phase":"typecheck","category":"control_flow","description":"Non-void function can fall through without returning a value."},{"code":"BKR_SELF_UNREACHABLE_CODE","rule_id":"BKR_SELF_UNREACHABLE_CODE","phase":"typecheck","category":"control_flow","description":"Statement cannot execute because a previous statement terminates control flow."},{"code":"BKR_SELF_MATCH_PATTERN","rule_id":"BKR_SELF_MATCH_PATTERN","phase":"typecheck","category":"pattern_matching","description":"Duplicate or unreachable match pattern."},{"code":"BKR_SELF_EXHAUSTIVENESS","rule_id":"BKR_SELF_EXHAUSTIVENESS","phase":"typecheck","category":"pattern_matching","description":"Non-exhaustive match for a known finite scrutinee."},{"code":"BKR_SELF_STRUCT_LITERAL","rule_id":"BKR_SELF_STRUCT_LITERAL","phase":"typecheck","category":"data_model","description":"Invalid struct literal shape such as duplicate or missing fields."},{"code":"BKR_SELF_CONST_ASSIGNMENT","rule_id":"BKR_SELF_CONST_ASSIGNMENT","phase":"typecheck","category":"control_flow","description":"Assignment attempts to modify a top-level constant."},{"code":"BKR_SELF_AMBIGUOUS_TYPE","rule_id":"BKR_SELF_AMBIGUOUS_TYPE","phase":"typecheck","category":"type_system","description":"Expression requires a type annotation or contextual type."},{"code":"BKR_SELF_VOID_VALUE","rule_id":"BKR_SELF_VOID_VALUE","phase":"typecheck","category":"type_system","description":"Void expression is used where a value is required."},{"code":"BKR_SELF_ENTRY_POINT","rule_id":"BKR_SELF_ENTRY_POINT","phase":"typecheck","category":"program_structure","description":"Kernel entry function is missing."},{"code":"BKR_SELF_CALL_TARGET","rule_id":"BKR_SELF_CALL_TARGET","phase":"typecheck","category":"type_system","description":"Known non-function symbol is used as a call target."}],"supported_constructs":"kernel, struct, fn, const, let, fixed arrays, field access, if, else, match, Option via Some and None, Result via result_* builtins, Vec<T> handles, HashMap<K,V> handles, for ranges, while, loop, break, continue, return, primitive types, calls, casts, ternary, bitwise operators, string literals, float literals, closures, lambdas","known_limits":"byte spans only, no file span table; import graph with normalized relative path policy, exact cycle path detection, visibility boundary checking, pure typechecker, modular typed C codegen, debug source mapping, and semantic validation passes active","agent_guidance":"Use BUNKER_CAPABILITY_JSON before generating Bunker code. Use BUNKER_DIAGNOSTIC_JSON, BUNKER_RESOLVER_JSON, and BUNKER_TYPECHECK_JSON for repair tasks. Treat production_language_ready=false as requiring CI validation before release."}
*/
/* BUNKER_IMPORT_GRAPH_JSON: {"schema_version":"bunker.self_host.import_graph.v1","root_base_dir":"self-host","path_policy":"normalized_relative_forward_slash","base_directory_resolution":true,"recursive_expansion":true,"duplicate_suppression":true,"cycle_safe_expansion":true,"unique_import_count":21,"edge_count":21,"ok_edge_count":21,"missing_edge_count":0,"invalid_edge_count":0,"duplicate_edge_count":0,"duplicate_or_cycle_edge_count":0,"imports":["self-host/modules/constants.bkr","self-host/modules/kind_model.bkr","self-host/modules/ast.bkr","self-host/modules/lexer_result.bkr","self-host/modules/lexer.bkr","self-host/modules/parser_state.bkr","self-host/modules/parser.bkr","self-host/modules/cgen_state.bkr","self-host/modules/c_codegen.bkr","self-host/modules/json.bkr","self-host/modules/report_support.bkr","self-host/modules/ast_report.bkr","self-host/modules/symbol_table.bkr","self-host/modules/type_graph.bkr","self-host/modules/resolver.bkr","self-host/modules/typecheck.bkr","self-host/modules/shell.bkr","self-host/modules/view.bkr","self-host/modules/verify.bkr","self-host/modules/x86_codegen.bkr","self-host/modules/driver.bkr"],"edges":[{"from_base":"self-host","requested":"modules/constants.bkr","resolved":"self-host/modules/constants.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/kind_model.bkr","resolved":"self-host/modules/kind_model.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/ast.bkr","resolved":"self-host/modules/ast.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/lexer_result.bkr","resolved":"self-host/modules/lexer_result.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/lexer.bkr","resolved":"self-host/modules/lexer.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/parser_state.bkr","resolved":"self-host/modules/parser_state.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/parser.bkr","resolved":"self-host/modules/parser.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/cgen_state.bkr","resolved":"self-host/modules/cgen_state.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/c_codegen.bkr","resolved":"self-host/modules/c_codegen.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/json.bkr","resolved":"self-host/modules/json.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/report_support.bkr","resolved":"self-host/modules/report_support.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/ast_report.bkr","resolved":"self-host/modules/ast_report.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/symbol_table.bkr","resolved":"self-host/modules/symbol_table.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/type_graph.bkr","resolved":"self-host/modules/type_graph.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/resolver.bkr","resolved":"self-host/modules/resolver.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/typecheck.bkr","resolved":"self-host/modules/typecheck.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/shell.bkr","resolved":"self-host/modules/shell.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/view.bkr","resolved":"self-host/modules/view.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/verify.bkr","resolved":"self-host/modules/verify.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/x86_codegen.bkr","resolved":"self-host/modules/x86_codegen.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/driver.bkr","resolved":"self-host/modules/driver.bkr","status":"ok"}],"has_duplicate_or_cycle_import":false,"has_invalid_import":false,"invalid_import":"","has_missing_import":false,"missing_import":""}
*/
/* BUNKER_AST_JSON: {"schema_version":"bunker.self_host.ast.v1","representation":"bootstrap_vec_i64","source_byte_spans":true,"complete_tree":false,"truncated":true,"root":{"kind":"kernel","name":"BunkerCompiler","entry":"main","source_start":178,"source_end":910127,"span_known":true},"summary":{"source_bytes":910128,"source_lines":20617,"item_count":1773,"function_count":1558,"struct_count":59,"enum_count":7,"const_count":149},"items":[],"tree":{"kind":"kernel"}}
*/
/* BUNKER_TYPE_GRAPH_JSON: {"schema_version":"bunker.self_host.type_graph.v1","representation":"bootstrap_codegen_inference","complete":false,"declared_types":false,"local_inference":false,"truncated":true,"known_limits":"Derived from declarations plus bootstrap C codegen inference; no real Bunker typechecker, generic graph, trait constraints, exhaustiveness graph, or cross-module type graph yet. Detail arrays are omitted when interned names exceed AST_REPORT_FULL_WALK_NAME_LIMIT.","summary":{"function_count":1558,"struct_count":59,"const_count":149},"structs":[],"constants":[],"functions":[]}
*/
/* BUNKER_SYMBOL_TABLE_JSON: {"schema_version":"bunker.self_host.symbol_table.v1","representation":"bootstrap_ast_walk","complete":false,"declarations":false,"references":false,"truncated":true,"scope_model":"bootstrap kernel/function/struct scopes paired with BUNKER_RESOLVER_JSON validation","known_limits":"Derived from AST names and paired with BUNKER_RESOLVER_JSON for bootstrap duplicate/unresolved diagnostics; imports, visibility, overloads, and related definition-use spans are not complete yet. Full declaration/reference tables are omitted when interned names exceed AST_REPORT_FULL_WALK_NAME_LIMIT so stage1 compile of bkrc stays inside runner memory.","resolver_report":"BUNKER_RESOLVER_JSON","summary":{"interned_name_count":2954,"function_count":1558,"struct_count":59,"const_count":149},"declaration_table":[],"reference_table":[]}
*/
/* BUNKER_RESOLVER_JSON: {"schema_version":"bunker.self_host.resolver.v1","representation":"bootstrap_name_resolver","complete":true,"truncated":true,"duplicate_detection":true,"unresolved_detection":true,"visibility_checking":true,"import_graph_awareness":true,"cross_file_definitions":true,"related_declarations":true,"structured_repair_metadata":true,"diagnostic_phase_field":true,"diagnostic_rule_ids":true,"diagnostic_severity":true,"diagnostic_severity_counts":true,"suggested_edit_envelope":true,"has_diagnostics":false,"diagnostic_count":0,"error_count":0,"warning_count":0,"scope_model":"kernel globals plus function/block/pattern binding scopes using interned names with visibility boundaries","known_limits":"Resolver validates duplicate declarations, unresolved identifiers, calls, struct types, struct literals, and struct literal fields with related declaration span objects; import visibility boundaries and cross-file definition origins verified.","diagnostics":[]}
*/
/* BUNKER_TYPECHECK_JSON: {"schema_version":"bunker.self_host.typecheck.v1","representation":"typecheck_pass","complete":true,"truncated":true,"annotation_checks":true,"return_checks":true,"condition_checks":true,"call_argument_checks":true,"call_arity_checks":true,"call_target_checks":true,"builtin_arity_checks":true,"builtin_argument_type_checks":true,"entry_point_checks":true,"entry_signature_checks":true,"assignment_target_checks":true,"const_assignment_checks":true,"struct_field_value_checks":true,"struct_field_shape_checks":true,"ambiguous_empty_array_checks":true,"ambiguous_none_checks":true,"ambiguous_result_constructor_checks":true,"ambiguous_collection_constructor_checks":true,"index_base_type_checks":true,"index_type_checks":true,"binary_operand_checks":true,"unary_operand_checks":true,"field_access_base_checks":true,"ternary_branch_checks":true,"match_arm_type_checks":true,"match_pattern_type_checks":true,"match_pattern_semantic_checks":true,"bool_match_exhaustiveness_checks":true,"option_match_exhaustiveness_checks":true,"result_match_exhaustiveness_checks":true,"enum_match_exhaustiveness_checks":true,"scalar_match_exhaustiveness_checks":true,"finite_match_redundancy_checks":true,"array_element_type_checks":true,"loop_control_checks":true,"return_path_checks":true,"unreachable_code_checks":true,"semantic_validation_passes":true,"void_value_checks":true,"compound_void_value_checks":true,"full_value_context_void_checks":true,"typed_diagnostic_context":true,"structured_repair_metadata":true,"diagnostic_phase_field":true,"diagnostic_rule_ids":true,"diagnostic_severity":true,"diagnostic_severity_counts":true,"suggested_edit_envelope":true,"has_diagnostics":false,"diagnostic_count":0,"error_count":0,"warning_count":0,"known_limits":"Typecheck pass enforces declared annotations, return values and return paths, void value use, conditions, ternary branches, match patterns and arm values, array elements, loop-control context, unreachable statements, assignments, index bases, field-access bases, operands, calls, and struct literal shapes; full language subset semantic checking active.","diagnostics":[]}
*/
/* Generated by Bunker Compiler */
#define BKR_REQUIRED_RUNTIME_ABI_MAJOR 1
#include "runtime.h"

typedef struct _v338 {
    bkr_i64 _v339;
    bkr_i64 _v340;
} _v338;

typedef struct _v341 {
    bkr_i64 _v342;
} _v341;

typedef struct _v343 {
    bkr_i64 _v319;
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v344;
    bkr_i64 _v345;
} _v343;

typedef struct _v346 {
    bkr_i64 _v342;
} _v346;

typedef struct _v347 {
    bkr_i64 _v319;
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v344;
} _v347;

typedef struct _v348 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v349;
    bkr_i64 _v350;
    bkr_i64 _v351;
} _v348;

typedef struct _v352 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v349;
    bkr_i64 _v353;
} _v352;

typedef struct _v354 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v355;
    bkr_i64 _v356;
} _v354;

typedef struct _v357 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v358;
    bkr_i64 _v359;
    bkr_i64 _v356;
} _v357;

typedef struct _v360 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v361;
    bkr_i64 _v362;
} _v360;

typedef struct _v363 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v361;
    bkr_i64 _v355;
} _v363;

typedef struct _v364 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v355;
    bkr_i64 _v365;
    bkr_i64 _v366;
} _v364;

typedef struct _v367 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v368;
} _v367;

typedef struct _v369 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v370;
} _v369;

typedef struct _v371 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v368;
} _v371;

typedef struct _v372 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v368;
    bkr_i64 _v373;
} _v372;

typedef struct _v374 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v375;
    bkr_i64 _v376;
    bkr_i64 _v377;
} _v374;

typedef struct _v378 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v375;
    bkr_i64 _v379;
} _v378;

typedef struct _v380 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v355;
    bkr_i64 _v381;
    bkr_i64 _v382;
    bkr_i64 _v383;
    bkr_i64 _v379;
} _v380;

typedef struct _v384 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v379;
} _v384;

typedef struct _v385 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v386;
    bkr_i64 _v387;
} _v385;

typedef struct _v388 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v368;
} _v388;

typedef struct _v389 {
    bkr_i64 _v339;
    bkr_i64 _v340;
} _v389;

typedef struct _v390 {
    bkr_i64 _v339;
    bkr_i64 _v340;
} _v390;

typedef struct _v391 {
    bkr_i64 _v339;
    bkr_i64 _v340;
} _v391;

typedef struct _v392 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v375;
    bkr_i64 _v393;
    bkr_i64 _v394;
} _v392;

typedef struct _v395 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v396;
} _v395;

typedef struct _v397 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v398;
    bkr_i64 _v399;
} _v397;

typedef struct _v400 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v355;
    bkr_i64 _v401;
    bkr_i64 _v402;
    bkr_i64 _v403;
} _v400;

typedef struct _v404 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v405;
    bkr_i64 _v406;
    bkr_i64 _v407;
    bkr_i64 _v408;
} _v404;

typedef struct _v409 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v355;
    bkr_i64 _v365;
} _v409;

typedef struct _v410 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v355;
    bkr_i64 _v411;
    bkr_i64 _v412;
    bkr_i64 _v379;
} _v410;

typedef struct _v413 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v355;
    bkr_i64 _v365;
    bkr_i64 _v387;
} _v413;

typedef struct _v414 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v355;
    bkr_i64 _v365;
} _v414;

typedef struct _v415 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v355;
    bkr_i64 _v416;
} _v415;

typedef struct _v417 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v355;
    bkr_i64 _v418;
    bkr_i64 _v419;
} _v417;

typedef struct _v420 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v355;
    bkr_i64 _v421;
} _v420;

typedef struct _v422 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v355;
    bkr_i64 _v423;
    bkr_i64 _v424;
    bkr_i64 _v425;
} _v422;

typedef struct _v426 {
    bkr_i64 _v342;
} _v426;

typedef struct _v427 {
    bkr_i64 _v342;
} _v427;

typedef struct _v428 {
    bkr_i64 _v342;
} _v428;

typedef struct _v429 {
    bkr_i64 _v342;
} _v429;

typedef struct _v430 {
    bkr_i64 _v319;
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v387;
    bkr_i64 _v345;
    bkr_i64 _v431;
    bkr_i64 _v432;
} _v430;

typedef struct _v433 {
    bkr_i64 _v342;
} _v433;

typedef struct _v434 {
    bkr_i64 _v342;
} _v434;

typedef struct _v435 {
    bkr_i64 _v342;
} _v435;

typedef struct _v436 {
    bkr_i64 _v342;
} _v436;

typedef struct _v437 {
    bkr_i64 _v342;
} _v437;

typedef struct _v1187 {
    bkr_i64 _v342;
} _v1187;

typedef struct _v1234 {
    bkr_i64 _v342;
} _v1234;

typedef struct _v1531 {
    bkr_i64 _v342;
} _v1531;

typedef struct _v1897 {
    bkr_i64 _v1898;
    bkr_i64 _v612;
} _v1897;

typedef struct _v1908 {
    bkr_i64 _v423;
} _v1908;

typedef struct _v2398 {
    bkr_str _v386;
    bkr_str _v1209;
    bkr_str _v2399;
    bkr_i64 _v344;
} _v2398;

typedef struct _v2400 {
    bkr_i64 _v2401;
    bkr_i64 _v2402;
    bkr_i64 _v2403;
    bkr_i64 _v2404;
    bkr_i64 _v2405;
    bkr_i64 _v2406;
    bkr_i64 _v2407;
    bkr_i64 _v2408;
    bkr_bool _v2361;
    bkr_i64 _v2409;
    bkr_i64 _v2411;
} _v2400;

typedef struct _v2436 {
    bkr_i64 _v2437;
    bkr_i64 _v2438;
    bkr_i64 _v2439;
    bkr_i64 _v2440;
    bkr_i64 _v2441;
    bkr_i64 _v2442;
    bkr_i64 _v2443;
    bkr_i64 _v2444;
    bkr_i64 _v2445;
    bkr_i64 _v2446;
    bkr_i64 _v2447;
    bkr_i64 _v2448;
    bkr_i64 _v2449;
    bkr_i64 _v2450;
    bkr_str _v1348;
} _v2436;

typedef struct _v2498 {
    bkr_i64 _v2499;
    bkr_i64 _v2500;
    bkr_i64 _v2501;
} _v2498;

typedef struct _v2502 {
    bkr_str _v2503;
    bkr_i64 _v2504;
    bkr_i64 _v2505;
    bkr_bool _v2506;
    bkr_bool _v2507;
    bkr_str _v2508;
} _v2502;

typedef struct _v2548 {
    bkr_i64 _v2103;
    bkr_i64 _v425;
    bkr_i64 _v2549;
    bkr_i64 _v2550;
    bkr_i64 _v2551;
    bkr_i64 _v2552;
    bkr_i64 _v2553;
    bkr_i64 _v1537;
    bkr_i64 _v2554;
    bkr_i64 _v1538;
    bkr_i64 _v2555;
    bkr_i64 _v2556;
    bkr_i64 _v2557;
    bkr_i64 _v2558;
    bkr_i64 _v2559;
    bkr_i64 _v2560;
    bkr_i64 _v2561;
    bkr_i64 _v2562;
    bkr_i64 _v2563;
    bkr_i64 _v2564;
    bkr_i64 _v2565;
    bkr_i64 _v2566;
    bkr_i64 _v2567;
    bkr_i64 _v2568;
    bkr_i64 _v2569;
    bkr_i64 _v2570;
    bkr_i64 _v2571;
    bkr_i64 _v2572;
    bkr_i64 _v2573;
} _v2548;

static const bkr_i64 _v129 = 0;
static const bkr_i64 _v131 = 10;
static const bkr_i64 _v132 = 11;
static const bkr_i64 _v133 = 12;
static const bkr_i64 _v134 = 13;
static const bkr_i64 _v135 = 14;
static const bkr_i64 _v136 = 15;
static const bkr_i64 _v137 = 20;
static const bkr_i64 _v138 = 21;
static const bkr_i64 _v139 = 22;
static const bkr_i64 _v140 = 23;
static const bkr_i64 _v141 = 24;
static const bkr_i64 _v142 = 25;
static const bkr_i64 _v143 = 26;
static const bkr_i64 _v144 = 27;
static const bkr_i64 _v145 = 28;
static const bkr_i64 _v146 = 29;
static const bkr_i64 _v147 = 30;
static const bkr_i64 _v148 = 31;
static const bkr_i64 _v149 = 32;
static const bkr_i64 _v150 = 33;
static const bkr_i64 _v151 = 34;
static const bkr_i64 _v152 = 35;
static const bkr_i64 _v153 = 36;
static const bkr_i64 _v154 = 37;
static const bkr_i64 _v155 = 38;
static const bkr_i64 _v156 = 60;
static const bkr_i64 _v157 = 61;
static const bkr_i64 _v158 = 62;
static const bkr_i64 _v159 = 63;
static const bkr_i64 _v160 = 64;
static const bkr_i64 _v161 = 80;
static const bkr_i64 _v162 = 81;
static const bkr_i64 _v163 = 82;
static const bkr_i64 _v164 = 83;
static const bkr_i64 _v165 = 84;
static const bkr_i64 _v166 = 85;
static const bkr_i64 _v167 = 86;
static const bkr_i64 _v168 = 87;
static const bkr_i64 _v169 = 88;
static const bkr_i64 _v170 = 89;
static const bkr_i64 _v171 = 90;
static const bkr_i64 _v172 = 91;
static const bkr_i64 _v173 = 92;
static const bkr_i64 _v174 = 93;
static const bkr_i64 _v175 = 94;
static const bkr_i64 _v176 = 95;
static const bkr_i64 _v177 = 96;
static const bkr_i64 _v178 = 97;
static const bkr_i64 _v179 = 98;
static const bkr_i64 _v180 = 99;
static const bkr_i64 _v181 = 101;
static const bkr_i64 _v182 = 102;
static const bkr_i64 _v183 = 103;
static const bkr_i64 _v184 = 104;
static const bkr_i64 _v185 = 110;
static const bkr_i64 _v186 = 111;
static const bkr_i64 _v187 = 112;
static const bkr_i64 _v188 = 113;
static const bkr_i64 _v189 = 114;
static const bkr_i64 _v190 = 115;
static const bkr_i64 _v191 = 116;
static const bkr_i64 _v192 = 117;
static const bkr_i64 _v193 = 118;
static const bkr_i64 _v194 = 119;
static const bkr_i64 _v195 = 120;
static const bkr_i64 _v196 = 121;
static const bkr_i64 _v197 = 122;
static const bkr_i64 _v198 = 123;
static const bkr_i64 _v223 = 1;
static const bkr_i64 _v224 = 2;
static const bkr_i64 _v225 = 3;
static const bkr_i64 _v226 = 4;
static const bkr_i64 _v227 = 5;
static const bkr_i64 _v228 = 6;
static const bkr_i64 _v229 = 7;
static const bkr_i64 _v230 = 8;
static const bkr_i64 _v231 = 9;
static const bkr_i64 _v232 = 10;
static const bkr_i64 _v233 = 11;
static const bkr_i64 _v234 = 12;
static const bkr_i64 _v235 = 13;
static const bkr_i64 _v236 = 14;
static const bkr_i64 _v237 = 15;
static const bkr_i64 _v238 = 16;
static const bkr_i64 _v239 = 17;
static const bkr_i64 _v240 = 18;
static const bkr_i64 _v241 = 19;
static const bkr_i64 _v242 = 20;
static const bkr_i64 _v243 = 21;
static const bkr_i64 _v244 = 22;
static const bkr_i64 _v245 = 23;
static const bkr_i64 _v246 = 24;
static const bkr_i64 _v247 = 25;
static const bkr_i64 _v248 = 26;
static const bkr_i64 _v249 = 27;
static const bkr_i64 _v250 = 28;
static const bkr_i64 _v251 = 29;
static const bkr_i64 _v252 = 30;
static const bkr_i64 _v253 = 31;
static const bkr_i64 _v254 = 32;
static const bkr_i64 _v255 = 33;
static const bkr_i64 _v256 = 34;
static const bkr_i64 _v257 = 35;
static const bkr_i64 _v258 = 36;
static const bkr_i64 _v259 = 37;
static const bkr_i64 _v260 = 38;
static const bkr_i64 _v261 = 39;
static const bkr_i64 _v262 = 0;
static const bkr_i64 _v263 = 1;
static const bkr_i64 _v264 = 2;
static const bkr_i64 _v265 = 3;
static const bkr_i64 _v266 = 4;
static const bkr_i64 _v267 = 5;
static const bkr_i64 _v268 = 2147483647;
static const bkr_i64 _v269 = 1;
static const bkr_i64 _v270 = 2;
static const bkr_i64 _v271 = 2;
static const bkr_i64 _v272 = 3;
static const bkr_i64 _v273 = 512;
static const bkr_i64 _v283 = 1;
static const bkr_i64 _v284 = 2;
static const bkr_i64 _v285 = 3;
static const bkr_i64 _v286 = 4;
static const bkr_i64 _v287 = 5;
static const bkr_i64 _v288 = 6;
static const bkr_i64 _v289 = 7;
static const bkr_i64 _v290 = 8;
static const bkr_i64 _v291 = 9;
static const bkr_i64 _v292 = 10;
static const bkr_i64 _v293 = 11;
static const bkr_i64 _v302 = 0;
static const bkr_i64 _v303 = 1;
static const bkr_i64 _v304 = 2;
static const bkr_i64 _v305 = 3;
static const bkr_i64 _v306 = 4;
static const bkr_i64 _v307 = 5;
static const bkr_i64 _v308 = 6;
static const bkr_i64 _v309 = 7;
static const bkr_i64 _v310 = 8;
static const bkr_i64 _v311 = 9;
static const bkr_i64 _v312 = 10;
static const bkr_i64 _v313 = 11;
static const bkr_i64 _v314 = 12;
static const bkr_i64 _v315 = 13;
static const bkr_i64 _v316 = 99;
static const bkr_i64 _v2574 = 4194480;
static const bkr_i64 _v2575 = 6291456;
static const bkr_i64 _v2576 = 1048576;

bkr_str _v318(bkr_i64 _v319);
bkr_str _v324(bkr_i64 _v319);
bkr_bool _v325(bkr_i64 _v319);
bkr_str _v327(bkr_i64 _v319);
bkr_str _v328(bkr_i64 _v319);
bkr_str _v329(bkr_i64 _v330);
bkr_i64 _v331(bkr_i64 _v319);
bkr_bool _v332(bkr_i64 _v319);
bkr_bool _v333(bkr_i64 _v319);
bkr_bool _v334(bkr_i64 _v319);
bkr_bool _v335(bkr_i64 _v319);
bkr_bool _v336(bkr_i64 _v319);
_v341 _v445(bkr_i64 _v319);
_v341 _v451(_v341 _v452, bkr_i64 _v387);
_v341 _v454(_v341 _v452, bkr_i64 _v339, bkr_i64 _v340);
_v341 _v456(_v341 _v452, _v338 _v457);
_v430 _v458(bkr_i64 _v319, bkr_i64 _v387);
_v430 _v459(bkr_i64 _v319, bkr_i64 _v387, bkr_i64 _v345);
_v430 _v460(bkr_i64 _v319, bkr_i64 _v387, bkr_i64 _v345, bkr_i64 _v431);
_v430 _v461(bkr_i64 _v319, bkr_i64 _v387, bkr_i64 _v345, bkr_i64 _v431, bkr_i64 _v432);
bkr_i64 _v462(_v430 _v463);
_v430 _v464(bkr_i64 _v447);
_v433 _v467(bkr_i64 _v319, bkr_i64 _v387);
_v433 _v468(bkr_i64 _v319, bkr_i64 _v387, bkr_i64 _v345);
_v433 _v469(bkr_i64 _v319, bkr_i64 _v387, bkr_i64 _v345, bkr_i64 _v431);
_v433 _v470(bkr_i64 _v319, bkr_i64 _v387, bkr_i64 _v345, bkr_i64 _v431, bkr_i64 _v432);
_v433 _v471(_v433 _v472, bkr_i64 _v339, bkr_i64 _v340);
bkr_i64 _v474(bkr_i64 _v319);
bkr_i64 _v475(bkr_i64 _v447, bkr_i64 _v387);
bkr_i64 _v477(bkr_i64 _v447);
bkr_i64 _v478(bkr_i64 _v447);
_v338 _v479(bkr_i64 _v339, bkr_i64 _v340);
_v338 _v480(void);
bkr_i64 _v481(_v338 _v457);
bkr_i64 _v482(_v338 _v457);
bkr_bool _v483(_v338 _v457);
bkr_i64 _v484(bkr_i64 _v447);
bkr_i64 _v485(bkr_i64 _v447);
_v338 _v486(bkr_i64 _v447);
bkr_bool _v487(bkr_i64 _v447);
bkr_i64 _v488(bkr_i64 _v447, bkr_i64 _v339, bkr_i64 _v340);
bkr_i64 _v489(bkr_i64 _v447, _v338 _v457);
bkr_bool _v490(bkr_i64 _v447, bkr_i64 _v362);
bkr_i64 _v491(bkr_i64 _v447);
bkr_bool _v492(bkr_i64 _v447);
bkr_bool _v493(bkr_i64 _v447);
bkr_bool _v494(bkr_i64 _v447);
bkr_bool _v495(bkr_i64 _v447);
bkr_str _v496(bkr_i64 _v447);
bkr_bool _v497(bkr_i64 _v447);
bkr_bool _v498(bkr_i64 _v447);
bkr_bool _v499(bkr_i64 _v447);
bkr_bool _v500(bkr_i64 _v447);
bkr_bool _v501(bkr_i64 _v447);
bkr_bool _v502(bkr_i64 _v447);
bkr_bool _v503(bkr_i64 _v447);
bkr_i64 _v504(bkr_i64 _v447, bkr_i64 _v362);
bkr_i64 _v505(bkr_i64 _v447);
_v341 _v506(bkr_i64 _v342);
_v341 _v476(bkr_i64 _v447);
bkr_i64 _v507(_v341 _v452);
bkr_i64 _v453(_v341 _v452);
bkr_i64 _v509(_v341 _v452);
bkr_i64 _v510(_v341 _v452);
bkr_i64 _v511(_v341 _v452);
bkr_i64 _v512(_v341 _v452);
bkr_i64 _v508(bkr_i64 _v342);
_v341 _v513(bkr_i64 _v342);
bkr_i64 _v514(bkr_i64 _v515);
_v346 _v516(bkr_i64 _v342);
_v346 _v517(bkr_i64 _v515);
_v346 _v518(_v341 _v452);
bkr_i64 _v519(_v346 _v520);
bkr_i64 _v521(_v346 _v520);
bkr_bool _v522(_v346 _v520);
bkr_bool _v524(_v346 _v520);
bkr_i64 _v526(_v346 _v520);
_v343 _v527(_v346 _v520);
bkr_i64 _v529(_v346 _v520);
bkr_i64 _v531(_v346 _v520);
bkr_i64 _v532(_v346 _v520);
bkr_i64 _v533(_v346 _v520);
bkr_i64 _v534(_v346 _v520);
bkr_i64 _v535(_v346 _v520);
bkr_i64 _v536(bkr_i64 _v368);
_v426 _v537(bkr_i64 _v342);
_v426 _v538(bkr_i64 _v368);
_v426 _v539(_v341 _v452);
bkr_i64 _v540(_v426 _v541);
bkr_i64 _v542(_v426 _v541);
bkr_i64 _v543(_v426 _v541);
bkr_i64 _v544(_v426 _v541);
bkr_i64 _v545(_v426 _v541);
bkr_i64 _v547(_v426 _v541);
bkr_i64 _v548(bkr_i64 _v370);
_v427 _v549(bkr_i64 _v342);
_v427 _v550(bkr_i64 _v370);
_v427 _v551(_v341 _v452);
bkr_i64 _v552(_v427 _v553);
bkr_i64 _v554(_v427 _v553);
bkr_i64 _v555(_v427 _v553);
bkr_i64 _v556(bkr_i64 _v557);
_v428 _v558(bkr_i64 _v342);
_v428 _v559(bkr_i64 _v557);
_v428 _v560(_v341 _v452);
bkr_i64 _v561(_v428 _v562);
_v428 _v563(void);
bkr_bool _v565(_v428 _v562);
bkr_bool _v566(_v428 _v562);
bkr_i64 _v567(_v428 _v562);
bkr_i64 _v568(_v428 _v562);
_v338 _v569(_v426 _v541);
_v338 _v570(_v427 _v553);
_v338 _v571(_v428 _v562);
bkr_i64 _v572(_v426 _v541);
bkr_i64 _v574(_v427 _v553);
bkr_i64 _v575(_v428 _v562);
bkr_i64 _v576(bkr_i64 _v577);
_v429 _v578(bkr_i64 _v342);
_v429 _v579(bkr_i64 _v577);
_v429 _v580(_v341 _v452);
bkr_i64 _v581(_v429 _v582);
bkr_i64 _v583(_v429 _v582);
bkr_i64 _v584(_v429 _v582);
_v341 _v585(_v346 _v520);
_v341 _v546(_v426 _v541);
_v341 _v586(_v427 _v553);
_v341 _v587(_v428 _v562);
_v341 _v588(_v429 _v582);
bkr_i64 _v589(_v429 _v582);
bkr_i64 _v590(bkr_i64 _v463);
_v433 _v591(bkr_i64 _v342);
_v433 _v592(bkr_i64 _v463);
bkr_i64 _v593(_v433 _v472);
bkr_i64 _v473(_v433 _v472);
_v430 _v595(_v433 _v472);
bkr_i64 _v596(_v433 _v472);
bkr_i64 _v597(_v433 _v472);
bkr_i64 _v598(_v433 _v472);
bkr_i64 _v599(_v433 _v472);
bkr_i64 _v600(_v433 _v472);
bkr_i64 _v601(_v433 _v472);
bkr_i64 _v602(_v433 _v472);
bkr_i64 _v594(bkr_i64 _v342);
_v434 _v603(bkr_i64 _v342);
_v434 _v604(bkr_i64 _v605);
bkr_i64 _v606(_v434 _v607);
bkr_i64 _v608(_v434 _v607);
bkr_i64 _v609(bkr_i64 _v342);
_v435 _v610(bkr_i64 _v342);
_v435 _v611(bkr_i64 _v612);
bkr_i64 _v613(_v435 _v614);
bkr_i64 _v615(_v435 _v614);
bkr_i64 _v616(bkr_i64 _v342);
_v436 _v617(bkr_i64 _v342);
_v436 _v618(bkr_i64 _v406);
bkr_i64 _v619(_v436 _v620);
bkr_i64 _v621(_v436 _v620);
bkr_i64 _v622(bkr_i64 _v342);
_v437 _v623(bkr_i64 _v342);
_v437 _v624(bkr_i64 _v612);
bkr_i64 _v625(_v437 _v614);
bkr_i64 _v626(_v437 _v614);
bkr_i64 _v627(bkr_i64 _v342);
bkr_i64 _v628(bkr_i64 _v605);
bkr_i64 _v629(bkr_i64 _v612);
bkr_i64 _v630(bkr_i64 _v406);
bkr_i64 _v631(bkr_i64 _v612);
bkr_i64 _v632(bkr_i64 _v605, bkr_i64 _v447);
_v434 _v633(_v434 _v607, bkr_i64 _v447);
_v434 _v634(_v434 _v607, _v341 _v452);
_v434 _v635(_v434 _v607, _v426 _v541);
_v434 _v636(_v434 _v607, _v428 _v562);
_v434 _v637(_v434 _v607, _v429 _v582);
bkr_i64 _v638(bkr_i64 _v406, bkr_i64 _v463);
_v436 _v639(_v436 _v620, bkr_i64 _v463);
_v436 _v640(_v436 _v620, _v433 _v472);
bkr_i64 _v641(bkr_i64 _v612, bkr_i64 _v387);
_v435 _v642(_v435 _v614, bkr_i64 _v387);
bkr_i64 _v643(bkr_i64 _v447, bkr_i64 _v362);
bkr_i64 _v644(bkr_i64 _v447, bkr_i64 _v362);
_v434 _v645(bkr_i64 _v447, bkr_i64 _v362);
bkr_i64 _v646(bkr_i64 _v447, bkr_i64 _v362);
_v435 _v647(bkr_i64 _v447, bkr_i64 _v362);
bkr_i64 _v648(bkr_i64 _v447, bkr_i64 _v362);
_v436 _v649(bkr_i64 _v447, bkr_i64 _v362);
bkr_i64 _v650(bkr_i64 _v447, bkr_i64 _v362);
_v437 _v651(bkr_i64 _v447, bkr_i64 _v362);
bkr_i64 _v564(void);
bkr_bool _v523(bkr_i64 _v387);
bkr_bool _v525(bkr_i64 _v387);
bkr_i64 _v652(bkr_i64 _v387);
bkr_i64 _v653(bkr_i64 _v515);
bkr_i64 _v654(bkr_i64 _v515);
bkr_i64 _v655(bkr_i64 _v515);
bkr_i64 _v656(bkr_i64 _v515);
bkr_i64 _v657(bkr_i64 _v515);
bkr_i64 _v658(bkr_i64 _v515);
bkr_i64 _v659(bkr_i64 _v447);
_v347 _v660(_v426 _v541);
bkr_i64 _v662(_v426 _v541);
bkr_i64 _v663(_v341 _v452);
bkr_i64 _v664(bkr_i64 _v447);
bkr_i64 _v665(_v426 _v541);
bkr_i64 _v666(bkr_i64 _v447);
bkr_i64 _v667(bkr_i64 _v447);
bkr_i64 _v668(bkr_i64 _v447);
_v348 _v669(_v426 _v541);
bkr_i64 _v671(_v426 _v541);
bkr_i64 _v672(bkr_i64 _v447);
bkr_i64 _v673(bkr_i64 _v447);
bkr_i64 _v674(_v426 _v541);
bkr_i64 _v675(bkr_i64 _v447);
bkr_i64 _v676(bkr_i64 _v447);
bkr_i64 _v677(_v426 _v541);
bkr_i64 _v678(bkr_i64 _v447);
_v352 _v679(_v426 _v541);
bkr_i64 _v681(_v426 _v541);
bkr_i64 _v682(bkr_i64 _v447);
bkr_i64 _v683(bkr_i64 _v447);
bkr_i64 _v684(_v426 _v541);
bkr_i64 _v685(bkr_i64 _v447);
_v354 _v686(_v426 _v541);
bkr_i64 _v688(_v426 _v541);
bkr_i64 _v689(bkr_i64 _v447);
_v434 _v690(bkr_i64 _v447);
_v434 _v691(_v426 _v541);
bkr_i64 _v692(bkr_i64 _v447);
bkr_i64 _v693(_v426 _v541);
_v426 _v694(_v426 _v541);
bkr_i64 _v695(bkr_i64 _v447);
bkr_i64 _v696(_v426 _v541);
_v434 _v697(bkr_i64 _v447);
_v434 _v698(_v426 _v541);
bkr_i64 _v699(bkr_i64 _v447);
_v434 _v700(bkr_i64 _v447);
_v434 _v701(_v426 _v541);
bkr_i64 _v702(bkr_i64 _v447);
bkr_i64 _v703(_v426 _v541);
_v426 _v704(_v426 _v541);
bkr_i64 _v705(bkr_i64 _v447);
bkr_i64 _v706(_v426 _v541);
bkr_i64 _v707(bkr_i64 _v447);
bkr_i64 _v708(bkr_i64 _v447);
_v360 _v709(_v426 _v541);
bkr_i64 _v711(_v426 _v541);
bkr_i64 _v712(bkr_i64 _v447);
bkr_i64 _v713(bkr_i64 _v447);
bkr_i64 _v714(_v426 _v541);
bkr_i64 _v715(bkr_i64 _v447);
bkr_i64 _v716(bkr_i64 _v447);
_v363 _v717(_v426 _v541);
bkr_i64 _v719(_v426 _v541);
_v426 _v720(_v426 _v541);
bkr_i64 _v721(bkr_i64 _v447);
bkr_i64 _v722(_v426 _v541);
bkr_i64 _v723(bkr_i64 _v447);
bkr_i64 _v724(_v426 _v541);
bkr_i64 _v725(bkr_i64 _v447);
_v435 _v726(bkr_i64 _v447);
_v435 _v727(_v426 _v541);
bkr_i64 _v728(bkr_i64 _v447);
_v434 _v729(bkr_i64 _v447);
_v434 _v730(_v426 _v541);
bkr_i64 _v731(bkr_i64 _v447);
bkr_i64 _v732(bkr_i64 _v447);
bkr_i64 _v733(_v426 _v541);
bkr_i64 _v734(bkr_i64 _v447);
bkr_i64 _v735(bkr_i64 _v447);
bkr_i64 _v736(_v426 _v541);
bkr_i64 _v737(bkr_i64 _v447);
bkr_i64 _v738(bkr_i64 _v447);
bkr_i64 _v739(_v426 _v541);
bkr_i64 _v740(bkr_i64 _v447);
bkr_i64 _v741(bkr_i64 _v447);
bkr_i64 _v742(_v426 _v541);
bkr_i64 _v743(bkr_i64 _v447);
_v436 _v744(bkr_i64 _v447);
_v436 _v745(_v426 _v541);
bkr_i64 _v746(bkr_i64 _v447);
_v434 _v747(bkr_i64 _v447);
_v434 _v748(_v426 _v541);
_v435 _v749(bkr_i64 _v447);
_v435 _v750(_v426 _v541);
bkr_i64 _v751(bkr_i64 _v463);
bkr_i64 _v753(bkr_i64 _v463);
bkr_i64 _v754(bkr_i64 _v447);
_v364 _v755(_v427 _v553);
bkr_i64 _v757(_v427 _v553);
bkr_i64 _v758(bkr_i64 _v447);
bkr_i64 _v759(bkr_i64 _v447);
bkr_i64 _v760(_v427 _v553);
bkr_i64 _v761(bkr_i64 _v447);
bkr_i64 _v762(bkr_i64 _v447);
bkr_i64 _v763(_v427 _v553);
bkr_i64 _v764(bkr_i64 _v447);
bkr_i64 _v765(bkr_i64 _v447);
_v367 _v766(_v427 _v553);
bkr_i64 _v768(_v427 _v553);
bkr_i64 _v769(bkr_i64 _v447);
_v369 _v770(_v427 _v553);
bkr_i64 _v772(_v427 _v553);
_v427 _v773(_v427 _v553);
bkr_i64 _v774(bkr_i64 _v447);
_v371 _v775(_v426 _v541);
bkr_i64 _v777(_v426 _v541);
_v426 _v778(_v426 _v541);
bkr_i64 _v779(bkr_i64 _v447);
bkr_i64 _v780(bkr_i64 _v447);
bkr_i64 _v781(_v426 _v541);
bkr_i64 _v782(_v426 _v541);
_v426 _v783(_v426 _v541);
_v346 _v784(_v426 _v541);
_v374 _v785(_v427 _v553);
_v378 _v787(_v427 _v553);
_v380 _v789(_v427 _v553);
_v384 _v791(_v427 _v553);
_v385 _v793(_v427 _v553);
_v388 _v795(_v427 _v553);
_v389 _v797(_v427 _v553);
_v390 _v799(_v427 _v553);
_v391 _v801(_v429 _v582);
_v392 _v803(_v426 _v541);
_v395 _v805(_v426 _v541);
_v400 _v807(_v426 _v541);
_v404 _v809(_v426 _v541);
_v409 _v811(_v341 _v452);
_v410 _v813(_v428 _v562);
_v413 _v815(_v428 _v562);
_v414 _v817(_v341 _v452);
_v415 _v819(_v428 _v562);
_v417 _v821(_v428 _v562);
_v422 _v823(_v341 _v452);
bkr_i64 _v825(bkr_i64 _v447);
bkr_i64 _v826(bkr_i64 _v447);
bkr_i64 _v827(_v427 _v553);
bkr_i64 _v828(bkr_i64 _v447);
_v429 _v829(_v427 _v553);
bkr_i64 _v830(bkr_i64 _v447);
bkr_i64 _v831(bkr_i64 _v447);
bkr_i64 _v832(_v427 _v553);
bkr_i64 _v833(bkr_i64 _v447);
bkr_i64 _v834(_v427 _v553);
bkr_i64 _v835(bkr_i64 _v447);
bkr_i64 _v836(bkr_i64 _v447);
bkr_i64 _v837(_v427 _v553);
bkr_i64 _v838(bkr_i64 _v447);
bkr_i64 _v839(bkr_i64 _v447);
bkr_i64 _v840(_v427 _v553);
bkr_i64 _v841(bkr_i64 _v447);
bkr_i64 _v842(_v427 _v553);
bkr_i64 _v843(bkr_i64 _v447);
_v429 _v844(_v427 _v553);
bkr_i64 _v845(bkr_i64 _v447);
_v429 _v846(_v427 _v553);
bkr_i64 _v847(bkr_i64 _v447);
bkr_i64 _v848(bkr_i64 _v447);
bkr_i64 _v849(_v427 _v553);
bkr_i64 _v850(bkr_i64 _v447);
_v429 _v851(_v427 _v553);
bkr_i64 _v852(bkr_i64 _v447);
bkr_i64 _v853(bkr_i64 _v447);
bkr_i64 _v854(_v427 _v553);
bkr_i64 _v855(bkr_i64 _v447);
bkr_i64 _v856(bkr_i64 _v447);
bkr_i64 _v857(_v427 _v553);
bkr_i64 _v858(bkr_i64 _v447);
bkr_i64 _v859(bkr_i64 _v447);
bkr_i64 _v860(_v427 _v553);
bkr_i64 _v861(bkr_i64 _v447);
bkr_i64 _v862(_v341 _v452);
bkr_i64 _v863(bkr_i64 _v447);
bkr_i64 _v864(bkr_i64 _v447);
bkr_i64 _v865(_v341 _v452);
_v346 _v866(_v341 _v452);
bkr_i64 _v867(bkr_i64 _v447);
bkr_i64 _v868(_v428 _v562);
bkr_i64 _v869(bkr_i64 _v447);
_v434 _v870(bkr_i64 _v447);
_v434 _v871(_v428 _v562);
bkr_i64 _v872(bkr_i64 _v447);
bkr_i64 _v873(bkr_i64 _v447);
bkr_i64 _v874(_v428 _v562);
bkr_i64 _v875(bkr_i64 _v447);
_v429 _v876(_v428 _v562);
bkr_i64 _v877(bkr_i64 _v447);
bkr_i64 _v878(_v428 _v562);
bkr_i64 _v879(bkr_i64 _v447);
bkr_i64 _v880(bkr_i64 _v447);
bkr_i64 _v881(_v428 _v562);
bkr_i64 _v882(bkr_i64 _v447);
bkr_i64 _v883(bkr_i64 _v447);
bkr_i64 _v884(_v428 _v562);
bkr_i64 _v885(bkr_i64 _v447);
bkr_i64 _v886(_v428 _v562);
bkr_i64 _v887(bkr_i64 _v447);
_v434 _v888(bkr_i64 _v447);
_v434 _v889(_v428 _v562);
bkr_i64 _v890(bkr_i64 _v447);
bkr_i64 _v891(_v341 _v452);
bkr_i64 _v892(bkr_i64 _v447);
bkr_i64 _v893(bkr_i64 _v447);
bkr_i64 _v894(_v341 _v452);
_v346 _v895(_v341 _v452);
bkr_i64 _v896(bkr_i64 _v447);
_v434 _v897(bkr_i64 _v447);
_v434 _v898(_v341 _v452);
bkr_i64 _v899(bkr_i64 _v447);
bkr_i64 _v900(_v341 _v452);
bkr_i64 _v901(bkr_i64 _v447);
bkr_i64 _v903(_v341 _v452);
_v437 _v902(bkr_i64 _v447);
_v437 _v904(_v341 _v452);
bkr_i64 _v905(bkr_i64 _v605);
bkr_i64 _v906(_v434 _v607);
bkr_i64 _v907(bkr_i64 _v605, bkr_i64 _v362);
bkr_i64 _v908(_v434 _v607, bkr_i64 _v362);
bkr_i64 _v910(bkr_i64 _v605, bkr_i64 _v362);
bkr_i64 _v909(_v434 _v607, bkr_i64 _v362);
_v341 _v911(bkr_i64 _v605, bkr_i64 _v362);
_v341 _v912(_v434 _v607, bkr_i64 _v362);
_v428 _v913(_v434 _v607, bkr_i64 _v362);
bkr_i64 _v914(bkr_i64 _v612);
bkr_i64 _v915(_v435 _v614);
bkr_i64 _v916(bkr_i64 _v612, bkr_i64 _v362);
bkr_i64 _v917(_v435 _v614, bkr_i64 _v362);
bkr_i64 _v918(bkr_i64 _v406);
bkr_i64 _v919(_v436 _v620);
bkr_i64 _v920(bkr_i64 _v406, bkr_i64 _v362);
bkr_i64 _v921(_v436 _v620, bkr_i64 _v362);
bkr_i64 _v922(_v436 _v620, bkr_i64 _v362);
_v433 _v923(bkr_i64 _v406, bkr_i64 _v362);
_v433 _v924(_v436 _v620, bkr_i64 _v362);
bkr_i64 _v925(bkr_i64 _v0);
bkr_i64 _v926(bkr_i64 _v0, bkr_i64 _v362);
bkr_i64 _v927(bkr_i64 _v0, bkr_i64 _v362);
bkr_i64 _v928(bkr_i64 _v929);
bkr_i64 _v930(bkr_i64 _v929, bkr_i64 _v362);
bkr_i64 _v931(bkr_i64 _v932);
bkr_i64 _v933(bkr_i64 _v932, bkr_i64 _v362);
bkr_i64 _v934(bkr_i64 _v935);
bkr_i64 _v936(bkr_i64 _v935, bkr_i64 _v362);
bkr_i64 _v937(bkr_i64 _v935, bkr_i64 _v362);
bkr_i64 _v938(bkr_i64 _v939);
bkr_i64 _v940(bkr_i64 _v939, bkr_i64 _v362);
bkr_i64 _v941(bkr_i64 _v939, bkr_i64 _v362);
bkr_i64 _v942(bkr_i64 _v943);
bkr_i64 _v944(bkr_i64 _v943, bkr_i64 _v362);
bkr_i64 _v945(bkr_i64 _v943, bkr_i64 _v362);
bkr_i64 _v946(bkr_i64 _v943, bkr_i64 _v362);
bkr_i64 _v947(bkr_i64 _v447);
bkr_i64 _v948(bkr_i64 _v447, bkr_i64 _v362);
bkr_i64 _v949(bkr_i64 _v447, bkr_i64 _v362);
bkr_i64 _v950(bkr_i64 _v447, bkr_i64 _v362);
_v343 _v951(bkr_i64 _v319);
_v343 _v952(bkr_i64 _v953, bkr_i64 _v954);
_v343 _v955(bkr_i64 _v355);
_v343 _v956(bkr_i64 _v319, bkr_i64 _v344, bkr_i64 _v345);
bkr_i64 _v957(_v343 _v958);
_v343 _v528(bkr_i64 _v447);
_v346 _v959(bkr_i64 _v319);
bkr_i64 _v960(bkr_i64 _v319);
_v346 _v961(bkr_i64 _v953, bkr_i64 _v954);
bkr_i64 _v962(bkr_i64 _v953, bkr_i64 _v954);
_v346 _v963(bkr_i64 _v355);
bkr_i64 _v964(bkr_i64 _v355);
_v346 _v965(bkr_i64 _v319, bkr_i64 _v344, bkr_i64 _v345);
bkr_i64 _v966(bkr_i64 _v319, bkr_i64 _v344, bkr_i64 _v345);
bkr_i64 _v967(bkr_i64 _v319, bkr_i64 _v387);
bkr_i64 _v968(bkr_i64 _v463);
bkr_i64 _v969(bkr_i64 _v463);
bkr_i64 _v970(bkr_i64 _v463, bkr_i64 _v339, bkr_i64 _v340);
_v404 _v971(bkr_i64 _v405, bkr_i64 _v406, bkr_i64 _v407, bkr_i64 _v408);
bkr_i64 _v972(_v404 _v368);
_v404 _v810(bkr_i64 _v447);
_v426 _v973(_v426 _v974, _v436 _v620, _v434 _v975, _v435 _v976);
bkr_i64 _v977(bkr_i64 _v405, bkr_i64 _v406, bkr_i64 _v407);
_v347 _v979(bkr_i64 _v319, bkr_i64 _v344);
bkr_i64 _v980(_v347 _v981);
_v347 _v661(bkr_i64 _v447);
_v426 _v982(bkr_i64 _v319, bkr_i64 _v344);
_v426 _v983(bkr_i64 _v387);
bkr_i64 _v984(bkr_i64 _v387);
_v426 _v985(bkr_str _v387);
bkr_i64 _v986(bkr_str _v387);
_v426 _v987(bkr_i64 _v387);
bkr_i64 _v988(bkr_i64 _v387);
_v426 _v989(bkr_str _v387);
bkr_i64 _v990(bkr_str _v387);
_v395 _v991(bkr_i64 _v396);
bkr_i64 _v992(_v395 _v368);
_v395 _v806(bkr_i64 _v447);
_v426 _v993(_v434 _v994);
bkr_i64 _v995(bkr_i64 _v396);
_v397 _v996(bkr_i64 _v398, bkr_i64 _v399);
bkr_i64 _v997(_v397 _v368);
_v397 _v998(bkr_i64 _v447);
_v426 _v999(_v426 _v1000, bkr_i64 _v399);
bkr_i64 _v1001(bkr_i64 _v398, bkr_i64 _v399);
_v400 _v1002(bkr_i64 _v355, bkr_i64 _v401, bkr_i64 _v402);
_v400 _v1003(bkr_i64 _v355, bkr_i64 _v401, bkr_i64 _v402, bkr_i64 _v403);
bkr_i64 _v1004(_v400 _v368);
_v400 _v808(bkr_i64 _v447);
bkr_i64 _v1005(_v426 _v541);
_v426 _v1006(bkr_i64 _v355, _v435 _v1007, _v434 _v1008, bkr_i64 _v403);
_v426 _v1009(bkr_i64 _v355, _v435 _v1007, _v434 _v1008);
bkr_i64 _v1010(bkr_i64 _v355, bkr_i64 _v401, bkr_i64 _v402);
_v354 _v1011(bkr_i64 _v355, bkr_i64 _v356);
bkr_i64 _v1012(_v354 _v1013);
_v354 _v687(bkr_i64 _v447);
_v426 _v1014(bkr_i64 _v355, _v434 _v1015);
bkr_i64 _v1016(bkr_i64 _v355, bkr_i64 _v356);
_v357 _v1017(bkr_i64 _v358, bkr_i64 _v359, bkr_i64 _v356);
bkr_i64 _v1018(_v357 _v1013);
_v357 _v1019(bkr_i64 _v447);
_v426 _v1020(_v426 _v1021, bkr_i64 _v359, _v434 _v1015);
bkr_i64 _v1022(bkr_i64 _v358, bkr_i64 _v359, bkr_i64 _v356);
_v426 _v1023(bkr_i64 _v355);
bkr_i64 _v1024(_v426 _v1025);
bkr_i64 _v1026(bkr_i64 _v355);
_v352 _v1027(bkr_i64 _v349, bkr_i64 _v353);
bkr_i64 _v1028(_v352 _v1029);
_v352 _v680(bkr_i64 _v447);
_v426 _v1030(bkr_i64 _v349, _v426 _v1031);
bkr_i64 _v1032(bkr_i64 _v349, bkr_i64 _v353);
_v360 _v1033(bkr_i64 _v361, bkr_i64 _v362);
bkr_i64 _v1034(_v360 _v1035);
_v360 _v710(bkr_i64 _v447);
_v426 _v1036(_v426 _v1037, _v426 _v1038);
bkr_i64 _v1039(bkr_i64 _v361, bkr_i64 _v362);
_v363 _v1040(bkr_i64 _v361, bkr_i64 _v355);
bkr_i64 _v1041(_v363 _v1042);
_v363 _v718(bkr_i64 _v447);
_v426 _v1043(_v426 _v1037, bkr_i64 _v1044);
bkr_i64 _v1045(bkr_i64 _v361, bkr_i64 _v1044);
_v348 _v1046(bkr_i64 _v349, bkr_i64 _v350, bkr_i64 _v351);
bkr_i64 _v1047(_v348 _v1048);
_v348 _v670(bkr_i64 _v447);
_v426 _v1049(bkr_i64 _v349, _v426 _v1050, _v426 _v1051);
bkr_i64 _v1052(bkr_i64 _v349, bkr_i64 _v350, bkr_i64 _v351);
_v392 _v1053(bkr_i64 _v375, bkr_i64 _v393, bkr_i64 _v394);
bkr_i64 _v1054(_v392 _v368);
_v392 _v804(bkr_i64 _v447);
_v426 _v1055(_v426 _v1056, _v426 _v1057, _v426 _v1058);
bkr_i64 _v1059(bkr_i64 _v375, bkr_i64 _v393, bkr_i64 _v394);
_v364 _v1060(bkr_i64 _v355, bkr_i64 _v365, bkr_i64 _v366);
bkr_i64 _v1061(_v364 _v370);
_v364 _v756(bkr_i64 _v447);
_v427 _v1062(bkr_i64 _v355, bkr_i64 _v515, bkr_i64 _v366);
bkr_i64 _v1063(bkr_i64 _v355, bkr_i64 _v515, bkr_i64 _v366);
_v367 _v1064(bkr_i64 _v368);
bkr_i64 _v1065(_v367 _v370);
_v367 _v767(bkr_i64 _v447);
_v427 _v1066(bkr_i64 _v368);
bkr_i64 _v1067(bkr_i64 _v368);
_v369 _v1068(bkr_i64 _v370);
bkr_i64 _v1069(_v369 _v370);
_v369 _v771(bkr_i64 _v447);
_v427 _v1070(_v427 _v370);
bkr_i64 _v1071(bkr_i64 _v370);
_v371 _v1072(bkr_i64 _v368);
bkr_i64 _v1073(_v371 _v1074);
_v371 _v776(bkr_i64 _v447);
_v426 _v1075(_v426 _v368);
bkr_i64 _v1076(bkr_i64 _v368);
_v372 _v1077(bkr_i64 _v368, bkr_i64 _v373);
bkr_i64 _v1078(_v372 _v1079);
_v372 _v1080(bkr_i64 _v447);
_v426 _v1081(_v426 _v368, _v346 _v373);
bkr_i64 _v1082(bkr_i64 _v368, bkr_i64 _v373);
_v389 _v1083(void);
bkr_i64 _v1084(_v389 _v370);
_v389 _v798(bkr_i64 _v447);
_v427 _v1085(void);
bkr_i64 _v1086(void);
_v390 _v1087(void);
bkr_i64 _v1088(_v390 _v370);
_v390 _v800(bkr_i64 _v447);
_v427 _v1089(void);
bkr_i64 _v1090(void);
_v385 _v1091(bkr_i64 _v386, bkr_i64 _v387);
bkr_i64 _v1092(_v385 _v370);
_v385 _v794(bkr_i64 _v447);
_v427 _v1093(_v426 _v1094, _v426 _v1095);
bkr_i64 _v1096(bkr_i64 _v386, bkr_i64 _v387);
_v388 _v1097(bkr_i64 _v368);
bkr_i64 _v1098(_v388 _v370);
_v388 _v796(bkr_i64 _v447);
_v427 _v1099(_v426 _v541);
bkr_i64 _v1100(bkr_i64 _v368);
_v391 _v1101(void);
bkr_i64 _v1102(_v391 _v577);
_v391 _v802(bkr_i64 _v447);
_v429 _v1103(void);
bkr_i64 _v1104(void);
bkr_i64 _v1105(bkr_i64 _v577);
bkr_i64 _v1106(bkr_i64 _v577, bkr_i64 _v362);
_v427 _v1107(_v429 _v582, bkr_i64 _v362);
bkr_i64 _v1108(bkr_i64 _v577);
_v429 _v1109(_v429 _v582, _v427 _v553);
bkr_i64 _v1110(bkr_i64 _v577, bkr_i64 _v370);
_v429 _v1111(_v427 _v553);
bkr_i64 _v1112(bkr_i64 _v370);
_v374 _v1113(bkr_i64 _v375, bkr_i64 _v376, bkr_i64 _v377);
bkr_i64 _v1114(_v374 _v370);
_v374 _v786(bkr_i64 _v447);
_v427 _v1115(_v426 _v1056, _v429 _v1116, bkr_i64 _v377);
bkr_i64 _v1117(bkr_i64 _v375, bkr_i64 _v376, bkr_i64 _v377);
_v380 _v1118(bkr_i64 _v355, bkr_i64 _v381, bkr_i64 _v382, bkr_i64 _v383, bkr_i64 _v379);
bkr_i64 _v1119(_v380 _v370);
_v380 _v790(bkr_i64 _v447);
_v427 _v1120(bkr_i64 _v355, _v426 _v1121, _v426 _v1122, bkr_i64 _v383, _v429 _v1123);
bkr_i64 _v1124(bkr_i64 _v355, bkr_i64 _v381, bkr_i64 _v382, bkr_i64 _v383, bkr_i64 _v379);
_v378 _v1125(bkr_i64 _v375, bkr_i64 _v379);
bkr_i64 _v1126(_v378 _v370);
_v378 _v788(bkr_i64 _v447);
_v427 _v1127(_v426 _v1056, _v429 _v1123);
bkr_i64 _v1128(bkr_i64 _v375, bkr_i64 _v379);
_v384 _v1129(bkr_i64 _v379);
bkr_i64 _v1130(_v384 _v370);
_v384 _v792(bkr_i64 _v447);
_v427 _v1131(_v429 _v1123);
bkr_i64 _v1132(bkr_i64 _v379);
_v409 _v1133(bkr_i64 _v355, bkr_i64 _v365);
bkr_i64 _v1134(_v409 _v1135);
_v409 _v812(bkr_i64 _v447);
_v341 _v1136(bkr_i64 _v355, _v346 _v520);
bkr_i64 _v1137(bkr_i64 _v355, bkr_i64 _v515);
_v410 _v1138(bkr_i64 _v355, bkr_i64 _v411, bkr_i64 _v412, bkr_i64 _v379);
bkr_i64 _v1139(_v410 _v557);
_v410 _v814(bkr_i64 _v447);
_v428 _v1140(bkr_i64 _v355, _v434 _v1141, bkr_i64 _v1142, _v429 _v1123);
bkr_i64 _v1143(bkr_i64 _v355, bkr_i64 _v411, bkr_i64 _v1142, bkr_i64 _v379);
_v413 _v1144(bkr_i64 _v355, bkr_i64 _v365, bkr_i64 _v387);
bkr_i64 _v1145(_v413 _v557);
_v413 _v816(bkr_i64 _v447);
_v428 _v1146(bkr_i64 _v355, bkr_i64 _v515, bkr_i64 _v387);
bkr_i64 _v1147(bkr_i64 _v355, bkr_i64 _v515, bkr_i64 _v387);
_v414 _v1148(bkr_i64 _v355, bkr_i64 _v365);
bkr_i64 _v1149(_v414 _v1150);
_v414 _v818(bkr_i64 _v447);
_v341 _v1151(bkr_i64 _v1044, _v346 _v1152);
bkr_i64 _v1153(bkr_i64 _v1044, bkr_i64 _v1154);
_v415 _v1155(bkr_i64 _v355, bkr_i64 _v416);
bkr_i64 _v1156(_v415 _v557);
_v415 _v820(bkr_i64 _v447);
_v428 _v1157(bkr_i64 _v355, _v434 _v1158);
_v417 _v1159(bkr_i64 _v355, bkr_i64 _v418, bkr_i64 _v419);
bkr_i64 _v1160(_v417 _v557);
_v417 _v822(bkr_i64 _v447);
_v428 _v1161(bkr_i64 _v355, _v435 _v1162, _v435 _v1163);
bkr_i64 _v1164(_v428 _v562);
_v435 _v1165(_v428 _v562);
_v435 _v1166(_v428 _v562);
bkr_i64 _v1167(_v428 _v562);
bkr_i64 _v1170(_v428 _v562);
_v420 _v1172(bkr_i64 _v355, bkr_i64 _v421);
bkr_i64 _v1173(_v420 _v557);
_v420 _v1174(bkr_i64 _v447);
_v428 _v1175(bkr_i64 _v355, _v346 _v1094);
bkr_i64 _v1176(bkr_i64 _v355, bkr_i64 _v373);
bkr_i64 _v1177(_v428 _v562);
bkr_i64 _v1178(_v428 _v562);
bkr_i64 _v1179(bkr_i64 _v355, bkr_i64 _v416);
_v422 _v1180(bkr_i64 _v355, bkr_i64 _v423, bkr_i64 _v424, bkr_i64 _v425);
bkr_i64 _v1181(_v422 _v0);
_v422 _v824(bkr_i64 _v447);
_v341 _v1182(bkr_i64 _v355, _v434 _v1183, bkr_i64 _v1184, _v437 _v1185);
bkr_i64 _v1186(bkr_i64 _v355, bkr_i64 _v423, bkr_i64 _v1184, bkr_i64 _v425);
bkr_i64 _v1188(bkr_i64 _v1189, bkr_i64 _v425, bkr_i64 _v612, bkr_i64 _v1190);
_v1187 _v1192(bkr_i64 _v1189, bkr_i64 _v425, bkr_i64 _v612, bkr_i64 _v1190);
_v1187 _v1194(bkr_i64 _v1193);
bkr_i64 _v1191(_v1187 _v1195);
bkr_i64 _v1196(bkr_i64 _v1193);
bkr_i64 _v1197(_v1187 _v1195);
bkr_i64 _v1198(bkr_i64 _v1193);
bkr_i64 _v1199(_v1187 _v1195);
bkr_i64 _v1200(bkr_i64 _v1193);
bkr_i64 _v1201(_v1187 _v1195);
bkr_i64 _v1202(bkr_i64 _v1193);
bkr_i64 _v1203(_v1187 _v1195);
bkr_bool _v1204(bkr_i64 _v1205);
bkr_bool _v1206(bkr_i64 _v1205);
bkr_bool _v1207(bkr_i64 _v1205);
bkr_i64 _v1208(bkr_str _v1209, bkr_i64 _v1210);
bkr_i64 _v1216(bkr_i64 _v425, bkr_str _v1217);
bkr_i64 _v1218(bkr_str _v1209);
_v1187 _v1219(bkr_str _v1209);
bkr_i64 _v1235(bkr_i64 _v1236);
_v1234 _v1238(_v1187 _v1236);
_v1234 _v1243(bkr_i64 _v1239);
bkr_i64 _v1237(_v1234 _v1244);
bkr_i64 _v1245(bkr_i64 _v1246);
bkr_i64 _v1247(_v1234 _v1244);
bkr_i64 _v1248(bkr_i64 _v1246);
bkr_i64 _v1249(_v1234 _v1244);
bkr_i64 _v1250(bkr_i64 _v1246);
bkr_i64 _v1251(_v1234 _v1244);
bkr_i64 _v1252(bkr_i64 _v1246);
bkr_i64 _v1253(_v1234 _v1244);
bkr_i64 _v1254(bkr_i64 _v1246);
bkr_i64 _v1255(_v1234 _v1244);
bkr_i64 _v1256(bkr_i64 _v1246, bkr_i64 _v1210);
_v1234 _v1257(_v1234 _v1244, bkr_i64 _v1210);
bkr_i64 _v1258(bkr_i64 _v1246, bkr_i64 _v1259);
_v1234 _v1260(_v1234 _v1244, bkr_i64 _v1259);
bkr_i64 _v1261(bkr_i64 _v1246, bkr_i64 _v1210);
_v1234 _v1262(_v1234 _v1244, bkr_i64 _v1210);
bkr_i64 _v1263(bkr_i64 _v1246, bkr_i64 _v1264);
_v1234 _v1265(_v1234 _v1244, bkr_i64 _v1264);
bkr_i64 _v1266(bkr_i64 _v1246, bkr_i64 _v1267);
_v1234 _v1268(_v1234 _v1244, bkr_i64 _v1267);
bkr_i64 _v1269(bkr_i64 _v1246);
bkr_i64 _v1270(_v1234 _v1244);
bkr_i64 _v1271(bkr_i64 _v1246);
bkr_i64 _v1272(_v1234 _v1244);
bkr_i64 _v1273(bkr_i64 _v1246, bkr_i64 _v1274);
bkr_i64 _v1275(_v1234 _v1244, bkr_i64 _v1274);
bkr_i64 _v1276(bkr_i64 _v1246);
bkr_i64 _v1277(_v1234 _v1244);
bkr_bool _v1278(bkr_i64 _v1246, bkr_i64 _v1264);
bkr_bool _v1279(_v1234 _v1244, bkr_i64 _v1264);
bkr_i64 _v1281(bkr_i64 _v1246, bkr_i64 _v1264);
_v1234 _v1280(_v1234 _v1244, bkr_i64 _v1264);
bkr_str _v1287(bkr_i64 _v1246, bkr_i64 _v1035);
bkr_str _v1288(_v1234 _v1244, bkr_i64 _v1035);
bkr_i64 _v1289(_v1234 _v1244, bkr_str _v1290);
bkr_i64 _v1291(bkr_i64 _v1246, bkr_i64 _v1035);
bkr_i64 _v1292(_v1234 _v1244, bkr_i64 _v1035);
bkr_str _v1293(bkr_i64 _v1246, bkr_i64 _v1035);
bkr_str _v1294(_v1234 _v1244, bkr_i64 _v1035);
bkr_bool _v1295(bkr_i64 _v1246);
bkr_bool _v1296(_v1234 _v1244);
bkr_i64 _v1297(bkr_i64 _v1246);
bkr_i64 _v1284(_v1234 _v1244);
bkr_i64 _v1298(bkr_i64 _v1246);
bkr_i64 _v1299(_v1234 _v1244);
bkr_i64 _v1300(bkr_i64 _v1246);
bkr_i64 _v1301(_v1234 _v1244);
bkr_i64 _v1302(_v1234 _v1244);
bkr_i64 _v1303(_v1234 _v1244, bkr_i64 _v1035);
bkr_i64 _v1304(_v1234 _v1244, bkr_i64 _v1035);
bkr_i64 _v1305(_v1234 _v1244, bkr_i64 _v1035);
bkr_str _v1306(bkr_i64 _v1307);
bkr_bool _v1308(bkr_i64 _v1307);
bkr_i64 _v1309(bkr_i64 _v1246, bkr_i64 _v1210);
bkr_i64 _v1310(_v1234 _v1246, bkr_i64 _v1210);
bkr_i64 _v1311(bkr_i64 _v1246, bkr_i64 _v1210);
bkr_i64 _v1312(_v1234 _v1246, bkr_i64 _v1210);
bkr_i64 _v1313(_v1234 _v1246);
bkr_i64 _v1314(_v1234 _v1246);
bkr_i64 _v1315(_v1234 _v1246, bkr_i64 _v339);
_v338 _v1316(_v1234 _v1246, bkr_i64 _v339);
_v341 _v1317(_v1234 _v1246, _v341 _v452, bkr_i64 _v339);
_v341 _v1318(_v341 _v452, bkr_i64 _v339, bkr_i64 _v340);
_v346 _v1319(_v1234 _v1246, _v346 _v520, bkr_i64 _v339);
_v426 _v1320(_v1234 _v1246, _v426 _v541, bkr_i64 _v339);
_v426 _v1321(_v426 _v541, bkr_i64 _v339, bkr_i64 _v340);
_v427 _v1322(_v1234 _v1246, _v427 _v553, bkr_i64 _v339);
_v427 _v1323(_v427 _v553, bkr_i64 _v339, bkr_i64 _v340);
_v428 _v1324(_v1234 _v1246, _v428 _v562, bkr_i64 _v339);
_v429 _v1325(_v1234 _v1246, _v429 _v582, bkr_i64 _v339);
bkr_i64 _v1326(_v1234 _v1246, bkr_i64 _v447, bkr_i64 _v339);
_v433 _v1328(_v1234 _v1246, _v433 _v472, bkr_i64 _v339);
bkr_i64 _v1329(_v1234 _v1246, bkr_i64 _v463, bkr_i64 _v339);
bkr_i64 _v1327(_v341 _v452);
bkr_i64 _v1331(_v346 _v520);
bkr_i64 _v1332(_v426 _v541);
bkr_i64 _v1333(_v427 _v553);
bkr_i64 _v1334(_v428 _v562);
bkr_i64 _v1335(_v429 _v582);
bkr_i64 _v1330(_v433 _v472);
bkr_i64 _v1336(_v434 _v607);
_v338 _v1337(bkr_i64 _v1246);
_v338 _v1338(_v1234 _v1246);
_v338 _v1339(_v1234 _v1246, bkr_i64 _v1035);
bkr_bool _v1340(_v1234 _v1246);
bkr_bool _v1341(_v1234 _v1246);
bkr_i64 _v1342(bkr_i64 _v1246);
bkr_i64 _v1343(_v1234 _v1246);
bkr_i64 _v1344(bkr_i64 _v1246);
bkr_i64 _v1345(_v1234 _v1246);
bkr_i64 _v1346(_v1234 _v1246);
bkr_bool _v1347(_v1234 _v1246, bkr_str _v1348);
_v1234 _v1349(_v1234 _v1246);
bkr_i64 _v1351(_v1234 _v1246);
_v346 _v1352(_v1234 _v1246);
bkr_i64 _v1373(_v1234 _v1246);
_v433 _v1374(_v1234 _v1246);
bkr_i64 _v1395(_v1234 _v1246);
_v426 _v1396(_v1234 _v1246);
bkr_i64 _v1401(_v1234 _v1246);
_v426 _v1402(_v1234 _v1246);
bkr_bool _v1426(_v1234 _v1246);
bkr_i64 _v1427(_v1234 _v1246);
_v426 _v1428(_v1234 _v1246);
bkr_i64 _v1451(_v1234 _v1246);
_v426 _v1452(_v1234 _v1246);
bkr_i64 _v1454(_v1234 _v1246);
_v426 _v1455(_v1234 _v1246);
bkr_i64 _v1456(_v1234 _v1246);
_v426 _v1457(_v1234 _v1246);
bkr_i64 _v1458(_v1234 _v1246);
_v426 _v1459(_v1234 _v1246);
bkr_i64 _v1460(_v1234 _v1246);
_v426 _v1461(_v1234 _v1246);
bkr_i64 _v1462(_v1234 _v1246);
_v426 _v1463(_v1234 _v1246);
bkr_i64 _v1464(_v1234 _v1246);
_v426 _v1465(_v1234 _v1246);
bkr_i64 _v1466(_v1234 _v1246);
_v426 _v1467(_v1234 _v1246);
bkr_i64 _v1468(_v1234 _v1246);
_v426 _v1469(_v1234 _v1246);
bkr_i64 _v1470(_v1234 _v1246);
_v426 _v1471(_v1234 _v1246);
bkr_i64 _v1473(_v1234 _v1246);
_v426 _v1397(_v1234 _v1246);
bkr_i64 _v1474(_v1234 _v1246);
_v427 _v1475(_v1234 _v1246);
bkr_i64 _v1477(_v1234 _v1246);
_v427 _v1478(_v1234 _v1246);
bkr_i64 _v1480(_v1234 _v1246);
_v427 _v1481(_v1234 _v1246);
bkr_i64 _v1489(_v1234 _v1246);
_v427 _v1490(_v1234 _v1246);
bkr_i64 _v1493(_v1234 _v1246);
_v427 _v1494(_v1234 _v1246);
bkr_i64 _v1496(_v1234 _v1246);
_v429 _v1400(_v1234 _v1246);
bkr_i64 _v1500(_v1234 _v1246);
_v434 _v1501(_v1234 _v1246);
_v434 _v1502(_v1234 _v1246, bkr_i64 _v1503);
bkr_i64 _v1512(_v1234 _v1246);
_v428 _v1513(_v1234 _v1246);
bkr_i64 _v1515(_v1234 _v1246);
_v428 _v1516(_v1234 _v1246);
bkr_i64 _v1518(_v1234 _v1246);
_v428 _v1519(_v1234 _v1246);
bkr_i64 _v1520(_v1234 _v1246);
_v428 _v1521(_v1234 _v1246);
bkr_i64 _v1524(bkr_i64 _v1246);
bkr_i64 _v1526(_v1234 _v1246);
_v428 _v1527(_v1234 _v1246);
bkr_i64 _v1525(_v1234 _v1246);
bkr_i64 _v1532(bkr_str _v1533, bkr_i64 _v425);
_v1531 _v1535(bkr_str _v1533, bkr_i64 _v425);
_v1531 _v1549(_v1531 _v1550, bkr_i64 _v1551);
bkr_i64 _v1552(_v1531 _v1550);
_v1531 _v1548(bkr_i64 _v1239);
bkr_i64 _v1534(_v1531 _v1550);
bkr_i64 _v1553(bkr_i64 _v1239);
bkr_i64 _v1554(_v1531 _v1550);
bkr_i64 _v1555(bkr_i64 _v1239);
bkr_i64 _v1556(_v1531 _v1550);
bkr_i64 _v1557(bkr_i64 _v1239, bkr_i64 _v1558);
_v1531 _v1559(_v1531 _v1550, bkr_i64 _v1558);
bkr_i64 _v1560(bkr_i64 _v1239);
bkr_i64 _v1561(_v1531 _v1550);
bkr_i64 _v1562(_v1531 _v1550, bkr_str _v1290);
bkr_i64 _v1563(bkr_i64 _v1239);
bkr_i64 _v1564(_v1531 _v1550);
bkr_i64 _v1565(bkr_i64 _v1239);
bkr_i64 _v1566(_v1531 _v1550);
bkr_i64 _v1567(bkr_i64 _v1239);
bkr_i64 _v1568(_v1531 _v1550);
bkr_i64 _v1569(bkr_i64 _v1239);
bkr_i64 _v1570(_v1531 _v1550);
bkr_i64 _v1571(bkr_i64 _v1239);
bkr_i64 _v1572(_v1531 _v1550);
bkr_i64 _v1573(bkr_i64 _v1239);
bkr_i64 _v1574(_v1531 _v1550);
bkr_i64 _v1575(bkr_i64 _v1239);
bkr_i64 _v1576(_v1531 _v1550);
bkr_i64 _v1577(bkr_i64 _v1239);
bkr_i64 _v1578(_v1531 _v1550);
bkr_i64 _v1579(bkr_i64 _v1239);
bkr_i64 _v1580(_v1531 _v1550);
bkr_i64 _v1581(bkr_i64 _v1239, bkr_str _v1582);
_v1531 _v1583(_v1531 _v1550, bkr_str _v1582);
bkr_i64 _v1585(bkr_i64 _v1239);
_v1531 _v1586(_v1531 _v1550);
bkr_i64 _v1587(bkr_i64 _v1239);
_v1531 _v1588(_v1531 _v1550);
bkr_i64 _v1589(bkr_i64 _v1239);
_v1531 _v1590(_v1531 _v1550);
bkr_i64 _v1591(bkr_i64 _v1239, bkr_i64 _v355, bkr_i64 _v319);
_v1531 _v1592(_v1531 _v1550, bkr_i64 _v355, bkr_i64 _v319);
_v1531 _v1594(_v1531 _v1550, bkr_i64 _v355, bkr_i64 _v319, bkr_i64 _v1503);
bkr_i64 _v1593(_v1531 _v1550);
bkr_i64 _v1596(_v1531 _v1550, bkr_i64 _v355);
bkr_i64 _v1597(_v1531 _v1550);
_v1531 _v1598(_v1531 _v1550, bkr_i64 _v1599);
bkr_str _v1600(_v1531 _v1550);
_v1531 _v1601(_v1531 _v1550, bkr_str _v1142);
bkr_i64 _v1602(_v1531 _v1550);
bkr_str _v1604(_v1531 _v1550, bkr_str _v1584);
bkr_i64 _v1606(bkr_i64 _v1239, bkr_i64 _v355, bkr_i64 _v319);
_v1531 _v1607(_v1531 _v1550, bkr_i64 _v355, bkr_i64 _v319);
bkr_i64 _v1608(bkr_i64 _v1239, bkr_i64 _v355, bkr_i64 _v319);
_v1531 _v1609(_v1531 _v1550, bkr_i64 _v355, bkr_i64 _v319);
bkr_i64 _v1610(bkr_i64 _v1239, bkr_i64 _v355, bkr_i64 _v953, bkr_i64 _v954);
_v1531 _v1611(_v1531 _v1550, bkr_i64 _v355, bkr_i64 _v953, bkr_i64 _v954);
bkr_i64 _v1612(bkr_i64 _v1239, bkr_i64 _v355);
bkr_i64 _v1613(_v1531 _v1550, bkr_i64 _v355);
bkr_i64 _v1614(bkr_i64 _v1239, bkr_i64 _v355);
bkr_i64 _v1615(_v1531 _v1550, bkr_i64 _v355);
bkr_i64 _v1616(bkr_i64 _v425, bkr_i64 _v1617, bkr_i64 _v355);
bkr_i64 _v1618(bkr_i64 _v1239, bkr_i64 _v355);
bkr_i64 _v1619(_v1531 _v1550, bkr_i64 _v355);
bkr_i64 _v1621(bkr_i64 _v1239, bkr_i64 _v355);
bkr_i64 _v1622(_v1531 _v1550, bkr_i64 _v355);
bkr_bool _v1623(_v1531 _v1239, bkr_i64 _v355);
bkr_bool _v1624(_v1531 _v1239, bkr_str _v1626);
bkr_i64 _v1627(_v1531 _v1239, bkr_str _v1626, bkr_str _v1628);
bkr_i64 _v1630(_v1531 _v1239, bkr_str _v1626, bkr_str _v1628, bkr_i64 _v1631);
bkr_bool _v1633(_v1531 _v1239, bkr_str _v1626);
bkr_str _v1634(bkr_i64 _v319);
bkr_str _v1635(bkr_i64 _v1239, bkr_i64 _v515);
bkr_str _v1636(_v1531 _v1239, _v346 _v520);
bkr_str _v1638(bkr_i64 _v349);
bkr_str _v1625(bkr_i64 _v425, bkr_i64 _v1035);
bkr_str _v1639(bkr_str _v1640);
bkr_str _v1641(bkr_i64 _v425, bkr_i64 _v1035);
bkr_str _v1644(bkr_i64 _v1239, bkr_i64 _v1035);
bkr_str _v1637(_v1531 _v1239, bkr_i64 _v1035);
bkr_i64 _v1645(bkr_i64 _v515);
bkr_i64 _v1646(_v346 _v520);
bkr_i64 _v1647(bkr_i64 _v515);
bkr_i64 _v1648(_v346 _v520);
bkr_i64 _v1649(bkr_i64 _v515);
bkr_i64 _v1650(_v346 _v520);
bkr_i64 _v1651(bkr_str _v1640);
bkr_i64 _v1652(bkr_i64 _v1239, bkr_i64 _v368);
bkr_i64 _v1654(bkr_i64 _v1239, bkr_i64 _v1655);
bkr_i64 _v1656(_v1531 _v1239, bkr_i64 _v1655);
_v346 _v1657(_v1531 _v1239, bkr_i64 _v1503, bkr_i64 _v1658);
bkr_i64 _v1659(_v1531 _v1239, bkr_i64 _v1503, bkr_i64 _v1631);
bkr_bool _v1660(_v1531 _v1239, bkr_i64 _v1503);
bkr_bool _v1661(_v1531 _v1239, bkr_i64 _v1503);
bkr_str _v1664(_v1531 _v1239, bkr_i64 _v1503, bkr_str _v1665);
_v346 _v1668(_v1531 _v1239, bkr_i64 _v1529);
bkr_i64 _v1653(_v1531 _v1239, _v426 _v541);
bkr_str _v1689(bkr_i64 _v1239, bkr_i64 _v370);
bkr_str _v1690(_v1531 _v1239, _v427 _v553);
bkr_str _v1702(bkr_i64 _v1239, bkr_str _v1703, bkr_i64 _v379);
bkr_str _v1704(_v1531 _v1239, bkr_str _v1703, _v341 _v1123);
bkr_str _v1708(bkr_i64 _v1239, bkr_str _v1709, bkr_i64 _v463);
bkr_str _v1710(_v1531 _v1239, bkr_str _v1709, _v433 _v472);
bkr_str _v1714(bkr_i64 _v1239, bkr_str _v1709, bkr_i64 _v463, bkr_i64 _v1715);
bkr_str _v1716(_v1531 _v1239, bkr_str _v1709, _v433 _v472, bkr_i64 _v1715);
bkr_str _v1735(bkr_i64 _v1239, bkr_i64 _v368);
bkr_str _v1736(_v1531 _v1239, _v426 _v541);
bkr_bool _v1743(bkr_i64 _v1239, bkr_i64 _v368);
bkr_bool _v1744(_v1531 _v1239, _v426 _v541);
bkr_str _v1745(bkr_i64 _v1239, bkr_i64 _v368);
bkr_str _v1746(_v1531 _v1239, _v426 _v541);
bkr_str _v1747(bkr_i64 _v1239, bkr_i64 _v515, bkr_i64 _v366);
bkr_str _v1701(_v1531 _v1239, bkr_i64 _v515, _v426 _v1693);
bkr_str _v1749(bkr_i64 _v1239, bkr_i64 _v368);
bkr_str _v1692(_v1531 _v1239, _v426 _v541);
bkr_i64 _v1832(bkr_i64 _v1239, bkr_i64 _v370);
_v1531 _v1785(_v1531 _v1239, _v427 _v553);
bkr_str _v1750(bkr_str _v1640);
bkr_i64 _v1846(bkr_i64 _v1239, bkr_i64 _v577);
_v1531 _v1837(_v1531 _v1239, _v429 _v582);
bkr_str _v1847(bkr_i64 _v1239, bkr_i64 _v929);
bkr_str _v1848(_v1531 _v1239, _v428 _v1514);
bkr_i64 _v1853(bkr_i64 _v1239, bkr_i64 _v929);
_v1531 _v1854(_v1531 _v1239, _v428 _v1514);
bkr_i64 _v1855(bkr_i64 _v1239, bkr_i64 _v929);
_v1531 _v1856(_v1531 _v1239, _v428 _v1514);
bkr_i64 _v1861(bkr_i64 _v1239, bkr_i64 _v1862);
_v1531 _v1863(_v1531 _v1239, _v428 _v1517);
bkr_i64 _v1866(bkr_i64 _v1239, bkr_i64 _v932);
_v1531 _v1867(_v1531 _v1239, _v428 _v1523);
bkr_i64 _v1869(bkr_i64 _v1239, bkr_i64 _v0);
_v1531 _v1870(_v1531 _v1239, _v341 _v1530);
bkr_i64 _v1871(bkr_i64 _v1239, bkr_i64 _v0);
_v1531 _v1872(_v1531 _v1239, _v341 _v1530);
bkr_i64 _v1873(bkr_i64 _v1239, bkr_i64 _v0);
_v1531 _v1874(_v1531 _v1239, _v341 _v1530);
_v1531 _v1875(_v1531 _v1239, _v341 _v1530);
bkr_i64 _v1878(bkr_i64 _v1239, bkr_i64 _v0);
_v1531 _v1879(_v1531 _v1239, _v341 _v1530);
bkr_i64 _v1880(bkr_i64 _v1239, bkr_i64 _v0);
_v1531 _v1881(_v1531 _v1239, _v341 _v1530);
bkr_str _v1882(bkr_i64 _v0);
bkr_str _v1883(_v341 _v1530);
bkr_str _v1886(bkr_str _v1640);
bkr_str _v1888(bkr_str _v1383);
bkr_str _v1889(bkr_i64 _v1383);
bkr_str _v1890(bkr_bool _v1383);
bkr_str _v1891(void);
bkr_str _v1892(bkr_str _v1826, bkr_str _v1383);
bkr_str _v1893(bkr_str _v1826, bkr_i64 _v1383);
bkr_str _v1894(bkr_str _v1826, bkr_bool _v1383);
bkr_str _v1895(bkr_str _v1826, bkr_str _v1896);
_v1897 _v1899(void);
void _v1901(_v1897 _v1902, bkr_str _v1826, bkr_str _v1383);
void _v1903(_v1897 _v1902, bkr_str _v1826, bkr_i64 _v1383);
void _v1904(_v1897 _v1902, bkr_str _v1826, bkr_bool _v1383);
void _v1905(_v1897 _v1902, bkr_str _v1826, bkr_str _v1896);
bkr_str _v1906(_v1897 _v1902);
_v1908 _v1909(void);
void _v1911(_v1908 _v1912, bkr_str _v1383);
void _v1913(_v1908 _v1912, bkr_i64 _v1383);
void _v1914(_v1908 _v1912, bkr_bool _v1383);
void _v1915(_v1908 _v1912, bkr_str _v1896);
bkr_str _v1916(_v1908 _v1912);
bkr_i64 _v1917(bkr_str _v1918, bkr_i64 _v1919);
bkr_str _v1920(bkr_str _v1918, bkr_str _v1826);
bkr_str _v1926(bkr_str _v1918, bkr_str _v1826);
bkr_i64 _v1927(bkr_str _v1918, bkr_str _v1826);
bkr_bool _v1928(bkr_str _v1918, bkr_str _v1826);
bkr_bool _v1929(bkr_str _v1918, bkr_str _v1826);
bkr_i64 _v1930(bkr_str _v1931);
bkr_bool _v1933(_v341 _v1530);
bkr_str _v1934(bkr_str _v1640);
bkr_str _v1935(bkr_str _v319, bkr_i64 _v1936, bkr_i64 _v1937, bkr_str _v1938, bkr_str _v1939, bkr_str _v1940);
bkr_str _v1942(void);
bkr_str _v1943(bkr_str _v1944);
bkr_str _v1945(bkr_i64 _v425, bkr_i64 _v1035);
bkr_i64 _v1946(void);
bkr_str _v1947(bkr_i64 _v1239);
bkr_i64 _v1949(bkr_i64 _v1239);
bkr_i64 _v1950(bkr_i64 _v1239, bkr_str _v1948);
bkr_bool _v1951(bkr_i64 _v612, bkr_i64 _v387);
bkr_i64 _v1952(void);
bkr_i64 _v1953(bkr_i64 _v612);
bkr_i64 _v1955(bkr_i64 _v612, bkr_i64 _v387);
bkr_i64 _v1956(bkr_str _v1209);
bkr_i64 _v1957(bkr_i64 _v557);
bkr_i64 _v1958(_v428 _v562);
bkr_i64 _v1959(bkr_i64 _v557);
bkr_i64 _v1960(_v428 _v562);
bkr_i64 _v1961(bkr_i64 _v557);
bkr_i64 _v1962(_v428 _v562);
bkr_i64 _v1963(bkr_i64 _v557);
bkr_i64 _v1964(_v428 _v562);
bkr_str _v1965(bkr_i64 _v425, bkr_i64 _v557);
bkr_str _v1966(bkr_i64 _v425, _v428 _v562);
bkr_i64 _v1968(bkr_i64 _v423, bkr_i64 _v319);
bkr_i64 _v1969(_v434 _v1183, bkr_i64 _v319);
bkr_str _v1970(bkr_i64 _v0);
bkr_str _v1971(bkr_i64 _v425, _v434 _v1183);
bkr_str _v1972(bkr_i64 _v425, bkr_i64 _v605);
bkr_str _v1973(bkr_i64 _v425, _v434 _v607);
bkr_str _v1975(bkr_i64 _v425, bkr_i64 _v1976);
bkr_str _v1977(bkr_i64 _v425, bkr_i64 _v577);
bkr_str _v1978(bkr_i64 _v425, _v429 _v582);
bkr_str _v1979(bkr_i64 _v425, bkr_i64 _v463);
bkr_str _v1980(bkr_i64 _v425, _v433 _v472);
bkr_str _v1981(bkr_i64 _v425, bkr_i64 _v406, bkr_i64 _v407);
bkr_str _v1982(bkr_i64 _v425, _v436 _v620, _v434 _v975);
bkr_str _v1983(bkr_i64 _v425, bkr_i64 _v447);
bkr_str _v1984(bkr_i64 _v425, _v426 _v541);
bkr_str _v1985(bkr_i64 _v425, bkr_i64 _v1986);
bkr_str _v1987(bkr_i64 _v425, bkr_i64 _v1599);
bkr_str _v1988(bkr_i64 _v425, bkr_i64 _v447);
bkr_str _v1974(bkr_i64 _v425, _v341 _v452);
bkr_str _v1990(bkr_str _v1209, bkr_i64 _v0);
bkr_str _v1996(bkr_str _v1209, bkr_i64 _v0);
bkr_str _v1997(bkr_str _v1193, bkr_str _v557);
bkr_str _v1998(bkr_str _v1193, bkr_str _v423);
bkr_str _v2000(bkr_str _v319, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v1936, bkr_i64 _v1937);
bkr_str _v2002(bkr_str _v319, bkr_str _v1348, bkr_str _v2001, _v341 _v452);
bkr_str _v2003(bkr_str _v319, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v447);
bkr_str _v2004(bkr_str _v319, bkr_str _v1348, bkr_str _v2001, _v433 _v472);
bkr_str _v2005(bkr_str _v319, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v463);
bkr_str _v2006(bkr_i64 _v425, bkr_i64 _v515, bkr_str _v2001);
bkr_str _v2007(bkr_i64 _v425, _v346 _v520, bkr_str _v2001);
bkr_str _v2008(bkr_i64 _v425, bkr_i64 _v463, bkr_str _v2001);
bkr_str _v2009(bkr_i64 _v425, _v433 _v472, bkr_str _v2001);
bkr_str _v2013(bkr_i64 _v425, bkr_i64 _v1655, bkr_str _v2001);
bkr_str _v2014(bkr_i64 _v425, _v426 _v541, bkr_str _v2001);
bkr_str _v2017(bkr_i64 _v425, bkr_i64 _v370, bkr_str _v2001);
bkr_str _v2018(bkr_i64 _v425, _v427 _v553, bkr_str _v2001);
bkr_str _v2019(bkr_i64 _v425, bkr_i64 _v577, bkr_str _v2001);
bkr_str _v2015(bkr_i64 _v425, _v429 _v582, bkr_str _v2001);
bkr_str _v2020(bkr_i64 _v0, bkr_i64 _v557, bkr_str _v2021);
bkr_str _v2022(_v341 _v1530, _v428 _v562, bkr_str _v2021);
bkr_str _v2026(bkr_i64 _v0);
bkr_str _v2027(_v341 _v1530);
bkr_str _v2028(bkr_i64 _v425, bkr_i64 _v1655, bkr_str _v2001);
bkr_str _v2029(bkr_i64 _v425, _v426 _v541, bkr_str _v2001);
bkr_str _v2031(bkr_i64 _v425, bkr_i64 _v370, bkr_str _v2001);
bkr_str _v2032(bkr_i64 _v425, _v427 _v553, bkr_str _v2001);
bkr_str _v2033(bkr_i64 _v425, bkr_i64 _v577, bkr_str _v2001);
bkr_str _v2030(bkr_i64 _v425, _v429 _v582, bkr_str _v2001);
bkr_str _v2034(bkr_i64 _v0, bkr_i64 _v557, bkr_str _v2021);
bkr_str _v2035(_v341 _v1530, _v428 _v562, bkr_str _v2021);
bkr_str _v2036(bkr_i64 _v0);
bkr_str _v2037(_v341 _v1530);
bkr_str _v2038(bkr_i64 _v0);
bkr_str _v2041(bkr_i64 _v0);
bkr_str _v2042(bkr_i64 _v319, bkr_str _v1209);
bkr_str _v2043(bkr_i64 _v425, bkr_i64 _v515, bkr_str _v1209);
bkr_str _v2044(bkr_i64 _v425, _v346 _v520, bkr_str _v1209);
bkr_str _v2045(bkr_i64 _v1239, bkr_i64 _v1655);
bkr_str _v2046(_v1531 _v1239, bkr_i64 _v1655);
bkr_str _v2047(_v1531 _v1239, _v426 _v541);
bkr_i64 _v2048(bkr_i64 _v1239, bkr_i64 _v515, bkr_i64 _v1655);
bkr_i64 _v2049(_v1531 _v1239, bkr_i64 _v515, bkr_i64 _v1655);
bkr_i64 _v2051(bkr_i64 _v1239, bkr_i64 _v355, bkr_i64 _v515);
_v1531 _v2052(_v1531 _v1239, bkr_i64 _v355, _v346 _v520);
bkr_i64 _v2053(bkr_i64 _v0);
_v1531 _v2054(_v341 _v1530);
bkr_str _v2056(bkr_str _v1193, bkr_str _v557);
bkr_str _v2057(bkr_str _v1193, bkr_str _v423);
bkr_str _v2058(bkr_i64 _v425, bkr_i64 _v1135);
bkr_str _v2059(bkr_i64 _v425, _v341 _v1507);
bkr_str _v2060(bkr_i64 _v425, bkr_i64 _v411);
bkr_str _v2061(bkr_i64 _v425, _v434 _v1141);
bkr_str _v2062(bkr_i64 _v425, bkr_i64 _v1150);
bkr_str _v2063(bkr_i64 _v425, _v341 _v1432);
bkr_str _v2064(bkr_i64 _v425, bkr_i64 _v416);
bkr_str _v2065(bkr_i64 _v425, _v434 _v1158);
bkr_str _v2066(bkr_i64 _v425, bkr_i64 _v557);
bkr_str _v2067(bkr_i64 _v425, _v428 _v562);
bkr_str _v2068(bkr_i64 _v0);
bkr_str _v2069(_v341 _v1530);
bkr_str _v2070(bkr_i64 _v1239, bkr_i64 _v425, bkr_i64 _v557);
bkr_str _v2071(_v1531 _v1239, bkr_i64 _v425, _v428 _v562);
bkr_str _v2072(bkr_i64 _v0, bkr_i64 _v1239);
bkr_str _v2073(_v341 _v1530, _v1531 _v1239);
bkr_str _v2074(bkr_i64 _v1239, bkr_i64 _v425, bkr_i64 _v370);
bkr_str _v2075(_v1531 _v1239, bkr_i64 _v425, _v427 _v553);
bkr_i64 _v2078(bkr_i64 _v1239, bkr_i64 _v370);
_v1531 _v2079(_v1531 _v1239, _v427 _v553);
bkr_str _v2080(bkr_i64 _v1239, bkr_i64 _v425, bkr_i64 _v577);
bkr_str _v2081(_v1531 _v1239, bkr_i64 _v425, _v429 _v582);
bkr_str _v2082(bkr_i64 _v1239, bkr_i64 _v370);
bkr_str _v2083(_v1531 _v1239, _v427 _v553);
bkr_str _v2084(bkr_i64 _v1239, bkr_i64 _v425, bkr_i64 _v577);
bkr_str _v2085(_v1531 _v1239, bkr_i64 _v425, _v429 _v582);
bkr_i64 _v2086(bkr_i64 _v0, bkr_i64 _v929);
_v1531 _v2087(_v341 _v1530, _v428 _v1514);
bkr_str _v2091(bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v557);
bkr_str _v2092(_v341 _v1530, bkr_i64 _v425, _v428 _v562);
bkr_str _v2095(bkr_i64 _v0);
bkr_str _v2096(_v341 _v1530);
bkr_str _v2097(bkr_i64 _v0);
bkr_str _v2101(bkr_i64 _v0);
bkr_str _v2102(bkr_str _v319, bkr_str _v2103, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v1936, bkr_i64 _v1937, bkr_str _v1264, bkr_str _v1267, bkr_str _v2104);
bkr_str _v2105(bkr_str _v319, bkr_str _v2103, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v1936, bkr_i64 _v1937, bkr_str _v1264, bkr_str _v1267, bkr_str _v2106, bkr_str _v2104);
bkr_str _v2107(bkr_str _v319, bkr_str _v2103, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v447, bkr_str _v1264, bkr_str _v1267, bkr_str _v2104);
bkr_str _v2108(bkr_str _v319, bkr_str _v2103, bkr_str _v1348, bkr_str _v2001, _v341 _v452, bkr_str _v1264, bkr_str _v1267, bkr_str _v2104);
bkr_str _v2109(bkr_str _v319, bkr_str _v2103, bkr_str _v1348, bkr_str _v2001, _v341 _v452, bkr_str _v1264, bkr_str _v1267, bkr_str _v2106, bkr_str _v2104);
bkr_str _v2110(bkr_str _v319, bkr_str _v2103, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v463, bkr_str _v1264, bkr_str _v1267, bkr_str _v2104);
bkr_str _v2111(bkr_str _v319, bkr_str _v2103, bkr_str _v1348, bkr_str _v2001, _v433 _v472, bkr_str _v1264, bkr_str _v1267, bkr_str _v2104);
bkr_i64 _v2112(bkr_i64 _v1239, bkr_str _v1348, bkr_str _v2001, bkr_str _v2113, bkr_i64 _v447);
bkr_i64 _v2114(bkr_i64 _v1239, bkr_str _v1348, bkr_str _v2001, bkr_str _v2113, _v341 _v452);
bkr_i64 _v2116(bkr_i64 _v1239, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v463);
bkr_i64 _v2117(bkr_i64 _v1239, bkr_str _v1348, bkr_str _v2001, _v433 _v472);
bkr_i64 _v2118(bkr_i64 _v1239, bkr_str _v1348, bkr_str _v2001, bkr_str _v2119, bkr_i64 _v447, bkr_str _v1264);
bkr_i64 _v2120(bkr_i64 _v1239, bkr_str _v1348, bkr_str _v2001, bkr_str _v2119, _v341 _v452, bkr_str _v1264);
bkr_i64 _v2121(bkr_i64 _v1239, bkr_str _v1348, bkr_str _v2001, bkr_str _v2119, _v341 _v452, bkr_str _v1264, bkr_str _v2106);
bkr_str _v2122(bkr_str _v1193, bkr_str _v557);
bkr_str _v2123(bkr_str _v319, bkr_str _v1348, _v341 _v452);
bkr_str _v2124(_v341 _v1530, bkr_i64 _v425);
bkr_str _v2125(_v341 _v1530, bkr_i64 _v425);
bkr_str _v2126(_v341 _v1530, bkr_i64 _v425);
bkr_str _v2127(_v341 _v1530, bkr_i64 _v425, bkr_i64 _v1503);
bkr_bool _v2128(bkr_str _v1348);
bkr_bool _v2129(bkr_i64 _v0, bkr_i64 _v355);
bkr_bool _v2130(_v341 _v1530, bkr_i64 _v355);
bkr_bool _v2131(bkr_i64 _v0, bkr_i64 _v355);
bkr_bool _v2132(_v341 _v1530, bkr_i64 _v355);
bkr_bool _v2133(bkr_i64 _v0, bkr_i64 _v355);
bkr_bool _v2135(_v341 _v1530, bkr_i64 _v355);
bkr_bool _v2134(_v341 _v1530, bkr_i64 _v355);
bkr_bool _v2136(_v341 _v1530, bkr_i64 _v355);
bkr_bool _v2137(bkr_i64 _v0, bkr_i64 _v1503, bkr_i64 _v1658);
bkr_bool _v2138(_v341 _v1530, bkr_i64 _v1503, bkr_i64 _v1658);
bkr_i64 _v2139(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v515, bkr_str _v2001);
bkr_i64 _v2140(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, bkr_i64 _v515, bkr_str _v2001);
bkr_i64 _v2141(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v346 _v520, bkr_str _v2001);
bkr_i64 _v2142(bkr_i64 _v1239, bkr_i64 _v425, bkr_i64 _v463, bkr_str _v2001, bkr_i64 _v2143);
bkr_i64 _v2144(bkr_i64 _v1239, bkr_i64 _v425, _v433 _v472, bkr_str _v2001, bkr_i64 _v2143);
bkr_i64 _v2145(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v1655, bkr_str _v2001, bkr_i64 _v2143);
bkr_i64 _v2146(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, bkr_i64 _v1655, bkr_str _v2001, bkr_i64 _v2143);
bkr_i64 _v2147(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v426 _v541, bkr_str _v2001, bkr_i64 _v2143);
bkr_i64 _v2155(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v370, bkr_str _v2001, bkr_i64 _v2143, bkr_i64 _v2156);
bkr_i64 _v2157(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v427 _v553, bkr_str _v2001, bkr_i64 _v2143, bkr_i64 _v2156);
bkr_i64 _v2160(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v577, bkr_str _v2001, bkr_i64 _v2161, bkr_i64 _v2162);
bkr_i64 _v2150(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v429 _v582, bkr_str _v2001, bkr_i64 _v2161, bkr_i64 _v2162);
bkr_i64 _v2163(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v557, bkr_str _v2021);
bkr_i64 _v2164(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v428 _v562, bkr_str _v2021);
bkr_i64 _v2165(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v557);
bkr_i64 _v2166(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v428 _v562);
bkr_i64 _v2167(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425);
bkr_i64 _v2168(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425);
bkr_i64 _v2169(bkr_i64 _v1239, bkr_i64 _v0);
bkr_i64 _v2170(bkr_i64 _v1239, _v341 _v1530);
bkr_str _v2171(bkr_i64 _v0);
bkr_str _v2172(bkr_i64 _v0);
bkr_bool _v2173(bkr_i64 _v319);
bkr_bool _v2174(bkr_i64 _v319);
bkr_bool _v2175(bkr_i64 _v319);
bkr_bool _v2176(bkr_i64 _v2177, bkr_i64 _v2178);
bkr_bool _v2179(bkr_i64 _v319);
bkr_bool _v2180(bkr_i64 _v319);
bkr_bool _v2181(bkr_i64 _v2182, bkr_i64 _v1787);
bkr_bool _v2187(bkr_i64 _v2177, bkr_i64 _v2178);
bkr_i64 _v2188(_v1531 _v2189, bkr_i64 _v1655);
bkr_i64 _v2190(_v1531 _v2189, _v426 _v541);
bkr_i64 _v2191(bkr_i64 _v515);
bkr_i64 _v2193(_v341 _v1530, bkr_i64 _v355);
bkr_bool _v2194(_v341 _v1530, bkr_i64 _v355);
bkr_i64 _v2050(_v341 _v1530, _v346 _v520);
bkr_i64 _v2196(_v341 _v1530, _v428 _v1514);
bkr_i64 _v2192(_v346 _v520);
bkr_i64 _v2197(bkr_i64 _v929);
bkr_i64 _v2198(_v428 _v1514);
bkr_str _v2199(bkr_str _v319, bkr_str _v2103, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v447, bkr_str _v1264, bkr_str _v2200, bkr_str _v2104);
bkr_str _v2201(bkr_str _v319, bkr_str _v2103, bkr_str _v1348, bkr_str _v2001, _v341 _v452, bkr_str _v1264, bkr_str _v2200, bkr_str _v2104);
bkr_str _v2202(bkr_str _v319, bkr_str _v2103, bkr_str _v1348, bkr_str _v2001, _v341 _v452, bkr_str _v1264, bkr_str _v2200, bkr_str _v2203, bkr_str _v2204, bkr_str _v2104);
bkr_str _v2205(bkr_str _v319, bkr_str _v2103, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v1936, bkr_i64 _v1937, bkr_str _v1264, bkr_str _v2200, bkr_str _v2203, bkr_str _v2204, bkr_str _v2104);
bkr_i64 _v2206(bkr_i64 _v1239, bkr_str _v319, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v447, bkr_i64 _v2177, bkr_i64 _v2178, bkr_str _v2104);
bkr_i64 _v2207(bkr_i64 _v1239, bkr_str _v319, bkr_str _v1348, bkr_str _v2001, _v341 _v452, bkr_i64 _v2177, bkr_i64 _v2178, bkr_str _v2104);
bkr_i64 _v2208(bkr_i64 _v1239, bkr_str _v319, bkr_str _v1348, bkr_str _v2001, _v341 _v452, bkr_i64 _v2209, bkr_i64 _v2210, bkr_str _v2104);
bkr_i64 _v2211(bkr_i64 _v1239, bkr_str _v2001, _v426 _v1094);
bkr_i64 _v2212(bkr_i64 _v1239, bkr_str _v2001, _v427 _v553);
bkr_i64 _v2214(bkr_i64 _v1239, bkr_i64 _v425, bkr_str _v2001, _v426 _v1094);
bkr_i64 _v2216(bkr_i64 _v1239, bkr_str _v1348, bkr_str _v2001, _v426 _v541);
bkr_i64 _v2217(bkr_i64 _v1239, bkr_str _v1348, bkr_str _v2001, _v426 _v541);
bkr_i64 _v2218(bkr_i64 _v1239, bkr_str _v1348, bkr_str _v2001, _v426 _v541);
bkr_i64 _v2219(bkr_i64 _v1239, bkr_str _v1348, bkr_str _v2001, _v426 _v541);
bkr_i64 _v2220(bkr_i64 _v1239, bkr_str _v1348, bkr_str _v2001, _v426 _v541);
bkr_i64 _v2221(bkr_i64 _v1239, bkr_i64 _v425, _v341 _v1530, bkr_str _v2021);
bkr_i64 _v2222(bkr_i64 _v1239, bkr_i64 _v425, bkr_str _v2021, _v428 _v2223, bkr_str _v1264, bkr_str _v2200, bkr_str _v2104);
bkr_i64 _v2224(bkr_i64 _v1239, bkr_i64 _v425, bkr_str _v2001, _v426 _v541, bkr_str _v1267);
bkr_i64 _v2225(bkr_i64 _v1239, bkr_i64 _v425, bkr_str _v2001, _v428 _v1514);
bkr_i64 _v2226(bkr_i64 _v1239, _v1531 _v2189, _v426 _v541, bkr_str _v1348, bkr_str _v2001);
bkr_i64 _v2227(bkr_i64 _v1239, bkr_str _v2001, _v427 _v553);
bkr_bool _v2228(_v426 _v1094);
bkr_bool _v2229(_v426 _v541);
bkr_bool _v2230(bkr_i64 _v1655);
bkr_bool _v2231(bkr_i64 _v425, _v426 _v541);
bkr_bool _v2232(bkr_i64 _v425, bkr_i64 _v1655);
bkr_bool _v2233(bkr_i64 _v425, _v426 _v541);
bkr_bool _v2234(bkr_i64 _v425, bkr_i64 _v1655);
bkr_bool _v2235(bkr_i64 _v425, _v426 _v541);
bkr_bool _v2236(bkr_i64 _v425, bkr_i64 _v1655);
bkr_bool _v2237(_v1531 _v2189, bkr_i64 _v1655);
bkr_i64 _v2238(bkr_str _v1348);
bkr_i64 _v2239(bkr_str _v1348, bkr_i64 _v362);
bkr_i64 _v2240(bkr_i64 _v1239, bkr_i64 _v425, _v426 _v541, bkr_str _v2001);
bkr_i64 _v2242(bkr_i64 _v1239, bkr_i64 _v425, _v1531 _v2189, _v426 _v541, bkr_str _v2001);
bkr_i64 _v2245(bkr_i64 _v1239, bkr_i64 _v425, _v1531 _v2189, _v426 _v541, bkr_str _v2001);
bkr_bool _v2246(bkr_i64 _v349);
bkr_bool _v2247(bkr_i64 _v349);
bkr_bool _v2248(bkr_i64 _v349);
bkr_i64 _v2249(bkr_i64 _v1239, bkr_str _v319, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v447, bkr_i64 _v2177, bkr_i64 _v2178, bkr_str _v2104);
bkr_i64 _v2244(bkr_i64 _v1239, bkr_str _v319, bkr_str _v1348, bkr_str _v2001, _v341 _v452, bkr_i64 _v2177, bkr_i64 _v2178, bkr_str _v2104);
bkr_i64 _v2250(bkr_i64 _v1239, bkr_str _v319, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v447, bkr_i64 _v2177, bkr_i64 _v2178, bkr_str _v2104);
bkr_i64 _v2251(bkr_i64 _v1239, bkr_str _v319, bkr_str _v1348, bkr_str _v2001, _v341 _v452, bkr_i64 _v2177, bkr_i64 _v2178, bkr_str _v2104);
_v428 _v2252(_v341 _v1530, bkr_i64 _v355);
bkr_i64 _v2253(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, bkr_str _v2021);
bkr_i64 _v2256(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v426 _v541, bkr_str _v2001);
_v428 _v2258(_v341 _v1530, bkr_i64 _v355);
_v428 _v2257(_v341 _v1530, bkr_i64 _v355);
bkr_i64 _v2260(_v341 _v1530, bkr_i64 _v1503, bkr_i64 _v1658);
bkr_i64 _v2261(bkr_i64 _v1239, bkr_i64 _v425, _v426 _v541, bkr_str _v2001);
bkr_bool _v2262(_v435 _v1007, bkr_i64 _v1658);
bkr_i64 _v2263(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v426 _v541, bkr_str _v2001);
bkr_i64 _v2265(bkr_i64 _v1239, bkr_str _v2001, bkr_str _v2266, _v426 _v1031, bkr_i64 _v2177, bkr_i64 _v2178, bkr_str _v2104);
bkr_i64 _v2267(bkr_i64 _v1239, _v1531 _v2189, _v426 _v541, bkr_str _v2001);
bkr_bool _v2269(_v1531 _v2189, _v426 _v541);
bkr_i64 _v2270(bkr_i64 _v1239, _v1531 _v2189, _v426 _v541, bkr_str _v2001);
bkr_i64 _v2272(bkr_i64 _v1239, _v1531 _v2189, _v426 _v541, bkr_str _v2001);
bkr_i64 _v2274(bkr_i64 _v1239, _v1531 _v2189, _v426 _v541, bkr_str _v2001);
bkr_i64 _v2275(_v1531 _v2189, _v341 _v1123);
bkr_i64 _v2276(bkr_i64 _v1239, _v1531 _v2189, _v434 _v975, bkr_str _v2001);
bkr_i64 _v2278(_v433 _v472);
bkr_bool _v2280(bkr_i64 _v1715, bkr_i64 _v2177);
bkr_i64 _v2281(bkr_i64 _v1239, _v436 _v620, bkr_i64 _v1715, bkr_str _v2001);
bkr_bool _v2282(_v433 _v472);
bkr_bool _v2283(_v433 _v472);
bkr_bool _v2284(_v433 _v1050, _v433 _v1051);
bkr_i64 _v2293(bkr_i64 _v1239, bkr_str _v319, bkr_str _v1348, bkr_str _v2001, _v433 _v472, bkr_str _v1264, bkr_str _v2200, bkr_str _v2104);
bkr_i64 _v2294(bkr_i64 _v1239, _v435 _v976, _v436 _v620, bkr_str _v2001);
bkr_bool _v2299(_v435 _v976, _v436 _v620, bkr_i64 _v387);
bkr_bool _v2301(_v436 _v620);
bkr_bool _v2302(bkr_i64 _v2303);
bkr_bool _v2312(_v435 _v976, _v436 _v620, bkr_i64 _v2279);
bkr_i64 _v2313(bkr_i64 _v1239, _v426 _v541, _v436 _v620, bkr_i64 _v1715, bkr_str _v2001);
bkr_i64 _v2317(bkr_i64 _v1239, _v435 _v976, _v436 _v620, bkr_i64 _v1715, bkr_str _v2001);
bkr_i64 _v2319(bkr_i64 _v1239, _v426 _v541, _v436 _v620, bkr_str _v2001);
bkr_i64 _v2322(bkr_i64 _v1239, _v435 _v976, _v436 _v620, bkr_str _v2001);
bkr_bool _v2323(_v436 _v620);
bkr_bool _v2324(_v435 _v976, _v436 _v620, bkr_i64 _v2279);
bkr_i64 _v2325(bkr_i64 _v1239, _v426 _v541, _v436 _v620, bkr_str _v2001);
bkr_i64 _v2328(bkr_i64 _v1239, _v435 _v976, _v436 _v620, bkr_str _v2001);
bkr_bool _v2331(_v436 _v620);
bkr_i64 _v2332(_v436 _v620);
_v428 _v2333(_v341 _v1530, bkr_i64 _v2334);
bkr_bool _v2335(_v435 _v976, _v436 _v620, bkr_i64 _v2334, bkr_i64 _v1388);
bkr_i64 _v2336(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v426 _v541, _v436 _v620, bkr_str _v2001);
bkr_i64 _v2339(bkr_i64 _v1239, _v426 _v541, _v436 _v620, bkr_i64 _v1715, bkr_str _v2001);
bkr_i64 _v2341(bkr_i64 _v1239, _v341 _v1530, _v435 _v976, _v436 _v620, bkr_str _v2001);
bkr_bool _v2344(_v435 _v1162, bkr_i64 _v1388);
bkr_bool _v2345(_v436 _v620, bkr_i64 _v2334, bkr_i64 _v1388, bkr_i64 _v2346);
bkr_i64 _v2347(bkr_i64 _v1239, _v1531 _v2189, _v434 _v994, bkr_str _v2001);
bkr_i64 _v2350(bkr_i64 _v1239, bkr_i64 _v1655, bkr_str _v2001, bkr_i64 _v2351);
bkr_i64 _v2352(bkr_i64 _v1239, _v426 _v541, bkr_str _v2001, bkr_i64 _v2351);
bkr_i64 _v2354(bkr_i64 _v1239, _v427 _v553, bkr_str _v2001, bkr_i64 _v2351);
bkr_i64 _v2353(bkr_i64 _v1239, _v429 _v582, bkr_str _v2001, bkr_i64 _v2351);
bkr_bool _v2355(_v427 _v553);
bkr_bool _v2356(_v429 _v582);
bkr_bool _v2357(_v427 _v553);
bkr_bool _v2358(_v429 _v582);
bkr_i64 _v2359(bkr_i64 _v1239, _v427 _v553, bkr_str _v2001);
bkr_i64 _v2360(bkr_i64 _v1239, _v429 _v582, bkr_str _v2001);
bkr_i64 _v2362(bkr_i64 _v1239, bkr_i64 _v425, _v1531 _v2189, bkr_i64 _v1655, bkr_str _v2001, bkr_str _v2363, bkr_str _v1348, bkr_i64 _v2177, bkr_str _v2104);
bkr_i64 _v2365(bkr_i64 _v1239, bkr_i64 _v425, _v1531 _v2189, _v426 _v541, bkr_str _v2001, bkr_str _v2363, bkr_str _v1348, bkr_i64 _v2177, bkr_str _v2104);
bkr_i64 _v2366(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425, _v1531 _v2189, bkr_i64 _v368, bkr_str _v2001);
bkr_i64 _v2367(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v1531 _v2189, _v426 _v541, bkr_str _v2001);
bkr_i64 _v2370(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425, _v1531 _v2189, bkr_i64 _v1655, bkr_str _v2001, bkr_i64 _v2371);
bkr_i64 _v2372(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v1531 _v2189, bkr_i64 _v1655, bkr_str _v2001, bkr_i64 _v2371);
bkr_i64 _v2373(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v1531 _v2189, _v426 _v541, bkr_str _v2001, bkr_i64 _v2371);
bkr_i64 _v2383(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425, _v1531 _v2189, bkr_i64 _v370, bkr_str _v2001, bkr_i64 _v2371);
bkr_i64 _v2384(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v1531 _v2189, _v427 _v553, bkr_str _v2001, bkr_i64 _v2371);
bkr_i64 _v2386(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425, _v1531 _v2189, bkr_i64 _v577, bkr_str _v2001, bkr_i64 _v2371);
bkr_i64 _v2381(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v1531 _v2189, _v429 _v582, bkr_str _v2001, bkr_i64 _v2371);
bkr_i64 _v2387(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425, _v1531 _v2189, bkr_i64 _v557, bkr_str _v2021);
bkr_i64 _v2388(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v1531 _v2189, _v428 _v562, bkr_str _v2021);
bkr_i64 _v2389(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v557);
bkr_i64 _v2390(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v428 _v562);
bkr_i64 _v2391(bkr_i64 _v1239, bkr_i64 _v0);
bkr_i64 _v2392(bkr_i64 _v1239, _v341 _v1530);
bkr_str _v2393(bkr_i64 _v0);
bkr_str _v2394(bkr_i64 _v0);
bkr_i64 _v2395(bkr_i64 _v1239, _v341 _v1530);
bkr_str _v2396(bkr_i64 _v0);
bkr_str _v2397(bkr_i64 _v0);
_v2400 _v2412(bkr_i64 _v2408);
bkr_bool _v2414(_v2400 _v2415, bkr_str _v1348);
bkr_str _v2416(bkr_str _v2417, bkr_str _v1826);
bkr_bool _v2418(_v2400 _v2415, bkr_str _v2417, bkr_str _v1826, bkr_i64 _v1383);
bkr_i64 _v2421(_v2400 _v2415, bkr_str _v2417, bkr_str _v1826);
bkr_bool _v2424(_v2400 _v2415, bkr_str _v2417, bkr_str _v1826, bkr_str _v1383);
bkr_str _v2425(_v2400 _v2415, bkr_str _v2417, bkr_str _v1826);
bkr_bool _v2426(_v2400 _v2415, bkr_str _v386, bkr_str _v1209, bkr_str _v2399, bkr_i64 _v344);
bkr_i64 _v2427(_v2400 _v2415);
bkr_bool _v2429(_v2400 _v2415);
_v2398 _v2430(_v2400 _v2415);
bkr_bool _v2431(_v2400 _v2415);
bkr_bool _v2432(_v2400 _v2415);
bkr_i64 _v2433(_v2400 _v2415);
bkr_str _v2434(_v2400 _v2415);
_v2436 _v2451(bkr_str _v1348);
bkr_i64 _v2465(_v2436 _v2466, bkr_str _v319);
bkr_bool _v2467(_v2436 _v2466, bkr_i64 _v2468, bkr_i64 _v2469);
bkr_bool _v2470(_v2436 _v2466, bkr_i64 _v1605, bkr_str _v2471);
bkr_bool _v2472(_v2436 _v2466, bkr_i64 _v1605, bkr_i64 _v2473, bkr_i64 _v2474);
bkr_bool _v2475(_v2436 _v2466, bkr_i64 _v1605, bkr_str _v1290);
bkr_bool _v2476(_v2436 _v2466, bkr_i64 _v1605, bkr_i64 _v2477);
bkr_bool _v2478(_v2436 _v2466, bkr_i64 _v1605, bkr_i64 _v2479);
bkr_bool _v2480(_v2436 _v2466, bkr_i64 _v1605, bkr_i64 _v2481);
bkr_bool _v2482(_v2436 _v2466, bkr_i64 _v1605, bkr_str _v2417, bkr_str _v1826);
bkr_bool _v2483(_v2436 _v2466, bkr_i64 _v1605, bkr_str _v386, bkr_str _v2399);
bkr_str _v2484(_v2436 _v2466, bkr_i64 _v1605);
bkr_str _v2485(_v2436 _v2466, bkr_i64 _v1605);
bkr_i64 _v2486(_v2436 _v2466, bkr_i64 _v1605);
bkr_i64 _v2487(_v2436 _v2466, bkr_i64 _v1605);
bkr_i64 _v2488(_v2436 _v2466, bkr_i64 _v1605);
bkr_str _v2489(_v2436 _v2466, bkr_i64 _v1605);
bkr_str _v2490(_v2436 _v2466, bkr_i64 _v1605);
bkr_str _v2491(_v2436 _v2466, bkr_i64 _v1605);
bkr_str _v2492(_v2436 _v2466, bkr_i64 _v1605, _v2400 _v2415);
bkr_bool _v2496(_v2436 _v2466, bkr_i64 _v1605, _v2400 _v2415);
bkr_str _v2497(_v2436 _v2466);
_v2498 _v2509(void);
_v2498 _v2511(bkr_i64 _v1205);
_v2498 _v2512(bkr_str _v1348);
_v2498 _v2513(bkr_str _v1348, bkr_i64 _v2514);
bkr_i64 _v2515(_v2498 _v368, bkr_str _v1348);
bkr_bool _v2516(_v2498 _v368, bkr_str _v1348, bkr_i64 _v2514);
_v2498 _v2517(_v2498 _v2518, _v2498 _v2519);
_v2498 _v2523(_v2498 _v2518, _v2498 _v2519);
_v2498 _v2524(_v2498 _v2518, bkr_i64 _v573);
bkr_bool _v2525(_v2498 _v368);
bkr_i64 _v2526(_v2498 _v368, bkr_i64 _v2527);
bkr_str _v2529(_v2498 _v368);
_v2502 _v2532(bkr_str _v2503);
bkr_bool _v2535(_v2502 _v2536, bkr_str _v2537);
bkr_bool _v2538(_v2502 _v2536, bkr_str _v2537);
bkr_bool _v2539(_v2498 _v2540, _v2498 _v2541);
bkr_str _v2543(_v2498 _v2540, _v2498 _v2541, bkr_i64 _v2527);
bkr_str _v2546(_v2502 _v2536);
_v2548 _v2577(bkr_i64 _v425);
bkr_str _v2578(_v2548 _v2579, bkr_i64 _v1035);
bkr_str _v2580(bkr_i64 _v319);
bkr_bool _v2581(_v2548 _v2579, bkr_str _v2399);
bkr_i64 _v2582(_v2548 _v2579);
bkr_bool _v2583(_v2548 _v2579, bkr_i64 _v2584);
bkr_bool _v2585(_v2548 _v2579, bkr_i64 _v2518, bkr_i64 _v2519);
bkr_bool _v2586(_v2548 _v2579, bkr_i64 _v2518, bkr_i64 _v2519, bkr_i64 _v1205);
bkr_bool _v2587(_v2548 _v2579, bkr_i64 _v387);
bkr_bool _v2588(_v2548 _v2579, bkr_i64 _v387);
bkr_bool _v2589(_v2548 _v2579, bkr_i64 _v1210, bkr_i64 _v387);
bkr_bool _v2590(_v2548 _v2579, bkr_i64 _v1210, bkr_i64 _v386);
bkr_bool _v2591(_v2548 _v2579, bkr_i64 _v387);
bkr_bool _v2592(_v2548 _v2579, bkr_i64 _v1274);
bkr_bool _v2593(_v2548 _v2579, bkr_i64 _v1274);
bkr_bool _v2594(_v2548 _v2579, bkr_i64 _v1274);
bkr_bool _v2595(_v2548 _v2579, bkr_i64 _v1274);
bkr_bool _v2596(_v2548 _v2579, bkr_i64 _v1274);
bkr_bool _v2597(_v2548 _v2579, bkr_i64 _v1217);
bkr_bool _v2598(_v2548 _v2579, bkr_i64 _v387);
bkr_bool _v2599(_v2548 _v2579, bkr_i64 _v387);
bkr_bool _v2600(_v2548 _v2579, bkr_i64 _v2601);
bkr_bool _v2602(_v2548 _v2579, bkr_i64 _v387);
bkr_bool _v2603(_v2548 _v2579, bkr_i64 _v2604);
bkr_i64 _v2605(_v2548 _v2579);
bkr_bool _v2606(_v2548 _v2579);
bkr_bool _v2607(_v2548 _v2579);
bkr_bool _v2608(_v2548 _v2579);
bkr_bool _v2609(_v2548 _v2579);
bkr_bool _v2610(_v2548 _v2579, bkr_i64 _v2611);
bkr_i64 _v2612(_v2548 _v2579);
bkr_i64 _v2613(_v2548 _v2579);
bkr_i64 _v2614(_v2548 _v2579);
bkr_bool _v2615(_v2548 _v2579, bkr_i64 _v386);
bkr_bool _v2616(_v2548 _v2579);
bkr_i64 _v2617(_v2548 _v2579, bkr_i64 _v2604);
bkr_i64 _v2618(_v2548 _v2579, bkr_str _v1348, bkr_i64 _v1274, bkr_str _v1663);
bkr_i64 _v2619(_v2548 _v2579, bkr_str _v1348);
bkr_i64 _v2620(_v2548 _v2579, bkr_str _v1348);
bkr_i64 _v2621(_v2548 _v2579, bkr_str _v1348);
bkr_str _v2622(_v2548 _v2579, bkr_str _v1348);
bkr_i64 _v2623(_v2548 _v2579);
bkr_bool _v2624(_v2548 _v2579, bkr_i64 _v2625);
bkr_bool _v2627(_v2548 _v2579, bkr_str _v1663);
bkr_bool _v2628(_v2548 _v2579, bkr_str _v1663);
bkr_str _v2629(bkr_i64 _v319);
bkr_str _v2630(bkr_str _v1663, bkr_str _v1584, bkr_i64 _v362);
bkr_bool _v2631(_v2548 _v2579, bkr_str _v1663);
bkr_i64 _v2632(_v2548 _v2579, bkr_str _v1663);
bkr_str _v2633(_v2548 _v2579, bkr_str _v1663);
bkr_i64 _v2634(_v2548 _v2579, bkr_str _v1663);
bkr_str _v2635(_v2548 _v2579, _v346 _v520);
bkr_str _v2636(bkr_str _v1348);
bkr_str _v2637(_v2548 _v2579, bkr_i64 _v342);
bkr_i64 _v2638(_v2548 _v2579, bkr_str _v1681, bkr_str _v1150);
bkr_i64 _v2639(_v2548 _v2579, bkr_str _v1681, bkr_i64 _v2640);
bkr_i64 _v2642(_v2548 _v2579, bkr_str _v1348, bkr_i64 _v1350);
bkr_str _v2645(_v2548 _v2579, _v426 _v541);
bkr_str _v2648(_v2548 _v2579, bkr_str _v1348);
bkr_str _v2647(_v2548 _v2579, _v426 _v541);
bkr_bool _v2657(_v2548 _v2579, bkr_i64 _v342);
bkr_bool _v2658(_v2548 _v2579, _v426 _v541);
bkr_bool _v2660(_v2548 _v2579, _v426 _v541);
bkr_bool _v2672(_v2548 _v2579, _v426 _v541);
bkr_bool _v2663(_v2548 _v2579, _v426 _v541);
bkr_bool _v2665(_v2548 _v2579, bkr_str _v2685, bkr_i64 _v2664);
bkr_bool _v2692(_v2548 _v2579, bkr_i64 _v2693, bkr_i64 _v1274);
bkr_bool _v2681(_v2548 _v2579, bkr_str _v1348, _v434 _v1015);
bkr_bool _v2694(_v2548 _v2579, bkr_i64 _v2693);
bkr_bool _v2683(_v2548 _v2579, bkr_i64 _v361, bkr_i64 _v2654, bkr_i64 _v2659);
bkr_bool _v2667(_v2548 _v2579, _v426 _v541);
bkr_bool _v2674(_v2548 _v2579, _v429 _v582);
bkr_bool _v2698(_v2548 _v2579, bkr_i64 _v342);
bkr_i64 _v2699(_v2548 _v2579, _v433 _v472);
bkr_i64 _v2700(_v2548 _v2579, bkr_i64 _v2669, bkr_i64 _v2601, bkr_i64 _v2701);
bkr_bool _v2703(_v2548 _v2579, _v433 _v472, bkr_i64 _v2669, bkr_i64 _v2704);
bkr_i64 _v2705(_v2548 _v2579, bkr_i64 _v2669);
bkr_bool _v2706(_v2548 _v2579, bkr_i64 _v355, bkr_i64 _v2669, bkr_i64 _v2601, bkr_i64 _v2701, bkr_str _v1663);
bkr_bool _v2707(_v2548 _v2579, _v433 _v472, bkr_i64 _v2669, bkr_str _v1663);
bkr_bool _v2673(_v2548 _v2579, _v426 _v541);
bkr_bool _v2713(_v2548 _v2579, _v429 _v582);
bkr_bool _v2714(_v2548 _v2579, bkr_i64 _v342, bkr_str _v1348);
bkr_i64 _v2715(_v2548 _v2579);
bkr_bool _v2716(_v2548 _v2579, bkr_i64 _v2717, bkr_i64 _v2718, bkr_i64 _v1605, bkr_i64 _v386);
bkr_bool _v2719(_v2548 _v2579, bkr_i64 _v1605, bkr_i64 _v2720, bkr_i64 _v2721);
bkr_i64 _v2722(_v2548 _v2579);
bkr_bool _v2697(_v2548 _v2579, _v427 _v553);
bkr_bool _v2728(_v2548 _v2579, bkr_i64 _v2693, bkr_i64 _v1274);
bkr_str _v2729(_v2548 _v2579, bkr_str _v2023, _v341 _v1507);
bkr_bool _v2732(_v2548 _v2579, _v428 _v1514);
_v2548 _v2737(_v341 _v1530);
bkr_bool _v2744(bkr_i64 _v1841, bkr_i64 _v387);
bkr_bool _v2745(bkr_i64 _v1841, bkr_i64 _v387);
bkr_bool _v2746(bkr_i64 _v1841, bkr_i64 _v387);
bkr_i64 _v2747(bkr_i64 _v2103);
bkr_bool _v2749(bkr_str _v2750, bkr_i64 _v2751);
bkr_bool _v2759(bkr_str _v1582);
bkr_str _v2762(bkr_str _v1582);
bkr_bool _v2763(bkr_str _v2764);
bkr_bool _v2765(bkr_str _v2764);
bkr_bool _v2766(bkr_str _v2764);
bkr_bool _v2769(bkr_str _v2764);
bkr_bool _v2770(bkr_str _v2764);
bkr_str _v2771(bkr_str _v2772, bkr_str _v2764);
bkr_str _v2773(bkr_str _v2774);
bkr_bool _v2776(bkr_i64 _v2641, bkr_str _v2764);
bkr_str _v2777(bkr_str _v2778, bkr_str _v1582, bkr_i64 _v2641, bkr_str _v2772);
bkr_str _v2783(bkr_str _v1209, bkr_i64 _v2641, bkr_str _v2772);
bkr_str _v2785(bkr_str _v1209);
bkr_str _v2786(bkr_str _v1209, bkr_str _v2772);
bkr_str _v2787(bkr_str _v1582, bkr_i64 _v2641, bkr_str _v2772);
bkr_str _v2788(bkr_str _v1209, bkr_i64 _v2641, bkr_str _v2772);
bkr_str _v2789(bkr_str _v1209);
bkr_str _v2790(bkr_str _v1209, bkr_str _v2772);
bkr_str _v2791(bkr_str _v1582, bkr_i64 _v2641, bkr_str _v2772);
bkr_str _v2792(bkr_str _v1209, bkr_i64 _v2641, bkr_str _v2772);
bkr_str _v2794(bkr_str _v1209);
bkr_str _v2795(bkr_str _v1209, bkr_str _v2772);
bkr_i64 _v2796(bkr_str _v1582, bkr_i64 _v2641, bkr_str _v2772);
bkr_i64 _v2797(bkr_str _v1209, bkr_i64 _v2641, bkr_str _v2772);
bkr_i64 _v2798(bkr_str _v1209);
bkr_i64 _v2799(bkr_str _v1209, bkr_str _v2772);
bkr_str _v2800(bkr_str _v1193, bkr_str _v557);
bkr_str _v2801(bkr_str _v1193, bkr_str _v423);
bkr_str _v2802(bkr_str _v1582, bkr_i64 _v2641, bkr_str _v2772);
bkr_str _v2803(bkr_str _v1209, bkr_i64 _v2641, bkr_str _v2772);
bkr_str _v2804(bkr_str _v1209);
bkr_str _v2805(bkr_str _v1209, bkr_str _v2772);
bkr_str _v2806(bkr_str _v2807, bkr_str _v2808, bkr_str _v2809, bkr_str _v2435);
bkr_str _v2810(bkr_str _v1582, bkr_i64 _v2641, bkr_str _v2772);
bkr_str _v2811(bkr_str _v1209, bkr_i64 _v2641, bkr_str _v2772);
bkr_str _v2812(bkr_str _v1209, bkr_str _v2772);
bkr_i64 _v2813(bkr_str _v2814, bkr_str _v2435);
bkr_i64 _v2816(bkr_str _v1209, bkr_str _v2772, bkr_str _v2435);
bkr_i64 _v2817(bkr_str _v1209, bkr_str _v2772);
bkr_i64 _v2818(bkr_str _v1209, bkr_i64 _v1274);
bkr_i64 _v2819(bkr_str _v1209, bkr_i64 _v1274);
bkr_str _v2821(bkr_str _v1209, bkr_i64 _v1274);
bkr_str _v2823(bkr_str _v330, bkr_str _v2103, bkr_str _v2399, bkr_i64 _v1936, bkr_i64 _v1937, bkr_i64 _v2824, bkr_i64 _v2825, bkr_str _v2826, bkr_str _v1264, bkr_str _v1267, bkr_str _v2104);
bkr_str _v2827(bkr_str _v330, bkr_str _v2103, bkr_str _v2399, bkr_i64 _v1936, bkr_i64 _v1937, bkr_i64 _v2824, bkr_i64 _v2825, bkr_str _v2826, bkr_str _v1264, bkr_str _v1267, bkr_str _v2104, bkr_bool _v2828, bkr_str _v2829);
bkr_str _v2830(bkr_i64 _v2831);
bkr_str _v2832(bkr_str _v2103, bkr_str _v2833, bkr_str _v330, bkr_str _v2834);
bkr_str _v2835(void);
bkr_str _v2836(void);
bkr_str _v2837(void);
bkr_str _v2838(bkr_str _v1209);
bkr_str _v2839(bkr_str _v1209, bkr_str _v2772);
bkr_str _v2842(bkr_str _v1209);
bkr_str _v2843(bkr_str _v1209, bkr_str _v2772);
bkr_str _v2844(bkr_str _v2840);
bkr_str _v2846(bkr_str _v2841);
bkr_str _v2847(bkr_str _v1209, _v1234 _v1246);
bkr_bool _v2877(void);
bkr_i64 _v2878(bkr_str _v2833);
bkr_str _v2881(bkr_str _v1209);
bkr_str _v2882(bkr_str _v1209, bkr_str _v2883);
bkr_bool _v2894(bkr_str _v2895);
bkr_str _v2898(bkr_str _v1826, bkr_str _v2899);
bkr_str _v2903(bkr_str _v1290);
bkr_str _v2906(void);
bkr_bool _v2911(bkr_str _v2895);
bkr_bool _v2915(bkr_str _v2750);
bkr_str _v2916(void);
bkr_bool _v2917(bkr_str _v2918, bkr_str _v2919);
bkr_bool _v2923(void);
bkr_i32 _v2924(void);

bkr_str _v318(bkr_i64 _v319) {
    if ((_v319 == 1)) {
        return "kernel";
    }
    if ((_v319 == 2)) {
        return "function";
    }
    if ((_v319 == 3)) {
        return "parameter";
    }
    if ((_v319 == 4)) {
        return "type";
    }
    if ((_v319 == 5)) {
        return "block";
    }
    if ((_v319 == 6)) {
        return "let";
    }
    if ((_v319 == 7)) {
        return "return";
    }
    if ((_v319 == 8)) {
        return "if";
    }
    if ((_v319 == 9)) {
        return "while";
    }
    if ((_v319 == 10)) {
        return "expression statement";
    }
    if ((_v319 == 11)) {
        return "assignment";
    }
    if ((_v319 == 12)) {
        return "break";
    }
    if ((_v319 == 13)) {
        return "continue";
    }
    if ((_v319 == 14)) {
        return "for";
    }
    if ((_v319 == 15)) {
        return "loop";
    }
    if ((_v319 == 16)) {
        return "defer";
    }
    if (((_v319 == 17) || (_v319 == 18))) {
        return "array repeat";
    }
    if ((_v319 == 18)) {
        return "try";
    }
    if ((_v319 == 19)) {
        return "cast expression";
    }
    if ((_v319 == 20)) {
        return "binary expression";
    }
    if ((_v319 == 21)) {
        return "unary expression";
    }
    if ((_v319 == 22)) {
        return "call expression";
    }
    if ((_v319 == 23)) {
        return "identifier";
    }
    if ((_v319 == 24)) {
        return "integer literal";
    }
    if ((_v319 == 25)) {
        return "boolean literal";
    }
    if ((_v319 == 26)) {
        return "string literal";
    }
    if ((_v319 == 27)) {
        return "constant";
    }
    if ((_v319 == 28)) {
        return "ternary expression";
    }
    if ((_v319 == 29)) {
        return "float literal";
    }
    if ((_v319 == 30)) {
        return "array literal";
    }
    if ((_v319 == 31)) {
        return "index expression";
    }
    if ((_v319 == 32)) {
        return "struct";
    }
    if ((_v319 == 37)) {
        return "enum";
    }
    if ((_v319 == 33)) {
        return "field";
    }
    if ((_v319 == 34)) {
        return "field access";
    }
    if ((_v319 == 35)) {
        return "struct literal";
    }
    if ((_v319 == 36)) {
        return "match expression";
    }
    if ((_v319 == 38)) {
        return "type alias";
    }
    if ((_v319 == 39)) {
        return "method call";
    }
    return bkr_str_concat("node ", int_to_string(_v319));
}

bkr_str _v324(bkr_i64 _v319) {
    if ((_v319 == 0)) {
        return "EOF";
    }
    if ((_v319 == 10)) {
        return "identifier";
    }
    if ((_v319 == 11)) {
        return "integer";
    }
    if ((_v319 == 12)) {
        return "string";
    }
    if ((_v319 == 13)) {
        return "float";
    }
    if ((_v319 == 14)) {
        return "true";
    }
    if ((_v319 == 15)) {
        return "false";
    }
    if ((_v319 == 20)) {
        return "kernel";
    }
    if ((_v319 == 21)) {
        return "enum";
    }
    if ((_v319 == 22)) {
        return "struct";
    }
    if ((_v319 == 23)) {
        return "fn";
    }
    if ((_v319 == 24)) {
        return "let";
    }
    if ((_v319 == 25)) {
        return "if";
    }
    if ((_v319 == 26)) {
        return "else";
    }
    if ((_v319 == 27)) {
        return "for";
    }
    if ((_v319 == 28)) {
        return "in";
    }
    if ((_v319 == 29)) {
        return "while";
    }
    if ((_v319 == 30)) {
        return "break";
    }
    if ((_v319 == 31)) {
        return "continue";
    }
    if ((_v319 == 32)) {
        return "loop";
    }
    if ((_v319 == 33)) {
        return "return";
    }
    if ((_v319 == 34)) {
        return "match";
    }
    if ((_v319 == 35)) {
        return "const";
    }
    if ((_v319 == 36)) {
        return "defer";
    }
    if ((_v319 == 37)) {
        return "type";
    }
    if ((_v319 == 38)) {
        return "as";
    }
    if ((_v319 == 60)) {
        return "i32";
    }
    if ((_v319 == 61)) {
        return "i64";
    }
    if ((_v319 == 62)) {
        return "f64";
    }
    if ((_v319 == 63)) {
        return "bool";
    }
    if ((_v319 == 64)) {
        return "str";
    }
    if ((_v319 == 80)) {
        return "+";
    }
    if ((_v319 == 81)) {
        return "-";
    }
    if ((_v319 == 82)) {
        return "*";
    }
    if ((_v319 == 83)) {
        return "/";
    }
    if ((_v319 == 84)) {
        return "%";
    }
    if ((_v319 == 85)) {
        return "==";
    }
    if ((_v319 == 86)) {
        return "!=";
    }
    if ((_v319 == 87)) {
        return "<";
    }
    if ((_v319 == 88)) {
        return ">";
    }
    if ((_v319 == 89)) {
        return "<=";
    }
    if ((_v319 == 90)) {
        return ">=";
    }
    if ((_v319 == 91)) {
        return "&&";
    }
    if ((_v319 == 92)) {
        return "||";
    }
    if ((_v319 == 93)) {
        return "!";
    }
    if ((_v319 == 94)) {
        return "&";
    }
    if ((_v319 == 95)) {
        return "|";
    }
    if ((_v319 == 96)) {
        return "^";
    }
    if ((_v319 == 97)) {
        return "<<";
    }
    if ((_v319 == 98)) {
        return ">>";
    }
    if ((_v319 == 99)) {
        return "=";
    }
    if ((_v319 == 101)) {
        return "->";
    }
    if ((_v319 == 120)) {
        return "=>";
    }
    if ((_v319 == 102)) {
        return "..";
    }
    if ((_v319 == 103)) {
        return "..=";
    }
    if ((_v319 == 104)) {
        return ".";
    }
    if ((_v319 == 110)) {
        return "(";
    }
    if ((_v319 == 111)) {
        return ")";
    }
    if ((_v319 == 112)) {
        return "{";
    }
    if ((_v319 == 113)) {
        return "}";
    }
    if ((_v319 == 114)) {
        return "[";
    }
    if ((_v319 == 115)) {
        return "]";
    }
    if ((_v319 == 116)) {
        return ",";
    }
    if ((_v319 == 117)) {
        return ";";
    }
    if ((_v319 == 118)) {
        return ":";
    }
    if ((_v319 == 121)) {
        return "::";
    }
    if ((_v319 == 119)) {
        return "?";
    }
    return bkr_str_concat("token ", int_to_string(_v319));
}

bkr_bool _v325(bkr_i64 _v319) {
    return ((((((((((((((((((((((_v319 == 10) || (_v319 == 20)) || (_v319 == 21)) || (_v319 == 22)) || (_v319 == 23)) || (_v319 == 24)) || (_v319 == 25)) || (_v319 == 26)) || (_v319 == 27)) || (_v319 == 28)) || (_v319 == 29)) || (_v319 == 30)) || (_v319 == 31)) || (_v319 == 32)) || (_v319 == 33)) || (_v319 == 34)) || (_v319 == 35)) || (_v319 == 60)) || (_v319 == 61)) || (_v319 == 62)) || (_v319 == 63)) || (_v319 == 64));
}

bkr_str _v327(bkr_i64 _v319) {
    if ((_v319 == 0)) {
        return "i32";
    }
    if ((_v319 == 1)) {
        return "i64";
    }
    if ((_v319 == 2)) {
        return "f64";
    }
    if ((_v319 == 3)) {
        return "bool";
    }
    if ((_v319 == 4)) {
        return "str";
    }
    if ((_v319 == 5)) {
        return "void";
    }
    if ((_v319 == 6)) {
        return "array";
    }
    if ((_v319 == 7)) {
        return "struct";
    }
    if ((_v319 == 8)) {
        return "Vec";
    }
    if ((_v319 == 9)) {
        return "HashMap";
    }
    if ((_v319 == 10)) {
        return "Option";
    }
    if ((_v319 == 11)) {
        return "Result";
    }
    if ((_v319 == 12)) {
        return "!";
    }
    if ((_v319 == 13)) {
        return "fn";
    }
    if ((_v319 == _v316)) {
        return "unknown";
    }
    return bkr_str_concat("type ", int_to_string(_v319));
}

bkr_str _v328(bkr_i64 _v319) {
    if ((_v319 == 1)) {
        return "integer pattern";
    }
    if ((_v319 == 2)) {
        return "boolean pattern";
    }
    if ((_v319 == 3)) {
        return "binding pattern";
    }
    if ((_v319 == 4)) {
        return "wildcard pattern";
    }
    if ((_v319 == 5)) {
        return "Some pattern";
    }
    if ((_v319 == 6)) {
        return "None pattern";
    }
    if ((_v319 == 7)) {
        return "enum variant pattern";
    }
    if ((_v319 == 8)) {
        return "Result.Ok pattern";
    }
    if ((_v319 == 9)) {
        return "Result.Err pattern";
    }
    return bkr_str_concat("pattern ", int_to_string(_v319));
}

bkr_str _v329(bkr_i64 _v330) {
    if ((_v330 == _v263)) {
        return "item";
    }
    if ((_v330 == _v264)) {
        return "statement";
    }
    if ((_v330 == _v265)) {
        return "expression";
    }
    if ((_v330 == _v266)) {
        return "type";
    }
    if ((_v330 == _v267)) {
        return "declaration";
    }
    return "unknown";
}

bkr_i64 _v331(bkr_i64 _v319) {
    if (((((((_v319 == 1) || (_v319 == 2)) || (_v319 == 27)) || (_v319 == 32)) || (_v319 == 37)) || (_v319 == 38))) {
        return _v263;
    }
    if (((((((((((((_v319 == 5) || (_v319 == 6)) || (_v319 == 7)) || (_v319 == 8)) || (_v319 == 9)) || (_v319 == 10)) || (_v319 == 11)) || (_v319 == 12)) || (_v319 == 13)) || (_v319 == 14)) || (_v319 == 15)) || (_v319 == 16))) {
        return _v264;
    }
    if (((((((((((((((((((_v319 == 20) || (_v319 == 21)) || (_v319 == 22)) || (_v319 == 23)) || (_v319 == 24)) || (_v319 == 25)) || (_v319 == 26)) || (_v319 == 28)) || (_v319 == 29)) || (_v319 == 30)) || (_v319 == 31)) || (_v319 == 34)) || (_v319 == 35)) || (_v319 == 36)) || (_v319 == 17)) || (_v319 == 18)) || (_v319 == 19)) || (_v319 == 39))) {
        return _v265;
    }
    if ((_v319 == 4)) {
        return _v266;
    }
    if (((_v319 == 3) || (_v319 == 33))) {
        return _v267;
    }
    return _v262;
}

bkr_bool _v332(bkr_i64 _v319) {
    return (_v331(_v319) == _v263);
}

bkr_bool _v333(bkr_i64 _v319) {
    return (_v331(_v319) == _v264);
}

bkr_bool _v334(bkr_i64 _v319) {
    return (_v331(_v319) == _v265);
}

bkr_bool _v335(bkr_i64 _v319) {
    return (_v331(_v319) == _v266);
}

bkr_bool _v336(bkr_i64 _v319) {
    return (_v331(_v319) == _v267);
}

_v341 _v445(bkr_i64 _v319) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v319);
    vec_push(_v447, _v268);
    vec_push(_v447, _v268);
    return (_v341){._v342 = ((bkr_i64)(_v447))};
}

_v341 _v451(_v341 _v452, bkr_i64 _v387) {
    vec_push(_v453(_v452), _v387);
    return _v452;
}

_v341 _v454(_v341 _v452, bkr_i64 _v339, bkr_i64 _v340) {
    bkr_i64 _v447 = _v453(_v452);
    vec_set(_v447, _v269, _v339);
    vec_set(_v447, _v270, _v340);
    return _v452;
}

_v341 _v456(_v341 _v452, _v338 _v457) {
    return _v454(_v452, _v457._v339, _v457._v340);
}

_v430 _v458(bkr_i64 _v319, bkr_i64 _v387) {
    return _v459(_v319, _v387, 0);
}

_v430 _v459(bkr_i64 _v319, bkr_i64 _v387, bkr_i64 _v345) {
    return _v460(_v319, _v387, _v345, (-1));
}

_v430 _v460(bkr_i64 _v319, bkr_i64 _v387, bkr_i64 _v345, bkr_i64 _v431) {
    return _v461(_v319, _v387, _v345, _v431, (-1));
}

_v430 _v461(bkr_i64 _v319, bkr_i64 _v387, bkr_i64 _v345, bkr_i64 _v431, bkr_i64 _v432) {
    return (_v430){._v319 = _v319, ._v339 = _v268, ._v340 = _v268, ._v387 = _v387, ._v345 = _v345, ._v431 = _v431, ._v432 = _v432};
}

bkr_i64 _v462(_v430 _v463) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v463._v319);
    vec_push(_v447, _v463._v339);
    vec_push(_v447, _v463._v340);
    vec_push(_v447, _v463._v387);
    vec_push(_v447, _v463._v345);
    vec_push(_v447, _v463._v431);
    vec_push(_v447, _v463._v432);
    return _v447;
}

_v430 _v464(bkr_i64 _v447) {
    bkr_i64 _v345 = 0;
    bkr_i64 _v431 = (-1);
    bkr_i64 _v432 = (-1);
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v345 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v431 = vec_get(_v447, (_v272 + 2));
    }
    if ((vec_len(_v447) > (_v272 + 3))) {
        _v432 = vec_get(_v447, (_v272 + 3));
    }
    return (_v430){._v319 = vec_get(_v447, 0), ._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v387 = vec_get(_v447, _v272), ._v345 = _v345, ._v431 = _v431, ._v432 = _v432};
}

_v433 _v467(bkr_i64 _v319, bkr_i64 _v387) {
    return _v468(_v319, _v387, 0);
}

_v433 _v468(bkr_i64 _v319, bkr_i64 _v387, bkr_i64 _v345) {
    _v430 _v463 = _v459(_v319, _v387, _v345);
    return (_v433){._v342 = ((bkr_i64)(_v462(_v463)))};
}

_v433 _v469(bkr_i64 _v319, bkr_i64 _v387, bkr_i64 _v345, bkr_i64 _v431) {
    _v430 _v463 = _v460(_v319, _v387, _v345, _v431);
    return (_v433){._v342 = ((bkr_i64)(_v462(_v463)))};
}

_v433 _v470(bkr_i64 _v319, bkr_i64 _v387, bkr_i64 _v345, bkr_i64 _v431, bkr_i64 _v432) {
    _v430 _v463 = _v461(_v319, _v387, _v345, _v431, _v432);
    return (_v433){._v342 = ((bkr_i64)(_v462(_v463)))};
}

_v433 _v471(_v433 _v472, bkr_i64 _v339, bkr_i64 _v340) {
    bkr_i64 _v463 = _v473(_v472);
    vec_set(_v463, _v269, _v339);
    vec_set(_v463, _v270, _v340);
    return _v472;
}

bkr_i64 _v474(bkr_i64 _v319) {
    return _v453(_v445(_v319));
}

bkr_i64 _v475(bkr_i64 _v447, bkr_i64 _v387) {
    _v451(_v476(_v447), _v387);
    return _v447;
}

bkr_i64 _v477(bkr_i64 _v447) {
    return vec_get(_v447, 0);
}

bkr_i64 _v478(bkr_i64 _v447) {
    return _v477(_v447);
}

_v338 _v479(bkr_i64 _v339, bkr_i64 _v340) {
    return (_v338){._v339 = _v339, ._v340 = _v340};
}

_v338 _v480(void) {
    return _v479(_v268, _v268);
}

bkr_i64 _v481(_v338 _v457) {
    return _v457._v339;
}

bkr_i64 _v482(_v338 _v457) {
    return _v457._v340;
}

bkr_bool _v483(_v338 _v457) {
    return ((_v457._v339 != _v268) && (_v457._v340 != _v268));
}

bkr_i64 _v484(bkr_i64 _v447) {
    return vec_get(_v447, _v269);
}

bkr_i64 _v485(bkr_i64 _v447) {
    return vec_get(_v447, _v270);
}

_v338 _v486(bkr_i64 _v447) {
    return _v479(_v484(_v447), _v485(_v447));
}

bkr_bool _v487(bkr_i64 _v447) {
    return _v483(_v486(_v447));
}

bkr_i64 _v488(bkr_i64 _v447, bkr_i64 _v339, bkr_i64 _v340) {
    _v454(_v476(_v447), _v339, _v340);
    return _v447;
}

bkr_i64 _v489(bkr_i64 _v447, _v338 _v457) {
    _v456(_v476(_v447), _v457);
    return _v447;
}

bkr_bool _v490(bkr_i64 _v447, bkr_i64 _v362) {
    return (vec_len(_v447) > (_v362 + _v271));
}

bkr_i64 _v491(bkr_i64 _v447) {
    return _v331(_v477(_v447));
}

bkr_bool _v492(bkr_i64 _v447) {
    return _v332(_v477(_v447));
}

bkr_bool _v493(bkr_i64 _v447) {
    return _v333(_v477(_v447));
}

bkr_bool _v494(bkr_i64 _v447) {
    return _v334(_v477(_v447));
}

bkr_bool _v495(bkr_i64 _v447) {
    return _v335(_v477(_v447));
}

bkr_str _v496(bkr_i64 _v447) {
    bkr_i64 _v330 = _v491(_v447);
    return bkr_str_concat(bkr_str_concat(_v329(_v330), ":"), _v318(_v477(_v447)));
}

bkr_bool _v497(bkr_i64 _v447) {
    return (_v477(_v447) == _v245);
}

bkr_bool _v498(bkr_i64 _v447) {
    return (_v477(_v447) == _v244);
}

bkr_bool _v499(bkr_i64 _v447) {
    return (_v477(_v447) == _v227);
}

bkr_bool _v500(bkr_i64 _v447) {
    return (_v477(_v447) == _v232);
}

bkr_bool _v501(bkr_i64 _v447) {
    return (_v477(_v447) == _v224);
}

bkr_bool _v502(bkr_i64 _v447) {
    return (_v477(_v447) == _v249);
}

bkr_bool _v503(bkr_i64 _v447) {
    return (_v477(_v447) == _v254);
}

bkr_i64 _v504(bkr_i64 _v447, bkr_i64 _v362) {
    return vec_get(_v447, (_v362 + _v271));
}

bkr_i64 _v505(bkr_i64 _v447) {
    return ((bkr_i64)(_v447));
}

_v341 _v506(bkr_i64 _v342) {
    return (_v341){._v342 = _v342};
}

_v341 _v476(bkr_i64 _v447) {
    return _v506(_v505(_v447));
}

bkr_i64 _v507(_v341 _v452) {
    return _v452._v342;
}

bkr_i64 _v453(_v341 _v452) {
    return _v508(_v507(_v452));
}

bkr_i64 _v509(_v341 _v452) {
    return _v478(_v453(_v452));
}

bkr_i64 _v510(_v341 _v452) {
    return _v491(_v453(_v452));
}

bkr_i64 _v511(_v341 _v452) {
    return _v484(_v453(_v452));
}

bkr_i64 _v512(_v341 _v452) {
    return _v485(_v453(_v452));
}

bkr_i64 _v508(bkr_i64 _v342) {
    return ((bkr_i64)(_v342));
}

_v341 _v513(bkr_i64 _v342) {
    return _v506(_v342);
}

bkr_i64 _v514(bkr_i64 _v515) {
    return _v505(_v515);
}

_v346 _v516(bkr_i64 _v342) {
    return (_v346){._v342 = _v342};
}

_v346 _v517(bkr_i64 _v515) {
    return _v516(_v514(_v515));
}

_v346 _v518(_v341 _v452) {
    return _v516(_v507(_v452));
}

bkr_i64 _v519(_v346 _v520) {
    return _v520._v342;
}

bkr_i64 _v521(_v346 _v520) {
    return _v519(_v520);
}

bkr_bool _v522(_v346 _v520) {
    return _v523(_v519(_v520));
}

bkr_bool _v524(_v346 _v520) {
    return _v525(_v519(_v520));
}

bkr_i64 _v526(_v346 _v520) {
    return _v508(_v519(_v520));
}

_v343 _v527(_v346 _v520) {
    return _v528(_v526(_v520));
}

bkr_i64 _v529(_v346 _v520) {
    _v343 _v530 = _v527(_v520);
    return _v530._v319;
}

bkr_i64 _v531(_v346 _v520) {
    _v343 _v530 = _v527(_v520);
    if ((_v530._v319 == 7)) {
        return _v530._v344;
    }
    return (-1);
}

bkr_i64 _v532(_v346 _v520) {
    _v343 _v530 = _v527(_v520);
    if (((_v530._v319 == 6) || (_v530._v319 == 8))) {
        return _v530._v344;
    }
    return _v316;
}

bkr_i64 _v533(_v346 _v520) {
    _v343 _v530 = _v527(_v520);
    if ((_v530._v319 == 6)) {
        return _v530._v345;
    }
    return (-1);
}

bkr_i64 _v534(_v346 _v520) {
    _v343 _v530 = _v527(_v520);
    return _v530._v344;
}

bkr_i64 _v535(_v346 _v520) {
    _v343 _v530 = _v527(_v520);
    return _v530._v345;
}

bkr_i64 _v536(bkr_i64 _v368) {
    return _v505(_v368);
}

_v426 _v537(bkr_i64 _v342) {
    return (_v426){._v342 = _v342};
}

_v426 _v538(bkr_i64 _v368) {
    return _v537(_v536(_v368));
}

_v426 _v539(_v341 _v452) {
    return _v537(_v507(_v452));
}

bkr_i64 _v540(_v426 _v541) {
    return _v541._v342;
}

bkr_i64 _v542(_v426 _v541) {
    return _v540(_v541);
}

bkr_i64 _v543(_v426 _v541) {
    return _v508(_v540(_v541));
}

bkr_i64 _v544(_v426 _v541) {
    return _v478(_v543(_v541));
}

bkr_i64 _v545(_v426 _v541) {
    return _v511(_v546(_v541));
}

bkr_i64 _v547(_v426 _v541) {
    return _v512(_v546(_v541));
}

bkr_i64 _v548(bkr_i64 _v370) {
    return _v505(_v370);
}

_v427 _v549(bkr_i64 _v342) {
    return (_v427){._v342 = _v342};
}

_v427 _v550(bkr_i64 _v370) {
    return _v549(_v548(_v370));
}

_v427 _v551(_v341 _v452) {
    return _v549(_v507(_v452));
}

bkr_i64 _v552(_v427 _v553) {
    return _v553._v342;
}

bkr_i64 _v554(_v427 _v553) {
    return _v508(_v552(_v553));
}

bkr_i64 _v555(_v427 _v553) {
    return _v478(_v554(_v553));
}

bkr_i64 _v556(bkr_i64 _v557) {
    return _v505(_v557);
}

_v428 _v558(bkr_i64 _v342) {
    return (_v428){._v342 = _v342};
}

_v428 _v559(bkr_i64 _v557) {
    return _v558(_v556(_v557));
}

_v428 _v560(_v341 _v452) {
    return _v558(_v507(_v452));
}

bkr_i64 _v561(_v428 _v562) {
    return _v562._v342;
}

_v428 _v563(void) {
    return _v558(_v564());
}

bkr_bool _v565(_v428 _v562) {
    return _v523(_v561(_v562));
}

bkr_bool _v566(_v428 _v562) {
    return _v525(_v561(_v562));
}

bkr_i64 _v567(_v428 _v562) {
    return _v508(_v561(_v562));
}

bkr_i64 _v568(_v428 _v562) {
    return _v478(_v567(_v562));
}

_v338 _v569(_v426 _v541) {
    return _v486(_v543(_v541));
}

_v338 _v570(_v427 _v553) {
    return _v486(_v554(_v553));
}

_v338 _v571(_v428 _v562) {
    return _v486(_v567(_v562));
}

bkr_i64 _v572(_v426 _v541) {
    bkr_i64 _v573 = _v544(_v541);
    if ((((((_v573 == 24) || (_v573 == 29)) || (_v573 == 25)) || (_v573 == 26)) || (_v573 == 23))) {
        return 0;
    }
    if ((_v573 == 20)) {
        return 1;
    }
    if ((_v573 == 21)) {
        return 2;
    }
    if ((_v573 == 22)) {
        return 3;
    }
    if ((_v573 == 39)) {
        return 4;
    }
    if ((_v573 == 31)) {
        return 5;
    }
    if ((_v573 == 34)) {
        return 6;
    }
    if ((_v573 == 19)) {
        return 7;
    }
    if ((_v573 == 28)) {
        return 8;
    }
    if ((_v573 == 30)) {
        return 9;
    }
    if ((_v573 == 17)) {
        return 10;
    }
    if ((_v573 == 35)) {
        return 11;
    }
    if ((_v573 == 36)) {
        return 12;
    }
    if ((_v573 == 5)) {
        return 13;
    }
    return 14;
}

bkr_i64 _v574(_v427 _v553) {
    bkr_i64 _v573 = _v555(_v553);
    if ((_v573 == 6)) {
        return 0;
    }
    if ((_v573 == 11)) {
        return 1;
    }
    if ((_v573 == 10)) {
        return 2;
    }
    if ((_v573 == 7)) {
        return 3;
    }
    if ((_v573 == 16)) {
        return 4;
    }
    if ((_v573 == 9)) {
        return 5;
    }
    if ((_v573 == 14)) {
        return 6;
    }
    if ((_v573 == 15)) {
        return 7;
    }
    if ((_v573 == 12)) {
        return 8;
    }
    if ((_v573 == 13)) {
        return 9;
    }
    return 10;
}

bkr_i64 _v575(_v428 _v562) {
    bkr_i64 _v573 = _v568(_v562);
    if ((_v573 == 2)) {
        return 0;
    }
    if ((_v573 == 27)) {
        return 1;
    }
    if ((_v573 == 32)) {
        return 2;
    }
    if ((_v573 == 37)) {
        return 3;
    }
    if ((_v573 == 38)) {
        return 4;
    }
    if ((_v573 == 1)) {
        return 5;
    }
    return 6;
}

bkr_i64 _v576(bkr_i64 _v577) {
    return _v505(_v577);
}

_v429 _v578(bkr_i64 _v342) {
    return (_v429){._v342 = _v342};
}

_v429 _v579(bkr_i64 _v577) {
    return _v578(_v576(_v577));
}

_v429 _v580(_v341 _v452) {
    return _v578(_v507(_v452));
}

bkr_i64 _v581(_v429 _v582) {
    return _v582._v342;
}

bkr_i64 _v583(_v429 _v582) {
    return _v581(_v582);
}

bkr_i64 _v584(_v429 _v582) {
    return _v508(_v581(_v582));
}

_v341 _v585(_v346 _v520) {
    return _v506(_v519(_v520));
}

_v341 _v546(_v426 _v541) {
    return _v506(_v540(_v541));
}

_v341 _v586(_v427 _v553) {
    return _v506(_v552(_v553));
}

_v341 _v587(_v428 _v562) {
    return _v506(_v561(_v562));
}

_v341 _v588(_v429 _v582) {
    return _v506(_v581(_v582));
}

bkr_i64 _v589(_v429 _v582) {
    return (vec_len(_v584(_v582)) - _v272);
}

bkr_i64 _v590(bkr_i64 _v463) {
    return ((bkr_i64)(_v463));
}

_v433 _v591(bkr_i64 _v342) {
    return (_v433){._v342 = _v342};
}

_v433 _v592(bkr_i64 _v463) {
    return _v591(_v590(_v463));
}

bkr_i64 _v593(_v433 _v472) {
    return _v472._v342;
}

bkr_i64 _v473(_v433 _v472) {
    return _v594(_v593(_v472));
}

_v430 _v595(_v433 _v472) {
    return _v464(_v473(_v472));
}

bkr_i64 _v596(_v433 _v472) {
    _v430 _v463 = _v595(_v472);
    return _v463._v319;
}

bkr_i64 _v597(_v433 _v472) {
    _v430 _v463 = _v595(_v472);
    return _v463._v387;
}

bkr_i64 _v598(_v433 _v472) {
    _v430 _v463 = _v595(_v472);
    return _v463._v345;
}

bkr_i64 _v599(_v433 _v472) {
    _v430 _v463 = _v595(_v472);
    return _v463._v431;
}

bkr_i64 _v600(_v433 _v472) {
    _v430 _v463 = _v595(_v472);
    return _v463._v432;
}

bkr_i64 _v601(_v433 _v472) {
    _v430 _v463 = _v595(_v472);
    return _v463._v339;
}

bkr_i64 _v602(_v433 _v472) {
    _v430 _v463 = _v595(_v472);
    return _v463._v340;
}

bkr_i64 _v594(bkr_i64 _v342) {
    return ((bkr_i64)(_v342));
}

_v434 _v603(bkr_i64 _v342) {
    return (_v434){._v342 = _v342};
}

_v434 _v604(bkr_i64 _v605) {
    return _v603(((bkr_i64)(_v605)));
}

bkr_i64 _v606(_v434 _v607) {
    return _v607._v342;
}

bkr_i64 _v608(_v434 _v607) {
    return ((bkr_i64)(_v606(_v607)));
}

bkr_i64 _v609(bkr_i64 _v342) {
    return _v608(_v603(_v342));
}

_v435 _v610(bkr_i64 _v342) {
    return (_v435){._v342 = _v342};
}

_v435 _v611(bkr_i64 _v612) {
    return _v610(((bkr_i64)(_v612)));
}

bkr_i64 _v613(_v435 _v614) {
    return _v614._v342;
}

bkr_i64 _v615(_v435 _v614) {
    return ((bkr_i64)(_v613(_v614)));
}

bkr_i64 _v616(bkr_i64 _v342) {
    return _v615(_v610(_v342));
}

_v436 _v617(bkr_i64 _v342) {
    return (_v436){._v342 = _v342};
}

_v436 _v618(bkr_i64 _v406) {
    return _v617(((bkr_i64)(_v406)));
}

bkr_i64 _v619(_v436 _v620) {
    return _v620._v342;
}

bkr_i64 _v621(_v436 _v620) {
    return ((bkr_i64)(_v619(_v620)));
}

bkr_i64 _v622(bkr_i64 _v342) {
    return _v621(_v617(_v342));
}

_v437 _v623(bkr_i64 _v342) {
    return (_v437){._v342 = _v342};
}

_v437 _v624(bkr_i64 _v612) {
    return _v623(((bkr_i64)(_v612)));
}

bkr_i64 _v625(_v437 _v614) {
    return _v614._v342;
}

bkr_i64 _v626(_v437 _v614) {
    return ((bkr_i64)(_v625(_v614)));
}

bkr_i64 _v627(bkr_i64 _v342) {
    return _v626(_v623(_v342));
}

bkr_i64 _v628(bkr_i64 _v605) {
    return _v606(_v604(_v605));
}

bkr_i64 _v629(bkr_i64 _v612) {
    return _v613(_v611(_v612));
}

bkr_i64 _v630(bkr_i64 _v406) {
    return _v619(_v618(_v406));
}

bkr_i64 _v631(bkr_i64 _v612) {
    return _v625(_v624(_v612));
}

bkr_i64 _v632(bkr_i64 _v605, bkr_i64 _v447) {
    _v633(_v604(_v605), _v447);
    return _v605;
}

_v434 _v633(_v434 _v607, bkr_i64 _v447) {
    vec_push(_v608(_v607), _v505(_v447));
    return _v607;
}

_v434 _v634(_v434 _v607, _v341 _v452) {
    vec_push(_v608(_v607), _v507(_v452));
    return _v607;
}

_v434 _v635(_v434 _v607, _v426 _v541) {
    return _v634(_v607, _v546(_v541));
}

_v434 _v636(_v434 _v607, _v428 _v562) {
    return _v634(_v607, _v587(_v562));
}

_v434 _v637(_v434 _v607, _v429 _v582) {
    return _v634(_v607, _v588(_v582));
}

bkr_i64 _v638(bkr_i64 _v406, bkr_i64 _v463) {
    _v639(_v618(_v406), _v463);
    return _v406;
}

_v436 _v639(_v436 _v620, bkr_i64 _v463) {
    vec_push(_v621(_v620), _v590(_v463));
    return _v620;
}

_v436 _v640(_v436 _v620, _v433 _v472) {
    vec_push(_v621(_v620), _v593(_v472));
    return _v620;
}

bkr_i64 _v641(bkr_i64 _v612, bkr_i64 _v387) {
    _v642(_v611(_v612), _v387);
    return _v612;
}

_v435 _v642(_v435 _v614, bkr_i64 _v387) {
    vec_push(_v615(_v614), _v387);
    return _v614;
}

bkr_i64 _v643(bkr_i64 _v447, bkr_i64 _v362) {
    return _v508(_v504(_v447, _v362));
}

bkr_i64 _v644(bkr_i64 _v447, bkr_i64 _v362) {
    return _v608(_v645(_v447, _v362));
}

_v434 _v645(bkr_i64 _v447, bkr_i64 _v362) {
    return _v603(_v504(_v447, _v362));
}

bkr_i64 _v646(bkr_i64 _v447, bkr_i64 _v362) {
    return _v615(_v647(_v447, _v362));
}

_v435 _v647(bkr_i64 _v447, bkr_i64 _v362) {
    return _v610(_v504(_v447, _v362));
}

bkr_i64 _v648(bkr_i64 _v447, bkr_i64 _v362) {
    return _v621(_v649(_v447, _v362));
}

_v436 _v649(bkr_i64 _v447, bkr_i64 _v362) {
    return _v617(_v504(_v447, _v362));
}

bkr_i64 _v650(bkr_i64 _v447, bkr_i64 _v362) {
    return _v626(_v651(_v447, _v362));
}

_v437 _v651(bkr_i64 _v447, bkr_i64 _v362) {
    return _v623(_v504(_v447, _v362));
}

bkr_i64 _v564(void) {
    return 0;
}

bkr_bool _v523(bkr_i64 _v387) {
    return (_v387 == 0);
}

bkr_bool _v525(bkr_i64 _v387) {
    return (_v387 != 0);
}

bkr_i64 _v652(bkr_i64 _v387) {
    return _v508(_v387);
}

bkr_i64 _v653(bkr_i64 _v515) {
    if (_v523(_v515)) {
        return _v316;
    }
    _v343 _v530 = _v528(_v508(_v515));
    return _v530._v319;
}

bkr_i64 _v654(bkr_i64 _v515) {
    if (_v523(_v515)) {
        return (-1);
    }
    _v343 _v530 = _v528(_v508(_v515));
    if ((_v530._v319 == 7)) {
        return _v530._v344;
    }
    return (-1);
}

bkr_i64 _v655(bkr_i64 _v515) {
    if (_v523(_v515)) {
        return _v316;
    }
    _v343 _v530 = _v528(_v508(_v515));
    if ((_v530._v319 == 6)) {
        return _v530._v344;
    }
    return _v316;
}

bkr_i64 _v656(bkr_i64 _v515) {
    if (_v523(_v515)) {
        return (-1);
    }
    _v343 _v530 = _v528(_v508(_v515));
    if ((_v530._v319 == 6)) {
        return _v530._v345;
    }
    return (-1);
}

bkr_i64 _v657(bkr_i64 _v515) {
    if (_v523(_v515)) {
        return 0;
    }
    _v343 _v530 = _v528(_v508(_v515));
    return _v530._v344;
}

bkr_i64 _v658(bkr_i64 _v515) {
    if (_v523(_v515)) {
        return (-1);
    }
    _v343 _v530 = _v528(_v508(_v515));
    return _v530._v345;
}

bkr_i64 _v659(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

_v347 _v660(_v426 _v541) {
    return _v661(_v543(_v541));
}

bkr_i64 _v662(_v426 _v541) {
    return _v659(_v543(_v541));
}

bkr_i64 _v663(_v341 _v452) {
    return _v659(_v453(_v452));
}

bkr_i64 _v664(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

bkr_i64 _v665(_v426 _v541) {
    return _v664(_v543(_v541));
}

bkr_i64 _v666(bkr_i64 _v447) {
    return _v504(_v447, 2);
}

bkr_i64 _v667(bkr_i64 _v447) {
    return _v504(_v447, 3);
}

bkr_i64 _v668(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

_v348 _v669(_v426 _v541) {
    return _v670(_v543(_v541));
}

bkr_i64 _v671(_v426 _v541) {
    return _v668(_v543(_v541));
}

bkr_i64 _v672(bkr_i64 _v447) {
    return _v643(_v447, 2);
}

bkr_i64 _v673(bkr_i64 _v447) {
    return _v504(_v447, 2);
}

bkr_i64 _v674(_v426 _v541) {
    return _v673(_v543(_v541));
}

bkr_i64 _v675(bkr_i64 _v447) {
    return _v643(_v447, 3);
}

bkr_i64 _v676(bkr_i64 _v447) {
    return _v504(_v447, 3);
}

bkr_i64 _v677(_v426 _v541) {
    return _v676(_v543(_v541));
}

bkr_i64 _v678(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

_v352 _v679(_v426 _v541) {
    return _v680(_v543(_v541));
}

bkr_i64 _v681(_v426 _v541) {
    return _v678(_v543(_v541));
}

bkr_i64 _v682(bkr_i64 _v447) {
    return _v643(_v447, 2);
}

bkr_i64 _v683(bkr_i64 _v447) {
    return _v504(_v447, 2);
}

bkr_i64 _v684(_v426 _v541) {
    return _v683(_v543(_v541));
}

bkr_i64 _v685(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

_v354 _v686(_v426 _v541) {
    return _v687(_v543(_v541));
}

bkr_i64 _v688(_v426 _v541) {
    return _v685(_v543(_v541));
}

bkr_i64 _v689(bkr_i64 _v447) {
    return _v608(_v690(_v447));
}

_v434 _v690(bkr_i64 _v447) {
    return _v645(_v447, 2);
}

_v434 _v691(_v426 _v541) {
    return _v690(_v543(_v541));
}

bkr_i64 _v692(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

bkr_i64 _v693(_v426 _v541) {
    return _v692(_v543(_v541));
}

_v426 _v694(_v426 _v541) {
    return _v537(_v692(_v543(_v541)));
}

bkr_i64 _v695(bkr_i64 _v447) {
    return _v504(_v447, 2);
}

bkr_i64 _v696(_v426 _v541) {
    return _v695(_v543(_v541));
}

_v434 _v697(bkr_i64 _v447) {
    return _v645(_v447, 3);
}

_v434 _v698(_v426 _v541) {
    return _v697(_v543(_v541));
}

bkr_i64 _v699(bkr_i64 _v447) {
    return _v608(_v700(_v447));
}

_v434 _v700(bkr_i64 _v447) {
    return _v645(_v447, 1);
}

_v434 _v701(_v426 _v541) {
    return _v700(_v543(_v541));
}

bkr_i64 _v702(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

bkr_i64 _v703(_v426 _v541) {
    return _v702(_v543(_v541));
}

_v426 _v704(_v426 _v541) {
    return _v537(_v703(_v541));
}

bkr_i64 _v705(bkr_i64 _v447) {
    return _v504(_v447, 2);
}

bkr_i64 _v706(_v426 _v541) {
    return _v705(_v543(_v541));
}

bkr_i64 _v707(bkr_i64 _v447) {
    return _v643(_v447, 1);
}

bkr_i64 _v708(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

_v360 _v709(_v426 _v541) {
    return _v710(_v543(_v541));
}

bkr_i64 _v711(_v426 _v541) {
    return _v708(_v543(_v541));
}

bkr_i64 _v712(bkr_i64 _v447) {
    return _v643(_v447, 2);
}

bkr_i64 _v713(bkr_i64 _v447) {
    return _v504(_v447, 2);
}

bkr_i64 _v714(_v426 _v541) {
    return _v713(_v543(_v541));
}

bkr_i64 _v715(bkr_i64 _v447) {
    return _v643(_v447, 1);
}

bkr_i64 _v716(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

_v363 _v717(_v426 _v541) {
    return _v718(_v543(_v541));
}

bkr_i64 _v719(_v426 _v541) {
    return _v716(_v543(_v541));
}

_v426 _v720(_v426 _v541) {
    return _v537(_v719(_v541));
}

bkr_i64 _v721(bkr_i64 _v447) {
    return _v504(_v447, 2);
}

bkr_i64 _v722(_v426 _v541) {
    return _v721(_v543(_v541));
}

bkr_i64 _v723(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

bkr_i64 _v724(_v426 _v541) {
    return _v723(_v543(_v541));
}

bkr_i64 _v725(bkr_i64 _v447) {
    return _v615(_v726(_v447));
}

_v435 _v726(bkr_i64 _v447) {
    return _v647(_v447, 2);
}

_v435 _v727(_v426 _v541) {
    return _v726(_v543(_v541));
}

bkr_i64 _v728(bkr_i64 _v447) {
    return _v608(_v729(_v447));
}

_v434 _v729(bkr_i64 _v447) {
    return _v645(_v447, 3);
}

_v434 _v730(_v426 _v541) {
    return _v729(_v543(_v541));
}

bkr_i64 _v731(bkr_i64 _v447) {
    return _v643(_v447, 1);
}

bkr_i64 _v732(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

bkr_i64 _v733(_v426 _v541) {
    return _v732(_v543(_v541));
}

bkr_i64 _v734(bkr_i64 _v447) {
    return _v643(_v447, 2);
}

bkr_i64 _v735(bkr_i64 _v447) {
    return _v504(_v447, 2);
}

bkr_i64 _v736(_v426 _v541) {
    return _v735(_v543(_v541));
}

bkr_i64 _v737(bkr_i64 _v447) {
    return _v643(_v447, 3);
}

bkr_i64 _v738(bkr_i64 _v447) {
    return _v504(_v447, 3);
}

bkr_i64 _v739(_v426 _v541) {
    return _v738(_v543(_v541));
}

bkr_i64 _v740(bkr_i64 _v447) {
    return _v643(_v447, 1);
}

bkr_i64 _v741(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

bkr_i64 _v742(_v426 _v541) {
    return _v741(_v543(_v541));
}

bkr_i64 _v743(bkr_i64 _v447) {
    return _v621(_v744(_v447));
}

_v436 _v744(bkr_i64 _v447) {
    return _v649(_v447, 2);
}

_v436 _v745(_v426 _v541) {
    return _v744(_v543(_v541));
}

bkr_i64 _v746(bkr_i64 _v447) {
    return _v608(_v747(_v447));
}

_v434 _v747(bkr_i64 _v447) {
    return _v645(_v447, 3);
}

_v434 _v748(_v426 _v541) {
    return _v747(_v543(_v541));
}

_v435 _v749(bkr_i64 _v447) {
    return _v647(_v447, 4);
}

_v435 _v750(_v426 _v541) {
    return _v749(_v543(_v541));
}

bkr_i64 _v751(bkr_i64 _v463) {
    _v430 _v752 = _v464(_v463);
    return _v752._v319;
}

bkr_i64 _v753(bkr_i64 _v463) {
    _v430 _v752 = _v464(_v463);
    return _v752._v387;
}

bkr_i64 _v754(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

_v364 _v755(_v427 _v553) {
    return _v756(_v554(_v553));
}

bkr_i64 _v757(_v427 _v553) {
    return _v754(_v554(_v553));
}

bkr_i64 _v758(bkr_i64 _v447) {
    return _v759(_v447);
}

bkr_i64 _v759(bkr_i64 _v447) {
    return _v504(_v447, 2);
}

bkr_i64 _v760(_v427 _v553) {
    return _v759(_v554(_v553));
}

bkr_i64 _v761(bkr_i64 _v447) {
    return _v762(_v447);
}

bkr_i64 _v762(bkr_i64 _v447) {
    return _v504(_v447, 3);
}

bkr_i64 _v763(_v427 _v553) {
    return _v762(_v554(_v553));
}

bkr_i64 _v764(bkr_i64 _v447) {
    return _v765(_v447);
}

bkr_i64 _v765(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

_v367 _v766(_v427 _v553) {
    return _v767(_v554(_v553));
}

bkr_i64 _v768(_v427 _v553) {
    return _v765(_v554(_v553));
}

bkr_i64 _v769(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

_v369 _v770(_v427 _v553) {
    return _v771(_v554(_v553));
}

bkr_i64 _v772(_v427 _v553) {
    return _v769(_v554(_v553));
}

_v427 _v773(_v427 _v553) {
    return _v549(_v772(_v553));
}

bkr_i64 _v774(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

_v371 _v775(_v426 _v541) {
    return _v776(_v543(_v541));
}

bkr_i64 _v777(_v426 _v541) {
    return _v774(_v543(_v541));
}

_v426 _v778(_v426 _v541) {
    return _v537(_v777(_v541));
}

bkr_i64 _v779(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

bkr_i64 _v780(bkr_i64 _v447) {
    return _v504(_v447, 2);
}

bkr_i64 _v781(_v426 _v541) {
    return _v779(_v543(_v541));
}

bkr_i64 _v782(_v426 _v541) {
    return _v780(_v543(_v541));
}

_v426 _v783(_v426 _v541) {
    return _v537(_v781(_v541));
}

_v346 _v784(_v426 _v541) {
    return _v516(_v782(_v541));
}

_v374 _v785(_v427 _v553) {
    return _v786(_v554(_v553));
}

_v378 _v787(_v427 _v553) {
    return _v788(_v554(_v553));
}

_v380 _v789(_v427 _v553) {
    return _v790(_v554(_v553));
}

_v384 _v791(_v427 _v553) {
    return _v792(_v554(_v553));
}

_v385 _v793(_v427 _v553) {
    return _v794(_v554(_v553));
}

_v388 _v795(_v427 _v553) {
    return _v796(_v554(_v553));
}

_v389 _v797(_v427 _v553) {
    return _v798(_v554(_v553));
}

_v390 _v799(_v427 _v553) {
    return _v800(_v554(_v553));
}

_v391 _v801(_v429 _v582) {
    return _v802(_v584(_v582));
}

_v392 _v803(_v426 _v541) {
    return _v804(_v543(_v541));
}

_v395 _v805(_v426 _v541) {
    return _v806(_v543(_v541));
}

_v400 _v807(_v426 _v541) {
    return _v808(_v543(_v541));
}

_v404 _v809(_v426 _v541) {
    return _v810(_v543(_v541));
}

_v409 _v811(_v341 _v452) {
    return _v812(_v453(_v452));
}

_v410 _v813(_v428 _v562) {
    return _v814(_v567(_v562));
}

_v413 _v815(_v428 _v562) {
    return _v816(_v567(_v562));
}

_v414 _v817(_v341 _v452) {
    return _v818(_v453(_v452));
}

_v415 _v819(_v428 _v562) {
    return _v820(_v567(_v562));
}

_v417 _v821(_v428 _v562) {
    return _v822(_v567(_v562));
}

_v422 _v823(_v341 _v452) {
    return _v824(_v453(_v452));
}

bkr_i64 _v825(bkr_i64 _v447) {
    return _v643(_v447, 1);
}

bkr_i64 _v826(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

bkr_i64 _v827(_v427 _v553) {
    return _v826(_v554(_v553));
}

bkr_i64 _v828(bkr_i64 _v447) {
    return _v643(_v447, 2);
}

_v429 _v829(_v427 _v553) {
    return _v579(_v828(_v554(_v553)));
}

bkr_i64 _v830(bkr_i64 _v447) {
    return _v831(_v447);
}

bkr_i64 _v831(bkr_i64 _v447) {
    return _v504(_v447, 3);
}

bkr_i64 _v832(_v427 _v553) {
    return _v831(_v554(_v553));
}

bkr_i64 _v833(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

bkr_i64 _v834(_v427 _v553) {
    return _v833(_v554(_v553));
}

bkr_i64 _v835(bkr_i64 _v447) {
    return _v643(_v447, 2);
}

bkr_i64 _v836(bkr_i64 _v447) {
    return _v504(_v447, 2);
}

bkr_i64 _v837(_v427 _v553) {
    return _v836(_v554(_v553));
}

bkr_i64 _v838(bkr_i64 _v447) {
    return _v643(_v447, 3);
}

bkr_i64 _v839(bkr_i64 _v447) {
    return _v504(_v447, 3);
}

bkr_i64 _v840(_v427 _v553) {
    return _v839(_v554(_v553));
}

bkr_i64 _v841(bkr_i64 _v447) {
    return _v504(_v447, 4);
}

bkr_i64 _v842(_v427 _v553) {
    return _v841(_v554(_v553));
}

bkr_i64 _v843(bkr_i64 _v447) {
    return _v643(_v447, 5);
}

_v429 _v844(_v427 _v553) {
    return _v579(_v843(_v554(_v553)));
}

bkr_i64 _v845(bkr_i64 _v447) {
    return _v643(_v447, 1);
}

_v429 _v846(_v427 _v553) {
    return _v579(_v845(_v554(_v553)));
}

bkr_i64 _v847(bkr_i64 _v447) {
    return _v643(_v447, 1);
}

bkr_i64 _v848(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

bkr_i64 _v849(_v427 _v553) {
    return _v848(_v554(_v553));
}

bkr_i64 _v850(bkr_i64 _v447) {
    return _v643(_v447, 2);
}

_v429 _v851(_v427 _v553) {
    return _v579(_v850(_v554(_v553)));
}

bkr_i64 _v852(bkr_i64 _v447) {
    return _v643(_v447, 1);
}

bkr_i64 _v853(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

bkr_i64 _v854(_v427 _v553) {
    return _v853(_v554(_v553));
}

bkr_i64 _v855(bkr_i64 _v447) {
    return _v643(_v447, 2);
}

bkr_i64 _v856(bkr_i64 _v447) {
    return _v504(_v447, 2);
}

bkr_i64 _v857(_v427 _v553) {
    return _v856(_v554(_v553));
}

bkr_i64 _v858(bkr_i64 _v447) {
    return _v643(_v447, 1);
}

bkr_i64 _v859(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

bkr_i64 _v860(_v427 _v553) {
    return _v859(_v554(_v553));
}

bkr_i64 _v861(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

bkr_i64 _v862(_v341 _v452) {
    return _v861(_v453(_v452));
}

bkr_i64 _v863(bkr_i64 _v447) {
    return _v643(_v447, 2);
}

bkr_i64 _v864(bkr_i64 _v447) {
    return _v504(_v447, 2);
}

bkr_i64 _v865(_v341 _v452) {
    return _v864(_v453(_v452));
}

_v346 _v866(_v341 _v452) {
    return _v516(_v865(_v452));
}

bkr_i64 _v867(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

bkr_i64 _v868(_v428 _v562) {
    return _v867(_v567(_v562));
}

bkr_i64 _v869(bkr_i64 _v447) {
    return _v608(_v870(_v447));
}

_v434 _v870(bkr_i64 _v447) {
    return _v645(_v447, 2);
}

_v434 _v871(_v428 _v562) {
    return _v870(_v567(_v562));
}

bkr_i64 _v872(bkr_i64 _v447) {
    return _v873(_v447);
}

bkr_i64 _v873(bkr_i64 _v447) {
    return _v504(_v447, 3);
}

bkr_i64 _v874(_v428 _v562) {
    return _v873(_v567(_v562));
}

bkr_i64 _v875(bkr_i64 _v447) {
    return _v643(_v447, 4);
}

_v429 _v876(_v428 _v562) {
    return _v579(_v875(_v567(_v562)));
}

bkr_i64 _v877(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

bkr_i64 _v878(_v428 _v562) {
    return _v877(_v567(_v562));
}

bkr_i64 _v879(bkr_i64 _v447) {
    return _v880(_v447);
}

bkr_i64 _v880(bkr_i64 _v447) {
    return _v504(_v447, 2);
}

bkr_i64 _v881(_v428 _v562) {
    return _v880(_v567(_v562));
}

bkr_i64 _v882(bkr_i64 _v447) {
    return _v883(_v447);
}

bkr_i64 _v883(bkr_i64 _v447) {
    return _v504(_v447, 3);
}

bkr_i64 _v884(_v428 _v562) {
    return _v883(_v567(_v562));
}

bkr_i64 _v885(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

bkr_i64 _v886(_v428 _v562) {
    return _v885(_v567(_v562));
}

bkr_i64 _v887(bkr_i64 _v447) {
    return _v608(_v888(_v447));
}

_v434 _v888(bkr_i64 _v447) {
    return _v645(_v447, 2);
}

_v434 _v889(_v428 _v562) {
    return _v888(_v567(_v562));
}

bkr_i64 _v890(bkr_i64 _v447) {
    return _v504(_v447, 1);
}

bkr_i64 _v891(_v341 _v452) {
    return _v890(_v453(_v452));
}

bkr_i64 _v892(bkr_i64 _v447) {
    return _v893(_v447);
}

bkr_i64 _v893(bkr_i64 _v447) {
    return _v504(_v447, 2);
}

bkr_i64 _v894(_v341 _v452) {
    return _v893(_v453(_v452));
}

_v346 _v895(_v341 _v452) {
    return _v516(_v894(_v452));
}

bkr_i64 _v896(bkr_i64 _v447) {
    return _v608(_v897(_v447));
}

_v434 _v897(bkr_i64 _v447) {
    return _v645(_v447, 2);
}

_v434 _v898(_v341 _v452) {
    return _v897(_v453(_v452));
}

bkr_i64 _v899(bkr_i64 _v447) {
    return _v504(_v447, 3);
}

bkr_i64 _v900(_v341 _v452) {
    return _v899(_v453(_v452));
}

bkr_i64 _v901(bkr_i64 _v447) {
    return _v626(_v902(_v447));
}

bkr_i64 _v903(_v341 _v452) {
    return _v901(_v453(_v452));
}

_v437 _v902(bkr_i64 _v447) {
    return _v651(_v447, 4);
}

_v437 _v904(_v341 _v452) {
    return _v902(_v453(_v452));
}

bkr_i64 _v905(bkr_i64 _v605) {
    return _v906(_v604(_v605));
}

bkr_i64 _v906(_v434 _v607) {
    return vec_len(_v608(_v607));
}

bkr_i64 _v907(bkr_i64 _v605, bkr_i64 _v362) {
    return _v908(_v604(_v605), _v362);
}

bkr_i64 _v908(_v434 _v607, bkr_i64 _v362) {
    return _v508(_v909(_v607, _v362));
}

bkr_i64 _v910(bkr_i64 _v605, bkr_i64 _v362) {
    return _v909(_v604(_v605), _v362);
}

bkr_i64 _v909(_v434 _v607, bkr_i64 _v362) {
    return vec_get(_v608(_v607), _v362);
}

_v341 _v911(bkr_i64 _v605, bkr_i64 _v362) {
    return _v912(_v604(_v605), _v362);
}

_v341 _v912(_v434 _v607, bkr_i64 _v362) {
    return _v506(_v909(_v607, _v362));
}

_v428 _v913(_v434 _v607, bkr_i64 _v362) {
    return _v558(_v909(_v607, _v362));
}

bkr_i64 _v914(bkr_i64 _v612) {
    return _v915(_v611(_v612));
}

bkr_i64 _v915(_v435 _v614) {
    return vec_len(_v615(_v614));
}

bkr_i64 _v916(bkr_i64 _v612, bkr_i64 _v362) {
    return _v917(_v611(_v612), _v362);
}

bkr_i64 _v917(_v435 _v614, bkr_i64 _v362) {
    return vec_get(_v615(_v614), _v362);
}

bkr_i64 _v918(bkr_i64 _v406) {
    return _v919(_v618(_v406));
}

bkr_i64 _v919(_v436 _v620) {
    return vec_len(_v621(_v620));
}

bkr_i64 _v920(bkr_i64 _v406, bkr_i64 _v362) {
    return _v921(_v618(_v406), _v362);
}

bkr_i64 _v921(_v436 _v620, bkr_i64 _v362) {
    return _v594(_v922(_v620, _v362));
}

bkr_i64 _v922(_v436 _v620, bkr_i64 _v362) {
    return vec_get(_v621(_v620), _v362);
}

_v433 _v923(bkr_i64 _v406, bkr_i64 _v362) {
    return _v924(_v618(_v406), _v362);
}

_v433 _v924(_v436 _v620, bkr_i64 _v362) {
    return _v591(_v922(_v620, _v362));
}

bkr_i64 _v925(bkr_i64 _v0) {
    return _v906(_v897(_v0));
}

bkr_i64 _v926(bkr_i64 _v0, bkr_i64 _v362) {
    return _v908(_v897(_v0), _v362);
}

bkr_i64 _v927(bkr_i64 _v0, bkr_i64 _v362) {
    return _v909(_v897(_v0), _v362);
}

bkr_i64 _v928(bkr_i64 _v929) {
    return _v906(_v870(_v929));
}

bkr_i64 _v930(bkr_i64 _v929, bkr_i64 _v362) {
    return _v908(_v870(_v929), _v362);
}

bkr_i64 _v931(bkr_i64 _v932) {
    return _v906(_v888(_v932));
}

bkr_i64 _v933(bkr_i64 _v932, bkr_i64 _v362) {
    return _v908(_v888(_v932), _v362);
}

bkr_i64 _v934(bkr_i64 _v935) {
    return _v906(_v690(_v935));
}

bkr_i64 _v936(bkr_i64 _v935, bkr_i64 _v362) {
    return _v908(_v690(_v935), _v362);
}

bkr_i64 _v937(bkr_i64 _v935, bkr_i64 _v362) {
    return _v909(_v690(_v935), _v362);
}

bkr_i64 _v938(bkr_i64 _v939) {
    return _v906(_v700(_v939));
}

bkr_i64 _v940(bkr_i64 _v939, bkr_i64 _v362) {
    return _v908(_v700(_v939), _v362);
}

bkr_i64 _v941(bkr_i64 _v939, bkr_i64 _v362) {
    return _v909(_v700(_v939), _v362);
}

bkr_i64 _v942(bkr_i64 _v943) {
    return _v919(_v744(_v943));
}

bkr_i64 _v944(bkr_i64 _v943, bkr_i64 _v362) {
    return _v921(_v744(_v943), _v362);
}

bkr_i64 _v945(bkr_i64 _v943, bkr_i64 _v362) {
    return _v908(_v747(_v943), _v362);
}

bkr_i64 _v946(bkr_i64 _v943, bkr_i64 _v362) {
    return _v909(_v747(_v943), _v362);
}

bkr_i64 _v947(bkr_i64 _v447) {
    return _v915(_v726(_v447));
}

bkr_i64 _v948(bkr_i64 _v447, bkr_i64 _v362) {
    return _v917(_v726(_v447), _v362);
}

bkr_i64 _v949(bkr_i64 _v447, bkr_i64 _v362) {
    return _v908(_v729(_v447), _v362);
}

bkr_i64 _v950(bkr_i64 _v447, bkr_i64 _v362) {
    return _v909(_v729(_v447), _v362);
}

_v343 _v951(bkr_i64 _v319) {
    return (_v343){._v319 = _v319, ._v339 = _v268, ._v340 = _v268, ._v344 = 0, ._v345 = (-1)};
}

_v343 _v952(bkr_i64 _v953, bkr_i64 _v954) {
    return (_v343){._v319 = 6, ._v339 = _v268, ._v340 = _v268, ._v344 = _v953, ._v345 = _v954};
}

_v343 _v955(bkr_i64 _v355) {
    return (_v343){._v319 = 7, ._v339 = _v268, ._v340 = _v268, ._v344 = _v355, ._v345 = (-1)};
}

_v343 _v956(bkr_i64 _v319, bkr_i64 _v344, bkr_i64 _v345) {
    return (_v343){._v319 = _v319, ._v339 = _v268, ._v340 = _v268, ._v344 = _v344, ._v345 = _v345};
}

bkr_i64 _v957(_v343 _v958) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v226);
    vec_push(_v447, _v958._v339);
    vec_push(_v447, _v958._v340);
    vec_push(_v447, _v958._v319);
    if ((_v958._v319 == 6)) {
        vec_push(_v447, _v958._v344);
        vec_push(_v447, _v958._v345);
    }
    if ((_v958._v319 == 7)) {
        vec_push(_v447, _v958._v344);
    }
    if (((((_v958._v319 == 8) || (_v958._v319 == 9)) || (_v958._v319 == 10)) || (_v958._v319 == 11))) {
        vec_push(_v447, _v958._v344);
        vec_push(_v447, _v958._v345);
    }
    return _v447;
}

_v343 _v528(bkr_i64 _v447) {
    bkr_i64 _v319 = _v316;
    bkr_i64 _v344 = 0;
    bkr_i64 _v345 = (-1);
    if ((vec_len(_v447) > _v272)) {
        _v319 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v344 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v345 = vec_get(_v447, (_v272 + 2));
    }
    return (_v343){._v319 = _v319, ._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v344 = _v344, ._v345 = _v345};
}

_v346 _v959(bkr_i64 _v319) {
    _v343 _v530 = _v951(_v319);
    return _v516(((bkr_i64)(_v957(_v530))));
}

bkr_i64 _v960(bkr_i64 _v319) {
    return _v526(_v959(_v319));
}

_v346 _v961(bkr_i64 _v953, bkr_i64 _v954) {
    _v343 _v530 = _v952(_v953, _v954);
    return _v516(((bkr_i64)(_v957(_v530))));
}

bkr_i64 _v962(bkr_i64 _v953, bkr_i64 _v954) {
    return _v526(_v961(_v953, _v954));
}

_v346 _v963(bkr_i64 _v355) {
    _v343 _v530 = _v955(_v355);
    return _v516(((bkr_i64)(_v957(_v530))));
}

bkr_i64 _v964(bkr_i64 _v355) {
    return _v526(_v963(_v355));
}

_v346 _v965(bkr_i64 _v319, bkr_i64 _v344, bkr_i64 _v345) {
    _v343 _v530 = _v956(_v319, _v344, _v345);
    return _v516(((bkr_i64)(_v957(_v530))));
}

bkr_i64 _v966(bkr_i64 _v319, bkr_i64 _v344, bkr_i64 _v345) {
    return _v526(_v965(_v319, _v344, _v345));
}

bkr_i64 _v967(bkr_i64 _v319, bkr_i64 _v387) {
    return _v462(_v458(_v319, _v387));
}

bkr_i64 _v968(bkr_i64 _v463) {
    _v430 _v752 = _v464(_v463);
    return _v752._v339;
}

bkr_i64 _v969(bkr_i64 _v463) {
    _v430 _v752 = _v464(_v463);
    return _v752._v340;
}

bkr_i64 _v970(bkr_i64 _v463, bkr_i64 _v339, bkr_i64 _v340) {
    _v471(_v592(_v463), _v339, _v340);
    return _v463;
}

_v404 _v971(bkr_i64 _v405, bkr_i64 _v406, bkr_i64 _v407, bkr_i64 _v408) {
    return (_v404){._v339 = _v268, ._v340 = _v268, ._v405 = _v405, ._v406 = _v406, ._v407 = _v407, ._v408 = _v408};
}

bkr_i64 _v972(_v404 _v368) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v258);
    vec_push(_v447, _v368._v339);
    vec_push(_v447, _v368._v340);
    vec_push(_v447, _v368._v405);
    vec_push(_v447, _v368._v406);
    vec_push(_v447, _v368._v407);
    vec_push(_v447, _v368._v408);
    return _v447;
}

_v404 _v810(bkr_i64 _v447) {
    bkr_i64 _v405 = 0;
    bkr_i64 _v406 = 0;
    bkr_i64 _v407 = 0;
    bkr_i64 _v408 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v405 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v406 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v407 = vec_get(_v447, (_v272 + 2));
    }
    if ((vec_len(_v447) > (_v272 + 3))) {
        _v408 = vec_get(_v447, (_v272 + 3));
    }
    return (_v404){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v405 = _v405, ._v406 = _v406, ._v407 = _v407, ._v408 = _v408};
}

_v426 _v973(_v426 _v974, _v436 _v620, _v434 _v975, _v435 _v976) {
    _v404 _v530 = _v971(_v540(_v974), _v619(_v620), _v606(_v975), _v613(_v976));
    return _v537(((bkr_i64)(_v972(_v530))));
}

bkr_i64 _v977(bkr_i64 _v405, bkr_i64 _v406, bkr_i64 _v407) {
    bkr_i64 _v978 = vec_new();
    return _v543(_v973(_v538(_v405), _v618(_v406), _v604(_v407), _v611(_v978)));
}

_v347 _v979(bkr_i64 _v319, bkr_i64 _v344) {
    return (_v347){._v319 = _v319, ._v339 = _v268, ._v340 = _v268, ._v344 = _v344};
}

bkr_i64 _v980(_v347 _v981) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v981._v319);
    vec_push(_v447, _v981._v339);
    vec_push(_v447, _v981._v340);
    vec_push(_v447, _v981._v344);
    return _v447;
}

_v347 _v661(bkr_i64 _v447) {
    bkr_i64 _v344 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v344 = vec_get(_v447, _v272);
    }
    return (_v347){._v319 = vec_get(_v447, 0), ._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v344 = _v344};
}

_v426 _v982(bkr_i64 _v319, bkr_i64 _v344) {
    _v347 _v530 = _v979(_v319, _v344);
    return _v537(((bkr_i64)(_v980(_v530))));
}

_v426 _v983(bkr_i64 _v387) {
    return _v982(24, _v387);
}

bkr_i64 _v984(bkr_i64 _v387) {
    return _v543(_v983(_v387));
}

_v426 _v985(bkr_str _v387) {
    return _v982(29, ((bkr_i64)(_v387)));
}

bkr_i64 _v986(bkr_str _v387) {
    return _v543(_v985(_v387));
}

_v426 _v987(bkr_i64 _v387) {
    return _v982(25, _v387);
}

bkr_i64 _v988(bkr_i64 _v387) {
    return _v543(_v987(_v387));
}

_v426 _v989(bkr_str _v387) {
    return _v982(26, ((bkr_i64)(_v387)));
}

bkr_i64 _v990(bkr_str _v387) {
    return _v543(_v989(_v387));
}

_v395 _v991(bkr_i64 _v396) {
    return (_v395){._v339 = _v268, ._v340 = _v268, ._v396 = _v396};
}

bkr_i64 _v992(_v395 _v368) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v252);
    vec_push(_v447, _v368._v339);
    vec_push(_v447, _v368._v340);
    vec_push(_v447, _v368._v396);
    return _v447;
}

_v395 _v806(bkr_i64 _v447) {
    bkr_i64 _v396 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v396 = vec_get(_v447, _v272);
    }
    return (_v395){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v396 = _v396};
}

_v426 _v993(_v434 _v994) {
    _v395 _v530 = _v991(_v606(_v994));
    return _v537(((bkr_i64)(_v992(_v530))));
}

bkr_i64 _v995(bkr_i64 _v396) {
    return _v543(_v993(_v604(_v396)));
}

_v397 _v996(bkr_i64 _v398, bkr_i64 _v399) {
    return (_v397){._v339 = _v268, ._v340 = _v268, ._v398 = _v398, ._v399 = _v399};
}

bkr_i64 _v997(_v397 _v368) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v239);
    vec_push(_v447, _v368._v339);
    vec_push(_v447, _v368._v340);
    vec_push(_v447, _v368._v398);
    vec_push(_v447, _v368._v399);
    return _v447;
}

_v397 _v998(bkr_i64 _v447) {
    bkr_i64 _v398 = 0;
    bkr_i64 _v399 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v398 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v399 = vec_get(_v447, (_v272 + 1));
    }
    return (_v397){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v398 = _v398, ._v399 = _v399};
}

_v426 _v999(_v426 _v1000, bkr_i64 _v399) {
    _v397 _v530 = _v996(_v540(_v1000), _v399);
    return _v537(((bkr_i64)(_v997(_v530))));
}

bkr_i64 _v1001(bkr_i64 _v398, bkr_i64 _v399) {
    return _v543(_v999(_v538(_v398), _v399));
}

_v400 _v1002(bkr_i64 _v355, bkr_i64 _v401, bkr_i64 _v402) {
    return (_v400){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v401 = _v401, ._v402 = _v402, ._v403 = 0};
}

_v400 _v1003(bkr_i64 _v355, bkr_i64 _v401, bkr_i64 _v402, bkr_i64 _v403) {
    return (_v400){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v401 = _v401, ._v402 = _v402, ._v403 = _v403};
}

bkr_i64 _v1004(_v400 _v368) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v257);
    vec_push(_v447, _v368._v339);
    vec_push(_v447, _v368._v340);
    vec_push(_v447, _v368._v355);
    vec_push(_v447, _v368._v401);
    vec_push(_v447, _v368._v402);
    vec_push(_v447, _v368._v403);
    return _v447;
}

_v400 _v808(bkr_i64 _v447) {
    bkr_i64 _v355 = 0;
    bkr_i64 _v401 = 0;
    bkr_i64 _v402 = 0;
    bkr_i64 _v403 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v355 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v401 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v402 = vec_get(_v447, (_v272 + 2));
    }
    if ((vec_len(_v447) > (_v272 + 3))) {
        _v403 = vec_get(_v447, (_v272 + 3));
    }
    return (_v400){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v355 = _v355, ._v401 = _v401, ._v402 = _v402, ._v403 = _v403};
}

bkr_i64 _v1005(_v426 _v541) {
    bkr_i64 _v447 = _v543(_v541);
    if ((vec_len(_v447) > (_v272 + 3))) {
        return vec_get(_v447, (_v272 + 3));
    }
    return 0;
}

_v426 _v1006(bkr_i64 _v355, _v435 _v1007, _v434 _v1008, bkr_i64 _v403) {
    _v400 _v530 = _v1003(_v355, _v613(_v1007), _v606(_v1008), _v403);
    return _v537(((bkr_i64)(_v1004(_v530))));
}

_v426 _v1009(bkr_i64 _v355, _v435 _v1007, _v434 _v1008) {
    _v400 _v530 = _v1002(_v355, _v613(_v1007), _v606(_v1008));
    return _v537(((bkr_i64)(_v1004(_v530))));
}

bkr_i64 _v1010(bkr_i64 _v355, bkr_i64 _v401, bkr_i64 _v402) {
    return _v543(_v1009(_v355, _v611(_v401), _v604(_v402)));
}

_v354 _v1011(bkr_i64 _v355, bkr_i64 _v356) {
    return (_v354){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v356 = _v356};
}

bkr_i64 _v1012(_v354 _v1013) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v244);
    vec_push(_v447, _v1013._v339);
    vec_push(_v447, _v1013._v340);
    vec_push(_v447, _v1013._v355);
    vec_push(_v447, _v1013._v356);
    return _v447;
}

_v354 _v687(bkr_i64 _v447) {
    bkr_i64 _v355 = 0;
    bkr_i64 _v356 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v355 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v356 = vec_get(_v447, (_v272 + 1));
    }
    return (_v354){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v355 = _v355, ._v356 = _v356};
}

_v426 _v1014(bkr_i64 _v355, _v434 _v1015) {
    _v354 _v530 = _v1011(_v355, _v606(_v1015));
    return _v537(((bkr_i64)(_v1012(_v530))));
}

bkr_i64 _v1016(bkr_i64 _v355, bkr_i64 _v356) {
    return _v543(_v1014(_v355, _v604(_v356)));
}

_v357 _v1017(bkr_i64 _v358, bkr_i64 _v359, bkr_i64 _v356) {
    return (_v357){._v339 = _v268, ._v340 = _v268, ._v358 = _v358, ._v359 = _v359, ._v356 = _v356};
}

bkr_i64 _v1018(_v357 _v1013) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v261);
    vec_push(_v447, _v1013._v339);
    vec_push(_v447, _v1013._v340);
    vec_push(_v447, _v1013._v358);
    vec_push(_v447, _v1013._v359);
    vec_push(_v447, _v1013._v356);
    return _v447;
}

_v357 _v1019(bkr_i64 _v447) {
    bkr_i64 _v358 = 0;
    bkr_i64 _v359 = 0;
    bkr_i64 _v356 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v358 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v359 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v356 = vec_get(_v447, (_v272 + 2));
    }
    return (_v357){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v358 = _v358, ._v359 = _v359, ._v356 = _v356};
}

_v426 _v1020(_v426 _v1021, bkr_i64 _v359, _v434 _v1015) {
    _v357 _v530 = _v1017(_v540(_v1021), _v359, _v606(_v1015));
    return _v537(((bkr_i64)(_v1018(_v530))));
}

bkr_i64 _v1022(bkr_i64 _v358, bkr_i64 _v359, bkr_i64 _v356) {
    return _v543(_v1020(_v538(_v358), _v359, _v604(_v356)));
}

_v426 _v1023(bkr_i64 _v355) {
    return _v982(23, _v355);
}

bkr_i64 _v1024(_v426 _v1025) {
    return _v662(_v1025);
}

bkr_i64 _v1026(bkr_i64 _v355) {
    return _v543(_v1023(_v355));
}

_v352 _v1027(bkr_i64 _v349, bkr_i64 _v353) {
    return (_v352){._v339 = _v268, ._v340 = _v268, ._v349 = _v349, ._v353 = _v353};
}

bkr_i64 _v1028(_v352 _v1029) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v243);
    vec_push(_v447, _v1029._v339);
    vec_push(_v447, _v1029._v340);
    vec_push(_v447, _v1029._v349);
    vec_push(_v447, _v1029._v353);
    return _v447;
}

_v352 _v680(bkr_i64 _v447) {
    bkr_i64 _v349 = 0;
    bkr_i64 _v353 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v349 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v353 = vec_get(_v447, (_v272 + 1));
    }
    return (_v352){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v349 = _v349, ._v353 = _v353};
}

_v426 _v1030(bkr_i64 _v349, _v426 _v1031) {
    _v352 _v530 = _v1027(_v349, _v540(_v1031));
    return _v537(((bkr_i64)(_v1028(_v530))));
}

bkr_i64 _v1032(bkr_i64 _v349, bkr_i64 _v353) {
    return _v543(_v1030(_v349, _v538(_v353)));
}

_v360 _v1033(bkr_i64 _v361, bkr_i64 _v362) {
    return (_v360){._v339 = _v268, ._v340 = _v268, ._v361 = _v361, ._v362 = _v362};
}

bkr_i64 _v1034(_v360 _v1035) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v253);
    vec_push(_v447, _v1035._v339);
    vec_push(_v447, _v1035._v340);
    vec_push(_v447, _v1035._v361);
    vec_push(_v447, _v1035._v362);
    return _v447;
}

_v360 _v710(bkr_i64 _v447) {
    bkr_i64 _v361 = 0;
    bkr_i64 _v362 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v361 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v362 = vec_get(_v447, (_v272 + 1));
    }
    return (_v360){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v361 = _v361, ._v362 = _v362};
}

_v426 _v1036(_v426 _v1037, _v426 _v1038) {
    _v360 _v530 = _v1033(_v540(_v1037), _v540(_v1038));
    return _v537(((bkr_i64)(_v1034(_v530))));
}

bkr_i64 _v1039(bkr_i64 _v361, bkr_i64 _v362) {
    return _v543(_v1036(_v538(_v361), _v538(_v362)));
}

_v363 _v1040(bkr_i64 _v361, bkr_i64 _v355) {
    return (_v363){._v339 = _v268, ._v340 = _v268, ._v361 = _v361, ._v355 = _v355};
}

bkr_i64 _v1041(_v363 _v1042) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v256);
    vec_push(_v447, _v1042._v339);
    vec_push(_v447, _v1042._v340);
    vec_push(_v447, _v1042._v361);
    vec_push(_v447, _v1042._v355);
    return _v447;
}

_v363 _v718(bkr_i64 _v447) {
    bkr_i64 _v361 = 0;
    bkr_i64 _v355 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v361 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v355 = vec_get(_v447, (_v272 + 1));
    }
    return (_v363){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v361 = _v361, ._v355 = _v355};
}

_v426 _v1043(_v426 _v1037, bkr_i64 _v1044) {
    _v363 _v530 = _v1040(_v540(_v1037), _v1044);
    return _v537(((bkr_i64)(_v1041(_v530))));
}

bkr_i64 _v1045(bkr_i64 _v361, bkr_i64 _v1044) {
    return _v543(_v1043(_v538(_v361), _v1044));
}

_v348 _v1046(bkr_i64 _v349, bkr_i64 _v350, bkr_i64 _v351) {
    return (_v348){._v339 = _v268, ._v340 = _v268, ._v349 = _v349, ._v350 = _v350, ._v351 = _v351};
}

bkr_i64 _v1047(_v348 _v1048) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v242);
    vec_push(_v447, _v1048._v339);
    vec_push(_v447, _v1048._v340);
    vec_push(_v447, _v1048._v349);
    vec_push(_v447, _v1048._v350);
    vec_push(_v447, _v1048._v351);
    return _v447;
}

_v348 _v670(bkr_i64 _v447) {
    bkr_i64 _v349 = 0;
    bkr_i64 _v350 = 0;
    bkr_i64 _v351 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v349 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v350 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v351 = vec_get(_v447, (_v272 + 2));
    }
    return (_v348){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v349 = _v349, ._v350 = _v350, ._v351 = _v351};
}

_v426 _v1049(bkr_i64 _v349, _v426 _v1050, _v426 _v1051) {
    _v348 _v530 = _v1046(_v349, _v540(_v1050), _v540(_v1051));
    return _v537(((bkr_i64)(_v1047(_v530))));
}

bkr_i64 _v1052(bkr_i64 _v349, bkr_i64 _v350, bkr_i64 _v351) {
    return _v543(_v1049(_v349, _v538(_v350), _v538(_v351)));
}

_v392 _v1053(bkr_i64 _v375, bkr_i64 _v393, bkr_i64 _v394) {
    return (_v392){._v339 = _v268, ._v340 = _v268, ._v375 = _v375, ._v393 = _v393, ._v394 = _v394};
}

bkr_i64 _v1054(_v392 _v368) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v250);
    vec_push(_v447, _v368._v339);
    vec_push(_v447, _v368._v340);
    vec_push(_v447, _v368._v375);
    vec_push(_v447, _v368._v393);
    vec_push(_v447, _v368._v394);
    return _v447;
}

_v392 _v804(bkr_i64 _v447) {
    bkr_i64 _v375 = 0;
    bkr_i64 _v393 = 0;
    bkr_i64 _v394 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v375 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v393 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v394 = vec_get(_v447, (_v272 + 2));
    }
    return (_v392){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v375 = _v375, ._v393 = _v393, ._v394 = _v394};
}

_v426 _v1055(_v426 _v1056, _v426 _v1057, _v426 _v1058) {
    _v392 _v530 = _v1053(_v540(_v1056), _v540(_v1057), _v540(_v1058));
    return _v537(((bkr_i64)(_v1054(_v530))));
}

bkr_i64 _v1059(bkr_i64 _v375, bkr_i64 _v393, bkr_i64 _v394) {
    return _v543(_v1055(_v538(_v375), _v538(_v393), _v538(_v394)));
}

_v364 _v1060(bkr_i64 _v355, bkr_i64 _v365, bkr_i64 _v366) {
    return (_v364){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v365 = _v365, ._v366 = _v366};
}

bkr_i64 _v1061(_v364 _v370) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v228);
    vec_push(_v447, _v370._v339);
    vec_push(_v447, _v370._v340);
    vec_push(_v447, _v370._v355);
    vec_push(_v447, _v370._v365);
    vec_push(_v447, _v370._v366);
    return _v447;
}

_v364 _v756(bkr_i64 _v447) {
    bkr_i64 _v355 = 0;
    bkr_i64 _v365 = 0;
    bkr_i64 _v366 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v355 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v365 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v366 = vec_get(_v447, (_v272 + 2));
    }
    return (_v364){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v355 = _v355, ._v365 = _v365, ._v366 = _v366};
}

_v427 _v1062(bkr_i64 _v355, bkr_i64 _v515, bkr_i64 _v366) {
    _v364 _v530 = _v1060(_v355, _v515, _v366);
    return _v549(((bkr_i64)(_v1061(_v530))));
}

bkr_i64 _v1063(bkr_i64 _v355, bkr_i64 _v515, bkr_i64 _v366) {
    return _v554(_v1062(_v355, _v515, _v366));
}

_v367 _v1064(bkr_i64 _v368) {
    return (_v367){._v339 = _v268, ._v340 = _v268, ._v368 = _v368};
}

bkr_i64 _v1065(_v367 _v370) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v229);
    vec_push(_v447, _v370._v339);
    vec_push(_v447, _v370._v340);
    vec_push(_v447, _v370._v368);
    return _v447;
}

_v367 _v767(bkr_i64 _v447) {
    bkr_i64 _v368 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v368 = vec_get(_v447, _v272);
    }
    return (_v367){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v368 = _v368};
}

_v427 _v1066(bkr_i64 _v368) {
    _v367 _v530 = _v1064(_v368);
    return _v549(((bkr_i64)(_v1065(_v530))));
}

bkr_i64 _v1067(bkr_i64 _v368) {
    return _v554(_v1066(_v368));
}

_v369 _v1068(bkr_i64 _v370) {
    return (_v369){._v339 = _v268, ._v340 = _v268, ._v370 = _v370};
}

bkr_i64 _v1069(_v369 _v370) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v238);
    vec_push(_v447, _v370._v339);
    vec_push(_v447, _v370._v340);
    vec_push(_v447, _v370._v370);
    return _v447;
}

_v369 _v771(bkr_i64 _v447) {
    bkr_i64 _v370 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v370 = vec_get(_v447, _v272);
    }
    return (_v369){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v370 = _v370};
}

_v427 _v1070(_v427 _v370) {
    _v369 _v530 = _v1068(_v552(_v370));
    return _v549(((bkr_i64)(_v1069(_v530))));
}

bkr_i64 _v1071(bkr_i64 _v370) {
    return _v554(_v1070(_v550(_v370)));
}

_v371 _v1072(bkr_i64 _v368) {
    return (_v371){._v339 = _v268, ._v340 = _v268, ._v368 = _v368};
}

bkr_i64 _v1073(_v371 _v1074) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v240);
    vec_push(_v447, _v1074._v339);
    vec_push(_v447, _v1074._v340);
    vec_push(_v447, _v1074._v368);
    return _v447;
}

_v371 _v776(bkr_i64 _v447) {
    bkr_i64 _v368 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v368 = vec_get(_v447, _v272);
    }
    return (_v371){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v368 = _v368};
}

_v426 _v1075(_v426 _v368) {
    _v371 _v530 = _v1072(_v540(_v368));
    return _v537(((bkr_i64)(_v1073(_v530))));
}

bkr_i64 _v1076(bkr_i64 _v368) {
    return _v543(_v1075(_v538(_v368)));
}

_v372 _v1077(bkr_i64 _v368, bkr_i64 _v373) {
    return (_v372){._v339 = _v268, ._v340 = _v268, ._v368 = _v368, ._v373 = _v373};
}

bkr_i64 _v1078(_v372 _v1079) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v241);
    vec_push(_v447, _v1079._v339);
    vec_push(_v447, _v1079._v340);
    vec_push(_v447, _v1079._v368);
    vec_push(_v447, _v1079._v373);
    return _v447;
}

_v372 _v1080(bkr_i64 _v447) {
    bkr_i64 _v368 = 0;
    bkr_i64 _v373 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v368 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v373 = vec_get(_v447, (_v272 + 1));
    }
    return (_v372){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v368 = _v368, ._v373 = _v373};
}

_v426 _v1081(_v426 _v368, _v346 _v373) {
    _v372 _v530 = _v1077(_v540(_v368), _v519(_v373));
    return _v537(((bkr_i64)(_v1078(_v530))));
}

bkr_i64 _v1082(bkr_i64 _v368, bkr_i64 _v373) {
    return _v543(_v1081(_v538(_v368), _v517(_v373)));
}

_v389 _v1083(void) {
    return (_v389){._v339 = _v268, ._v340 = _v268};
}

bkr_i64 _v1084(_v389 _v370) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v234);
    vec_push(_v447, _v370._v339);
    vec_push(_v447, _v370._v340);
    return _v447;
}

_v389 _v798(bkr_i64 _v447) {
    return (_v389){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270)};
}

_v427 _v1085(void) {
    _v389 _v530 = _v1083();
    return _v549(((bkr_i64)(_v1084(_v530))));
}

bkr_i64 _v1086(void) {
    return _v554(_v1085());
}

_v390 _v1087(void) {
    return (_v390){._v339 = _v268, ._v340 = _v268};
}

bkr_i64 _v1088(_v390 _v370) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v235);
    vec_push(_v447, _v370._v339);
    vec_push(_v447, _v370._v340);
    return _v447;
}

_v390 _v800(bkr_i64 _v447) {
    return (_v390){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270)};
}

_v427 _v1089(void) {
    _v390 _v530 = _v1087();
    return _v549(((bkr_i64)(_v1088(_v530))));
}

bkr_i64 _v1090(void) {
    return _v554(_v1089());
}

_v385 _v1091(bkr_i64 _v386, bkr_i64 _v387) {
    return (_v385){._v339 = _v268, ._v340 = _v268, ._v386 = _v386, ._v387 = _v387};
}

bkr_i64 _v1092(_v385 _v370) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v233);
    vec_push(_v447, _v370._v339);
    vec_push(_v447, _v370._v340);
    vec_push(_v447, _v370._v386);
    vec_push(_v447, _v370._v387);
    return _v447;
}

_v385 _v794(bkr_i64 _v447) {
    bkr_i64 _v386 = 0;
    bkr_i64 _v387 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v386 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v387 = vec_get(_v447, (_v272 + 1));
    }
    return (_v385){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v386 = _v386, ._v387 = _v387};
}

_v427 _v1093(_v426 _v1094, _v426 _v1095) {
    _v385 _v530 = _v1091(_v540(_v1094), _v540(_v1095));
    return _v549(((bkr_i64)(_v1092(_v530))));
}

bkr_i64 _v1096(bkr_i64 _v386, bkr_i64 _v387) {
    return _v554(_v1093(_v538(_v386), _v538(_v387)));
}

_v388 _v1097(bkr_i64 _v368) {
    return (_v388){._v339 = _v268, ._v340 = _v268, ._v368 = _v368};
}

bkr_i64 _v1098(_v388 _v370) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v232);
    vec_push(_v447, _v370._v339);
    vec_push(_v447, _v370._v340);
    vec_push(_v447, _v370._v368);
    return _v447;
}

_v388 _v796(bkr_i64 _v447) {
    bkr_i64 _v368 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v368 = vec_get(_v447, _v272);
    }
    return (_v388){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v368 = _v368};
}

_v427 _v1099(_v426 _v541) {
    _v388 _v530 = _v1097(_v540(_v541));
    return _v549(((bkr_i64)(_v1098(_v530))));
}

bkr_i64 _v1100(bkr_i64 _v368) {
    return _v554(_v1099(_v538(_v368)));
}

_v391 _v1101(void) {
    return (_v391){._v339 = _v268, ._v340 = _v268};
}

bkr_i64 _v1102(_v391 _v577) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v227);
    vec_push(_v447, _v577._v339);
    vec_push(_v447, _v577._v340);
    return _v447;
}

_v391 _v802(bkr_i64 _v447) {
    return (_v391){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270)};
}

_v429 _v1103(void) {
    _v391 _v530 = _v1101();
    return _v578(((bkr_i64)(_v1102(_v530))));
}

bkr_i64 _v1104(void) {
    return _v584(_v1103());
}

bkr_i64 _v1105(bkr_i64 _v577) {
    return _v589(_v579(_v577));
}

bkr_i64 _v1106(bkr_i64 _v577, bkr_i64 _v362) {
    return _v508(vec_get(_v577, (_v272 + _v362)));
}

_v427 _v1107(_v429 _v582, bkr_i64 _v362) {
    return _v550(_v1106(_v584(_v582), _v362));
}

bkr_i64 _v1108(bkr_i64 _v577) {
    return _v1106(_v577, (_v1105(_v577) - 1));
}

_v429 _v1109(_v429 _v582, _v427 _v553) {
    _v451(_v506(_v581(_v582)), _v552(_v553));
    return _v582;
}

bkr_i64 _v1110(bkr_i64 _v577, bkr_i64 _v370) {
    _v1109(_v579(_v577), _v550(_v370));
    return _v577;
}

_v429 _v1111(_v427 _v553) {
    bkr_i64 _v370 = _v554(_v553);
    _v429 _v582 = _v1103();
    _v454(_v506(_v581(_v582)), _v484(_v370), _v485(_v370));
    _v1109(_v582, _v553);
    return _v582;
}

bkr_i64 _v1112(bkr_i64 _v370) {
    return _v584(_v1111(_v550(_v370)));
}

_v374 _v1113(bkr_i64 _v375, bkr_i64 _v376, bkr_i64 _v377) {
    return (_v374){._v339 = _v268, ._v340 = _v268, ._v375 = _v375, ._v376 = _v376, ._v377 = _v377};
}

bkr_i64 _v1114(_v374 _v370) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v230);
    vec_push(_v447, _v370._v339);
    vec_push(_v447, _v370._v340);
    vec_push(_v447, _v370._v375);
    vec_push(_v447, _v370._v376);
    vec_push(_v447, _v370._v377);
    return _v447;
}

_v374 _v786(bkr_i64 _v447) {
    bkr_i64 _v375 = 0;
    bkr_i64 _v376 = 0;
    bkr_i64 _v377 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v375 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v376 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v377 = vec_get(_v447, (_v272 + 2));
    }
    return (_v374){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v375 = _v375, ._v376 = _v376, ._v377 = _v377};
}

_v427 _v1115(_v426 _v1056, _v429 _v1116, bkr_i64 _v377) {
    _v374 _v530 = _v1113(_v540(_v1056), _v581(_v1116), _v377);
    return _v549(((bkr_i64)(_v1114(_v530))));
}

bkr_i64 _v1117(bkr_i64 _v375, bkr_i64 _v376, bkr_i64 _v377) {
    return _v554(_v1115(_v538(_v375), _v579(_v376), _v377));
}

_v380 _v1118(bkr_i64 _v355, bkr_i64 _v381, bkr_i64 _v382, bkr_i64 _v383, bkr_i64 _v379) {
    return (_v380){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v381 = _v381, ._v382 = _v382, ._v383 = _v383, ._v379 = _v379};
}

bkr_i64 _v1119(_v380 _v370) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v236);
    vec_push(_v447, _v370._v339);
    vec_push(_v447, _v370._v340);
    vec_push(_v447, _v370._v355);
    vec_push(_v447, _v370._v381);
    vec_push(_v447, _v370._v382);
    vec_push(_v447, _v370._v383);
    vec_push(_v447, _v370._v379);
    return _v447;
}

_v380 _v790(bkr_i64 _v447) {
    bkr_i64 _v355 = 0;
    bkr_i64 _v381 = 0;
    bkr_i64 _v382 = 0;
    bkr_i64 _v383 = 0;
    bkr_i64 _v379 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v355 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v381 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v382 = vec_get(_v447, (_v272 + 2));
    }
    if ((vec_len(_v447) > (_v272 + 3))) {
        _v383 = vec_get(_v447, (_v272 + 3));
    }
    if ((vec_len(_v447) > (_v272 + 4))) {
        _v379 = vec_get(_v447, (_v272 + 4));
    }
    return (_v380){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v355 = _v355, ._v381 = _v381, ._v382 = _v382, ._v383 = _v383, ._v379 = _v379};
}

_v427 _v1120(bkr_i64 _v355, _v426 _v1121, _v426 _v1122, bkr_i64 _v383, _v429 _v1123) {
    _v380 _v530 = _v1118(_v355, _v540(_v1121), _v540(_v1122), _v383, _v581(_v1123));
    return _v549(((bkr_i64)(_v1119(_v530))));
}

bkr_i64 _v1124(bkr_i64 _v355, bkr_i64 _v381, bkr_i64 _v382, bkr_i64 _v383, bkr_i64 _v379) {
    return _v554(_v1120(_v355, _v538(_v381), _v538(_v382), _v383, _v579(_v379)));
}

_v378 _v1125(bkr_i64 _v375, bkr_i64 _v379) {
    return (_v378){._v339 = _v268, ._v340 = _v268, ._v375 = _v375, ._v379 = _v379};
}

bkr_i64 _v1126(_v378 _v370) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v231);
    vec_push(_v447, _v370._v339);
    vec_push(_v447, _v370._v340);
    vec_push(_v447, _v370._v375);
    vec_push(_v447, _v370._v379);
    return _v447;
}

_v378 _v788(bkr_i64 _v447) {
    bkr_i64 _v375 = 0;
    bkr_i64 _v379 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v375 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v379 = vec_get(_v447, (_v272 + 1));
    }
    return (_v378){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v375 = _v375, ._v379 = _v379};
}

_v427 _v1127(_v426 _v1056, _v429 _v1123) {
    _v378 _v530 = _v1125(_v540(_v1056), _v581(_v1123));
    return _v549(((bkr_i64)(_v1126(_v530))));
}

bkr_i64 _v1128(bkr_i64 _v375, bkr_i64 _v379) {
    return _v554(_v1127(_v538(_v375), _v579(_v379)));
}

_v384 _v1129(bkr_i64 _v379) {
    return (_v384){._v339 = _v268, ._v340 = _v268, ._v379 = _v379};
}

bkr_i64 _v1130(_v384 _v370) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v237);
    vec_push(_v447, _v370._v339);
    vec_push(_v447, _v370._v340);
    vec_push(_v447, _v370._v379);
    return _v447;
}

_v384 _v792(bkr_i64 _v447) {
    bkr_i64 _v379 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v379 = vec_get(_v447, _v272);
    }
    return (_v384){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v379 = _v379};
}

_v427 _v1131(_v429 _v1123) {
    _v384 _v530 = _v1129(_v581(_v1123));
    return _v549(((bkr_i64)(_v1130(_v530))));
}

bkr_i64 _v1132(bkr_i64 _v379) {
    return _v554(_v1131(_v579(_v379)));
}

_v409 _v1133(bkr_i64 _v355, bkr_i64 _v365) {
    return (_v409){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v365 = _v365};
}

bkr_i64 _v1134(_v409 _v1135) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v225);
    vec_push(_v447, _v1135._v339);
    vec_push(_v447, _v1135._v340);
    vec_push(_v447, _v1135._v355);
    vec_push(_v447, _v1135._v365);
    return _v447;
}

_v409 _v812(bkr_i64 _v447) {
    bkr_i64 _v355 = 0;
    bkr_i64 _v365 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v355 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v365 = vec_get(_v447, (_v272 + 1));
    }
    return (_v409){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v355 = _v355, ._v365 = _v365};
}

_v341 _v1136(bkr_i64 _v355, _v346 _v520) {
    _v409 _v530 = _v1133(_v355, _v519(_v520));
    return _v506(((bkr_i64)(_v1134(_v530))));
}

bkr_i64 _v1137(bkr_i64 _v355, bkr_i64 _v515) {
    return _v453(_v1136(_v355, _v517(_v515)));
}

_v410 _v1138(bkr_i64 _v355, bkr_i64 _v411, bkr_i64 _v412, bkr_i64 _v379) {
    return (_v410){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v411 = _v411, ._v412 = _v412, ._v379 = _v379};
}

bkr_i64 _v1139(_v410 _v557) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v224);
    vec_push(_v447, _v557._v339);
    vec_push(_v447, _v557._v340);
    vec_push(_v447, _v557._v355);
    vec_push(_v447, _v557._v411);
    vec_push(_v447, _v557._v412);
    vec_push(_v447, _v557._v379);
    return _v447;
}

_v410 _v814(bkr_i64 _v447) {
    bkr_i64 _v355 = 0;
    bkr_i64 _v411 = 0;
    bkr_i64 _v412 = 0;
    bkr_i64 _v379 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v355 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v411 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v412 = vec_get(_v447, (_v272 + 2));
    }
    if ((vec_len(_v447) > (_v272 + 3))) {
        _v379 = vec_get(_v447, (_v272 + 3));
    }
    return (_v410){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v355 = _v355, ._v411 = _v411, ._v412 = _v412, ._v379 = _v379};
}

_v428 _v1140(bkr_i64 _v355, _v434 _v1141, bkr_i64 _v1142, _v429 _v1123) {
    _v410 _v530 = _v1138(_v355, _v606(_v1141), _v1142, _v581(_v1123));
    return _v558(((bkr_i64)(_v1139(_v530))));
}

bkr_i64 _v1143(bkr_i64 _v355, bkr_i64 _v411, bkr_i64 _v1142, bkr_i64 _v379) {
    return _v567(_v1140(_v355, _v604(_v411), _v1142, _v579(_v379)));
}

_v413 _v1144(bkr_i64 _v355, bkr_i64 _v365, bkr_i64 _v387) {
    return (_v413){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v365 = _v365, ._v387 = _v387};
}

bkr_i64 _v1145(_v413 _v557) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v249);
    vec_push(_v447, _v557._v339);
    vec_push(_v447, _v557._v340);
    vec_push(_v447, _v557._v355);
    vec_push(_v447, _v557._v365);
    vec_push(_v447, _v557._v387);
    return _v447;
}

_v413 _v816(bkr_i64 _v447) {
    bkr_i64 _v355 = 0;
    bkr_i64 _v365 = 0;
    bkr_i64 _v387 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v355 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v365 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v387 = vec_get(_v447, (_v272 + 2));
    }
    return (_v413){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v355 = _v355, ._v365 = _v365, ._v387 = _v387};
}

_v428 _v1146(bkr_i64 _v355, bkr_i64 _v515, bkr_i64 _v387) {
    _v413 _v530 = _v1144(_v355, _v515, _v387);
    return _v558(((bkr_i64)(_v1145(_v530))));
}

bkr_i64 _v1147(bkr_i64 _v355, bkr_i64 _v515, bkr_i64 _v387) {
    return _v567(_v1146(_v355, _v515, _v387));
}

_v414 _v1148(bkr_i64 _v355, bkr_i64 _v365) {
    return (_v414){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v365 = _v365};
}

bkr_i64 _v1149(_v414 _v1150) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v255);
    vec_push(_v447, _v1150._v339);
    vec_push(_v447, _v1150._v340);
    vec_push(_v447, _v1150._v355);
    vec_push(_v447, _v1150._v365);
    return _v447;
}

_v414 _v818(bkr_i64 _v447) {
    bkr_i64 _v355 = 0;
    bkr_i64 _v365 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v355 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v365 = vec_get(_v447, (_v272 + 1));
    }
    return (_v414){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v355 = _v355, ._v365 = _v365};
}

_v341 _v1151(bkr_i64 _v1044, _v346 _v1152) {
    _v414 _v530 = _v1148(_v1044, _v519(_v1152));
    return _v506(((bkr_i64)(_v1149(_v530))));
}

bkr_i64 _v1153(bkr_i64 _v1044, bkr_i64 _v1154) {
    return _v453(_v1151(_v1044, _v517(_v1154)));
}

_v415 _v1155(bkr_i64 _v355, bkr_i64 _v416) {
    return (_v415){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v416 = _v416};
}

bkr_i64 _v1156(_v415 _v557) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v254);
    vec_push(_v447, _v557._v339);
    vec_push(_v447, _v557._v340);
    vec_push(_v447, _v557._v355);
    vec_push(_v447, _v557._v416);
    return _v447;
}

_v415 _v820(bkr_i64 _v447) {
    bkr_i64 _v355 = 0;
    bkr_i64 _v416 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v355 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v416 = vec_get(_v447, (_v272 + 1));
    }
    return (_v415){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v355 = _v355, ._v416 = _v416};
}

_v428 _v1157(bkr_i64 _v355, _v434 _v1158) {
    _v415 _v530 = _v1155(_v355, _v606(_v1158));
    return _v558(((bkr_i64)(_v1156(_v530))));
}

_v417 _v1159(bkr_i64 _v355, bkr_i64 _v418, bkr_i64 _v419) {
    return (_v417){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v418 = _v418, ._v419 = _v419};
}

bkr_i64 _v1160(_v417 _v557) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v259);
    vec_push(_v447, _v557._v339);
    vec_push(_v447, _v557._v340);
    vec_push(_v447, _v557._v355);
    vec_push(_v447, _v557._v418);
    vec_push(_v447, _v557._v419);
    return _v447;
}

_v417 _v822(bkr_i64 _v447) {
    bkr_i64 _v355 = 0;
    bkr_i64 _v418 = 0;
    bkr_i64 _v419 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v355 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v418 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v419 = vec_get(_v447, (_v272 + 2));
    }
    return (_v417){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v355 = _v355, ._v418 = _v418, ._v419 = _v419};
}

_v428 _v1161(bkr_i64 _v355, _v435 _v1162, _v435 _v1163) {
    _v417 _v530 = _v1159(_v355, _v613(_v1162), _v613(_v1163));
    return _v558(((bkr_i64)(_v1160(_v530))));
}

bkr_i64 _v1164(_v428 _v562) {
    return _v504(_v567(_v562), 1);
}

_v435 _v1165(_v428 _v562) {
    return _v647(_v567(_v562), 2);
}

_v435 _v1166(_v428 _v562) {
    return _v647(_v567(_v562), 3);
}

bkr_i64 _v1167(_v428 _v562) {
    _v435 _v1163 = _v1166(_v562);
    bkr_i64 _v399 = 0;
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v915(_v1163))) {
        if (_v525(_v917(_v1163, _v1168))) {
            _v399 = (_v399 + 1);
        }
        _v1168 = (_v1168 + 1);
    }
    return _v399;
}

bkr_i64 _v1170(_v428 _v562) {
    _v435 _v1163 = _v1166(_v562);
    bkr_i64 _v1171 = 0;
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v915(_v1163))) {
        bkr_i64 _v344 = _v917(_v1163, _v1168);
        if (_v525(_v344)) {
            _v1171 = (_v1171 + _v915(_v610(_v344)));
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1171;
}

_v420 _v1172(bkr_i64 _v355, bkr_i64 _v421) {
    return (_v420){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v421 = _v421};
}

bkr_i64 _v1173(_v420 _v557) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v260);
    vec_push(_v447, _v557._v339);
    vec_push(_v447, _v557._v340);
    vec_push(_v447, _v557._v355);
    vec_push(_v447, _v557._v421);
    return _v447;
}

_v420 _v1174(bkr_i64 _v447) {
    bkr_i64 _v355 = 0;
    bkr_i64 _v421 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v355 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v421 = vec_get(_v447, (_v272 + 1));
    }
    return (_v420){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v355 = _v355, ._v421 = _v421};
}

_v428 _v1175(bkr_i64 _v355, _v346 _v1094) {
    _v420 _v530 = _v1172(_v355, _v519(_v1094));
    return _v558(((bkr_i64)(_v1173(_v530))));
}

bkr_i64 _v1176(bkr_i64 _v355, bkr_i64 _v373) {
    return _v567(_v1175(_v355, _v517(_v373)));
}

bkr_i64 _v1177(_v428 _v562) {
    return _v504(_v567(_v562), 1);
}

bkr_i64 _v1178(_v428 _v562) {
    return _v504(_v567(_v562), 2);
}

bkr_i64 _v1179(bkr_i64 _v355, bkr_i64 _v416) {
    return _v567(_v1157(_v355, _v604(_v416)));
}

_v422 _v1180(bkr_i64 _v355, bkr_i64 _v423, bkr_i64 _v424, bkr_i64 _v425) {
    return (_v422){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v423 = _v423, ._v424 = _v424, ._v425 = _v425};
}

bkr_i64 _v1181(_v422 _v0) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v223);
    vec_push(_v447, _v0._v339);
    vec_push(_v447, _v0._v340);
    vec_push(_v447, _v0._v355);
    vec_push(_v447, _v0._v423);
    vec_push(_v447, _v0._v424);
    vec_push(_v447, _v0._v425);
    return _v447;
}

_v422 _v824(bkr_i64 _v447) {
    bkr_i64 _v355 = 0;
    bkr_i64 _v423 = 0;
    bkr_i64 _v424 = 0;
    bkr_i64 _v425 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v355 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v423 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v424 = vec_get(_v447, (_v272 + 2));
    }
    if ((vec_len(_v447) > (_v272 + 3))) {
        _v425 = vec_get(_v447, (_v272 + 3));
    }
    return (_v422){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v355 = _v355, ._v423 = _v423, ._v424 = _v424, ._v425 = _v425};
}

_v341 _v1182(bkr_i64 _v355, _v434 _v1183, bkr_i64 _v1184, _v437 _v1185) {
    _v422 _v530 = _v1180(_v355, _v606(_v1183), _v1184, _v625(_v1185));
    return _v506(((bkr_i64)(_v1181(_v530))));
}

bkr_i64 _v1186(bkr_i64 _v355, bkr_i64 _v423, bkr_i64 _v1184, bkr_i64 _v425) {
    return _v453(_v1182(_v355, _v604(_v423), _v1184, _v624(_v425)));
}

bkr_i64 _v1188(bkr_i64 _v1189, bkr_i64 _v425, bkr_i64 _v612, bkr_i64 _v1190) {
    return _v1191(_v1192(_v1189, _v425, _v612, _v1190));
}

_v1187 _v1192(bkr_i64 _v1189, bkr_i64 _v425, bkr_i64 _v612, bkr_i64 _v1190) {
    bkr_i64 _v1193 = vec_new();
    vec_push(_v1193, ((bkr_i64)(_v1189)));
    vec_push(_v1193, ((bkr_i64)(_v425)));
    vec_push(_v1193, ((bkr_i64)(_v612)));
    vec_push(_v1193, ((bkr_i64)(_v1190)));
    return _v1194(_v1193);
}

_v1187 _v1194(bkr_i64 _v1193) {
    return (_v1187){._v342 = ((bkr_i64)(_v1193))};
}

bkr_i64 _v1191(_v1187 _v1195) {
    return ((bkr_i64)(_v1195._v342));
}

bkr_i64 _v1196(bkr_i64 _v1193) {
    return _v1197(_v1194(_v1193));
}

bkr_i64 _v1197(_v1187 _v1195) {
    return ((bkr_i64)(vec_get(_v1191(_v1195), 0)));
}

bkr_i64 _v1198(bkr_i64 _v1193) {
    return _v1199(_v1194(_v1193));
}

bkr_i64 _v1199(_v1187 _v1195) {
    return ((bkr_i64)(vec_get(_v1191(_v1195), 1)));
}

bkr_i64 _v1200(bkr_i64 _v1193) {
    return _v1201(_v1194(_v1193));
}

bkr_i64 _v1201(_v1187 _v1195) {
    return ((bkr_i64)(vec_get(_v1191(_v1195), 2)));
}

bkr_i64 _v1202(bkr_i64 _v1193) {
    return _v1203(_v1194(_v1193));
}

bkr_i64 _v1203(_v1187 _v1195) {
    return ((bkr_i64)(vec_get(_v1191(_v1195), 3)));
}

bkr_bool _v1204(bkr_i64 _v1205) {
    return ((((_v1205 >= 97) && (_v1205 <= 122)) || ((_v1205 >= 65) && (_v1205 <= 90))) || (_v1205 == 95));
}

bkr_bool _v1206(bkr_i64 _v1205) {
    return ((_v1205 >= 48) && (_v1205 <= 57));
}

bkr_bool _v1207(bkr_i64 _v1205) {
    return (_v1204(_v1205) || _v1206(_v1205));
}

bkr_i64 _v1208(bkr_str _v1209, bkr_i64 _v1210) {
    bkr_i64 _v1211 = bkr_len((bkr_str)(intptr_t)(_v1209));
    while ((_v1210 < _v1211)) {
        bkr_i64 _v1205 = char_code_at(_v1209, _v1210);
        if (((((_v1205 == 32) || (_v1205 == 9)) || (_v1205 == 10)) || (_v1205 == 13))) {
            _v1210 = (_v1210 + 1);
        } else {
            if (((_v1205 == 47) && ((_v1210 + 1) < _v1211))) {
                bkr_i64 _v1215 = char_code_at(_v1209, (_v1210 + 1));
                if ((_v1215 == 47)) {
                    _v1210 = (_v1210 + 2);
                    while (((_v1210 < _v1211) && (char_code_at(_v1209, _v1210) != 10))) {
                        _v1210 = (_v1210 + 1);
                    }
                } else {
                    return _v1210;
                }
            } else {
                return _v1210;
            }
        }
    }
    return _v1210;
}

bkr_i64 _v1216(bkr_i64 _v425, bkr_str _v1217) {
    bkr_i64 _v1168 = 0;
    while ((_v1168 < vec_len(_v425))) {
        if (bkr_str_eq(vec_get(_v425, _v1168), _v1217)) {
            return _v1168;
        }
        _v1168 = (_v1168 + 1);
    }
    bkr_i64 _v1035 = vec_len(_v425);
    vec_push(_v425, ((bkr_i64)(intptr_t)_v1217));
    return _v1035;
}

bkr_i64 _v1218(bkr_str _v1209) {
    return _v1191(_v1219(_v1209));
}

_v1187 _v1219(bkr_str _v1209) {
    bkr_i64 _v1189 = vec_new();
    bkr_i64 _v425 = vec_new();
    bkr_i64 _v612 = vec_new();
    bkr_i64 _v1190 = vec_new();
    bkr_i64 _v1210 = 0;
    bkr_i64 _v1211 = bkr_len((bkr_str)(intptr_t)(_v1209));
    while ((_v1210 < _v1211)) {
        _v1210 = _v1208(_v1209, _v1210);
        if ((_v1210 >= _v1211)) {
            vec_push(_v1189, _v129);
            vec_push(_v1189, _v1210);
            vec_push(_v1189, _v1210);
            return _v1192(_v1189, _v425, _v612, _v1190);
        }
        bkr_i64 _v339 = _v1210;
        bkr_i64 _v1205 = char_code_at(_v1209, _v1210);
        bkr_i64 _v1220 = 0;
        bkr_bool _v1221 = BKR_FALSE;
        if (_v1204(_v1205)) {
            while (((_v1210 < _v1211) && _v1207(char_code_at(_v1209, _v1210)))) {
                _v1210 = (_v1210 + 1);
            }
            bkr_str _v1217 = substring(_v1209, _v339, _v1210);
            _v1220 = _v131;
            if (bkr_str_eq(_v1217, "kernel")) {
                _v1220 = _v137;
            }
            if (bkr_str_eq(_v1217, "struct")) {
                _v1220 = _v139;
            }
            if (bkr_str_eq(_v1217, "enum")) {
                _v1220 = _v138;
            }
            if (bkr_str_eq(_v1217, "fn")) {
                _v1220 = _v140;
            }
            if (bkr_str_eq(_v1217, "let")) {
                _v1220 = _v141;
            }
            if (bkr_str_eq(_v1217, "pub")) {
                _v1220 = _v197;
            }
            if (bkr_str_eq(_v1217, "mut")) {
                _v1220 = _v198;
            }
            if (bkr_str_eq(_v1217, "if")) {
                _v1220 = _v142;
            }
            if (bkr_str_eq(_v1217, "else")) {
                _v1220 = _v143;
            }
            if (bkr_str_eq(_v1217, "for")) {
                _v1220 = _v144;
            }
            if (bkr_str_eq(_v1217, "in")) {
                _v1220 = _v145;
            }
            if (bkr_str_eq(_v1217, "while")) {
                _v1220 = _v146;
            }
            if (bkr_str_eq(_v1217, "break")) {
                _v1220 = _v147;
            }
            if (bkr_str_eq(_v1217, "continue")) {
                _v1220 = _v148;
            }
            if (bkr_str_eq(_v1217, "loop")) {
                _v1220 = _v149;
            }
            if (bkr_str_eq(_v1217, "return")) {
                _v1220 = _v150;
            }
            if (bkr_str_eq(_v1217, "defer")) {
                _v1220 = _v153;
            }
            if (bkr_str_eq(_v1217, "type")) {
                _v1220 = _v154;
            }
            if (bkr_str_eq(_v1217, "as")) {
                _v1220 = _v155;
            }
            if (bkr_str_eq(_v1217, "match")) {
                _v1220 = _v151;
            }
            if (bkr_str_eq(_v1217, "const")) {
                _v1220 = _v152;
            }
            if (bkr_str_eq(_v1217, "true")) {
                _v1220 = _v135;
            }
            if (bkr_str_eq(_v1217, "false")) {
                _v1220 = _v136;
            }
            if (bkr_str_eq(_v1217, "i32")) {
                _v1220 = _v156;
            }
            if (bkr_str_eq(_v1217, "i64")) {
                _v1220 = _v157;
            }
            if (bkr_str_eq(_v1217, "f64")) {
                _v1220 = _v158;
            }
            if (bkr_str_eq(_v1217, "bool")) {
                _v1220 = _v159;
            }
            if (bkr_str_eq(_v1217, "str")) {
                _v1220 = _v160;
            }
            bkr_i64 _v1224 = _v1216(_v425, _v1217);
            vec_push(_v1189, _v1220);
            vec_push(_v1189, _v1224);
            vec_push(_v1189, _v1210);
            _v1221 = BKR_TRUE;
        }
        if (((!_v1221) && _v1206(_v1205))) {
            while (((_v1210 < _v1211) && _v1206(char_code_at(_v1209, _v1210)))) {
                _v1210 = (_v1210 + 1);
            }
            if (((((_v1210 + 1) < _v1211) && (char_code_at(_v1209, _v1210) == 46)) && _v1206(char_code_at(_v1209, (_v1210 + 1))))) {
                _v1210 = (_v1210 + 1);
                while (((_v1210 < _v1211) && _v1206(char_code_at(_v1209, _v1210)))) {
                    _v1210 = (_v1210 + 1);
                }
                bkr_str _v1226 = substring(_v1209, _v339, _v1210);
                vec_push(_v1189, _v134);
                vec_push(_v1189, vec_len(_v1190));
                vec_push(_v1189, _v1210);
                vec_push(_v1190, ((bkr_i64)(intptr_t)_v1226));
            } else {
                bkr_str _v1227 = substring(_v1209, _v339, _v1210);
                bkr_i64 _v1228 = parse_int(_v1227);
                vec_push(_v1189, _v132);
                vec_push(_v1189, vec_len(_v612));
                vec_push(_v1189, _v1210);
                vec_push(_v612, _v1228);
            }
            _v1221 = BKR_TRUE;
        }
        if (((!_v1221) && (_v1205 == 34))) {
            _v1210 = (_v1210 + 1);
            bkr_i64 _v1230 = _v1210;
            while (((_v1210 < _v1211) && (char_code_at(_v1209, _v1210) != 34))) {
                if (((char_code_at(_v1209, _v1210) == 92) && ((_v1210 + 1) < _v1211))) {
                    _v1210 = (_v1210 + 2);
                } else {
                    _v1210 = (_v1210 + 1);
                }
            }
            bkr_str _v1231 = substring(_v1209, _v1230, _v1210);
            _v1210 = (_v1210 + 1);
            vec_push(_v1189, _v133);
            vec_push(_v1189, vec_len(_v1190));
            vec_push(_v1189, _v1210);
            vec_push(_v1190, ((bkr_i64)(intptr_t)_v1231));
            _v1221 = BKR_TRUE;
        }
        if (((!_v1221) && ((_v1210 + 2) < _v1211))) {
            bkr_i64 _v1232 = char_code_at(_v1209, (_v1210 + 1));
            bkr_i64 _v1233 = char_code_at(_v1209, (_v1210 + 2));
            if ((((_v1205 == 46) && (_v1232 == 46)) && (_v1233 == 61))) {
                _v1220 = _v183;
                _v1210 = (_v1210 + 3);
                _v1221 = BKR_TRUE;
            }
            if (_v1221) {
                vec_push(_v1189, _v1220);
                vec_push(_v1189, _v339);
                vec_push(_v1189, _v1210);
            }
        }
        if (((!_v1221) && ((_v1210 + 1) < _v1211))) {
            bkr_i64 _v1232 = char_code_at(_v1209, (_v1210 + 1));
            if (((_v1205 == 45) && (_v1232 == 62))) {
                _v1220 = _v181;
                _v1210 = (_v1210 + 2);
                _v1221 = BKR_TRUE;
            }
            if ((((!_v1221) && (_v1205 == 61)) && (_v1232 == 62))) {
                _v1220 = _v195;
                _v1210 = (_v1210 + 2);
                _v1221 = BKR_TRUE;
            }
            if ((((!_v1221) && (_v1205 == 46)) && (_v1232 == 46))) {
                _v1220 = _v182;
                _v1210 = (_v1210 + 2);
                _v1221 = BKR_TRUE;
            }
            if ((((!_v1221) && (_v1205 == 61)) && (_v1232 == 61))) {
                _v1220 = _v166;
                _v1210 = (_v1210 + 2);
                _v1221 = BKR_TRUE;
            }
            if ((((!_v1221) && (_v1205 == 33)) && (_v1232 == 61))) {
                _v1220 = _v167;
                _v1210 = (_v1210 + 2);
                _v1221 = BKR_TRUE;
            }
            if ((((!_v1221) && (_v1205 == 60)) && (_v1232 == 61))) {
                _v1220 = _v170;
                _v1210 = (_v1210 + 2);
                _v1221 = BKR_TRUE;
            }
            if ((((!_v1221) && (_v1205 == 62)) && (_v1232 == 61))) {
                _v1220 = _v171;
                _v1210 = (_v1210 + 2);
                _v1221 = BKR_TRUE;
            }
            if ((((!_v1221) && (_v1205 == 60)) && (_v1232 == 60))) {
                _v1220 = _v178;
                _v1210 = (_v1210 + 2);
                _v1221 = BKR_TRUE;
            }
            if ((((!_v1221) && (_v1205 == 62)) && (_v1232 == 62))) {
                _v1220 = _v179;
                _v1210 = (_v1210 + 2);
                _v1221 = BKR_TRUE;
            }
            if ((((!_v1221) && (_v1205 == 38)) && (_v1232 == 38))) {
                _v1220 = _v172;
                _v1210 = (_v1210 + 2);
                _v1221 = BKR_TRUE;
            }
            if ((((!_v1221) && (_v1205 == 124)) && (_v1232 == 124))) {
                _v1220 = _v173;
                _v1210 = (_v1210 + 2);
                _v1221 = BKR_TRUE;
            }
            if ((((!_v1221) && (_v1205 == 58)) && (_v1232 == 58))) {
                _v1220 = _v196;
                _v1210 = (_v1210 + 2);
                _v1221 = BKR_TRUE;
            }
            if (_v1221) {
                vec_push(_v1189, _v1220);
                vec_push(_v1189, _v339);
                vec_push(_v1189, _v1210);
            }
        }
        if ((!_v1221)) {
            if ((_v1205 == 43)) {
                _v1220 = _v161;
            }
            if ((_v1205 == 45)) {
                _v1220 = _v162;
            }
            if ((_v1205 == 42)) {
                _v1220 = _v163;
            }
            if ((_v1205 == 47)) {
                _v1220 = _v164;
            }
            if ((_v1205 == 37)) {
                _v1220 = _v165;
            }
            if ((_v1205 == 60)) {
                _v1220 = _v168;
            }
            if ((_v1205 == 62)) {
                _v1220 = _v169;
            }
            if ((_v1205 == 33)) {
                _v1220 = _v174;
            }
            if ((_v1205 == 38)) {
                _v1220 = _v175;
            }
            if ((_v1205 == 124)) {
                _v1220 = _v176;
            }
            if ((_v1205 == 94)) {
                _v1220 = _v177;
            }
            if ((_v1205 == 46)) {
                _v1220 = _v184;
            }
            if ((_v1205 == 61)) {
                _v1220 = _v180;
            }
            if ((_v1205 == 40)) {
                _v1220 = _v185;
            }
            if ((_v1205 == 41)) {
                _v1220 = _v186;
            }
            if ((_v1205 == 123)) {
                _v1220 = _v187;
            }
            if ((_v1205 == 125)) {
                _v1220 = _v188;
            }
            if ((_v1205 == 91)) {
                _v1220 = _v189;
            }
            if ((_v1205 == 93)) {
                _v1220 = _v190;
            }
            if ((_v1205 == 44)) {
                _v1220 = _v191;
            }
            if ((_v1205 == 59)) {
                _v1220 = _v192;
            }
            if ((_v1205 == 58)) {
                _v1220 = _v193;
            }
            if ((_v1205 == 63)) {
                _v1220 = _v194;
            }
            _v1210 = (_v1210 + 1);
            vec_push(_v1189, _v1220);
            vec_push(_v1189, _v339);
            vec_push(_v1189, _v1210);
        }
    }
    vec_push(_v1189, _v129);
    vec_push(_v1189, _v1210);
    vec_push(_v1189, _v1210);
    return _v1192(_v1189, _v425, _v612, _v1190);
}

bkr_i64 _v1235(bkr_i64 _v1236) {
    return _v1237(_v1238(_v1194(_v1236)));
}

_v1234 _v1238(_v1187 _v1236) {
    bkr_i64 _v1239 = vec_new();
    vec_push(_v1239, ((bkr_i64)(_v1197(_v1236))));
    vec_push(_v1239, ((bkr_i64)(_v1199(_v1236))));
    vec_push(_v1239, ((bkr_i64)(_v1201(_v1236))));
    vec_push(_v1239, ((bkr_i64)(_v1203(_v1236))));
    vec_push(_v1239, 0);
    vec_push(_v1239, 0);
    vec_push(_v1239, (-1));
    vec_push(_v1239, _v129);
    vec_push(_v1239, _v129);
    bkr_i64 _v1240 = vec_new();
    bkr_i64 _v1241 = vec_new();
    bkr_i64 _v1242 = vec_new();
    vec_push(_v1239, ((bkr_i64)(_v1240)));
    vec_push(_v1239, ((bkr_i64)(_v1241)));
    vec_push(_v1239, ((bkr_i64)(_v1242)));
    return _v1243(_v1239);
}

_v1234 _v1243(bkr_i64 _v1239) {
    return (_v1234){._v342 = ((bkr_i64)(_v1239))};
}

bkr_i64 _v1237(_v1234 _v1244) {
    return ((bkr_i64)(_v1244._v342));
}

bkr_i64 _v1245(bkr_i64 _v1246) {
    return _v1247(_v1243(_v1246));
}

bkr_i64 _v1247(_v1234 _v1244) {
    return ((bkr_i64)(vec_get(_v1237(_v1244), 0)));
}

bkr_i64 _v1248(bkr_i64 _v1246) {
    return _v1249(_v1243(_v1246));
}

bkr_i64 _v1249(_v1234 _v1244) {
    return ((bkr_i64)(vec_get(_v1237(_v1244), 1)));
}

bkr_i64 _v1250(bkr_i64 _v1246) {
    return _v1251(_v1243(_v1246));
}

bkr_i64 _v1251(_v1234 _v1244) {
    return ((bkr_i64)(vec_get(_v1237(_v1244), 2)));
}

bkr_i64 _v1252(bkr_i64 _v1246) {
    return _v1253(_v1243(_v1246));
}

bkr_i64 _v1253(_v1234 _v1244) {
    return ((bkr_i64)(vec_get(_v1237(_v1244), 3)));
}

bkr_i64 _v1254(bkr_i64 _v1246) {
    return _v1255(_v1243(_v1246));
}

bkr_i64 _v1255(_v1234 _v1244) {
    return vec_get(_v1237(_v1244), 4);
}

bkr_i64 _v1256(bkr_i64 _v1246, bkr_i64 _v1210) {
    _v1257(_v1243(_v1246), _v1210);
    return _v1246;
}

_v1234 _v1257(_v1234 _v1244, bkr_i64 _v1210) {
    vec_set(_v1237(_v1244), 4, _v1210);
    return _v1244;
}

bkr_i64 _v1258(bkr_i64 _v1246, bkr_i64 _v1259) {
    _v1260(_v1243(_v1246), _v1259);
    return _v1246;
}

_v1234 _v1260(_v1234 _v1244, bkr_i64 _v1259) {
    vec_set(_v1237(_v1244), 5, _v1259);
    return _v1244;
}

bkr_i64 _v1261(bkr_i64 _v1246, bkr_i64 _v1210) {
    _v1262(_v1243(_v1246), _v1210);
    return _v1246;
}

_v1234 _v1262(_v1234 _v1244, bkr_i64 _v1210) {
    vec_set(_v1237(_v1244), 6, _v1210);
    return _v1244;
}

bkr_i64 _v1263(bkr_i64 _v1246, bkr_i64 _v1264) {
    _v1265(_v1243(_v1246), _v1264);
    return _v1246;
}

_v1234 _v1265(_v1234 _v1244, bkr_i64 _v1264) {
    vec_set(_v1237(_v1244), 7, _v1264);
    return _v1244;
}

bkr_i64 _v1266(bkr_i64 _v1246, bkr_i64 _v1267) {
    _v1268(_v1243(_v1246), _v1267);
    return _v1246;
}

_v1234 _v1268(_v1234 _v1244, bkr_i64 _v1267) {
    vec_set(_v1237(_v1244), 8, _v1267);
    return _v1244;
}

bkr_i64 _v1269(bkr_i64 _v1246) {
    return _v1270(_v1243(_v1246));
}

bkr_i64 _v1270(_v1234 _v1244) {
    bkr_i64 _v1189 = _v1247(_v1244);
    bkr_i64 _v1210 = _v1255(_v1244);
    bkr_i64 _v1035 = (_v1210 * 3);
    if ((_v1035 >= vec_len(_v1189))) {
        return 0;
    }
    return vec_get(_v1189, _v1035);
}

bkr_i64 _v1271(bkr_i64 _v1246) {
    return _v1272(_v1243(_v1246));
}

bkr_i64 _v1272(_v1234 _v1244) {
    bkr_i64 _v1189 = _v1247(_v1244);
    bkr_i64 _v1210 = _v1255(_v1244);
    return vec_get(_v1189, ((_v1210 * 3) + 1));
}

bkr_i64 _v1273(bkr_i64 _v1246, bkr_i64 _v1274) {
    return _v1275(_v1243(_v1246), _v1274);
}

bkr_i64 _v1275(_v1234 _v1244, bkr_i64 _v1274) {
    bkr_i64 _v1189 = _v1247(_v1244);
    bkr_i64 _v1210 = (_v1255(_v1244) + _v1274);
    bkr_i64 _v1035 = (_v1210 * 3);
    if ((_v1035 >= vec_len(_v1189))) {
        return 0;
    }
    return vec_get(_v1189, _v1035);
}

bkr_i64 _v1276(bkr_i64 _v1246) {
    return _v1277(_v1243(_v1246));
}

bkr_i64 _v1277(_v1234 _v1244) {
    _v1257(_v1244, (_v1255(_v1244) + 1));
    return _v1270(_v1244);
}

bkr_bool _v1278(bkr_i64 _v1246, bkr_i64 _v1264) {
    return _v1279(_v1243(_v1246), _v1264);
}

bkr_bool _v1279(_v1234 _v1244, bkr_i64 _v1264) {
    if ((_v1270(_v1244) == _v1264)) {
        _v1277(_v1244);
        return BKR_TRUE;
    }
    if (((_v1264 == _v169) && (_v1270(_v1244) == _v179))) {
        bkr_i64 _v1035 = (_v1255(_v1244) * 3);
        vec_set(_v1247(_v1244), _v1035, _v169);
        return BKR_TRUE;
    }
    _v1280(_v1244, _v1264);
    return BKR_FALSE;
}

bkr_i64 _v1281(bkr_i64 _v1246, bkr_i64 _v1264) {
    _v1280(_v1243(_v1246), _v1264);
    return _v1246;
}

_v1234 _v1280(_v1234 _v1244, bkr_i64 _v1264) {
    _v1260(_v1244, 1);
    bkr_i64 _v1282 = _v1255(_v1244);
    bkr_i64 _v1283 = _v1270(_v1244);
    if ((_v1284(_v1244) < 0)) {
        _v1262(_v1244, _v1282);
        _v1265(_v1244, _v1264);
        _v1268(_v1244, _v1283);
    }
    bkr_i64 _v1239 = _v1237(_v1244);
    if ((vec_len(_v1239) >= 12)) {
        bkr_i64 _v1240 = ((bkr_i64)(vec_get(_v1239, 9)));
        bkr_i64 _v1241 = ((bkr_i64)(vec_get(_v1239, 10)));
        bkr_i64 _v1242 = ((bkr_i64)(vec_get(_v1239, 11)));
        bkr_bool _v1285 = BKR_FALSE;
        bkr_i64 _v1168 = 0;
        while ((_v1168 < vec_len(_v1240))) {
            if ((vec_get(_v1240, _v1168) == _v1282)) {
                _v1285 = BKR_TRUE;
                break;
            }
            _v1168 = (_v1168 + 1);
        }
        if ((!_v1285)) {
            vec_push(_v1240, _v1282);
            vec_push(_v1241, _v1264);
            vec_push(_v1242, _v1283);
        }
    }
    return _v1244;
}

bkr_str _v1287(bkr_i64 _v1246, bkr_i64 _v1035) {
    return _v1288(_v1243(_v1246), _v1035);
}

bkr_str _v1288(_v1234 _v1244, bkr_i64 _v1035) {
    bkr_i64 _v425 = _v1249(_v1244);
    if (((_v1035 < 0) || (_v1035 >= vec_len(_v425)))) {
        return "";
    }
    return vec_get(_v425, _v1035);
}

bkr_i64 _v1289(_v1234 _v1244, bkr_str _v1290) {
    bkr_i64 _v425 = _v1249(_v1244);
    bkr_i64 _v1168 = 0;
    bkr_i64 _v399 = vec_len(_v425);
    while ((_v1168 < _v399)) {
        if (bkr_str_eq(vec_get(_v425, _v1168), _v1290)) {
            return _v1168;
        }
        _v1168 = (_v1168 + 1);
    }
    vec_push(_v425, ((bkr_i64)(intptr_t)_v1290));
    return _v399;
}

bkr_i64 _v1291(bkr_i64 _v1246, bkr_i64 _v1035) {
    return _v1292(_v1243(_v1246), _v1035);
}

bkr_i64 _v1292(_v1234 _v1244, bkr_i64 _v1035) {
    return vec_get(_v1251(_v1244), _v1035);
}

bkr_str _v1293(bkr_i64 _v1246, bkr_i64 _v1035) {
    return _v1294(_v1243(_v1246), _v1035);
}

bkr_str _v1294(_v1234 _v1244, bkr_i64 _v1035) {
    bkr_i64 _v1190 = _v1253(_v1244);
    if (((_v1035 < 0) || (_v1035 >= vec_len(_v1190)))) {
        return "";
    }
    return vec_get(_v1190, _v1035);
}

bkr_bool _v1295(bkr_i64 _v1246) {
    return _v1296(_v1243(_v1246));
}

bkr_bool _v1296(_v1234 _v1244) {
    return (vec_get(_v1237(_v1244), 5) != 0);
}

bkr_i64 _v1297(bkr_i64 _v1246) {
    return _v1284(_v1243(_v1246));
}

bkr_i64 _v1284(_v1234 _v1244) {
    return vec_get(_v1237(_v1244), 6);
}

bkr_i64 _v1298(bkr_i64 _v1246) {
    return _v1299(_v1243(_v1246));
}

bkr_i64 _v1299(_v1234 _v1244) {
    return vec_get(_v1237(_v1244), 7);
}

bkr_i64 _v1300(bkr_i64 _v1246) {
    return _v1301(_v1243(_v1246));
}

bkr_i64 _v1301(_v1234 _v1244) {
    return vec_get(_v1237(_v1244), 8);
}

bkr_i64 _v1302(_v1234 _v1244) {
    bkr_i64 _v1239 = _v1237(_v1244);
    if ((vec_len(_v1239) < 12)) {
        if (_v1296(_v1244)) {
            return 1;
        }
        return 0;
    }
    bkr_i64 _v1240 = ((bkr_i64)(vec_get(_v1239, 9)));
    bkr_i64 _v399 = vec_len(_v1240);
    if (((_v399 == 0) && _v1296(_v1244))) {
        return 1;
    }
    return _v399;
}

bkr_i64 _v1303(_v1234 _v1244, bkr_i64 _v1035) {
    bkr_i64 _v1239 = _v1237(_v1244);
    if ((vec_len(_v1239) < 12)) {
        return _v1284(_v1244);
    }
    bkr_i64 _v1240 = ((bkr_i64)(vec_get(_v1239, 9)));
    if (((_v1035 >= 0) && (_v1035 < vec_len(_v1240)))) {
        return vec_get(_v1240, _v1035);
    }
    return _v1284(_v1244);
}

bkr_i64 _v1304(_v1234 _v1244, bkr_i64 _v1035) {
    bkr_i64 _v1239 = _v1237(_v1244);
    if ((vec_len(_v1239) < 12)) {
        return _v1299(_v1244);
    }
    bkr_i64 _v1241 = ((bkr_i64)(vec_get(_v1239, 10)));
    if (((_v1035 >= 0) && (_v1035 < vec_len(_v1241)))) {
        return vec_get(_v1241, _v1035);
    }
    return _v1299(_v1244);
}

bkr_i64 _v1305(_v1234 _v1244, bkr_i64 _v1035) {
    bkr_i64 _v1239 = _v1237(_v1244);
    if ((vec_len(_v1239) < 12)) {
        return _v1301(_v1244);
    }
    bkr_i64 _v1242 = ((bkr_i64)(vec_get(_v1239, 11)));
    if (((_v1035 >= 0) && (_v1035 < vec_len(_v1242)))) {
        return vec_get(_v1242, _v1035);
    }
    return _v1301(_v1244);
}

bkr_str _v1306(bkr_i64 _v1307) {
    return _v324(_v1307);
}

bkr_bool _v1308(bkr_i64 _v1307) {
    return _v325(_v1307);
}

bkr_i64 _v1309(bkr_i64 _v1246, bkr_i64 _v1210) {
    return _v1310(_v1243(_v1246), _v1210);
}

bkr_i64 _v1310(_v1234 _v1246, bkr_i64 _v1210) {
    bkr_i64 _v1189 = _v1247(_v1246);
    bkr_i64 _v1035 = (_v1210 * 3);
    if (((_v1210 < 0) || ((_v1035 + 2) >= vec_len(_v1189)))) {
        return 0;
    }
    return vec_get(_v1189, (_v1035 + 2));
}

bkr_i64 _v1311(bkr_i64 _v1246, bkr_i64 _v1210) {
    return _v1312(_v1243(_v1246), _v1210);
}

bkr_i64 _v1312(_v1234 _v1246, bkr_i64 _v1210) {
    bkr_i64 _v1189 = _v1247(_v1246);
    bkr_i64 _v1035 = (_v1210 * 3);
    if (((_v1210 < 0) || ((_v1035 + 2) >= vec_len(_v1189)))) {
        return 0;
    }
    bkr_i64 _v1307 = vec_get(_v1189, _v1035);
    bkr_i64 _v387 = vec_get(_v1189, (_v1035 + 1));
    bkr_i64 _v340 = vec_get(_v1189, (_v1035 + 2));
    if ((_v1307 == _v129)) {
        return _v340;
    }
    if ((_v1307 == _v131)) {
        return (_v340 - bkr_len((bkr_str)(intptr_t)(_v1288(_v1246, _v387))));
    }
    if ((_v1307 == _v132)) {
        return (_v340 - bkr_len((bkr_str)(intptr_t)(int_to_string(_v1292(_v1246, _v387)))));
    }
    if ((_v1307 == _v133)) {
        return ((_v340 - bkr_len((bkr_str)(intptr_t)(_v1294(_v1246, _v387)))) - 2);
    }
    if ((_v1307 == _v134)) {
        return (_v340 - bkr_len((bkr_str)(intptr_t)(_v1294(_v1246, _v387))));
    }
    if (_v1308(_v1307)) {
        return (_v340 - bkr_len((bkr_str)(intptr_t)(_v1306(_v1307))));
    }
    return _v387;
}

bkr_i64 _v1313(_v1234 _v1246) {
    return _v1312(_v1246, _v1255(_v1246));
}

bkr_i64 _v1314(_v1234 _v1246) {
    bkr_i64 _v1210 = (_v1255(_v1246) - 1);
    if ((_v1210 < 0)) {
        return _v1313(_v1246);
    }
    return _v1310(_v1246, _v1210);
}

bkr_i64 _v1315(_v1234 _v1246, bkr_i64 _v339) {
    bkr_i64 _v340 = _v1314(_v1246);
    if ((_v340 < _v339)) {
        return _v1310(_v1246, _v1255(_v1246));
    }
    return _v340;
}

_v338 _v1316(_v1234 _v1246, bkr_i64 _v339) {
    return _v479(_v339, _v1315(_v1246, _v339));
}

_v341 _v1317(_v1234 _v1246, _v341 _v452, bkr_i64 _v339) {
    return _v454(_v452, _v339, _v1315(_v1246, _v339));
}

_v341 _v1318(_v341 _v452, bkr_i64 _v339, bkr_i64 _v340) {
    return _v454(_v452, _v339, _v340);
}

_v346 _v1319(_v1234 _v1246, _v346 _v520, bkr_i64 _v339) {
    _v1317(_v1246, _v585(_v520), _v339);
    return _v520;
}

_v426 _v1320(_v1234 _v1246, _v426 _v541, bkr_i64 _v339) {
    _v1317(_v1246, _v546(_v541), _v339);
    return _v541;
}

_v426 _v1321(_v426 _v541, bkr_i64 _v339, bkr_i64 _v340) {
    _v1318(_v546(_v541), _v339, _v340);
    return _v541;
}

_v427 _v1322(_v1234 _v1246, _v427 _v553, bkr_i64 _v339) {
    _v1317(_v1246, _v586(_v553), _v339);
    return _v553;
}

_v427 _v1323(_v427 _v553, bkr_i64 _v339, bkr_i64 _v340) {
    _v1318(_v586(_v553), _v339, _v340);
    return _v553;
}

_v428 _v1324(_v1234 _v1246, _v428 _v562, bkr_i64 _v339) {
    _v1317(_v1246, _v587(_v562), _v339);
    return _v562;
}

_v429 _v1325(_v1234 _v1246, _v429 _v582, bkr_i64 _v339) {
    _v1317(_v1246, _v588(_v582), _v339);
    return _v582;
}

bkr_i64 _v1326(_v1234 _v1246, bkr_i64 _v447, bkr_i64 _v339) {
    return _v1327(_v1317(_v1246, _v476(_v447), _v339));
}

_v433 _v1328(_v1234 _v1246, _v433 _v472, bkr_i64 _v339) {
    return _v471(_v472, _v339, _v1315(_v1246, _v339));
}

bkr_i64 _v1329(_v1234 _v1246, bkr_i64 _v463, bkr_i64 _v339) {
    return _v1330(_v1328(_v1246, _v592(_v463), _v339));
}

bkr_i64 _v1327(_v341 _v452) {
    return _v453(_v452);
}

bkr_i64 _v1331(_v346 _v520) {
    return _v526(_v520);
}

bkr_i64 _v1332(_v426 _v541) {
    return _v543(_v541);
}

bkr_i64 _v1333(_v427 _v553) {
    return _v554(_v553);
}

bkr_i64 _v1334(_v428 _v562) {
    return _v567(_v562);
}

bkr_i64 _v1335(_v429 _v582) {
    return _v584(_v582);
}

bkr_i64 _v1330(_v433 _v472) {
    return _v473(_v472);
}

bkr_i64 _v1336(_v434 _v607) {
    return _v608(_v607);
}

_v338 _v1337(bkr_i64 _v1246) {
    return _v1338(_v1243(_v1246));
}

_v338 _v1338(_v1234 _v1246) {
    bkr_i64 _v1210 = _v1284(_v1246);
    return _v479(_v1312(_v1246, _v1210), _v1310(_v1246, _v1210));
}

_v338 _v1339(_v1234 _v1246, bkr_i64 _v1035) {
    bkr_i64 _v1210 = _v1303(_v1246, _v1035);
    return _v479(_v1312(_v1246, _v1210), _v1310(_v1246, _v1210));
}

bkr_bool _v1340(_v1234 _v1246) {
    while ((((_v1270(_v1246) != _v192) && (_v1270(_v1246) != _v188)) && (_v1270(_v1246) != _v129))) {
        _v1277(_v1246);
    }
    if ((_v1270(_v1246) == _v192)) {
        _v1277(_v1246);
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_bool _v1341(_v1234 _v1246) {
    while (((((((((_v1270(_v1246) != _v140) && (_v1270(_v1246) != _v152)) && (_v1270(_v1246) != _v139)) && (_v1270(_v1246) != _v138)) && (_v1270(_v1246) != _v154)) && (_v1270(_v1246) != _v197)) && (_v1270(_v1246) != _v188)) && (_v1270(_v1246) != _v129))) {
        _v1277(_v1246);
    }
    return (_v1270(_v1246) != _v129);
}

bkr_i64 _v1342(bkr_i64 _v1246) {
    return _v1343(_v1243(_v1246));
}

bkr_i64 _v1343(_v1234 _v1246) {
    return _v482(_v1338(_v1246));
}

bkr_i64 _v1344(bkr_i64 _v1246) {
    return _v1345(_v1243(_v1246));
}

bkr_i64 _v1345(_v1234 _v1246) {
    return _v481(_v1338(_v1246));
}

bkr_i64 _v1346(_v1234 _v1246) {
    bkr_i64 _v387 = _v1272(_v1246);
    if (_v1308(_v1270(_v1246))) {
        _v1277(_v1246);
        return _v387;
    }
    _v1280(_v1246, _v131);
    return _v1289(_v1246, "");
}

bkr_bool _v1347(_v1234 _v1246, bkr_str _v1348) {
    if ((_v1270(_v1246) != _v131)) {
        return BKR_FALSE;
    }
    return bkr_str_eq(_v1288(_v1246, _v1272(_v1246)), _v1348);
}

_v1234 _v1349(_v1234 _v1246) {
    if ((_v1270(_v1246) == _v168)) {
        bkr_i64 _v1350 = 0;
        while ((_v1270(_v1246) != _v129)) {
            bkr_i64 _v1307 = _v1270(_v1246);
            if ((_v1307 == _v168)) {
                _v1350 = (_v1350 + 1);
            }
            if ((_v1307 == _v169)) {
                _v1350 = (_v1350 - 1);
            }
            _v1277(_v1246);
            if ((_v1350 <= 0)) {
                return _v1246;
            }
        }
    }
    return _v1246;
}

bkr_i64 _v1351(_v1234 _v1246) {
    return _v1331(_v1352(_v1246));
}

_v346 _v1352(_v1234 _v1246) {
    bkr_i64 _v339 = _v1313(_v1246);
    bkr_i64 _v1307 = _v1270(_v1246);
    bkr_i64 _v319 = _v303;
    bkr_bool _v1353 = BKR_FALSE;
    if ((_v1307 == _v185)) {
        _v1277(_v1246);
        if ((_v1270(_v1246) == _v186)) {
            _v1277(_v1246);
            return _v1319(_v1246, _v959(_v307), _v339);
        }
        _v346 _v1354 = _v1352(_v1246);
        while ((_v1270(_v1246) == _v191)) {
            _v1277(_v1246);
            _v346 _v1355 = _v1352(_v1246);
        }
        _v1279(_v1246, _v186);
        return _v1319(_v1246, _v959(_v303), _v339);
    }
    if ((_v1307 == _v189)) {
        _v1277(_v1246);
        _v346 _v1356 = _v1352(_v1246);
        _v1279(_v1246, _v192);
        bkr_i64 _v954 = 0;
        if ((_v1270(_v1246) == _v132)) {
            _v954 = _v1292(_v1246, _v1272(_v1246));
            _v1277(_v1246);
        } else {
            _v1280(_v1246, _v132);
        }
        _v1279(_v1246, _v190);
        return _v1319(_v1246, _v961(_v529(_v1356), _v954), _v339);
    }
    if ((_v1307 == _v140)) {
        _v1277(_v1246);
        _v1279(_v1246, _v185);
        if ((_v1270(_v1246) != _v186)) {
            _v346 _v1357 = _v1352(_v1246);
            while ((_v1270(_v1246) == _v191)) {
                _v1277(_v1246);
                if ((_v1270(_v1246) != _v186)) {
                    _v346 _v1358 = _v1352(_v1246);
                }
            }
        }
        _v1279(_v1246, _v186);
        if ((_v1270(_v1246) == _v181)) {
            _v1277(_v1246);
            _v346 _v1359 = _v1352(_v1246);
            bkr_i64 _v1360 = _v529(_v1359);
            return _v1319(_v1246, _v965(13, _v1360, 0), _v339);
        }
        return _v1319(_v1246, _v965(13, _v307, 0), _v339);
    }
    if ((_v1307 == _v174)) {
        _v1277(_v1246);
        return _v1319(_v1246, _v959(_v314), _v339);
    }
    if ((_v1307 == _v156)) {
        _v319 = _v302;
        _v1277(_v1246);
        _v1353 = BKR_TRUE;
    }
    if ((_v1307 == _v157)) {
        _v319 = _v303;
        _v1277(_v1246);
        _v1353 = BKR_TRUE;
    }
    if ((_v1307 == _v158)) {
        _v319 = _v304;
        _v1277(_v1246);
        _v1353 = BKR_TRUE;
    }
    if ((_v1307 == _v159)) {
        _v319 = _v305;
        _v1277(_v1246);
        _v1353 = BKR_TRUE;
    }
    if ((_v1307 == _v160)) {
        _v319 = _v306;
        _v1277(_v1246);
        _v1353 = BKR_TRUE;
    }
    if ((_v1307 == _v131)) {
        bkr_i64 _v355 = _v1272(_v1246);
        bkr_str _v1348 = _v1288(_v1246, _v355);
        if ((bkr_str_eq(_v1348, "never") && (_v1270(_v1246) != _v168))) {
            _v1277(_v1246);
            return _v1319(_v1246, _v959(_v314), _v339);
        }
        _v1277(_v1246);
        if ((_v1270(_v1246) == _v168)) {
            if (bkr_str_eq(_v1348, "Vec")) {
                _v1277(_v1246);
                _v346 _v1000 = _v1352(_v1246);
                bkr_i64 _v953 = _v529(_v1000);
                bkr_i64 _v1361 = _v531(_v1000);
                _v1279(_v1246, _v169);
                return _v1319(_v1246, _v965(8, _v953, _v1361), _v339);
            }
            if (bkr_str_eq(_v1348, "HashMap")) {
                _v1277(_v1246);
                _v346 _v1362 = _v1352(_v1246);
                bkr_i64 _v1363 = _v529(_v1362);
                _v1279(_v1246, _v191);
                _v346 _v1364 = _v1352(_v1246);
                bkr_i64 _v1365 = _v529(_v1364);
                _v1279(_v1246, _v169);
                return _v1319(_v1246, _v965(9, _v1363, _v1365), _v339);
            }
            if (bkr_str_eq(_v1348, "Option")) {
                _v1277(_v1246);
                _v346 _v1366 = _v1352(_v1246);
                bkr_i64 _v1367 = _v529(_v1366);
                bkr_i64 _v1368 = _v531(_v1366);
                _v1279(_v1246, _v169);
                return _v1319(_v1246, _v965(10, _v1367, _v1368), _v339);
            }
            if (bkr_str_eq(_v1348, "Result")) {
                _v1277(_v1246);
                _v346 _v1369 = _v1352(_v1246);
                bkr_i64 _v1370 = _v529(_v1369);
                _v1279(_v1246, _v191);
                _v346 _v1371 = _v1352(_v1246);
                bkr_i64 _v1372 = _v529(_v1371);
                _v1279(_v1246, _v169);
                return _v1319(_v1246, _v965(11, _v1370, _v1372), _v339);
            }
            _v1349(_v1246);
            _v1353 = BKR_TRUE;
        } else {
            return _v1319(_v1246, _v963(_v355), _v339);
        }
    }
    if (((!_v1353) && (_v1307 != _v129))) {
        _v1277(_v1246);
    }
    return _v1319(_v1246, _v959(_v319), _v339);
}

bkr_i64 _v1373(_v1234 _v1246) {
    return _v1330(_v1374(_v1246));
}

_v433 _v1374(_v1234 _v1246) {
    bkr_i64 _v339 = _v1313(_v1246);
    bkr_i64 _v1307 = _v1270(_v1246);
    if ((_v1307 == _v185)) {
        _v1277(_v1246);
        if ((_v1270(_v1246) == _v186)) {
            _v1277(_v1246);
            return _v1328(_v1246, _v467(_v286, 0), _v339);
        }
        bkr_i64 _v1375 = vec_new();
        _v433 _v1376 = _v1374(_v1246);
        vec_push(_v1375, _v593(_v1376));
        bkr_i64 _v1377 = (-1);
        if ((_v596(_v1376) == _v285)) {
            _v1377 = _v597(_v1376);
        }
        bkr_i64 _v432 = (-1);
        bkr_i64 _v1378 = (-1);
        if ((_v1270(_v1246) == _v191)) {
            _v1277(_v1246);
            if ((_v1270(_v1246) != _v186)) {
                _v433 _v1379 = _v1374(_v1246);
                vec_push(_v1375, _v593(_v1379));
                if ((_v596(_v1379) == _v285)) {
                    _v432 = _v597(_v1379);
                }
                if ((_v1270(_v1246) == _v191)) {
                    _v1277(_v1246);
                    if ((_v1270(_v1246) != _v186)) {
                        _v433 _v1380 = _v1374(_v1246);
                        vec_push(_v1375, _v593(_v1380));
                        if ((_v596(_v1380) == _v285)) {
                            _v1378 = _v597(_v1380);
                        }
                        if ((_v1270(_v1246) == _v191)) {
                            _v1277(_v1246);
                        }
                    }
                }
            }
        }
        _v1279(_v1246, _v186);
        bkr_i64 _v1381 = ((bkr_i64)(_v1375));
        return _v1328(_v1246, _v470(_v292, _v1378, _v1381, _v1377, _v432), _v339);
    }
    if ((_v1307 == _v132)) {
        bkr_i64 _v1382 = _v1272(_v1246);
        bkr_i64 _v1383 = _v1292(_v1246, _v1382);
        _v1277(_v1246);
        return _v1328(_v1246, _v467(_v283, _v1383), _v339);
    }
    if ((_v1307 == _v135)) {
        _v1277(_v1246);
        return _v1328(_v1246, _v467(_v284, 1), _v339);
    }
    if ((_v1307 == _v136)) {
        _v1277(_v1246);
        return _v1328(_v1246, _v467(_v284, 0), _v339);
    }
    if (_v1308(_v1307)) {
        bkr_i64 _v355 = _v1272(_v1246);
        bkr_str _v1384 = _v1288(_v1246, _v355);
        _v1277(_v1246);
        if ((_v1270(_v1246) == _v187)) {
            _v1277(_v1246);
            bkr_i64 _v1385 = (-1);
            bkr_i64 _v1386 = (-1);
            bkr_i64 _v1387 = (-1);
            if ((_v1270(_v1246) != _v188)) {
                _v1385 = _v1346(_v1246);
                if ((_v1270(_v1246) == _v193)) {
                    _v1277(_v1246);
                    _v1385 = _v1346(_v1246);
                }
                if ((_v1270(_v1246) == _v191)) {
                    _v1277(_v1246);
                    if ((_v1270(_v1246) != _v188)) {
                        _v1386 = _v1346(_v1246);
                        if ((_v1270(_v1246) == _v193)) {
                            _v1277(_v1246);
                            _v1386 = _v1346(_v1246);
                        }
                        if ((_v1270(_v1246) == _v191)) {
                            _v1277(_v1246);
                            if ((_v1270(_v1246) != _v188)) {
                                _v1387 = _v1346(_v1246);
                                if ((_v1270(_v1246) == _v193)) {
                                    _v1277(_v1246);
                                    _v1387 = _v1346(_v1246);
                                }
                            }
                        }
                    }
                }
            }
            _v1279(_v1246, _v188);
            return _v1328(_v1246, _v470(_v293, _v355, _v1387, _v1385, _v1386), _v339);
        }
        if ((_v1270(_v1246) == _v184)) {
            _v1277(_v1246);
            bkr_i64 _v1388 = _v1346(_v1246);
            bkr_str _v1389 = _v1288(_v1246, _v1388);
            bkr_i64 _v1390 = (-1);
            bkr_i64 _v1391 = (-1);
            bkr_i64 _v1392 = 0;
            if ((_v1270(_v1246) == _v185)) {
                _v1277(_v1246);
                _v433 _v1393 = _v1374(_v1246);
                if ((_v596(_v1393) == _v285)) {
                    _v1390 = _v597(_v1393);
                } else {
                    _v1392 = _v593(_v1393);
                }
                if ((_v1270(_v1246) == _v191)) {
                    _v1277(_v1246);
                    _v1391 = _v1346(_v1246);
                }
                _v1279(_v1246, _v186);
            }
            if (bkr_str_eq(_v1384, "Option")) {
                if (bkr_str_eq(_v1389, "Some")) {
                    return _v1328(_v1246, _v468(_v287, _v1390, _v1392), _v339);
                }
                if (bkr_str_eq(_v1389, "None")) {
                    return _v1328(_v1246, _v467(_v288, 0), _v339);
                }
            }
            if (bkr_str_eq(_v1384, "Result")) {
                if (bkr_str_eq(_v1389, "Ok")) {
                    return _v1328(_v1246, _v468(_v290, _v1390, _v1392), _v339);
                }
                if (bkr_str_eq(_v1389, "Err")) {
                    return _v1328(_v1246, _v468(_v291, _v1390, _v1392), _v339);
                }
            }
            return _v1328(_v1246, _v470(_v289, _v355, _v1388, _v1390, _v1391), _v339);
        }
        if (bkr_str_eq(_v1384, "_")) {
            return _v1328(_v1246, _v467(_v286, 0), _v339);
        }
        if ((bkr_str_eq(_v1384, "Some") && (_v1270(_v1246) == _v185))) {
            _v1277(_v1246);
            _v433 _v1393 = _v1374(_v1246);
            _v1279(_v1246, _v186);
            bkr_i64 _v1390 = (-1);
            bkr_i64 _v1394 = 0;
            if ((_v596(_v1393) == _v285)) {
                _v1390 = _v597(_v1393);
            } else {
                _v1394 = _v593(_v1393);
            }
            return _v1328(_v1246, _v468(_v287, _v1390, _v1394), _v339);
        }
        if (bkr_str_eq(_v1384, "None")) {
            return _v1328(_v1246, _v467(_v288, 0), _v339);
        }
        if ((bkr_str_eq(_v1384, "Ok") && (_v1270(_v1246) == _v185))) {
            _v1277(_v1246);
            _v433 _v1393 = _v1374(_v1246);
            _v1279(_v1246, _v186);
            bkr_i64 _v1390 = (-1);
            bkr_i64 _v1394 = 0;
            if ((_v596(_v1393) == _v285)) {
                _v1390 = _v597(_v1393);
            } else {
                _v1394 = _v593(_v1393);
            }
            return _v1328(_v1246, _v468(_v290, _v1390, _v1394), _v339);
        }
        if ((bkr_str_eq(_v1384, "Err") && (_v1270(_v1246) == _v185))) {
            _v1277(_v1246);
            _v433 _v1393 = _v1374(_v1246);
            _v1279(_v1246, _v186);
            bkr_i64 _v1390 = (-1);
            bkr_i64 _v1394 = 0;
            if ((_v596(_v1393) == _v285)) {
                _v1390 = _v597(_v1393);
            } else {
                _v1394 = _v593(_v1393);
            }
            return _v1328(_v1246, _v468(_v291, _v1390, _v1394), _v339);
        }
        if ((_v1270(_v1246) == _v185)) {
            _v1277(_v1246);
            bkr_i64 _v1376 = _v1346(_v1246);
            bkr_i64 _v1379 = (-1);
            bkr_i64 _v1380 = (-1);
            if ((_v1270(_v1246) == _v191)) {
                _v1277(_v1246);
                _v1379 = _v1346(_v1246);
                if ((_v1270(_v1246) == _v191)) {
                    _v1277(_v1246);
                    _v1380 = _v1346(_v1246);
                }
            }
            _v1279(_v1246, _v186);
            return _v1328(_v1246, _v470(_v293, _v355, _v1380, _v1376, _v1379), _v339);
        }
        return _v1328(_v1246, _v467(_v285, _v355), _v339);
    }
    _v1280(_v1246, _v131);
    if ((_v1307 != _v129)) {
        _v1277(_v1246);
    }
    return _v1328(_v1246, _v467(_v286, 0), _v339);
}

bkr_i64 _v1395(_v1234 _v1246) {
    return _v1332(_v1396(_v1246));
}

_v426 _v1396(_v1234 _v1246) {
    bkr_i64 _v339 = _v1313(_v1246);
    _v1279(_v1246, _v151);
    _v426 _v974 = _v1397(_v1246);
    _v1279(_v1246, _v187);
    bkr_i64 _v406 = vec_new();
    bkr_i64 _v407 = vec_new();
    bkr_i64 _v408 = vec_new();
    _v436 _v620 = _v618(_v406);
    _v434 _v975 = _v604(_v407);
    _v435 _v976 = _v611(_v408);
    while (((_v1270(_v1246) != _v188) && (_v1270(_v1246) != _v129))) {
        _v433 _v472 = _v1374(_v1246);
        bkr_i64 _v1398 = 0;
        if ((_v1270(_v1246) == _v142)) {
            _v1277(_v1246);
            _v426 _v1399 = _v1397(_v1246);
            _v1398 = _v540(_v1399);
        }
        _v642(_v976, _v1398);
        _v1279(_v1246, _v195);
        if ((_v1270(_v1246) == _v187)) {
            _v637(_v975, _v1400(_v1246));
            if (((_v1270(_v1246) == _v192) || (_v1270(_v1246) == _v191))) {
                _v1277(_v1246);
            }
        } else {
            _v635(_v975, _v1397(_v1246));
            _v1279(_v1246, _v192);
        }
        _v640(_v620, _v472);
    }
    _v1279(_v1246, _v188);
    return _v1320(_v1246, _v973(_v974, _v620, _v975, _v976), _v339);
}

bkr_i64 _v1401(_v1234 _v1246) {
    return _v1332(_v1402(_v1246));
}

_v426 _v1402(_v1234 _v1246) {
    bkr_i64 _v339 = _v1313(_v1246);
    bkr_i64 _v1307 = _v1270(_v1246);
    if ((_v1307 == _v151)) {
        return _v1396(_v1246);
    }
    if ((_v1307 == _v142)) {
        _v1277(_v1246);
        _v426 _v1056 = _v1397(_v1246);
        _v429 _v376 = _v1400(_v1246);
        _v426 _v1403 = _v537(_v581(_v376));
        _v1279(_v1246, _v143);
        _v426 _v1404 = _v537(0);
        if ((_v1270(_v1246) == _v142)) {
            _v1404 = _v1402(_v1246);
        } else {
            _v429 _v377 = _v1400(_v1246);
            _v1404 = _v537(_v581(_v377));
        }
        return _v1320(_v1246, _v1055(_v1056, _v1403, _v1404), _v339);
    }
    if ((_v1307 == _v187)) {
        _v429 _v582 = _v1400(_v1246);
        return _v537(_v581(_v582));
    }
    if ((_v1307 == _v132)) {
        bkr_i64 _v1382 = _v1272(_v1246);
        bkr_i64 _v1383 = _v1292(_v1246, _v1382);
        _v1277(_v1246);
        return _v1320(_v1246, _v983(_v1383), _v339);
    }
    if ((_v1307 == _v134)) {
        bkr_i64 _v1405 = _v1272(_v1246);
        _v1277(_v1246);
        return _v1320(_v1246, _v985(_v1294(_v1246, _v1405)), _v339);
    }
    if ((_v1307 == _v135)) {
        _v1277(_v1246);
        return _v1320(_v1246, _v987(1), _v339);
    }
    if ((_v1307 == _v136)) {
        _v1277(_v1246);
        return _v1320(_v1246, _v987(0), _v339);
    }
    if ((_v1307 == _v133)) {
        bkr_i64 _v1405 = _v1272(_v1246);
        _v1277(_v1246);
        return _v1320(_v1246, _v989(_v1294(_v1246, _v1405)), _v339);
    }
    if ((_v1307 == _v185)) {
        _v1277(_v1246);
        if ((_v1270(_v1246) == _v186)) {
            _v1277(_v1246);
            return _v1320(_v1246, _v983(0), _v339);
        }
        _v426 _v541 = _v1397(_v1246);
        if ((_v1270(_v1246) == _v191)) {
            _v1277(_v1246);
            _v426 _v1406 = _v1397(_v1246);
            if ((_v1270(_v1246) == _v191)) {
                _v1277(_v1246);
                _v426 _v1407 = _v1397(_v1246);
                _v1279(_v1246, _v186);
                bkr_i64 _v1408 = vec_new();
                _v434 _v1409 = _v604(_v1408);
                _v635(_v1409, _v541);
                _v635(_v1409, _v1406);
                _v635(_v1409, _v1407);
                bkr_i64 _v1410 = _v1289(_v1246, "bkr_tuple3");
                _v426 _v1411 = _v1014(_v1410, _v1409);
                return _v1320(_v1246, _v1411, _v339);
            }
            _v1279(_v1246, _v186);
            bkr_i64 _v1412 = vec_new();
            _v434 _v1413 = _v604(_v1412);
            _v635(_v1413, _v541);
            _v635(_v1413, _v1406);
            bkr_i64 _v1414 = _v1289(_v1246, "bkr_tuple2");
            _v426 _v1415 = _v1014(_v1414, _v1413);
            return _v1320(_v1246, _v1415, _v339);
        }
        _v1279(_v1246, _v186);
        return _v1320(_v1246, _v541, _v339);
    }
    if ((_v1307 == _v189)) {
        _v1277(_v1246);
        if ((_v1270(_v1246) == _v190)) {
            _v1277(_v1246);
            bkr_i64 _v396 = vec_new();
            _v434 _v994 = _v604(_v396);
            return _v1320(_v1246, _v993(_v994), _v339);
        }
        _v426 _v1416 = _v1397(_v1246);
        if ((_v1270(_v1246) == _v192)) {
            _v1277(_v1246);
            bkr_i64 _v1417 = 0;
            if ((_v1270(_v1246) == _v132)) {
                _v1417 = _v1292(_v1246, _v1272(_v1246));
                _v1277(_v1246);
            } else {
                _v1280(_v1246, _v132);
            }
            _v1279(_v1246, _v190);
            return _v1320(_v1246, _v999(_v1416, _v1417), _v339);
        }
        bkr_i64 _v396 = vec_new();
        _v434 _v994 = _v604(_v396);
        _v635(_v994, _v1416);
        if ((_v1270(_v1246) == _v191)) {
            _v1277(_v1246);
        }
        while (((_v1270(_v1246) != _v190) && (_v1270(_v1246) != _v129))) {
            _v426 _v1000 = _v1397(_v1246);
            _v635(_v994, _v1000);
            if ((_v1270(_v1246) == _v191)) {
                _v1277(_v1246);
            }
        }
        _v1279(_v1246, _v190);
        return _v1320(_v1246, _v993(_v994), _v339);
    }
    if (_v1308(_v1307)) {
        bkr_i64 _v355 = _v1272(_v1246);
        bkr_str _v1384 = _v1288(_v1246, _v355);
        if (bkr_str_eq(_v1384, "copy")) {
            _v1277(_v1246);
            _v426 _v1031 = _v1402(_v1246);
            return _v1320(_v1246, _v1031, _v339);
        }
        _v1277(_v1246);
        bkr_bool _v1418 = (((bkr_len((bkr_str)(intptr_t)(_v1384)) > 0) && (char_code_at(_v1384, 0) >= 65)) && (char_code_at(_v1384, 0) <= 90));
        bkr_i64 _v1419 = _v1275(_v1246, 1);
        bkr_i64 _v1420 = _v1275(_v1246, 2);
        bkr_bool _v1421 = (((_v1270(_v1246) == _v187) && _v1418) && (((_v1419 == _v188) || (_v1419 == _v182)) || (_v1308(_v1419) && (_v1420 == _v193))));
        if (_v1421) {
            _v1277(_v1246);
            bkr_i64 _v401 = vec_new();
            bkr_i64 _v402 = vec_new();
            _v435 _v1007 = _v611(_v401);
            _v434 _v1008 = _v604(_v402);
            bkr_i64 _v403 = 0;
            while (((_v1270(_v1246) != _v188) && (_v1270(_v1246) != _v129))) {
                if ((_v1270(_v1246) == _v182)) {
                    _v1277(_v1246);
                    _v426 _v1037 = _v1397(_v1246);
                    _v403 = _v540(_v1037);
                    if ((_v1270(_v1246) == _v191)) {
                        _v1277(_v1246);
                    }
                } else {
                    bkr_i64 _v1044 = _v1346(_v1246);
                    _v1279(_v1246, _v193);
                    _v426 _v1422 = _v1397(_v1246);
                    _v642(_v1007, _v1044);
                    _v635(_v1008, _v1422);
                    if ((_v1270(_v1246) == _v191)) {
                        _v1277(_v1246);
                    }
                }
            }
            _v1279(_v1246, _v188);
            return _v1320(_v1246, _v1006(_v355, _v1007, _v1008, _v403), _v339);
        }
        if ((_v1270(_v1246) == _v196)) {
            _v1277(_v1246);
            bkr_i64 _v1423 = _v1346(_v1246);
            bkr_str _v1424 = bkr_str_concat(bkr_str_concat(_v1288(_v1246, _v355), "::"), _v1288(_v1246, _v1423));
            _v355 = _v1289(_v1246, _v1424);
        }
        if ((_v1270(_v1246) == _v185)) {
            _v1277(_v1246);
            bkr_i64 _v356 = vec_new();
            _v434 _v1015 = _v604(_v356);
            while (((_v1270(_v1246) != _v186) && (_v1270(_v1246) != _v129))) {
                _v426 _v1425 = _v1397(_v1246);
                _v635(_v1015, _v1425);
                if ((_v1270(_v1246) == _v191)) {
                    _v1277(_v1246);
                }
            }
            _v1279(_v1246, _v186);
            return _v1320(_v1246, _v1014(_v355, _v1015), _v339);
        }
        return _v1320(_v1246, _v1023(_v355), _v339);
    }
    if ((_v1307 == _v174)) {
        _v1277(_v1246);
        _v426 _v1031 = _v1402(_v1246);
        return _v1320(_v1246, _v1030(_v174, _v1031), _v339);
    }
    if ((_v1307 == _v162)) {
        _v1277(_v1246);
        _v426 _v1031 = _v1402(_v1246);
        return _v1320(_v1246, _v1030(_v162, _v1031), _v339);
    }
    if ((_v1307 != _v129)) {
        _v1277(_v1246);
    }
    return _v1320(_v1246, _v983(0), _v339);
}

bkr_bool _v1426(_v1234 _v1246) {
    bkr_i64 _v1274 = 1;
    while (BKR_TRUE) {
        bkr_i64 _v1307 = _v1275(_v1246, _v1274);
        if ((_v1307 == _v193)) {
            return BKR_TRUE;
        }
        if (((((((_v1307 == _v192) || (_v1307 == _v188)) || (_v1307 == _v186)) || (_v1307 == _v190)) || (_v1307 == _v191)) || (_v1307 == _v129))) {
            return BKR_FALSE;
        }
        _v1274 = (_v1274 + 1);
    }
    return BKR_FALSE;
}

bkr_i64 _v1427(_v1234 _v1246) {
    return _v1332(_v1428(_v1246));
}

_v426 _v1428(_v1234 _v1246) {
    _v426 _v1037 = _v1402(_v1246);
    bkr_bool _v1429 = BKR_TRUE;
    while (_v1429) {
        bkr_i64 _v1430 = _v1270(_v1246);
        if ((_v1430 == _v189)) {
            bkr_i64 _v339 = _v545(_v1037);
            _v1277(_v1246);
            _v426 _v1431 = _v1397(_v1246);
            _v1279(_v1246, _v190);
            _v426 _v1038 = _v1036(_v1037, _v1431);
            _v1037 = _v1321(_v1038, _v339, _v1314(_v1246));
        } else {
            if ((_v1430 == _v184)) {
                bkr_i64 _v339 = _v545(_v1037);
                _v1277(_v1246);
                bkr_i64 _v1044 = 0;
                if ((_v1270(_v1246) == _v132)) {
                    bkr_i64 _v1382 = _v1272(_v1246);
                    bkr_i64 _v1383 = _v1292(_v1246, _v1382);
                    _v1277(_v1246);
                    if ((_v1383 == 0)) {
                        _v1044 = _v1289(_v1246, "0");
                    }
                    if ((_v1383 == 1)) {
                        _v1044 = _v1289(_v1246, "1");
                    }
                    if ((_v1383 == 2)) {
                        _v1044 = _v1289(_v1246, "2");
                    }
                    if ((_v1383 == 3)) {
                        _v1044 = _v1289(_v1246, "3");
                    }
                } else {
                    _v1044 = _v1346(_v1246);
                }
                _v426 _v1432 = _v1043(_v1037, _v1044);
                _v1037 = _v1321(_v1432, _v339, _v1314(_v1246));
            } else {
                if ((_v1430 == _v194)) {
                    bkr_bool _v1433 = _v1426(_v1246);
                    if ((!_v1433)) {
                        bkr_i64 _v339 = _v545(_v1037);
                        _v1277(_v1246);
                        _v426 _v1434 = _v1075(_v1037);
                        _v1037 = _v1321(_v1434, _v339, _v1314(_v1246));
                    } else {
                        _v1429 = BKR_FALSE;
                    }
                } else {
                    if ((_v1430 == _v155)) {
                        bkr_i64 _v339 = _v545(_v1037);
                        _v1277(_v1246);
                        _v346 _v1435 = _v1352(_v1246);
                        _v426 _v1436 = _v1081(_v1037, _v1435);
                        _v1037 = _v1321(_v1436, _v339, _v1314(_v1246));
                    } else {
                        _v1429 = BKR_FALSE;
                    }
                }
            }
        }
    }
    if ((_v1270(_v1246) == _v185)) {
        bkr_i64 _v339 = _v545(_v1037);
        bkr_bool _v1437 = BKR_FALSE;
        if ((_v544(_v1037) == _v256)) {
            _v426 _v1438 = _v720(_v1037);
            if ((_v544(_v1438) == _v245)) {
                bkr_str _v1439 = _v1288(_v1246, _v662(_v1438));
                bkr_i64 _v1440 = char_code_at(_v1439, 0);
                if (((_v1440 >= 65) && (_v1440 <= 90))) {
                    _v1437 = BKR_TRUE;
                }
            }
        }
        if (_v1437) {
            _v1277(_v1246);
            if ((_v1270(_v1246) != _v186)) {
                _v426 _v1441 = _v1397(_v1246);
                if ((_v1270(_v1246) == _v191)) {
                    _v1277(_v1246);
                    _v426 _v1442 = _v1397(_v1246);
                    _v1279(_v1246, _v186);
                    _v426 _v1443 = _v983(20);
                    _v426 _v1444 = _v983(8);
                    _v426 _v1445 = _v1049(_v178, _v1441, _v1443);
                    _v426 _v1446 = _v1049(_v178, _v1442, _v1444);
                    _v426 _v1158 = _v1049(_v176, _v1445, _v1446);
                    _v426 _v1447 = _v1049(_v176, _v1158, _v1037);
                    _v1037 = _v1321(_v1447, _v339, _v1314(_v1246));
                } else {
                    _v1279(_v1246, _v186);
                    _v426 _v1444 = _v983(8);
                    _v426 _v1448 = _v1049(_v178, _v1441, _v1444);
                    _v426 _v1447 = _v1049(_v176, _v1448, _v1037);
                    _v1037 = _v1321(_v1447, _v339, _v1314(_v1246));
                }
            } else {
                _v1277(_v1246);
            }
        } else {
            if ((_v544(_v1037) == _v256)) {
                _v426 _v1438 = _v720(_v1037);
                bkr_i64 _v359 = _v722(_v1037);
                _v1277(_v1246);
                bkr_i64 _v1449 = vec_new();
                _v434 _v1015 = _v604(_v1449);
                while (((_v1270(_v1246) != _v186) && (_v1270(_v1246) != _v129))) {
                    _v426 _v1425 = _v1397(_v1246);
                    _v635(_v1015, _v1425);
                    if ((_v1270(_v1246) == _v191)) {
                        _v1277(_v1246);
                    }
                }
                _v1279(_v1246, _v186);
                _v426 _v1450 = _v1020(_v1438, _v359, _v1015);
                _v1037 = _v1321(_v1450, _v339, _v1314(_v1246));
            }
        }
    }
    return _v1037;
}

bkr_i64 _v1451(_v1234 _v1246) {
    return _v1332(_v1452(_v1246));
}

_v426 _v1452(_v1234 _v1246) {
    _v426 _v1050 = _v1428(_v1246);
    while ((((_v1270(_v1246) == _v163) || (_v1270(_v1246) == _v164)) || (_v1270(_v1246) == _v165))) {
        bkr_i64 _v349 = _v1270(_v1246);
        bkr_i64 _v339 = _v545(_v1050);
        _v1277(_v1246);
        _v426 _v1051 = _v1428(_v1246);
        _v426 _v1453 = _v1049(_v349, _v1050, _v1051);
        _v1050 = _v1321(_v1453, _v339, _v547(_v1051));
    }
    return _v1050;
}

bkr_i64 _v1454(_v1234 _v1246) {
    return _v1332(_v1455(_v1246));
}

_v426 _v1455(_v1234 _v1246) {
    _v426 _v1050 = _v1452(_v1246);
    while (((_v1270(_v1246) == _v161) || (_v1270(_v1246) == _v162))) {
        bkr_i64 _v349 = _v1270(_v1246);
        bkr_i64 _v339 = _v545(_v1050);
        _v1277(_v1246);
        _v426 _v1051 = _v1452(_v1246);
        _v426 _v1453 = _v1049(_v349, _v1050, _v1051);
        _v1050 = _v1321(_v1453, _v339, _v547(_v1051));
    }
    return _v1050;
}

bkr_i64 _v1456(_v1234 _v1246) {
    return _v1332(_v1457(_v1246));
}

_v426 _v1457(_v1234 _v1246) {
    _v426 _v1050 = _v1455(_v1246);
    while (((_v1270(_v1246) == _v178) || (_v1270(_v1246) == _v179))) {
        bkr_i64 _v349 = _v1270(_v1246);
        bkr_i64 _v339 = _v545(_v1050);
        _v1277(_v1246);
        _v426 _v1051 = _v1455(_v1246);
        _v426 _v1453 = _v1049(_v349, _v1050, _v1051);
        _v1050 = _v1321(_v1453, _v339, _v547(_v1051));
    }
    return _v1050;
}

bkr_i64 _v1458(_v1234 _v1246) {
    return _v1332(_v1459(_v1246));
}

_v426 _v1459(_v1234 _v1246) {
    _v426 _v1050 = _v1457(_v1246);
    while ((_v1270(_v1246) == _v175)) {
        bkr_i64 _v339 = _v545(_v1050);
        _v1277(_v1246);
        _v426 _v1051 = _v1457(_v1246);
        _v426 _v1453 = _v1049(_v175, _v1050, _v1051);
        _v1050 = _v1321(_v1453, _v339, _v547(_v1051));
    }
    return _v1050;
}

bkr_i64 _v1460(_v1234 _v1246) {
    return _v1332(_v1461(_v1246));
}

_v426 _v1461(_v1234 _v1246) {
    _v426 _v1050 = _v1459(_v1246);
    while ((_v1270(_v1246) == _v177)) {
        bkr_i64 _v339 = _v545(_v1050);
        _v1277(_v1246);
        _v426 _v1051 = _v1459(_v1246);
        _v426 _v1453 = _v1049(_v177, _v1050, _v1051);
        _v1050 = _v1321(_v1453, _v339, _v547(_v1051));
    }
    return _v1050;
}

bkr_i64 _v1462(_v1234 _v1246) {
    return _v1332(_v1463(_v1246));
}

_v426 _v1463(_v1234 _v1246) {
    _v426 _v1050 = _v1461(_v1246);
    while ((_v1270(_v1246) == _v176)) {
        bkr_i64 _v339 = _v545(_v1050);
        _v1277(_v1246);
        _v426 _v1051 = _v1461(_v1246);
        _v426 _v1453 = _v1049(_v176, _v1050, _v1051);
        _v1050 = _v1321(_v1453, _v339, _v547(_v1051));
    }
    return _v1050;
}

bkr_i64 _v1464(_v1234 _v1246) {
    return _v1332(_v1465(_v1246));
}

_v426 _v1465(_v1234 _v1246) {
    _v426 _v1050 = _v1463(_v1246);
    bkr_i64 _v1307 = _v1270(_v1246);
    if (((((((_v1307 == _v166) || (_v1307 == _v167)) || (_v1307 == _v168)) || (_v1307 == _v169)) || (_v1307 == _v170)) || (_v1307 == _v171))) {
        bkr_i64 _v339 = _v545(_v1050);
        _v1277(_v1246);
        _v426 _v1051 = _v1463(_v1246);
        _v426 _v1453 = _v1049(_v1307, _v1050, _v1051);
        return _v1321(_v1453, _v339, _v547(_v1051));
    }
    return _v1050;
}

bkr_i64 _v1466(_v1234 _v1246) {
    return _v1332(_v1467(_v1246));
}

_v426 _v1467(_v1234 _v1246) {
    _v426 _v1050 = _v1465(_v1246);
    while ((_v1270(_v1246) == _v172)) {
        bkr_i64 _v339 = _v545(_v1050);
        _v1277(_v1246);
        _v426 _v1051 = _v1465(_v1246);
        _v426 _v1453 = _v1049(_v172, _v1050, _v1051);
        _v1050 = _v1321(_v1453, _v339, _v547(_v1051));
    }
    return _v1050;
}

bkr_i64 _v1468(_v1234 _v1246) {
    return _v1332(_v1469(_v1246));
}

_v426 _v1469(_v1234 _v1246) {
    _v426 _v1050 = _v1467(_v1246);
    while ((_v1270(_v1246) == _v173)) {
        bkr_i64 _v339 = _v545(_v1050);
        _v1277(_v1246);
        _v426 _v1051 = _v1467(_v1246);
        _v426 _v1453 = _v1049(_v173, _v1050, _v1051);
        _v1050 = _v1321(_v1453, _v339, _v547(_v1051));
    }
    return _v1050;
}

bkr_i64 _v1470(_v1234 _v1246) {
    return _v1332(_v1471(_v1246));
}

_v426 _v1471(_v1234 _v1246) {
    _v426 _v1056 = _v1469(_v1246);
    if ((_v1270(_v1246) == _v194)) {
        _v1277(_v1246);
        _v426 _v1057 = _v1397(_v1246);
        _v1279(_v1246, _v193);
        _v426 _v1058 = _v1397(_v1246);
        _v426 _v1472 = _v1055(_v1056, _v1057, _v1058);
        return _v1321(_v1472, _v545(_v1056), _v547(_v1058));
    }
    return _v1056;
}

bkr_i64 _v1473(_v1234 _v1246) {
    return _v1332(_v1397(_v1246));
}

_v426 _v1397(_v1234 _v1246) {
    _v426 _v541 = _v1471(_v1246);
    while (_v1347(_v1246, "as")) {
        _v1277(_v1246);
        _v1352(_v1246);
    }
    return _v541;
}

bkr_i64 _v1474(_v1234 _v1246) {
    return _v1333(_v1475(_v1246));
}

_v427 _v1475(_v1234 _v1246) {
    bkr_i64 _v339 = _v1313(_v1246);
    _v1277(_v1246);
    if ((_v1270(_v1246) == _v198)) {
        _v1277(_v1246);
    }
    bkr_i64 _v355 = _v1346(_v1246);
    bkr_i64 _v515 = _v564();
    if ((_v1270(_v1246) == _v193)) {
        _v1277(_v1246);
        _v515 = _v521(_v1352(_v1246));
    }
    bkr_i64 _v366 = _v564();
    if ((_v1270(_v1246) == _v180)) {
        _v1277(_v1246);
        _v366 = _v542(_v1397(_v1246));
    }
    if ((!_v1279(_v1246, _v192))) {
        _v1340(_v1246);
    }
    _v427 _v1476 = _v1062(_v355, _v515, _v366);
    return _v1322(_v1246, _v1476, _v339);
}

bkr_i64 _v1477(_v1234 _v1246) {
    return _v1333(_v1478(_v1246));
}

_v427 _v1478(_v1234 _v1246) {
    bkr_i64 _v339 = _v1313(_v1246);
    _v1277(_v1246);
    bkr_i64 _v368 = _v564();
    if ((_v1270(_v1246) != _v192)) {
        _v368 = _v542(_v1397(_v1246));
    }
    if ((!_v1279(_v1246, _v192))) {
        _v1340(_v1246);
    }
    _v427 _v1479 = _v1066(_v368);
    return _v1322(_v1246, _v1479, _v339);
}

bkr_i64 _v1480(_v1234 _v1246) {
    return _v1333(_v1481(_v1246));
}

_v427 _v1481(_v1234 _v1246) {
    bkr_i64 _v339 = _v1313(_v1246);
    bkr_i64 _v1307 = _v1270(_v1246);
    if ((_v1307 == _v141)) {
        return _v1475(_v1246);
    }
    if ((_v1307 == _v150)) {
        return _v1478(_v1246);
    }
    if ((_v1307 == _v153)) {
        _v1277(_v1246);
        _v427 _v1482 = _v549(0);
        if ((_v1270(_v1246) == _v187)) {
            _v429 _v582 = _v1400(_v1246);
            _v1482 = _v549(_v581(_v582));
        } else {
            _v426 _v541 = _v1397(_v1246);
            _v1279(_v1246, _v192);
            _v427 _v1483 = _v1099(_v541);
            _v1482 = _v1323(_v1483, _v545(_v541), _v1314(_v1246));
        }
        _v427 _v1484 = _v1070(_v1482);
        return _v1322(_v1246, _v1484, _v339);
    }
    if ((_v1307 == _v147)) {
        _v1277(_v1246);
        _v1279(_v1246, _v192);
        _v427 _v1485 = _v1085();
        return _v1322(_v1246, _v1485, _v339);
    }
    if ((_v1307 == _v148)) {
        _v1277(_v1246);
        _v1279(_v1246, _v192);
        _v427 _v1486 = _v1089();
        return _v1322(_v1246, _v1486, _v339);
    }
    _v426 _v541 = _v1397(_v1246);
    if ((_v1270(_v1246) == _v180)) {
        bkr_i64 _v1487 = _v545(_v541);
        _v1277(_v1246);
        _v426 _v1095 = _v1397(_v1246);
        _v1279(_v1246, _v192);
        _v427 _v1488 = _v1093(_v541, _v1095);
        return _v1323(_v1488, _v1487, _v1314(_v1246));
    }
    if ((!_v1279(_v1246, _v192))) {
        _v1340(_v1246);
    }
    _v427 _v1483 = _v1099(_v541);
    return _v1323(_v1483, _v545(_v541), _v1314(_v1246));
}

bkr_i64 _v1489(_v1234 _v1246) {
    return _v1333(_v1490(_v1246));
}

_v427 _v1490(_v1234 _v1246) {
    bkr_i64 _v339 = _v1313(_v1246);
    _v1279(_v1246, _v142);
    _v426 _v1056 = _v1397(_v1246);
    _v429 _v1116 = _v1400(_v1246);
    bkr_i64 _v377 = _v564();
    if ((_v1270(_v1246) == _v143)) {
        _v1277(_v1246);
        if ((_v1270(_v1246) == _v142)) {
            _v427 _v1491 = _v1490(_v1246);
            _v377 = _v583(_v1111(_v1491));
        } else {
            _v377 = _v583(_v1400(_v1246));
        }
    }
    _v427 _v1492 = _v1115(_v1056, _v1116, _v377);
    return _v1322(_v1246, _v1492, _v339);
}

bkr_i64 _v1493(_v1234 _v1246) {
    return _v1333(_v1494(_v1246));
}

_v427 _v1494(_v1234 _v1246) {
    bkr_i64 _v339 = _v1313(_v1246);
    _v1279(_v1246, _v144);
    bkr_i64 _v355 = _v1346(_v1246);
    _v1279(_v1246, _v145);
    _v426 _v1121 = _v1397(_v1246);
    bkr_i64 _v383 = 0;
    if ((_v1270(_v1246) == _v183)) {
        _v383 = 1;
        _v1277(_v1246);
    } else {
        _v1279(_v1246, _v182);
    }
    _v426 _v1122 = _v1397(_v1246);
    _v429 _v1123 = _v1400(_v1246);
    _v427 _v1495 = _v1120(_v355, _v1121, _v1122, _v383, _v1123);
    return _v1322(_v1246, _v1495, _v339);
}

bkr_i64 _v1496(_v1234 _v1246) {
    return _v1335(_v1400(_v1246));
}

_v429 _v1400(_v1234 _v1246) {
    bkr_i64 _v339 = _v1313(_v1246);
    _v429 _v582 = _v1103();
    _v1279(_v1246, _v187);
    while (((_v1270(_v1246) != _v188) && (_v1270(_v1246) != _v129))) {
        bkr_i64 _v1307 = _v1270(_v1246);
        if ((_v1307 == _v142)) {
            _v1109(_v582, _v1490(_v1246));
        } else {
            if ((_v1307 == _v144)) {
                _v1109(_v582, _v1494(_v1246));
            } else {
                if ((_v1307 == _v146)) {
                    bkr_i64 _v1497 = _v1313(_v1246);
                    _v1277(_v1246);
                    _v426 _v1056 = _v1397(_v1246);
                    _v429 _v1123 = _v1400(_v1246);
                    _v427 _v1498 = _v1127(_v1056, _v1123);
                    _v1109(_v582, _v1323(_v1498, _v1497, _v1314(_v1246)));
                } else {
                    if ((_v1307 == _v149)) {
                        bkr_i64 _v1497 = _v1313(_v1246);
                        _v1277(_v1246);
                        _v429 _v1123 = _v1400(_v1246);
                        _v427 _v1499 = _v1131(_v1123);
                        _v1109(_v582, _v1323(_v1499, _v1497, _v1314(_v1246)));
                    } else {
                        _v1109(_v582, _v1481(_v1246));
                    }
                }
            }
        }
    }
    _v1279(_v1246, _v188);
    return _v1325(_v1246, _v582, _v339);
}

bkr_i64 _v1500(_v1234 _v1246) {
    return _v1336(_v1501(_v1246));
}

_v434 _v1501(_v1234 _v1246) {
    return _v1502(_v1246, 0);
}

_v434 _v1502(_v1234 _v1246, bkr_i64 _v1503) {
    bkr_i64 _v411 = vec_new();
    _v434 _v1141 = _v604(_v411);
    _v1279(_v1246, _v185);
    if ((_v1270(_v1246) != _v186)) {
        bkr_i64 _v1504 = _v1313(_v1246);
        bkr_i64 _v355 = _v1346(_v1246);
        _v346 _v1505 = _v959(0);
        bkr_str _v1506 = _v1288(_v1246, _v355);
        if ((_v1270(_v1246) == _v193)) {
            _v1277(_v1246);
            _v1505 = _v1352(_v1246);
        } else {
            if ((bkr_str_eq(_v1506, "self") && (_v1503 != 0))) {
                _v1505 = _v963(_v1503);
            }
        }
        _v341 _v1507 = _v1318(_v1136(_v355, _v1505), _v1504, _v1314(_v1246));
        _v634(_v1141, _v1507);
        while ((_v1270(_v1246) == _v191)) {
            _v1277(_v1246);
            if ((_v1270(_v1246) == _v186)) {
                break;
            }
            bkr_i64 _v1508 = _v1313(_v1246);
            bkr_i64 _v1509 = _v1346(_v1246);
            _v1279(_v1246, _v193);
            _v346 _v1510 = _v1352(_v1246);
            _v341 _v1511 = _v1318(_v1136(_v1509, _v1510), _v1508, _v1314(_v1246));
            _v634(_v1141, _v1511);
        }
    }
    _v1279(_v1246, _v186);
    return _v1141;
}

bkr_i64 _v1512(_v1234 _v1246) {
    return _v1334(_v1513(_v1246));
}

_v428 _v1513(_v1234 _v1246) {
    bkr_i64 _v339 = _v1313(_v1246);
    _v1279(_v1246, _v140);
    bkr_i64 _v355 = _v1346(_v1246);
    bkr_i64 _v1503 = 0;
    if ((_v1270(_v1246) == _v196)) {
        _v1277(_v1246);
        bkr_i64 _v359 = _v1346(_v1246);
        _v1503 = _v355;
        bkr_str _v1424 = bkr_str_concat(bkr_str_concat(_v1288(_v1246, _v355), "::"), _v1288(_v1246, _v359));
        _v355 = _v1289(_v1246, _v1424);
    }
    _v434 _v1141 = _v1502(_v1246, _v1503);
    bkr_i64 _v1142 = _v564();
    if ((_v1270(_v1246) == _v181)) {
        _v1277(_v1246);
        _v1142 = _v521(_v1352(_v1246));
    }
    _v429 _v1123 = _v1400(_v1246);
    _v428 _v1514 = _v1140(_v355, _v1141, _v1142, _v1123);
    return _v1324(_v1246, _v1514, _v339);
}

bkr_i64 _v1515(_v1234 _v1246) {
    return _v1334(_v1516(_v1246));
}

_v428 _v1516(_v1234 _v1246) {
    bkr_i64 _v339 = _v1313(_v1246);
    _v1279(_v1246, _v152);
    bkr_i64 _v355 = _v1346(_v1246);
    bkr_i64 _v515 = _v564();
    if ((_v1270(_v1246) == _v193)) {
        _v1277(_v1246);
        _v515 = _v521(_v1352(_v1246));
    }
    bkr_i64 _v387 = _v564();
    if ((_v1270(_v1246) == _v180)) {
        _v1277(_v1246);
        _v387 = _v542(_v1397(_v1246));
    }
    if ((!_v1279(_v1246, _v192))) {
        _v1340(_v1246);
    }
    _v428 _v1517 = _v1146(_v355, _v515, _v387);
    return _v1324(_v1246, _v1517, _v339);
}

bkr_i64 _v1518(_v1234 _v1246) {
    return _v1334(_v1519(_v1246));
}

_v428 _v1519(_v1234 _v1246) {
    bkr_i64 _v339 = _v1313(_v1246);
    _v1279(_v1246, _v138);
    bkr_i64 _v355 = _v1346(_v1246);
    _v1279(_v1246, _v187);
    bkr_i64 _v418 = vec_new();
    _v435 _v1162 = _v611(_v418);
    bkr_i64 _v419 = vec_new();
    _v435 _v1163 = _v611(_v419);
    while (((_v1270(_v1246) != _v188) && (_v1270(_v1246) != _v129))) {
        _v642(_v1162, _v1346(_v1246));
        bkr_i64 _v344 = _v564();
        if ((_v1270(_v1246) == _v185)) {
            _v1277(_v1246);
            bkr_i64 _v416 = vec_new();
            _v435 _v1158 = _v611(_v416);
            _v642(_v1158, _v521(_v1352(_v1246)));
            while ((_v1270(_v1246) == _v191)) {
                _v1277(_v1246);
                _v642(_v1158, _v521(_v1352(_v1246)));
            }
            _v1279(_v1246, _v186);
            _v344 = _v613(_v1158);
        }
        _v642(_v1163, _v344);
        if ((_v1270(_v1246) == _v191)) {
            _v1277(_v1246);
        }
    }
    _v1279(_v1246, _v188);
    return _v1324(_v1246, _v1161(_v355, _v1162, _v1163), _v339);
}

bkr_i64 _v1520(_v1234 _v1246) {
    return _v1334(_v1521(_v1246));
}

_v428 _v1521(_v1234 _v1246) {
    bkr_i64 _v339 = _v1313(_v1246);
    _v1279(_v1246, _v139);
    bkr_i64 _v355 = _v1346(_v1246);
    bkr_i64 _v416 = vec_new();
    _v434 _v1158 = _v604(_v416);
    if ((_v1270(_v1246) == _v185)) {
        _v1277(_v1246);
        bkr_i64 _v1035 = 0;
        while (((_v1270(_v1246) != _v186) && (_v1270(_v1246) != _v129))) {
            bkr_i64 _v1522 = _v1313(_v1246);
            _v346 _v1152 = _v1352(_v1246);
            bkr_i64 _v1044 = _v1289(_v1246, int_to_string(_v1035));
            _v341 _v1432 = _v1318(_v1151(_v1044, _v1152), _v1522, _v1314(_v1246));
            _v634(_v1158, _v1432);
            _v1035 = (_v1035 + 1);
            if ((_v1270(_v1246) == _v191)) {
                _v1277(_v1246);
            }
        }
        _v1279(_v1246, _v186);
        if ((_v1270(_v1246) == _v192)) {
            _v1277(_v1246);
        }
    } else {
        _v1279(_v1246, _v187);
        while (((_v1270(_v1246) != _v188) && (_v1270(_v1246) != _v129))) {
            bkr_i64 _v1522 = _v1313(_v1246);
            bkr_i64 _v1044 = _v1346(_v1246);
            _v1279(_v1246, _v193);
            _v346 _v1152 = _v1352(_v1246);
            _v341 _v1432 = _v1318(_v1151(_v1044, _v1152), _v1522, _v1314(_v1246));
            _v634(_v1158, _v1432);
            if ((_v1270(_v1246) == _v191)) {
                _v1277(_v1246);
            }
        }
        _v1279(_v1246, _v188);
    }
    _v428 _v1523 = _v1157(_v355, _v1158);
    return _v1324(_v1246, _v1523, _v339);
}

bkr_i64 _v1524(bkr_i64 _v1246) {
    return _v1525(_v1243(_v1246));
}

bkr_i64 _v1526(_v1234 _v1246) {
    return _v1334(_v1527(_v1246));
}

_v428 _v1527(_v1234 _v1246) {
    bkr_i64 _v339 = _v1313(_v1246);
    _v1279(_v1246, _v154);
    bkr_i64 _v355 = _v1346(_v1246);
    _v1279(_v1246, _v180);
    _v346 _v373 = _v1352(_v1246);
    if ((!_v1279(_v1246, _v192))) {
        _v1340(_v1246);
    }
    _v428 _v1528 = _v1175(_v355, _v373);
    return _v1324(_v1246, _v1528, _v339);
}

bkr_i64 _v1525(_v1234 _v1246) {
    bkr_i64 _v339 = _v1313(_v1246);
    _v1279(_v1246, _v137);
    bkr_i64 _v355 = _v1346(_v1246);
    _v1279(_v1246, _v187);
    bkr_i64 _v423 = vec_new();
    _v434 _v1183 = _v604(_v423);
    bkr_i64 _v1184 = (-1);
    while (((_v1270(_v1246) != _v188) && (_v1270(_v1246) != _v129))) {
        bkr_i64 _v1307 = _v1270(_v1246);
        if ((_v1307 == _v197)) {
            _v1277(_v1246);
            _v1307 = _v1270(_v1246);
        }
        if ((_v1307 == _v140)) {
            _v428 _v1514 = _v1513(_v1246);
            bkr_i64 _v1529 = _v868(_v1514);
            if (bkr_str_eq(_v1288(_v1246, _v1529), "main")) {
                _v1184 = _v1529;
            }
            _v636(_v1183, _v1514);
        } else {
            if ((_v1307 == _v152)) {
                _v636(_v1183, _v1516(_v1246));
            } else {
                if ((_v1307 == _v139)) {
                    _v636(_v1183, _v1521(_v1246));
                } else {
                    if ((_v1307 == _v138)) {
                        _v636(_v1183, _v1519(_v1246));
                    } else {
                        if ((_v1307 == _v154)) {
                            _v636(_v1183, _v1527(_v1246));
                        } else {
                            _v1280(_v1246, _v140);
                            _v1277(_v1246);
                            _v1341(_v1246);
                        }
                    }
                }
            }
        }
    }
    _v1279(_v1246, _v188);
    _v437 _v1185 = _v624(_v1249(_v1246));
    _v341 _v1530 = _v1182(_v355, _v1183, _v1184, _v1185);
    return _v1327(_v1317(_v1246, _v1530, _v339));
}

bkr_i64 _v1532(bkr_str _v1533, bkr_i64 _v425) {
    return _v1534(_v1535(_v1533, _v425));
}

_v1531 _v1535(bkr_str _v1533, bkr_i64 _v425) {
    bkr_i64 _v1239 = vec_new();
    bkr_i64 _v1536 = vec_new();
    bkr_i64 _v1537 = vec_new();
    bkr_i64 _v1538 = vec_new();
    bkr_i64 _v1539 = vec_new();
    bkr_i64 _v1540 = vec_new();
    bkr_i64 _v1541 = vec_new();
    bkr_i64 _v1542 = vec_new();
    bkr_i64 _v1543 = vec_new();
    bkr_i64 _v1544 = vec_new();
    bkr_i64 _v1545 = vec_new();
    vec_push(_v1239, ((bkr_i64)(_v1536)));
    vec_push(_v1239, 0);
    vec_push(_v1239, ((bkr_i64)(_v1533)));
    vec_push(_v1239, ((bkr_i64)(_v425)));
    vec_push(_v1239, ((bkr_i64)(_v1537)));
    vec_push(_v1239, ((bkr_i64)(_v1538)));
    vec_push(_v1239, ((bkr_i64)(_v1539)));
    vec_push(_v1239, ((bkr_i64)(_v1540)));
    vec_push(_v1239, ((bkr_i64)(_v1541)));
    vec_push(_v1239, ((bkr_i64)(_v1542)));
    vec_push(_v1239, ((bkr_i64)(_v1543)));
    vec_push(_v1239, ((bkr_i64)(_v1544)));
    bkr_i64 _v1546 = vec_new();
    bkr_i64 _v1547 = vec_new();
    vec_push(_v1239, ((bkr_i64)(_v1545)));
    vec_push(_v1239, 0);
    vec_push(_v1239, 0);
    vec_push(_v1239, ((bkr_i64)(_v1546)));
    vec_push(_v1239, 0);
    vec_push(_v1239, ((bkr_i64)(_v1547)));
    return _v1548(_v1239);
}

_v1531 _v1549(_v1531 _v1550, bkr_i64 _v1551) {
    bkr_i64 _v1239 = _v1534(_v1550);
    if ((vec_len(_v1239) < 14)) {
        vec_push(_v1239, _v1551);
    } else {
        vec_set(_v1239, 13, _v1551);
    }
    return _v1550;
}

bkr_i64 _v1552(_v1531 _v1550) {
    bkr_i64 _v1239 = _v1534(_v1550);
    if ((vec_len(_v1239) < 14)) {
        return 0;
    }
    return vec_get(_v1239, 13);
}

_v1531 _v1548(bkr_i64 _v1239) {
    return (_v1531){._v342 = ((bkr_i64)(_v1239))};
}

bkr_i64 _v1534(_v1531 _v1550) {
    return ((bkr_i64)(_v1550._v342));
}

bkr_i64 _v1553(bkr_i64 _v1239) {
    return _v1554(_v1548(_v1239));
}

bkr_i64 _v1554(_v1531 _v1550) {
    return ((bkr_i64)(vec_get(_v1534(_v1550), 0)));
}

bkr_i64 _v1555(bkr_i64 _v1239) {
    return _v1556(_v1548(_v1239));
}

bkr_i64 _v1556(_v1531 _v1550) {
    return vec_get(_v1534(_v1550), 1);
}

bkr_i64 _v1557(bkr_i64 _v1239, bkr_i64 _v1558) {
    _v1559(_v1548(_v1239), _v1558);
    return _v1239;
}

_v1531 _v1559(_v1531 _v1550, bkr_i64 _v1558) {
    vec_set(_v1534(_v1550), 1, _v1558);
    return _v1550;
}

bkr_i64 _v1560(bkr_i64 _v1239) {
    return _v1561(_v1548(_v1239));
}

bkr_i64 _v1561(_v1531 _v1550) {
    return ((bkr_i64)(vec_get(_v1534(_v1550), 3)));
}

bkr_i64 _v1562(_v1531 _v1550, bkr_str _v1290) {
    bkr_i64 _v425 = _v1561(_v1550);
    bkr_i64 _v1168 = 0;
    bkr_i64 _v399 = vec_len(_v425);
    while ((_v1168 < _v399)) {
        if (bkr_str_eq(vec_get(_v425, _v1168), _v1290)) {
            return _v1168;
        }
        _v1168 = (_v1168 + 1);
    }
    vec_push(_v425, ((bkr_i64)(intptr_t)_v1290));
    return _v399;
}

bkr_i64 _v1563(bkr_i64 _v1239) {
    return _v1564(_v1548(_v1239));
}

bkr_i64 _v1564(_v1531 _v1550) {
    return ((bkr_i64)(vec_get(_v1534(_v1550), 4)));
}

bkr_i64 _v1565(bkr_i64 _v1239) {
    return _v1566(_v1548(_v1239));
}

bkr_i64 _v1566(_v1531 _v1550) {
    return ((bkr_i64)(vec_get(_v1534(_v1550), 5)));
}

bkr_i64 _v1567(bkr_i64 _v1239) {
    return _v1568(_v1548(_v1239));
}

bkr_i64 _v1568(_v1531 _v1550) {
    return ((bkr_i64)(vec_get(_v1534(_v1550), 6)));
}

bkr_i64 _v1569(bkr_i64 _v1239) {
    return _v1570(_v1548(_v1239));
}

bkr_i64 _v1570(_v1531 _v1550) {
    return ((bkr_i64)(vec_get(_v1534(_v1550), 7)));
}

bkr_i64 _v1571(bkr_i64 _v1239) {
    return _v1572(_v1548(_v1239));
}

bkr_i64 _v1572(_v1531 _v1550) {
    return ((bkr_i64)(vec_get(_v1534(_v1550), 8)));
}

bkr_i64 _v1573(bkr_i64 _v1239) {
    return _v1574(_v1548(_v1239));
}

bkr_i64 _v1574(_v1531 _v1550) {
    return ((bkr_i64)(vec_get(_v1534(_v1550), 9)));
}

bkr_i64 _v1575(bkr_i64 _v1239) {
    return _v1576(_v1548(_v1239));
}

bkr_i64 _v1576(_v1531 _v1550) {
    return ((bkr_i64)(vec_get(_v1534(_v1550), 10)));
}

bkr_i64 _v1577(bkr_i64 _v1239) {
    return _v1578(_v1548(_v1239));
}

bkr_i64 _v1578(_v1531 _v1550) {
    return ((bkr_i64)(vec_get(_v1534(_v1550), 11)));
}

bkr_i64 _v1579(bkr_i64 _v1239) {
    return _v1580(_v1548(_v1239));
}

bkr_i64 _v1580(_v1531 _v1550) {
    return ((bkr_i64)(vec_get(_v1534(_v1550), 12)));
}

bkr_i64 _v1581(bkr_i64 _v1239, bkr_str _v1582) {
    _v1583(_v1548(_v1239), _v1582);
    return _v1239;
}

_v1531 _v1583(_v1531 _v1550, bkr_str _v1582) {
    bkr_i64 _v1536 = _v1554(_v1550);
    bkr_i64 _v1558 = _v1556(_v1550);
    bkr_str _v1584 = "";
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v1558)) {
        _v1584 = bkr_str_concat(_v1584, "    ");
        _v1168 = (_v1168 + 1);
    }
    vec_push(_v1536, ((bkr_i64)(intptr_t)bkr_str_concat(_v1584, _v1582)));
    return _v1550;
}

bkr_i64 _v1585(bkr_i64 _v1239) {
    _v1586(_v1548(_v1239));
    return _v1239;
}

_v1531 _v1586(_v1531 _v1550) {
    _v1559(_v1550, (_v1556(_v1550) + 1));
    return _v1550;
}

bkr_i64 _v1587(bkr_i64 _v1239) {
    _v1588(_v1548(_v1239));
    return _v1239;
}

_v1531 _v1588(_v1531 _v1550) {
    _v1559(_v1550, (_v1556(_v1550) - 1));
    return _v1550;
}

bkr_i64 _v1589(bkr_i64 _v1239) {
    _v1590(_v1548(_v1239));
    return _v1239;
}

_v1531 _v1590(_v1531 _v1550) {
    bkr_i64 _v1239 = _v1534(_v1550);
    bkr_i64 _v1537 = vec_new();
    bkr_i64 _v1538 = vec_new();
    bkr_i64 _v1543 = vec_new();
    bkr_i64 _v1544 = vec_new();
    bkr_i64 _v1545 = vec_new();
    bkr_i64 _v1546 = vec_new();
    bkr_i64 _v1547 = vec_new();
    vec_set(_v1239, 4, ((bkr_i64)(_v1537)));
    vec_set(_v1239, 5, ((bkr_i64)(_v1538)));
    vec_set(_v1239, 10, ((bkr_i64)(_v1543)));
    vec_set(_v1239, 11, ((bkr_i64)(_v1544)));
    vec_set(_v1239, 12, ((bkr_i64)(_v1545)));
    if ((vec_len(_v1239) > 15)) {
        vec_set(_v1239, 15, ((bkr_i64)(_v1546)));
    }
    if ((vec_len(_v1239) > 17)) {
        vec_set(_v1239, 17, ((bkr_i64)(_v1547)));
    }
    return _v1550;
}

bkr_i64 _v1591(bkr_i64 _v1239, bkr_i64 _v355, bkr_i64 _v319) {
    _v1592(_v1548(_v1239), _v355, _v319);
    return _v1239;
}

_v1531 _v1592(_v1531 _v1550, bkr_i64 _v355, bkr_i64 _v319) {
    bkr_i64 _v1537 = _v1564(_v1550);
    bkr_i64 _v1538 = _v1566(_v1550);
    bkr_i64 _v1547 = _v1593(_v1550);
    vec_push(_v1537, _v355);
    vec_push(_v1538, _v319);
    vec_push(_v1547, (-1));
    return _v1550;
}

_v1531 _v1594(_v1531 _v1550, bkr_i64 _v355, bkr_i64 _v319, bkr_i64 _v1503) {
    _v1592(_v1550, _v355, _v319);
    bkr_i64 _v1547 = _v1593(_v1550);
    vec_set(_v1547, (vec_len(_v1547) - 1), _v1503);
    return _v1550;
}

bkr_i64 _v1593(_v1531 _v1550) {
    bkr_i64 _v1239 = _v1534(_v1550);
    if ((vec_len(_v1239) <= 17)) {
        bkr_i64 _v1595 = vec_new();
        return _v1595;
    }
    return ((bkr_i64)(vec_get(_v1239, 17)));
}

bkr_i64 _v1596(_v1531 _v1550, bkr_i64 _v355) {
    bkr_i64 _v1537 = _v1564(_v1550);
    bkr_i64 _v1547 = _v1593(_v1550);
    bkr_i64 _v1168 = (vec_len(_v1537) - 1);
    while ((_v1168 >= 0)) {
        if ((vec_get(_v1537, _v1168) == _v355)) {
            if ((_v1168 < vec_len(_v1547))) {
                return vec_get(_v1547, _v1168);
            }
            return (-1);
        }
        _v1168 = (_v1168 - 1);
    }
    return (-1);
}

bkr_i64 _v1597(_v1531 _v1550) {
    bkr_i64 _v1239 = _v1534(_v1550);
    if ((vec_len(_v1239) <= 15)) {
        bkr_i64 _v1546 = vec_new();
        return _v1546;
    }
    return ((bkr_i64)(vec_get(_v1239, 15)));
}

_v1531 _v1598(_v1531 _v1550, bkr_i64 _v1599) {
    bkr_i64 _v1546 = _v1597(_v1550);
    vec_push(_v1546, _v1599);
    return _v1550;
}

bkr_str _v1600(_v1531 _v1550) {
    bkr_i64 _v1239 = _v1534(_v1550);
    if ((vec_len(_v1239) <= 14)) {
        return "bkr_i64";
    }
    bkr_i64 _v1383 = vec_get(_v1239, 14);
    if ((_v1383 == 0)) {
        return "bkr_i64";
    }
    return ((bkr_str)(_v1383));
}

_v1531 _v1601(_v1531 _v1550, bkr_str _v1142) {
    bkr_i64 _v1239 = _v1534(_v1550);
    if ((vec_len(_v1239) > 14)) {
        vec_set(_v1239, 14, ((bkr_i64)(_v1142)));
    }
    return _v1550;
}

bkr_i64 _v1602(_v1531 _v1550) {
    bkr_i64 _v1239 = _v1534(_v1550);
    if ((vec_len(_v1239) <= 16)) {
        return 0;
    }
    bkr_i64 _v1603 = vec_get(_v1239, 16);
    vec_set(_v1239, 16, (_v1603 + 1));
    return _v1603;
}

bkr_str _v1604(_v1531 _v1550, bkr_str _v1584) {
    bkr_i64 _v1605 = _v1602(_v1550);
    return bkr_str_concat(bkr_str_concat(_v1584, "_"), int_to_string(_v1605));
}

bkr_i64 _v1606(bkr_i64 _v1239, bkr_i64 _v355, bkr_i64 _v319) {
    _v1607(_v1548(_v1239), _v355, _v319);
    return _v1239;
}

_v1531 _v1607(_v1531 _v1550, bkr_i64 _v355, bkr_i64 _v319) {
    bkr_i64 _v1539 = _v1568(_v1550);
    bkr_i64 _v1540 = _v1570(_v1550);
    vec_push(_v1539, _v355);
    vec_push(_v1540, _v319);
    return _v1550;
}

bkr_i64 _v1608(bkr_i64 _v1239, bkr_i64 _v355, bkr_i64 _v319) {
    _v1609(_v1548(_v1239), _v355, _v319);
    return _v1239;
}

_v1531 _v1609(_v1531 _v1550, bkr_i64 _v355, bkr_i64 _v319) {
    bkr_i64 _v1541 = _v1572(_v1550);
    bkr_i64 _v1542 = _v1574(_v1550);
    vec_push(_v1541, _v355);
    vec_push(_v1542, _v319);
    return _v1550;
}

bkr_i64 _v1610(bkr_i64 _v1239, bkr_i64 _v355, bkr_i64 _v953, bkr_i64 _v954) {
    _v1611(_v1548(_v1239), _v355, _v953, _v954);
    return _v1239;
}

_v1531 _v1611(_v1531 _v1550, bkr_i64 _v355, bkr_i64 _v953, bkr_i64 _v954) {
    bkr_i64 _v1543 = _v1576(_v1550);
    bkr_i64 _v1544 = _v1578(_v1550);
    bkr_i64 _v1545 = _v1580(_v1550);
    vec_push(_v1543, _v355);
    vec_push(_v1544, _v954);
    vec_push(_v1545, _v953);
    return _v1550;
}

bkr_i64 _v1612(bkr_i64 _v1239, bkr_i64 _v355) {
    return _v1613(_v1548(_v1239), _v355);
}

bkr_i64 _v1613(_v1531 _v1550, bkr_i64 _v355) {
    bkr_i64 _v1543 = _v1576(_v1550);
    bkr_i64 _v1544 = _v1578(_v1550);
    bkr_i64 _v1193 = (-1);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < vec_len(_v1543))) {
        if ((vec_get(_v1543, _v1168) == _v355)) {
            _v1193 = vec_get(_v1544, _v1168);
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1193;
}

bkr_i64 _v1614(bkr_i64 _v1239, bkr_i64 _v355) {
    return _v1615(_v1548(_v1239), _v355);
}

bkr_i64 _v1615(_v1531 _v1550, bkr_i64 _v355) {
    bkr_i64 _v1543 = _v1576(_v1550);
    bkr_i64 _v1545 = _v1580(_v1550);
    bkr_i64 _v1193 = _v316;
    bkr_i64 _v1168 = 0;
    while ((_v1168 < vec_len(_v1543))) {
        if ((vec_get(_v1543, _v1168) == _v355)) {
            _v1193 = vec_get(_v1545, _v1168);
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1193;
}

bkr_i64 _v1616(bkr_i64 _v425, bkr_i64 _v1617, bkr_i64 _v355) {
    bkr_i64 _v1193 = _v316;
    bkr_i64 _v1168 = 0;
    while ((_v1168 < vec_len(_v425))) {
        if ((vec_get(_v425, _v1168) == _v355)) {
            _v1193 = vec_get(_v1617, _v1168);
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1193;
}

bkr_i64 _v1618(bkr_i64 _v1239, bkr_i64 _v355) {
    return _v1619(_v1548(_v1239), _v355);
}

bkr_i64 _v1619(_v1531 _v1550, bkr_i64 _v355) {
    bkr_i64 _v1620 = _v1616(_v1564(_v1550), _v1566(_v1550), _v355);
    if ((_v1620 != _v316)) {
        return _v1620;
    }
    return _v1616(_v1572(_v1550), _v1574(_v1550), _v355);
}

bkr_i64 _v1621(bkr_i64 _v1239, bkr_i64 _v355) {
    return _v1622(_v1548(_v1239), _v355);
}

bkr_i64 _v1622(_v1531 _v1550, bkr_i64 _v355) {
    return _v1616(_v1568(_v1550), _v1570(_v1550), _v355);
}

bkr_bool _v1623(_v1531 _v1239, bkr_i64 _v355) {
    bkr_i64 _v425 = _v1561(_v1239);
    return _v1624(_v1239, _v1625(_v425, _v355));
}

bkr_bool _v1624(_v1531 _v1239, bkr_str _v1626) {
    bkr_i64 _v1551 = _v1552(_v1239);
    if ((_v1551 == 0)) {
        return BKR_FALSE;
    }
    _v341 _v1530 = _v506(_v1551);
    bkr_i64 _v425 = _v1561(_v1239);
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if ((_v568(_v562) == _v259)) {
            if (bkr_str_eq(_v1625(_v425, _v1164(_v562)), _v1626)) {
                return BKR_TRUE;
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_FALSE;
}

bkr_i64 _v1627(_v1531 _v1239, bkr_str _v1626, bkr_str _v1628) {
    bkr_i64 _v1551 = _v1552(_v1239);
    if ((_v1551 == 0)) {
        return (-1);
    }
    _v341 _v1530 = _v506(_v1551);
    bkr_i64 _v425 = _v1561(_v1239);
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if ((_v568(_v562) == _v259)) {
            if (bkr_str_eq(_v1625(_v425, _v1164(_v562)), _v1626)) {
                _v435 _v1162 = _v1165(_v562);
                bkr_i64 _v1629 = 0;
                while ((_v1629 < _v915(_v1162))) {
                    if (bkr_str_eq(_v1625(_v425, _v917(_v1162, _v1629)), _v1628)) {
                        return _v1629;
                    }
                    _v1629 = (_v1629 + 1);
                }
                return (-1);
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return (-1);
}

bkr_i64 _v1630(_v1531 _v1239, bkr_str _v1626, bkr_str _v1628, bkr_i64 _v1631) {
    bkr_i64 _v1551 = _v1552(_v1239);
    if ((_v1551 == 0)) {
        return _v316;
    }
    _v341 _v1530 = _v506(_v1551);
    bkr_i64 _v425 = _v1561(_v1239);
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if ((_v568(_v562) == _v259)) {
            if (bkr_str_eq(_v1625(_v425, _v1164(_v562)), _v1626)) {
                _v435 _v1162 = _v1165(_v562);
                _v435 _v1163 = _v1166(_v562);
                bkr_i64 _v1629 = 0;
                while ((_v1629 < _v915(_v1162))) {
                    if (bkr_str_eq(_v1625(_v425, _v917(_v1162, _v1629)), _v1628)) {
                        if ((_v1629 < _v915(_v1163))) {
                            bkr_i64 _v344 = _v917(_v1163, _v1629);
                            if (_v525(_v344)) {
                                _v435 _v1158 = _v610(_v344);
                                if (((_v1631 >= 0) && (_v1631 < _v915(_v1158)))) {
                                    bkr_i64 _v1632 = _v917(_v1158, _v1631);
                                    if (_v525(_v1632)) {
                                        return _v529(_v516(_v1632));
                                    }
                                }
                            }
                        }
                        return _v316;
                    }
                    _v1629 = (_v1629 + 1);
                }
                return _v316;
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return _v316;
}

bkr_bool _v1633(_v1531 _v1239, bkr_str _v1626) {
    bkr_i64 _v1551 = _v1552(_v1239);
    if ((_v1551 == 0)) {
        return BKR_FALSE;
    }
    _v341 _v1530 = _v506(_v1551);
    bkr_i64 _v425 = _v1561(_v1239);
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if ((_v568(_v562) == _v259)) {
            if (bkr_str_eq(_v1625(_v425, _v1164(_v562)), _v1626)) {
                _v435 _v1163 = _v1166(_v562);
                bkr_i64 _v1629 = 0;
                while ((_v1629 < _v915(_v1163))) {
                    bkr_i64 _v344 = _v917(_v1163, _v1629);
                    if (_v525(_v344)) {
                        _v435 _v1158 = _v610(_v344);
                        bkr_i64 _v573 = 0;
                        while ((_v573 < _v915(_v1158))) {
                            bkr_i64 _v1632 = _v917(_v1158, _v573);
                            if (_v525(_v1632)) {
                                if ((_v529(_v516(_v1632)) == _v306)) {
                                    return BKR_TRUE;
                                }
                            }
                            _v573 = (_v573 + 1);
                        }
                    }
                    _v1629 = (_v1629 + 1);
                }
                return BKR_FALSE;
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_FALSE;
}

bkr_str _v1634(bkr_i64 _v319) {
    if ((_v319 == _v302)) {
        return "bkr_i32";
    }
    if ((_v319 == _v303)) {
        return "bkr_i64";
    }
    if ((_v319 == _v304)) {
        return "bkr_f64";
    }
    if ((_v319 == _v305)) {
        return "bkr_bool";
    }
    if ((_v319 == _v306)) {
        return "bkr_str";
    }
    if (((_v319 == _v307) || (_v319 == _v314))) {
        return "void";
    }
    if ((((((_v319 == _v310) || (_v319 == _v311)) || (_v319 == _v312)) || (_v319 == _v313)) || (_v319 == _v315))) {
        return "bkr_i64";
    }
    return "bkr_i64";
}

bkr_str _v1635(bkr_i64 _v1239, bkr_i64 _v515) {
    if (_v523(_v515)) {
        return "bkr_i64";
    }
    return _v1636(_v1548(_v1239), _v516(_v515));
}

bkr_str _v1636(_v1531 _v1239, _v346 _v520) {
    bkr_i64 _v319 = _v529(_v520);
    if ((_v319 == _v308)) {
        bkr_i64 _v953 = _v532(_v520);
        return bkr_str_concat(_v1634(_v953), "*");
    }
    if ((_v319 == _v309)) {
        bkr_i64 _v1503 = _v531(_v520);
        if ((_v1503 >= 0)) {
            if (_v1623(_v1239, _v1503)) {
                return "bkr_i64";
            }
            return _v1637(_v1239, _v1503);
        }
    }
    return _v1634(_v319);
}

bkr_str _v1638(bkr_i64 _v349) {
    if ((_v349 == _v161)) {
        return " + ";
    }
    if ((_v349 == _v162)) {
        return " - ";
    }
    if ((_v349 == _v163)) {
        return " * ";
    }
    if ((_v349 == _v164)) {
        return " / ";
    }
    if ((_v349 == _v165)) {
        return " % ";
    }
    if ((_v349 == _v166)) {
        return " == ";
    }
    if ((_v349 == _v167)) {
        return " != ";
    }
    if ((_v349 == _v168)) {
        return " < ";
    }
    if ((_v349 == _v169)) {
        return " > ";
    }
    if ((_v349 == _v170)) {
        return " <= ";
    }
    if ((_v349 == _v171)) {
        return " >= ";
    }
    if ((_v349 == _v172)) {
        return " && ";
    }
    if ((_v349 == _v173)) {
        return " || ";
    }
    if ((_v349 == _v175)) {
        return " & ";
    }
    if ((_v349 == _v176)) {
        return " | ";
    }
    if ((_v349 == _v177)) {
        return " ^ ";
    }
    if ((_v349 == _v178)) {
        return " << ";
    }
    if ((_v349 == _v179)) {
        return " >> ";
    }
    return " ? ";
}

bkr_str _v1625(bkr_i64 _v425, bkr_i64 _v1035) {
    if (((_v1035 >= 0) && (_v1035 < vec_len(_v425)))) {
        return vec_get(_v425, _v1035);
    }
    return "";
}

bkr_str _v1639(bkr_str _v1640) {
    if (bkr_str_eq(_v1640, "len")) {
        return "bkr_len";
    }
    if (bkr_str_eq(_v1640, "strlen")) {
        return "bkr_len";
    }
    if (bkr_str_eq(_v1640, "print")) {
        return "bkr_print";
    }
    if (bkr_str_eq(_v1640, "println")) {
        return "bkr_println";
    }
    if (bkr_str_eq(_v1640, "log")) {
        return "bkr_log";
    }
    if (bkr_str_eq(_v1640, "read_file")) {
        return "read_file";
    }
    if (bkr_str_eq(_v1640, "write_file")) {
        return "write_file";
    }
    if (bkr_str_eq(_v1640, "file_exists")) {
        return "file_exists";
    }
    if (bkr_str_eq(_v1640, "file_set_executable")) {
        return "file_set_executable";
    }
    if (bkr_str_eq(_v1640, "vec_new")) {
        return "vec_new";
    }
    if (bkr_str_eq(_v1640, "vec_push")) {
        return "vec_push";
    }
    if (bkr_str_eq(_v1640, "vec_get")) {
        return "vec_get";
    }
    if (bkr_str_eq(_v1640, "vec_set")) {
        return "vec_set";
    }
    if (bkr_str_eq(_v1640, "vec_len")) {
        return "vec_len";
    }
    if (bkr_str_eq(_v1640, "vec_pop")) {
        return "vec_pop";
    }
    if (bkr_str_eq(_v1640, "vec_clear")) {
        return "vec_clear";
    }
    if (bkr_str_eq(_v1640, "vec_contains")) {
        return "vec_contains";
    }
    if (bkr_str_eq(_v1640, "vec_is_empty")) {
        return "vec_is_empty";
    }
    if (bkr_str_eq(_v1640, "vec_clone")) {
        return "vec_clone";
    }
    if (bkr_str_eq(_v1640, "vec_reverse")) {
        return "vec_reverse";
    }
    if (bkr_str_eq(_v1640, "hashmap_is_empty")) {
        return "hashmap_is_empty";
    }
    if (bkr_str_eq(_v1640, "hashmap_values")) {
        return "hashmap_values";
    }
    if (bkr_str_eq(_v1640, "vec_map")) {
        return "vec_map";
    }
    if (bkr_str_eq(_v1640, "vec_filter")) {
        return "vec_filter";
    }
    if (bkr_str_eq(_v1640, "vec_fold")) {
        return "vec_fold";
    }
    if (bkr_str_eq(_v1640, "vec_find")) {
        return "vec_find";
    }
    if (bkr_str_eq(_v1640, "hashmap_new")) {
        return "hashmap_new";
    }
    if (bkr_str_eq(_v1640, "hashmap_insert")) {
        return "hashmap_insert";
    }
    if (bkr_str_eq(_v1640, "hashmap_get")) {
        return "hashmap_get";
    }
    if (bkr_str_eq(_v1640, "hashmap_contains")) {
        return "hashmap_contains";
    }
    if (bkr_str_eq(_v1640, "hashmap_remove")) {
        return "hashmap_remove";
    }
    if (bkr_str_eq(_v1640, "hashmap_keys")) {
        return "hashmap_keys";
    }
    if (bkr_str_eq(_v1640, "hashmap_len")) {
        return "hashmap_len";
    }
    if (bkr_str_eq(_v1640, "hashmap_clear")) {
        return "hashmap_clear";
    }
    if (bkr_str_eq(_v1640, "char_at")) {
        return "char_at";
    }
    if (bkr_str_eq(_v1640, "char_code")) {
        return "char_code";
    }
    if (bkr_str_eq(_v1640, "char_code_at")) {
        return "char_code_at";
    }
    if (bkr_str_eq(_v1640, "substring")) {
        return "substring";
    }
    if (bkr_str_eq(_v1640, "contains")) {
        return "contains";
    }
    if (bkr_str_eq(_v1640, "starts_with")) {
        return "starts_with";
    }
    if (bkr_str_eq(_v1640, "ends_with")) {
        return "ends_with";
    }
    if (bkr_str_eq(_v1640, "trim")) {
        return "trim";
    }
    if (bkr_str_eq(_v1640, "parse_int")) {
        return "parse_int";
    }
    if (bkr_str_eq(_v1640, "int_to_string")) {
        return "int_to_string";
    }
    if (bkr_str_eq(_v1640, "from_char_code")) {
        return "from_char_code";
    }
    if (bkr_str_eq(_v1640, "join_lines")) {
        return "join_lines";
    }
    if (bkr_str_eq(_v1640, "args_count")) {
        return "bkr_args_count";
    }
    if (bkr_str_eq(_v1640, "arg_at")) {
        return "bkr_arg_at";
    }
    if (bkr_str_eq(_v1640, "str_index_of")) {
        return "str_index_of";
    }
    if (bkr_str_eq(_v1640, "str_replace")) {
        return "str_replace";
    }
    if (bkr_str_eq(_v1640, "str_split")) {
        return "str_split";
    }
    if (bkr_str_eq(_v1640, "str_to_upper")) {
        return "str_to_upper";
    }
    if (bkr_str_eq(_v1640, "str_to_lower")) {
        return "str_to_lower";
    }
    if (bkr_str_eq(_v1640, "str_repeat")) {
        return "str_repeat";
    }
    if (bkr_str_eq(_v1640, "path_join")) {
        return "path_join";
    }
    if (bkr_str_eq(_v1640, "path_dir")) {
        return "path_dir";
    }
    if (bkr_str_eq(_v1640, "path_base")) {
        return "path_base";
    }
    if (bkr_str_eq(_v1640, "path_ext")) {
        return "path_ext";
    }
    if (bkr_str_eq(_v1640, "path_is_abs")) {
        return "path_is_abs";
    }
    if (bkr_str_eq(_v1640, "env_var")) {
        return "env_var";
    }
    if (bkr_str_eq(_v1640, "env_get")) {
        return "env_get";
    }
    if (bkr_str_eq(_v1640, "env_set")) {
        return "env_set";
    }
    if (bkr_str_eq(_v1640, "env_has")) {
        return "env_has";
    }
    if (bkr_str_eq(_v1640, "time_now_ms")) {
        return "time_now_ms";
    }
    if (bkr_str_eq(_v1640, "time_now_unix")) {
        return "time_now_unix";
    }
    if (bkr_str_eq(_v1640, "runtime_version_major")) {
        return "runtime_version_major";
    }
    if (bkr_str_eq(_v1640, "runtime_version_minor")) {
        return "runtime_version_minor";
    }
    if (bkr_str_eq(_v1640, "runtime_version_patch")) {
        return "runtime_version_patch";
    }
    if (bkr_str_eq(_v1640, "runtime_version_str")) {
        return "runtime_version_str";
    }
    if (bkr_str_eq(_v1640, "bytes_new")) {
        return "bytes_new";
    }
    if (bkr_str_eq(_v1640, "bytes_len")) {
        return "bytes_len";
    }
    if (bkr_str_eq(_v1640, "bytes_capacity")) {
        return "bytes_capacity";
    }
    if (bkr_str_eq(_v1640, "bytes_get")) {
        return "bytes_get";
    }
    if (bkr_str_eq(_v1640, "bytes_set")) {
        return "bytes_set";
    }
    if (bkr_str_eq(_v1640, "bytes_push")) {
        return "bytes_push";
    }
    if (bkr_str_eq(_v1640, "bytes_from_str")) {
        return "bytes_from_str";
    }
    if (bkr_str_eq(_v1640, "bytes_to_str")) {
        return "bytes_to_str";
    }
    if (bkr_str_eq(_v1640, "slice_new")) {
        return "slice_new";
    }
    if (bkr_str_eq(_v1640, "slice_len")) {
        return "slice_len";
    }
    if (bkr_str_eq(_v1640, "slice_get")) {
        return "slice_get";
    }
    if (bkr_str_eq(_v1640, "slice_sub")) {
        return "slice_sub";
    }
    if (bkr_str_eq(_v1640, "slice_to_vec")) {
        return "slice_to_vec";
    }
    if (bkr_str_eq(_v1640, "slice_contains")) {
        return "slice_contains";
    }
    if (bkr_str_eq(_v1640, "vec_as_slice")) {
        return "vec_as_slice";
    }
    if (bkr_str_eq(_v1640, "vec_slice")) {
        return "vec_slice";
    }
    if (bkr_str_eq(_v1640, "bytes_as_slice")) {
        return "bytes_as_slice";
    }
    if (bkr_str_eq(_v1640, "bytes_slice")) {
        return "bytes_slice";
    }
    if (bkr_str_eq(_v1640, "path_exists")) {
        return "path_exists";
    }
    if (bkr_str_eq(_v1640, "path_is_file")) {
        return "path_is_file";
    }
    if (bkr_str_eq(_v1640, "path_is_dir")) {
        return "path_is_dir";
    }
    if (bkr_str_eq(_v1640, "file_read")) {
        return "file_read";
    }
    if (bkr_str_eq(_v1640, "file_write")) {
        return "file_write";
    }
    if (bkr_str_eq(_v1640, "file_size")) {
        return "file_size";
    }
    if (bkr_str_eq(_v1640, "file_remove")) {
        return "file_remove";
    }
    if (bkr_str_eq(_v1640, "file_read_bytes")) {
        return "file_read_bytes";
    }
    if (bkr_str_eq(_v1640, "file_write_bytes")) {
        return "file_write_bytes";
    }
    if (bkr_str_eq(_v1640, "dir_create")) {
        return "dir_create";
    }
    if (bkr_str_eq(_v1640, "dir_remove")) {
        return "dir_remove";
    }
    if (bkr_str_eq(_v1640, "process_run")) {
        return "process_run";
    }
    if (bkr_str_eq(_v1640, "process_run_status")) {
        return "process_run_status";
    }
    if (bkr_str_eq(_v1640, "process_exit")) {
        return "process_exit";
    }
    if (bkr_str_eq(_v1640, "process_pid")) {
        return "process_pid";
    }
    if (bkr_str_eq(_v1640, "process_is_sandboxed")) {
        return "process_is_sandboxed";
    }
    return "";
}

bkr_str _v1641(bkr_i64 _v425, bkr_i64 _v1035) {
    bkr_str _v1640 = _v1625(_v425, _v1035);
    bkr_str _v1642 = _v1639(_v1640);
    if ((!bkr_str_eq(_v1642, ""))) {
        return _v1642;
    }
    if (starts_with(_v1640, "bkr_")) {
        return _v1640;
    }
    return bkr_str_concat("_v", int_to_string(_v1035));
}

bkr_str _v1644(bkr_i64 _v1239, bkr_i64 _v1035) {
    return _v1637(_v1548(_v1239), _v1035);
}

bkr_str _v1637(_v1531 _v1239, bkr_i64 _v1035) {
    return _v1641(_v1561(_v1239), _v1035);
}

bkr_i64 _v1645(bkr_i64 _v515) {
    return _v1646(_v516(_v515));
}

bkr_i64 _v1646(_v346 _v520) {
    return _v529(_v520);
}

bkr_i64 _v1647(bkr_i64 _v515) {
    return _v1648(_v516(_v515));
}

bkr_i64 _v1648(_v346 _v520) {
    return _v532(_v520);
}

bkr_i64 _v1649(bkr_i64 _v515) {
    return _v1650(_v516(_v515));
}

bkr_i64 _v1650(_v346 _v520) {
    return _v533(_v520);
}

bkr_i64 _v1651(bkr_str _v1640) {
    if (bkr_str_eq(_v1640, "len")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "strlen")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "vec_new")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "vec_push")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "vec_get")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "vec_set")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "vec_len")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "vec_pop")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "vec_clear")) {
        return _v307;
    }
    if (bkr_str_eq(_v1640, "hashmap_new")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "hashmap_insert")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "hashmap_get")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "hashmap_contains")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "hashmap_remove")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "hashmap_keys")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "hashmap_len")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "hashmap_clear")) {
        return _v302;
    }
    if (bkr_str_eq(_v1640, "char_code")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "char_code_at")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "parse_int")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "char_at")) {
        return _v306;
    }
    if (bkr_str_eq(_v1640, "substring")) {
        return _v306;
    }
    if (bkr_str_eq(_v1640, "contains")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "starts_with")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "ends_with")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "trim")) {
        return _v306;
    }
    if (bkr_str_eq(_v1640, "int_to_string")) {
        return _v306;
    }
    if (bkr_str_eq(_v1640, "from_char_code")) {
        return _v306;
    }
    if (bkr_str_eq(_v1640, "join_lines")) {
        return _v306;
    }
    if (bkr_str_eq(_v1640, "read_file")) {
        return _v306;
    }
    if (bkr_str_eq(_v1640, "write_file")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "file_exists")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "file_set_executable")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "result_ok")) {
        return _v313;
    }
    if (bkr_str_eq(_v1640, "result_err")) {
        return _v313;
    }
    if (bkr_str_eq(_v1640, "result_is_ok")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "result_is_err")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "result_unwrap")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "result_unwrap_err")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "result_tag")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "result_value")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "hashmap_get_opt")) {
        return _v312;
    }
    if (bkr_str_eq(_v1640, "vec_get_opt")) {
        return _v312;
    }
    if (bkr_str_eq(_v1640, "vec_pop_opt")) {
        return _v312;
    }
    if (bkr_str_eq(_v1640, "vec_contains")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "vec_is_empty")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "vec_clone")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "vec_reverse")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "hashmap_is_empty")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "hashmap_values")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "vec_map")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "vec_filter")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "vec_fold")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "vec_find")) {
        return _v312;
    }
    if (bkr_str_eq(_v1640, "read_file_result")) {
        return _v313;
    }
    if (bkr_str_eq(_v1640, "write_file_result")) {
        return _v313;
    }
    if (bkr_str_eq(_v1640, "parse_int_result")) {
        return _v313;
    }
    if (bkr_str_eq(_v1640, "bkr_tuple2")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "bkr_tuple3")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "bkr_tuple_get")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "args_count")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "arg_at")) {
        return _v306;
    }
    if (bkr_str_eq(_v1640, "str_index_of")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "str_replace")) {
        return _v306;
    }
    if (bkr_str_eq(_v1640, "str_split")) {
        return _v310;
    }
    if (bkr_str_eq(_v1640, "str_to_upper")) {
        return _v306;
    }
    if (bkr_str_eq(_v1640, "str_to_lower")) {
        return _v306;
    }
    if (bkr_str_eq(_v1640, "str_repeat")) {
        return _v306;
    }
    if (bkr_str_eq(_v1640, "path_join")) {
        return _v306;
    }
    if (bkr_str_eq(_v1640, "path_dir")) {
        return _v306;
    }
    if (bkr_str_eq(_v1640, "path_base")) {
        return _v306;
    }
    if (bkr_str_eq(_v1640, "path_ext")) {
        return _v306;
    }
    if (bkr_str_eq(_v1640, "path_is_abs")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "env_var")) {
        return _v313;
    }
    if (bkr_str_eq(_v1640, "env_get")) {
        return _v312;
    }
    if (bkr_str_eq(_v1640, "env_set")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "env_has")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "time_now_ms")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "time_now_unix")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "runtime_version_major")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "runtime_version_minor")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "runtime_version_patch")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "runtime_version_str")) {
        return _v306;
    }
    if (bkr_str_eq(_v1640, "bytes_new")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "bytes_len")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "bytes_capacity")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "bytes_get")) {
        return _v302;
    }
    if (bkr_str_eq(_v1640, "bytes_set")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "bytes_push")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "bytes_from_str")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "bytes_to_str")) {
        return _v306;
    }
    if (bkr_str_eq(_v1640, "slice_new")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "slice_len")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "slice_get")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "slice_sub")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "slice_to_vec")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "slice_contains")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "vec_as_slice")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "vec_slice")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "bytes_as_slice")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "bytes_slice")) {
        return _v303;
    }
    if (bkr_str_eq(_v1640, "path_exists")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "path_is_file")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "path_is_dir")) {
        return _v305;
    }
    if (bkr_str_eq(_v1640, "file_read")) {
        return _v313;
    }
    if (bkr_str_eq(_v1640, "file_write")) {
        return _v313;
    }
    if (bkr_str_eq(_v1640, "file_size")) {
        return _v313;
    }
    if (bkr_str_eq(_v1640, "file_remove")) {
        return _v313;
    }
    if (bkr_str_eq(_v1640, "file_read_bytes")) {
        return _v313;
    }
    if (bkr_str_eq(_v1640, "file_write_bytes")) {
        return _v313;
    }
    if (bkr_str_eq(_v1640, "dir_create")) {
        return _v313;
    }
    if (bkr_str_eq(_v1640, "dir_remove")) {
        return _v313;
    }
    if (bkr_str_eq(_v1640, "process_run")) {
        return _v313;
    }
    if (bkr_str_eq(_v1640, "process_run_status")) {
        return _v313;
    }
    if (bkr_str_eq(_v1640, "process_exit")) {
        return _v316;
    }
    if (bkr_str_eq(_v1640, "process_pid")) {
        return _v302;
    }
    if (bkr_str_eq(_v1640, "process_is_sandboxed")) {
        return _v305;
    }
    return _v316;
}

bkr_i64 _v1652(bkr_i64 _v1239, bkr_i64 _v368) {
    return _v1653(_v1548(_v1239), _v538(_v368));
}

bkr_i64 _v1654(bkr_i64 _v1239, bkr_i64 _v1655) {
    return _v1656(_v1548(_v1239), _v1655);
}

bkr_i64 _v1656(_v1531 _v1239, bkr_i64 _v1655) {
    if (_v523(_v1655)) {
        return _v316;
    }
    return _v1653(_v1239, _v537(_v1655));
}

_v346 _v1657(_v1531 _v1239, bkr_i64 _v1503, bkr_i64 _v1658) {
    bkr_i64 _v1551 = _v1552(_v1239);
    if (_v523(_v1551)) {
        return _v516(0);
    }
    _v341 _v1530 = _v506(_v1551);
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if (((_v568(_v562) == _v254) && (_v886(_v562) == _v1503))) {
            _v434 _v1158 = _v889(_v562);
            bkr_i64 _v1629 = 0;
            while ((_v1629 < _v906(_v1158))) {
                _v341 _v1432 = _v912(_v1158, _v1629);
                if ((_v891(_v1432) == _v1658)) {
                    return _v516(_v894(_v1432));
                }
                _v1629 = (_v1629 + 1);
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return _v516(0);
}

bkr_i64 _v1659(_v1531 _v1239, bkr_i64 _v1503, bkr_i64 _v1631) {
    bkr_i64 _v1551 = _v1552(_v1239);
    if (_v523(_v1551)) {
        return (-1);
    }
    _v341 _v1530 = _v506(_v1551);
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if (((_v568(_v562) == _v254) && (_v886(_v562) == _v1503))) {
            _v434 _v1158 = _v889(_v562);
            if (((_v1631 >= 0) && (_v1631 < _v906(_v1158)))) {
                _v341 _v1432 = _v912(_v1158, _v1631);
                return _v891(_v1432);
            }
            return (-1);
        }
        _v1168 = (_v1168 + 1);
    }
    return (-1);
}

bkr_bool _v1660(_v1531 _v1239, bkr_i64 _v1503) {
    bkr_i64 _v1551 = _v1552(_v1239);
    if (_v523(_v1551)) {
        return BKR_FALSE;
    }
    _v341 _v1530 = _v506(_v1551);
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if (((_v568(_v562) == _v254) && (_v886(_v562) == _v1503))) {
            return BKR_TRUE;
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_FALSE;
}

bkr_bool _v1661(_v1531 _v1239, bkr_i64 _v1503) {
    bkr_i64 _v1662 = _v1562(_v1239, "0");
    _v346 _v1663 = _v1657(_v1239, _v1503, _v1662);
    return _v524(_v1663);
}

bkr_str _v1664(_v1531 _v1239, bkr_i64 _v1503, bkr_str _v1665) {
    bkr_i64 _v1666 = _v1562(_v1239, _v1665);
    _v346 _v1667 = _v1657(_v1239, _v1503, _v1666);
    if (_v524(_v1667)) {
        return _v1636(_v1239, _v1667);
    }
    return "bkr_i64";
}

_v346 _v1668(_v1531 _v1239, bkr_i64 _v1529) {
    bkr_i64 _v1551 = _v1552(_v1239);
    if (_v523(_v1551)) {
        return _v516(0);
    }
    _v341 _v1530 = _v506(_v1551);
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if (((_v568(_v562) == _v224) && (_v868(_v562) == _v1529))) {
            bkr_i64 _v1669 = _v874(_v562);
            if (_v525(_v1669)) {
                return _v516(_v1669);
            }
            return _v516(0);
        }
        _v1168 = (_v1168 + 1);
    }
    return _v516(0);
}

bkr_i64 _v1653(_v1531 _v1239, _v426 _v541) {
    bkr_i64 _v1670 = _v544(_v541);
    if ((_v1670 == _v246)) {
        return _v303;
    }
    if ((_v1670 == _v251)) {
        return _v304;
    }
    if ((_v1670 == _v247)) {
        return _v305;
    }
    if ((_v1670 == _v248)) {
        return _v306;
    }
    if ((_v1670 == _v227)) {
        _v429 _v582 = _v578(_v540(_v541));
        bkr_i64 _v399 = _v589(_v582);
        if ((_v399 > 0)) {
            _v427 _v1671 = _v1107(_v582, (_v399 - 1));
            if ((_v555(_v1671) == _v232)) {
                return _v1653(_v1239, _v537(_v860(_v1671)));
            }
        }
        return _v307;
    }
    if ((_v1670 == _v252)) {
        return _v308;
    }
    if ((_v1670 == _v257)) {
        return _v309;
    }
    if ((_v1670 == _v245)) {
        bkr_i64 _v425 = _v1561(_v1239);
        bkr_i64 _v355 = _v662(_v541);
        bkr_str _v1640 = _v1625(_v425, _v355);
        if (bkr_str_eq(_v1640, "None")) {
            return _v312;
        }
        return _v1619(_v1239, _v355);
    }
    if ((_v1670 == _v239)) {
        return _v308;
    }
    if ((_v1670 == _v253)) {
        _v426 _v1037 = _v537(_v711(_v541));
        if ((_v544(_v1037) == _v245)) {
            return _v1615(_v1239, _v662(_v1037));
        }
        if ((_v544(_v1037) == _v256)) {
            _v426 _v1672 = _v537(_v719(_v1037));
            if ((_v544(_v1672) == _v245)) {
                bkr_i64 _v1503 = _v1596(_v1239, _v662(_v1672));
                if ((_v1503 >= 0)) {
                    _v346 _v1152 = _v1657(_v1239, _v1503, _v722(_v1037));
                    if ((_v524(_v1152) && (_v529(_v1152) == _v308))) {
                        return _v532(_v1152);
                    }
                }
            }
        }
        return _v316;
    }
    if ((_v1670 == _v256)) {
        _v426 _v1037 = _v537(_v719(_v541));
        if ((_v544(_v1037) == _v245)) {
            if (_v1623(_v1239, _v662(_v1037))) {
                return _v303;
            }
            bkr_i64 _v1503 = _v1596(_v1239, _v662(_v1037));
            if ((_v1503 >= 0)) {
                _v346 _v1152 = _v1657(_v1239, _v1503, _v722(_v541));
                if (_v524(_v1152)) {
                    return _v529(_v1152);
                }
            }
        }
        return _v316;
    }
    if ((_v1670 == _v242)) {
        bkr_i64 _v349 = _v671(_v541);
        _v426 _v1050 = _v537(_v674(_v541));
        _v426 _v1051 = _v537(_v677(_v541));
        if (((_v349 == _v176) && (_v544(_v1051) == _v256))) {
            _v426 _v1673 = _v537(_v719(_v1051));
            if ((_v544(_v1673) == _v245)) {
                bkr_i64 _v425 = _v1561(_v1239);
                bkr_str _v1626 = _v1625(_v425, _v662(_v1673));
                bkr_str _v1628 = _v1625(_v425, _v722(_v1051));
                bkr_i64 _v1674 = _v1627(_v1239, _v1626, _v1628);
                if ((_v1674 >= 0)) {
                    return _v303;
                }
            }
        }
        bkr_i64 _v1675 = _v1653(_v1239, _v1050);
        bkr_i64 _v1676 = _v1653(_v1239, _v1051);
        if (((_v349 == _v161) && ((_v1675 == _v306) || (_v1676 == _v306)))) {
            return _v306;
        }
        if (((((((((_v349 == _v166) || (_v349 == _v167)) || (_v349 == _v168)) || (_v349 == _v169)) || (_v349 == _v170)) || (_v349 == _v171)) || (_v349 == _v172)) || (_v349 == _v173))) {
            return _v305;
        }
        return _v1675;
    }
    if ((_v1670 == _v250)) {
        bkr_i64 _v1677 = _v1653(_v1239, _v537(_v736(_v541)));
        if ((_v1677 != _v314)) {
            return _v1677;
        }
        return _v1653(_v1239, _v537(_v739(_v541)));
    }
    if ((_v1670 == _v240)) {
        _v426 _v1678 = _v537(_v777(_v541));
        bkr_i64 _v1367 = _v1653(_v1239, _v1678);
        if (((_v1367 == _v313) || (_v1367 == _v312))) {
            if ((_v544(_v1678) == _v244)) {
                _v346 _v1679 = _v1668(_v1239, _v688(_v1678));
                if (_v524(_v1679)) {
                    bkr_i64 _v1680 = _v534(_v1679);
                    if (((_v1680 > 0) && (_v1680 != _v316))) {
                        return _v1680;
                    }
                }
            }
            return _v303;
        }
        return _v1367;
    }
    if ((_v1670 == _v241)) {
        _v346 _v1435 = _v516(_v782(_v541));
        return _v529(_v1435);
    }
    if ((_v1670 == _v243)) {
        bkr_i64 _v349 = _v681(_v541);
        if ((_v349 == _v174)) {
            return _v305;
        }
        return _v1653(_v1239, _v537(_v684(_v541)));
    }
    if ((_v1670 == _v258)) {
        _v434 _v975 = _v748(_v541);
        if ((_v906(_v975) > 0)) {
            _v341 _v1123 = _v912(_v975, 0);
            if ((_v509(_v1123) == _v227)) {
                _v429 _v582 = _v580(_v1123);
                if ((_v589(_v582) <= 0)) {
                    return _v316;
                }
                _v427 _v1671 = _v1107(_v582, (_v589(_v582) - 1));
                if ((_v555(_v1671) == _v232)) {
                    return _v1653(_v1239, _v537(_v860(_v1671)));
                }
                return _v316;
            }
            return _v1653(_v1239, _v539(_v1123));
        }
        return _v316;
    }
    if ((_v1670 == _v261)) {
        _v426 _v1021 = _v694(_v541);
        bkr_i64 _v1503 = (-1);
        if ((_v544(_v1021) == _v245)) {
            _v1503 = _v1596(_v1239, _v662(_v1021));
        }
        if ((_v1503 >= 0)) {
            bkr_i64 _v425 = _v1561(_v1239);
            bkr_str _v1681 = _v1625(_v425, _v1503);
            bkr_str _v1682 = _v1625(_v425, _v696(_v541));
            bkr_str _v1424 = bkr_str_concat(bkr_str_concat(_v1681, "::"), _v1682);
            bkr_i64 _v1683 = _v1562(_v1239, _v1424);
            bkr_i64 _v1684 = _v1622(_v1239, _v1683);
            if ((_v1684 != _v316)) {
                return _v1684;
            }
            _v346 _v1679 = _v1668(_v1239, _v1683);
            if (_v524(_v1679)) {
                return _v529(_v1679);
            }
        }
        return _v316;
    }
    if ((_v1670 == _v244)) {
        bkr_i64 _v355 = _v688(_v541);
        if (_v1660(_v1239, _v355)) {
            return _v309;
        }
        bkr_i64 _v1685 = _v1619(_v1239, _v355);
        if ((_v1685 == _v315)) {
            return _v303;
        }
        bkr_i64 _v425 = _v1561(_v1239);
        bkr_str _v1640 = _v1625(_v425, _v355);
        if (bkr_str_eq(_v1640, "panic")) {
            return _v314;
        }
        if (bkr_str_eq(_v1640, "Some")) {
            return _v312;
        }
        if ((bkr_str_eq(_v1640, "Ok") || bkr_str_eq(_v1640, "Err"))) {
            return _v313;
        }
        if ((bkr_str_eq(_v1640, "vec_get") || bkr_str_eq(_v1640, "vec_pop"))) {
            _v434 _v1015 = _v691(_v541);
            if ((_v906(_v1015) > 0)) {
                _v426 _v1686 = _v537(_v909(_v1015, 0));
                if ((_v544(_v1686) == _v245)) {
                    bkr_i64 _v1687 = _v1615(_v1239, _v1024(_v1686));
                    if (((_v1687 != _v316) && (_v1687 != 0))) {
                        return _v1687;
                    }
                }
            }
        }
        bkr_i64 _v1688 = _v1651(_v1640);
        if ((_v1688 != _v316)) {
            return _v1688;
        }
        bkr_i64 _v1684 = _v1622(_v1239, _v355);
        if ((_v1684 != _v316)) {
            return _v1684;
        }
        _v346 _v1679 = _v1668(_v1239, _v355);
        if (_v524(_v1679)) {
            return _v529(_v1679);
        }
        return _v316;
    }
    return _v316;
}

bkr_str _v1689(bkr_i64 _v1239, bkr_i64 _v370) {
    return _v1690(_v1548(_v1239), _v550(_v370));
}

bkr_str _v1690(_v1531 _v1239, _v427 _v553) {
    bkr_str _v1348 = _v1637(_v1239, _v757(_v553));
    bkr_i64 _v515 = _v760(_v553);
    bkr_i64 _v366 = _v763(_v553);
    if ((_v525(_v515) && (_v1646(_v516(_v515)) == _v308))) {
        bkr_i64 _v953 = _v1648(_v516(_v515));
        bkr_i64 _v1691 = _v1650(_v516(_v515));
        bkr_str _v1582 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1634(_v953), " "), _v1348), "["), int_to_string(_v1691)), "]");
        if (_v525(_v366)) {
            _v1582 = bkr_str_concat(bkr_str_concat(_v1582, " = "), _v1692(_v1239, _v537(_v366)));
        }
        return bkr_str_concat(_v1582, "; ");
    }
    if ((_v523(_v515) && _v525(_v366))) {
        _v426 _v1693 = _v537(_v366);
        bkr_i64 _v1694 = _v544(_v1693);
        if ((_v1694 == _v252)) {
            _v434 _v994 = _v701(_v1693);
            bkr_i64 _v1691 = _v906(_v994);
            if ((_v1691 > 0)) {
                bkr_i64 _v953 = _v1653(_v1239, _v537(_v909(_v994, 0)));
                bkr_str _v1582 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1634(_v953), " "), _v1348), "["), int_to_string(_v1691)), "] = "), _v1692(_v1239, _v1693));
                return bkr_str_concat(_v1582, "; ");
            }
        } else {
            if ((_v1694 == _v239)) {
                bkr_i64 _v1691 = _v706(_v1693);
                bkr_i64 _v953 = _v1653(_v1239, _v704(_v1693));
                bkr_str _v1582 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1634(_v953), " "), _v1348), "["), int_to_string(_v1691)), "] = "), _v1692(_v1239, _v1693));
                return bkr_str_concat(_v1582, "; ");
            }
        }
    }
    bkr_i64 _v319 = _v303;
    bkr_i64 _v1503 = (-1);
    if (_v525(_v515)) {
        _v319 = _v1646(_v516(_v515));
        if ((_v319 == _v309)) {
            _v1503 = _v531(_v516(_v515));
        }
    } else {
        if (_v525(_v366)) {
            bkr_i64 _v1695 = _v1656(_v1239, _v366);
            if (((_v1695 != _v316) && (_v1695 != _v307))) {
                _v319 = _v1695;
            }
            _v426 _v1693 = _v537(_v366);
            if ((_v544(_v1693) == _v257)) {
                _v319 = _v309;
                _v1503 = _v724(_v1693);
            } else {
                if ((_v544(_v1693) == _v244)) {
                    bkr_i64 _v1696 = _v688(_v1693);
                    if (_v1660(_v1239, _v1696)) {
                        _v319 = _v309;
                        _v1503 = _v1696;
                    } else {
                        _v346 _v1679 = _v1668(_v1239, _v1696);
                        if ((_v524(_v1679) && (_v529(_v1679) == _v309))) {
                            _v319 = _v309;
                            _v1503 = _v531(_v1679);
                        }
                    }
                } else {
                    if ((_v544(_v1693) == _v245)) {
                        bkr_i64 _v1697 = _v1596(_v1239, _v1024(_v1693));
                        if ((_v1697 >= 0)) {
                            _v319 = _v309;
                            _v1503 = _v1697;
                        }
                    } else {
                        if ((_v544(_v1693) == _v227)) {
                            _v429 _v582 = _v578(_v540(_v1693));
                            bkr_i64 _v399 = _v589(_v582);
                            if ((_v399 > 0)) {
                                _v427 _v1671 = _v1107(_v582, (_v399 - 1));
                                if ((_v555(_v1671) == _v232)) {
                                    _v426 _v1698 = _v537(_v860(_v1671));
                                    bkr_i64 _v1699 = _v544(_v1698);
                                    if ((_v1699 == _v257)) {
                                        _v319 = _v309;
                                        _v1503 = _v724(_v1698);
                                    } else {
                                        if ((_v1699 == _v245)) {
                                            bkr_i64 _v1697 = _v1596(_v1239, _v662(_v1698));
                                            if ((_v1697 >= 0)) {
                                                _v319 = _v309;
                                                _v1503 = _v1697;
                                            }
                                        } else {
                                            if (((_v1699 == _v244) && _v1660(_v1239, _v688(_v1698)))) {
                                                _v319 = _v309;
                                                _v1503 = _v688(_v1698);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    bkr_str _v1700 = _v1634(_v319);
    if (_v525(_v515)) {
        _v1700 = _v1636(_v1239, _v516(_v515));
    } else {
        if (((_v319 == _v309) && (_v1503 >= 0))) {
            if (_v1623(_v1239, _v1503)) {
                _v1700 = "bkr_i64";
            } else {
                _v1700 = _v1637(_v1239, _v1503);
            }
        }
    }
    bkr_str _v1582 = bkr_str_concat(bkr_str_concat(_v1700, " "), _v1348);
    if (_v525(_v366)) {
        _v1582 = bkr_str_concat(bkr_str_concat(_v1582, " = "), _v1701(_v1239, _v515, _v537(_v366)));
    }
    return bkr_str_concat(_v1582, "; ");
}

bkr_str _v1702(bkr_i64 _v1239, bkr_str _v1703, bkr_i64 _v379) {
    return _v1704(_v1548(_v1239), _v1703, _v476(_v379));
}

bkr_str _v1704(_v1531 _v1239, bkr_str _v1703, _v341 _v1123) {
    if ((_v509(_v1123) != _v227)) {
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1703, " = "), _v1692(_v1239, _v539(_v1123))), "; ");
    }
    _v429 _v582 = _v580(_v1123);
    bkr_str _v1193 = "{ ";
    bkr_i64 _v1168 = 0;
    bkr_i64 _v399 = _v589(_v582);
    while ((_v1168 < _v399)) {
        _v427 _v553 = _v1107(_v582, _v1168);
        bkr_i64 _v1705 = _v555(_v553);
        bkr_bool _v1706 = (_v1168 == (_v399 - 1));
        if ((_v1706 && (_v1705 == _v232))) {
            if ((!bkr_str_eq(_v1703, ""))) {
                _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1703), " = "), _v1692(_v1239, _v537(_v860(_v553)))), "; ");
            } else {
                _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1692(_v1239, _v537(_v860(_v553)))), "; ");
            }
        } else {
            if ((_v1705 == _v228)) {
                _v1193 = bkr_str_concat(_v1193, _v1690(_v1239, _v553));
            } else {
                if ((_v1705 == _v233)) {
                    _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1692(_v1239, _v537(_v854(_v553)))), " = "), _v1692(_v1239, _v537(_v857(_v553)))), "; ");
                } else {
                    if ((_v1705 == _v232)) {
                        _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1692(_v1239, _v537(_v860(_v553)))), "; ");
                    } else {
                        if ((_v1705 == _v229)) {
                            bkr_i64 _v1707 = _v768(_v553);
                            if (_v525(_v1707)) {
                                _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, "return "), _v1692(_v1239, _v537(_v1707))), "; ");
                            } else {
                                _v1193 = bkr_str_concat(_v1193, "return; ");
                            }
                        }
                    }
                }
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(_v1193, "} ");
}

bkr_str _v1708(bkr_i64 _v1239, bkr_str _v1709, bkr_i64 _v463) {
    return _v1710(_v1548(_v1239), _v1709, _v592(_v463));
}

bkr_str _v1710(_v1531 _v1239, bkr_str _v1709, _v433 _v472) {
    bkr_i64 _v319 = _v596(_v472);
    bkr_i64 _v387 = _v597(_v472);
    if ((_v319 == _v283)) {
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("(", _v1709), " == "), int_to_string(_v387)), ")");
    }
    if ((_v319 == _v284)) {
        if ((_v387 != 0)) {
            return bkr_str_concat(bkr_str_concat("(", _v1709), " == BKR_TRUE)");
        }
        return bkr_str_concat(bkr_str_concat("(", _v1709), " == BKR_FALSE)");
    }
    if (((_v319 == _v285) || (_v319 == _v286))) {
        return "BKR_TRUE";
    }
    if ((_v319 == _v287)) {
        bkr_str _v1711 = bkr_str_concat(bkr_str_concat("((", _v1709), " & 1) != 0)");
        bkr_i64 _v345 = _v598(_v472);
        if ((_v345 != 0)) {
            _v433 _v1393 = _v591(_v345);
            bkr_str _v1712 = _v1710(_v1239, bkr_str_concat(bkr_str_concat("(", _v1709), " >> 1)"), _v1393);
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("(", _v1711), " && "), _v1712), ")");
        }
        return _v1711;
    }
    if ((_v319 == _v288)) {
        return bkr_str_concat(bkr_str_concat("(", _v1709), " == 0)");
    }
    if ((_v319 == _v290)) {
        bkr_str _v1711 = bkr_str_concat(bkr_str_concat("(bkr_result_is_ok(", _v1709), ") == BKR_TRUE)");
        bkr_i64 _v345 = _v598(_v472);
        if ((_v345 != 0)) {
            _v433 _v1393 = _v591(_v345);
            bkr_str _v1712 = _v1710(_v1239, bkr_str_concat(bkr_str_concat("bkr_result_unwrap(", _v1709), ")"), _v1393);
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("(", _v1711), " && "), _v1712), ")");
        }
        return _v1711;
    }
    if ((_v319 == _v291)) {
        bkr_str _v1711 = bkr_str_concat(bkr_str_concat("(bkr_result_is_err(", _v1709), ") == BKR_TRUE)");
        bkr_i64 _v345 = _v598(_v472);
        if ((_v345 != 0)) {
            _v433 _v1393 = _v591(_v345);
            bkr_str _v1712 = _v1710(_v1239, bkr_str_concat(bkr_str_concat("bkr_result_unwrap_err(", _v1709), ")"), _v1393);
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("(", _v1711), " && "), _v1712), ")");
        }
        return _v1711;
    }
    if ((_v319 == _v292)) {
        bkr_i64 _v345 = _v598(_v472);
        if ((_v345 != 0)) {
            bkr_i64 _v1375 = ((bkr_i64)(_v345));
            bkr_str _v375 = "";
            bkr_i64 _v1168 = 0;
            while ((_v1168 < vec_len(_v1375))) {
                _v433 _v1393 = _v591(vec_get(_v1375, _v1168));
                bkr_str _v1713 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_tuple_get(", _v1709), ", "), int_to_string(_v1168)), ")");
                bkr_str _v1712 = _v1710(_v1239, _v1713, _v1393);
                if ((!bkr_str_eq(_v1712, "BKR_TRUE"))) {
                    if (bkr_str_eq(_v375, "")) {
                        _v375 = bkr_str_concat(bkr_str_concat("(", _v1712), ")");
                    } else {
                        _v375 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("(", _v375), " && "), _v1712), ")");
                    }
                }
                _v1168 = (_v1168 + 1);
            }
            if ((!bkr_str_eq(_v375, ""))) {
                return _v375;
            }
        }
        return "BKR_TRUE";
    }
    if ((_v319 == _v293)) {
        return "BKR_TRUE";
    }
    if ((_v319 == _v289)) {
        bkr_i64 _v425 = _v1561(_v1239);
        bkr_str _v1626 = _v1625(_v425, _v387);
        bkr_str _v1628 = _v1625(_v425, _v598(_v472));
        bkr_i64 _v1674 = _v1627(_v1239, _v1626, _v1628);
        if ((_v1674 >= 0)) {
            if (_v1633(_v1239, _v1626)) {
                return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("(bkr_enum_tag(", _v1709), ") == "), int_to_string(_v1674)), ")");
            }
            if ((_v599(_v472) >= 0)) {
                return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("((", _v1709), " & 255) == "), int_to_string(_v1674)), ")");
            }
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("(", _v1709), " == "), int_to_string(_v1674)), ")");
        }
    }
    return "BKR_FALSE";
}

bkr_str _v1714(bkr_i64 _v1239, bkr_str _v1709, bkr_i64 _v463, bkr_i64 _v1715) {
    return _v1716(_v1548(_v1239), _v1709, _v592(_v463), _v1715);
}

bkr_str _v1716(_v1531 _v1239, bkr_str _v1709, _v433 _v472, bkr_i64 _v1715) {
    bkr_i64 _v319 = _v596(_v472);
    bkr_i64 _v387 = _v597(_v472);
    if ((_v319 == _v285)) {
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1634(_v1715), " "), _v1637(_v1239, _v387)), " = "), _v1709), "; ");
    }
    if ((_v319 == _v287)) {
        bkr_str _v1717 = "";
        if ((_v387 >= 0)) {
            _v1717 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1717, "bkr_i64 "), _v1637(_v1239, _v387)), " = ("), _v1709), " >> 1); ");
        }
        bkr_i64 _v345 = _v598(_v472);
        if ((_v345 != 0)) {
            _v433 _v1393 = _v591(_v345);
            bkr_str _v1718 = bkr_str_concat(bkr_str_concat("(", _v1709), " >> 1)");
            _v1717 = bkr_str_concat(_v1717, _v1716(_v1239, _v1718, _v1393, _v303));
        }
        return _v1717;
    }
    if ((_v319 == _v290)) {
        bkr_str _v1717 = "";
        if ((_v387 >= 0)) {
            _v1717 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1717, "bkr_i64 "), _v1637(_v1239, _v387)), " = bkr_result_unwrap("), _v1709), "); ");
        }
        bkr_i64 _v345 = _v598(_v472);
        if ((_v345 != 0)) {
            _v433 _v1393 = _v591(_v345);
            bkr_str _v1718 = bkr_str_concat(bkr_str_concat("bkr_result_unwrap(", _v1709), ")");
            _v1717 = bkr_str_concat(_v1717, _v1716(_v1239, _v1718, _v1393, _v303));
        }
        return _v1717;
    }
    if ((_v319 == _v291)) {
        bkr_str _v1717 = "";
        if ((_v387 >= 0)) {
            _v1717 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1717, "bkr_i64 "), _v1637(_v1239, _v387)), " = bkr_result_unwrap_err("), _v1709), "); ");
        }
        bkr_i64 _v345 = _v598(_v472);
        if ((_v345 != 0)) {
            _v433 _v1393 = _v591(_v345);
            bkr_str _v1718 = bkr_str_concat(bkr_str_concat("bkr_result_unwrap_err(", _v1709), ")");
            _v1717 = bkr_str_concat(_v1717, _v1716(_v1239, _v1718, _v1393, _v303));
        }
        return _v1717;
    }
    if ((_v319 == _v292)) {
        bkr_i64 _v345 = _v598(_v472);
        if ((_v345 != 0)) {
            bkr_i64 _v1375 = ((bkr_i64)(_v345));
            bkr_str _v1717 = "";
            bkr_i64 _v1168 = 0;
            while ((_v1168 < vec_len(_v1375))) {
                _v433 _v1393 = _v591(vec_get(_v1375, _v1168));
                bkr_str _v1713 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_tuple_get(", _v1709), ", "), int_to_string(_v1168)), ")");
                _v1717 = bkr_str_concat(_v1717, _v1716(_v1239, _v1713, _v1393, _v303));
                _v1168 = (_v1168 + 1);
            }
            return _v1717;
        }
        bkr_i64 _v1377 = _v599(_v472);
        bkr_i64 _v432 = _v600(_v472);
        bkr_i64 _v1378 = _v597(_v472);
        bkr_str _v1717 = "";
        if ((_v1377 >= 0)) {
            _v1717 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1717, "bkr_i64 "), _v1637(_v1239, _v1377)), " = bkr_tuple_get("), _v1709), ", 0); ");
        }
        if ((_v432 >= 0)) {
            _v1717 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1717, "bkr_i64 "), _v1637(_v1239, _v432)), " = bkr_tuple_get("), _v1709), ", 1); ");
        }
        if ((_v1378 >= 0)) {
            _v1717 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1717, "bkr_i64 "), _v1637(_v1239, _v1378)), " = bkr_tuple_get("), _v1709), ", 2); ");
        }
        return _v1717;
    }
    if ((_v319 == _v293)) {
        bkr_i64 _v1503 = _v597(_v472);
        bkr_bool _v1719 = _v1661(_v1239, _v1503);
        bkr_i64 _v1385 = _v599(_v472);
        bkr_i64 _v1386 = _v600(_v472);
        bkr_i64 _v1387 = _v598(_v472);
        bkr_str _v1717 = "";
        if (_v1719) {
            if ((_v1385 >= 0)) {
                bkr_str _v1720 = _v1637(_v1239, _v1385);
                bkr_str _v1721 = _v1637(_v1239, _v1562(_v1239, "0"));
                bkr_str _v1700 = _v1664(_v1239, _v1503, "0");
                _v1717 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1717, _v1700), " "), _v1720), " = "), _v1709), "."), _v1721), "; ");
            }
            if ((_v1386 >= 0)) {
                bkr_str _v1720 = _v1637(_v1239, _v1386);
                bkr_str _v1722 = _v1637(_v1239, _v1562(_v1239, "1"));
                bkr_str _v1700 = _v1664(_v1239, _v1503, "1");
                _v1717 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1717, _v1700), " "), _v1720), " = "), _v1709), "."), _v1722), "; ");
            }
            if ((_v1387 >= 0)) {
                bkr_str _v1720 = _v1637(_v1239, _v1387);
                bkr_str _v1723 = _v1637(_v1239, _v1562(_v1239, "2"));
                bkr_str _v1700 = _v1664(_v1239, _v1503, "2");
                _v1717 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1717, _v1700), " "), _v1720), " = "), _v1709), "."), _v1723), "; ");
            }
            return _v1717;
        }
        if ((_v1385 >= 0)) {
            bkr_i64 _v1724 = _v1659(_v1239, _v1503, 0);
            bkr_str _v1725 = _v1637(_v1239, _v1385);
            if ((_v1724 >= 0)) {
                _v1725 = _v1637(_v1239, _v1724);
            }
            bkr_str _v1726 = _v1637(_v1239, _v1385);
            _v346 _v1667 = _v1657(_v1239, _v1503, _v1724);
            bkr_str _v1700 = "bkr_i64";
            if (_v524(_v1667)) {
                _v1700 = _v1636(_v1239, _v1667);
            }
            _v1717 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1717, _v1700), " "), _v1726), " = "), _v1709), "."), _v1725), "; ");
        }
        if ((_v1386 >= 0)) {
            bkr_i64 _v1727 = _v1659(_v1239, _v1503, 1);
            bkr_str _v1728 = _v1637(_v1239, _v1386);
            if ((_v1727 >= 0)) {
                _v1728 = _v1637(_v1239, _v1727);
            }
            bkr_str _v1729 = _v1637(_v1239, _v1386);
            _v346 _v1667 = _v1657(_v1239, _v1503, _v1727);
            bkr_str _v1700 = "bkr_i64";
            if (_v524(_v1667)) {
                _v1700 = _v1636(_v1239, _v1667);
            }
            _v1717 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1717, _v1700), " "), _v1729), " = "), _v1709), "."), _v1728), "; ");
        }
        if ((_v1387 >= 0)) {
            bkr_i64 _v1730 = _v1659(_v1239, _v1503, 2);
            bkr_str _v1731 = _v1637(_v1239, _v1387);
            if ((_v1730 >= 0)) {
                _v1731 = _v1637(_v1239, _v1730);
            }
            bkr_str _v1732 = _v1637(_v1239, _v1387);
            _v346 _v1667 = _v1657(_v1239, _v1503, _v1730);
            bkr_str _v1700 = "bkr_i64";
            if (_v524(_v1667)) {
                _v1700 = _v1636(_v1239, _v1667);
            }
            _v1717 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1717, _v1700), " "), _v1732), " = "), _v1709), "."), _v1731), "; ");
        }
        return _v1717;
    }
    if ((_v319 == _v289)) {
        bkr_i64 _v1390 = _v599(_v472);
        if ((_v1390 >= 0)) {
            bkr_i64 _v425 = _v1561(_v1239);
            bkr_str _v1626 = _v1625(_v425, _v387);
            bkr_str _v1628 = _v1625(_v425, _v598(_v472));
            bkr_i64 _v1733 = _v1630(_v1239, _v1626, _v1628, 0);
            if (_v1633(_v1239, _v1626)) {
                bkr_i64 _v1391 = _v600(_v472);
                bkr_str _v1717 = "";
                if ((_v1733 == _v306)) {
                    _v1717 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_str ", _v1637(_v1239, _v1390)), " = (bkr_str)(intptr_t)bkr_enum_field("), _v1709), ", 0); ");
                } else {
                    _v1717 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_i64 ", _v1637(_v1239, _v1390)), " = bkr_enum_field("), _v1709), ", 0); ");
                }
                if ((_v1391 >= 0)) {
                    bkr_i64 _v1734 = _v1630(_v1239, _v1626, _v1628, 1);
                    if ((_v1734 == _v306)) {
                        _v1717 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1717, "bkr_str "), _v1637(_v1239, _v1391)), " = (bkr_str)(intptr_t)bkr_enum_field("), _v1709), ", 1); ");
                    } else {
                        _v1717 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1717, "bkr_i64 "), _v1637(_v1239, _v1391)), " = bkr_enum_field("), _v1709), ", 1); ");
                    }
                }
                return _v1717;
            }
            bkr_i64 _v1391 = _v600(_v472);
            if ((_v1391 >= 0)) {
                return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_i64 ", _v1637(_v1239, _v1390)), " = ("), _v1709), " >> 20); "), "bkr_i64 "), _v1637(_v1239, _v1391)), " = (("), _v1709), " >> 8) & 4095); ");
            }
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_i64 ", _v1637(_v1239, _v1390)), " = ("), _v1709), " >> 8); ");
        }
    }
    return "";
}

bkr_str _v1735(bkr_i64 _v1239, bkr_i64 _v368) {
    return _v1736(_v1548(_v1239), _v538(_v368));
}

bkr_str _v1736(_v1531 _v1239, _v426 _v541) {
    _v426 _v974 = _v537(_v742(_v541));
    bkr_i64 _v1715 = _v1653(_v1239, _v974);
    bkr_i64 _v1737 = _v1653(_v1239, _v541);
    if (((_v1737 == _v316) || (_v1737 == _v307))) {
        _v1737 = _v303;
    }
    bkr_str _v1738 = _v1634(_v1715);
    if (((_v1715 == _v309) && (_v544(_v974) == _v245))) {
        bkr_i64 _v1739 = _v1596(_v1239, _v662(_v974));
        if ((_v1739 >= 0)) {
            if (_v1623(_v1239, _v1739)) {
                _v1738 = "bkr_i64";
            } else {
                _v1738 = _v1637(_v1239, _v1739);
            }
        }
    }
    bkr_str _v1709 = _v1604(_v1239, "_match_val");
    bkr_str _v1703 = _v1604(_v1239, "_match_res");
    bkr_str _v1740 = _v1604(_v1239, "_matched");
    bkr_str _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("({ ", _v1738), " "), _v1709), " = "), _v1692(_v1239, _v974)), "; "), _v1634(_v1737)), " "), _v1703), " = 0; int "), _v1740), " = 0; ");
    _v436 _v620 = _v745(_v541);
    _v434 _v975 = _v748(_v541);
    _v435 _v976 = _v750(_v541);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v919(_v620))) {
        _v433 _v472 = _v924(_v620, _v1168);
        _v341 _v1123 = _v912(_v975, _v1168);
        bkr_i64 _v1398 = 0;
        if ((_v1168 < _v915(_v976))) {
            _v1398 = _v917(_v976, _v1168);
        }
        bkr_str _v1741 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("!", _v1740), " && ("), _v1710(_v1239, _v1709, _v472)), ")");
        _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, "if ("), _v1741), ") { "), _v1716(_v1239, _v1709, _v472, _v1715));
        if ((_v1398 != 0)) {
            _v426 _v1742 = _v537(_v1398);
            _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, "if ("), _v1692(_v1239, _v1742)), ") { "), _v1704(_v1239, _v1703, _v1123)), _v1740), " = 1; } } ");
        } else {
            _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1704(_v1239, _v1703, _v1123)), _v1740), " = 1; } ");
        }
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(bkr_str_concat(_v1193, _v1703), "; })");
}

bkr_bool _v1743(bkr_i64 _v1239, bkr_i64 _v368) {
    return _v1744(_v1548(_v1239), _v538(_v368));
}

bkr_bool _v1744(_v1531 _v1239, _v426 _v541) {
    if ((_v544(_v541) != _v244)) {
        return BKR_FALSE;
    }
    bkr_i64 _v355 = _v688(_v541);
    bkr_i64 _v425 = _v1561(_v1239);
    bkr_str _v1640 = _v1625(_v425, _v355);
    return (((((bkr_str_eq(_v1640, "result_unwrap") || bkr_str_eq(_v1640, "result_unwrap_err")) || bkr_str_eq(_v1640, "result_value")) || bkr_str_eq(_v1640, "vec_get")) || bkr_str_eq(_v1640, "vec_pop")) || bkr_str_eq(_v1640, "hashmap_get"));
}

bkr_str _v1745(bkr_i64 _v1239, bkr_i64 _v368) {
    return _v1746(_v1548(_v1239), _v538(_v368));
}

bkr_str _v1746(_v1531 _v1239, _v426 _v541) {
    bkr_str _v1193 = _v1692(_v1239, _v541);
    bkr_i64 _v319 = _v1653(_v1239, _v541);
    if ((_v319 == _v306)) {
        return bkr_str_concat(bkr_str_concat("((bkr_i64)(intptr_t)", _v1193), ")");
    }
    return _v1193;
}

bkr_str _v1747(bkr_i64 _v1239, bkr_i64 _v515, bkr_i64 _v366) {
    return _v1701(_v1548(_v1239), _v515, _v538(_v366));
}

bkr_str _v1701(_v1531 _v1239, bkr_i64 _v515, _v426 _v1693) {
    if ((_v525(_v515) && (_v1646(_v516(_v515)) == _v311))) {
        bkr_i64 _v1363 = _v534(_v516(_v515));
        if (((_v1363 == _v306) && (_v544(_v1693) == _v244))) {
            bkr_i64 _v355 = _v688(_v1693);
            bkr_i64 _v425 = _v1561(_v1239);
            bkr_str _v1748 = _v1625(_v425, _v355);
            if (bkr_str_eq(_v1748, "hashmap_new")) {
                return "hashmap_new_str()";
            }
        }
    }
    bkr_str _v1193 = _v1692(_v1239, _v1693);
    if (((_v525(_v515) && (_v1646(_v516(_v515)) == _v306)) && _v1744(_v1239, _v1693))) {
        return bkr_str_concat(bkr_str_concat("(bkr_str)(intptr_t)(", _v1193), ")");
    }
    return _v1193;
}

bkr_str _v1749(bkr_i64 _v1239, bkr_i64 _v368) {
    return _v1692(_v1548(_v1239), _v538(_v368));
}

bkr_str _v1692(_v1531 _v1239, _v426 _v541) {
    bkr_i64 _v1670 = _v544(_v541);
    if ((_v1670 == _v246)) {
        return int_to_string(_v665(_v541));
    }
    if ((_v1670 == _v251)) {
        return ((bkr_str)(_v665(_v541)));
    }
    if ((_v1670 == _v247)) {
        if ((_v665(_v541) == 1)) {
            return "BKR_TRUE";
        }
        return "BKR_FALSE";
    }
    if ((_v1670 == _v248)) {
        bkr_str _v1640 = ((bkr_str)(_v665(_v541)));
        return _v1750(_v1640);
    }
    if ((_v1670 == _v227)) {
        bkr_str _v1751 = _v1604(_v1239, "_blk_res");
        bkr_i64 _v1752 = _v1653(_v1239, _v541);
        bkr_str _v1753 = _v1634(_v1752);
        if ((_v1752 == _v309)) {
            _v429 _v582 = _v578(_v540(_v541));
            bkr_i64 _v399 = _v589(_v582);
            if ((_v399 > 0)) {
                _v427 _v1671 = _v1107(_v582, (_v399 - 1));
                if ((_v555(_v1671) == _v232)) {
                    _v426 _v1698 = _v537(_v860(_v1671));
                    bkr_i64 _v1699 = _v544(_v1698);
                    bkr_i64 _v1697 = (-1);
                    if ((_v1699 == _v257)) {
                        _v1697 = _v724(_v1698);
                    } else {
                        if ((_v1699 == _v245)) {
                            _v1697 = _v1596(_v1239, _v662(_v1698));
                        } else {
                            if (((_v1699 == _v244) && _v1660(_v1239, _v688(_v1698)))) {
                                _v1697 = _v688(_v1698);
                            }
                        }
                    }
                    if ((_v1697 >= 0)) {
                        _v1753 = _v1637(_v1239, _v1697);
                    }
                }
            }
        }
        if ((_v1752 == _v307)) {
            return bkr_str_concat(bkr_str_concat("({ ", _v1704(_v1239, "", _v506(_v540(_v541)))), "; })");
        }
        if ((_v1752 == _v309)) {
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("({ ", _v1753), " "), _v1751), "; "), _v1704(_v1239, _v1751, _v506(_v540(_v541)))), _v1751), "; })");
        }
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("({ ", _v1753), " "), _v1751), " = 0; "), _v1704(_v1239, _v1751, _v506(_v540(_v541)))), _v1751), "; })");
    }
    if ((_v1670 == _v239)) {
        _v426 _v1000 = _v704(_v541);
        bkr_i64 _v399 = _v706(_v541);
        bkr_str _v1754 = _v1692(_v1239, _v1000);
        if ((bkr_str_eq(_v1754, "0") || (_v399 <= 0))) {
            return "{ 0 }";
        }
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{ [0 ... ", int_to_string((_v399 - 1))), "] = "), _v1754), " }");
    }
    if ((_v1670 == _v252)) {
        _v434 _v994 = _v701(_v541);
        bkr_str _v1193 = "{";
        bkr_i64 _v1168 = 0;
        while ((_v1168 < _v906(_v994))) {
            if ((_v1168 > 0)) {
                _v1193 = bkr_str_concat(_v1193, ", ");
            }
            _v1193 = bkr_str_concat(_v1193, _v1692(_v1239, _v537(_v909(_v994, _v1168))));
            _v1168 = (_v1168 + 1);
        }
        return bkr_str_concat(_v1193, "}");
    }
    if ((_v1670 == _v257)) {
        bkr_str _v1755 = _v1637(_v1239, _v724(_v541));
        _v435 _v1007 = _v727(_v541);
        _v434 _v1008 = _v730(_v541);
        bkr_i64 _v403 = _v1005(_v541);
        bkr_str _v1193 = bkr_str_concat(bkr_str_concat("(", _v1755), "){");
        bkr_i64 _v1168 = 0;
        while ((_v1168 < _v915(_v1007))) {
            if ((_v1168 > 0)) {
                _v1193 = bkr_str_concat(_v1193, ", ");
            }
            _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, "."), _v1637(_v1239, _v917(_v1007, _v1168))), " = "), _v1692(_v1239, _v537(_v909(_v1008, _v1168))));
            _v1168 = (_v1168 + 1);
        }
        if ((_v403 != 0)) {
            bkr_str _v1756 = _v1692(_v1239, _v537(_v403));
            bkr_i64 _v1739 = _v724(_v541);
            bkr_i64 _v1757 = _v1552(_v1239);
            if (_v525(_v1757)) {
                _v341 _v1758 = _v506(_v1757);
                _v434 _v1759 = _v898(_v1758);
                bkr_i64 _v1760 = 0;
                while ((_v1760 < _v906(_v1759))) {
                    _v428 _v1761 = _v913(_v1759, _v1760);
                    if (((_v568(_v1761) == _v254) && (_v886(_v1761) == _v1739))) {
                        _v434 _v1762 = _v889(_v1761);
                        bkr_i64 _v1763 = 0;
                        while ((_v1763 < _v906(_v1762))) {
                            _v341 _v1764 = _v912(_v1762, _v1763);
                            bkr_i64 _v1666 = _v891(_v1764);
                            bkr_bool _v1765 = BKR_FALSE;
                            bkr_i64 _v1766 = 0;
                            while ((_v1766 < _v915(_v1007))) {
                                if ((_v917(_v1007, _v1766) == _v1666)) {
                                    _v1765 = BKR_TRUE;
                                }
                                _v1766 = (_v1766 + 1);
                            }
                            if ((!_v1765)) {
                                if ((_v1168 > 0)) {
                                    _v1193 = bkr_str_concat(_v1193, ", ");
                                }
                                _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, "."), _v1637(_v1239, _v1666)), " = ("), _v1756), ")."), _v1637(_v1239, _v1666));
                                _v1168 = (_v1168 + 1);
                            }
                            _v1763 = (_v1763 + 1);
                        }
                    }
                    _v1760 = (_v1760 + 1);
                }
            }
        }
        return bkr_str_concat(_v1193, "}");
    }
    if ((_v1670 == _v245)) {
        bkr_i64 _v355 = _v662(_v541);
        bkr_i64 _v425 = _v1561(_v1239);
        bkr_str _v1640 = _v1625(_v425, _v355);
        if (bkr_str_eq(_v1640, "None")) {
            return "0";
        }
        return _v1637(_v1239, _v355);
    }
    if ((_v1670 == _v253)) {
        _v426 _v1037 = _v537(_v711(_v541));
        _v426 _v1431 = _v537(_v714(_v541));
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1692(_v1239, _v1037), "["), _v1692(_v1239, _v1431)), "]");
    }
    if ((_v1670 == _v256)) {
        _v426 _v1037 = _v537(_v719(_v541));
        bkr_i64 _v1044 = _v722(_v541);
        bkr_i64 _v425 = _v1561(_v1239);
        bkr_str _v1767 = _v1625(_v425, _v1044);
        if ((((bkr_str_eq(_v1767, "0") || bkr_str_eq(_v1767, "1")) || bkr_str_eq(_v1767, "2")) || bkr_str_eq(_v1767, "3"))) {
            bkr_bool _v1768 = (_v1653(_v1239, _v1037) == _v309);
            if (((!_v1768) && (_v544(_v1037) == _v245))) {
                if ((_v1596(_v1239, _v662(_v1037)) >= 0)) {
                    _v1768 = BKR_TRUE;
                }
            }
            if (_v1768) {
                return bkr_str_concat(bkr_str_concat(_v1692(_v1239, _v1037), "."), _v1637(_v1239, _v1044));
            }
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_tuple_get(", _v1692(_v1239, _v1037)), ", "), _v1767), ")");
        }
        if ((_v544(_v1037) == _v245)) {
            bkr_str _v1626 = _v1625(_v425, _v662(_v1037));
            bkr_i64 _v1674 = _v1627(_v1239, _v1626, _v1767);
            if ((_v1674 >= 0)) {
                return int_to_string(_v1674);
            }
        }
        return bkr_str_concat(bkr_str_concat(_v1692(_v1239, _v1037), "."), _v1637(_v1239, _v1044));
    }
    if ((_v1670 == _v242)) {
        bkr_i64 _v349 = _v671(_v541);
        _v426 _v1050 = _v537(_v674(_v541));
        _v426 _v1051 = _v537(_v677(_v541));
        if ((_v349 == _v176)) {
            if ((_v544(_v1051) == _v256)) {
                _v426 _v1037 = _v537(_v719(_v1051));
                bkr_i64 _v1044 = _v722(_v1051);
                bkr_i64 _v425 = _v1561(_v1239);
                if ((_v544(_v1037) == _v245)) {
                    bkr_str _v1626 = _v1625(_v425, _v662(_v1037));
                    bkr_str _v1628 = _v1625(_v425, _v1044);
                    bkr_i64 _v1674 = _v1627(_v1239, _v1626, _v1628);
                    if (((_v1674 >= 0) && _v1633(_v1239, _v1626))) {
                        if ((_v544(_v1050) == _v242)) {
                            bkr_i64 _v1769 = _v671(_v1050);
                            if ((_v1769 == _v178)) {
                                _v426 _v1770 = _v537(_v674(_v1050));
                                bkr_str _v1771 = _v1692(_v1239, _v1770);
                                return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_enum_payload1(", int_to_string(_v1674)), ", (bkr_i64)(intptr_t)("), _v1771), "))");
                            }
                            if ((_v1769 == _v176)) {
                                _v426 _v1772 = _v537(_v674(_v1050));
                                _v426 _v1773 = _v537(_v677(_v1050));
                                if (((_v544(_v1772) == _v242) && (_v544(_v1773) == _v242))) {
                                    _v426 _v1774 = _v537(_v674(_v1772));
                                    _v426 _v1775 = _v537(_v674(_v1773));
                                    bkr_str _v1776 = _v1692(_v1239, _v1774);
                                    bkr_str _v1777 = _v1692(_v1239, _v1775);
                                    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_enum_payload2(", int_to_string(_v1674)), ", (bkr_i64)(intptr_t)("), _v1776), "), (bkr_i64)(intptr_t)("), _v1777), "))");
                                }
                            }
                        }
                    }
                }
            }
        }
        if (((_v349 == _v166) || (_v349 == _v167))) {
            bkr_i64 _v1675 = _v1653(_v1239, _v1050);
            bkr_i64 _v1676 = _v1653(_v1239, _v1051);
            if (((_v1675 == _v306) || (_v1676 == _v306))) {
                bkr_str _v1778 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_str_eq(", _v1692(_v1239, _v1050)), ", "), _v1692(_v1239, _v1051)), ")");
                if ((_v349 == _v167)) {
                    return bkr_str_concat(bkr_str_concat("(!", _v1778), ")");
                }
                return _v1778;
            }
        }
        if ((_v349 == _v161)) {
            bkr_i64 _v1675 = _v1653(_v1239, _v1050);
            bkr_i64 _v1676 = _v1653(_v1239, _v1051);
            if (((_v1675 == _v306) || (_v1676 == _v306))) {
                return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_str_concat(", _v1692(_v1239, _v1050)), ", "), _v1692(_v1239, _v1051)), ")");
            }
        }
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("(", _v1692(_v1239, _v1050)), _v1638(_v349)), _v1692(_v1239, _v1051)), ")");
    }
    if ((_v1670 == _v250)) {
        _v426 _v1056 = _v537(_v733(_v541));
        _v426 _v1403 = _v537(_v736(_v541));
        _v426 _v1404 = _v537(_v739(_v541));
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("(", _v1692(_v1239, _v1056)), " ? "), _v1692(_v1239, _v1403)), " : "), _v1692(_v1239, _v1404)), ")");
    }
    if ((_v1670 == _v240)) {
        _v426 _v1366 = _v537(_v777(_v541));
        bkr_str _v1779 = _v1604(_v1239, "_bkr_try");
        bkr_str _v1780 = _v1692(_v1239, _v1366);
        bkr_i64 _v1546 = _v1597(_v1239);
        bkr_i64 _v1781 = vec_len(_v1546);
        bkr_str _v1782 = "";
        if ((_v1781 > 0)) {
            _v1531 _v1783 = _v1535("", _v1561(_v1239));
            bkr_i64 _v1784 = (_v1781 - 1);
            while ((_v1784 >= 0)) {
                _v1785(_v1783, _v549(vec_get(_v1546, _v1784)));
                _v1784 = (_v1784 - 1);
            }
            bkr_i64 _v1536 = _v1554(_v1783);
            bkr_i64 _v1786 = 0;
            while ((_v1786 < vec_len(_v1536))) {
                _v1782 = bkr_str_concat(bkr_str_concat(_v1782, " "), vec_get(_v1536, _v1786));
                _v1786 = (_v1786 + 1);
            }
        }
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("({ bkr_i64 ", _v1779), " = "), _v1780), "; if (bkr_try_is_err("), _v1779), ")) {"), _v1782), " return "), _v1779), "; } bkr_try_unwrap("), _v1779), "); })");
    }
    if ((_v1670 == _v241)) {
        _v426 _v1678 = _v537(_v781(_v541));
        _v346 _v1435 = _v516(_v782(_v541));
        bkr_i64 _v1787 = _v529(_v1435);
        bkr_str _v1700 = _v1634(_v1787);
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("((", _v1700), ")("), _v1692(_v1239, _v1678)), "))");
    }
    if ((_v1670 == _v243)) {
        bkr_i64 _v349 = _v681(_v541);
        _v426 _v1031 = _v537(_v684(_v541));
        if ((_v349 == _v174)) {
            return bkr_str_concat(bkr_str_concat("(!", _v1692(_v1239, _v1031)), ")");
        }
        if ((_v349 == _v162)) {
            return bkr_str_concat(bkr_str_concat("(-", _v1692(_v1239, _v1031)), ")");
        }
        return _v1692(_v1239, _v1031);
    }
    if ((_v1670 == _v258)) {
        return _v1736(_v1239, _v541);
    }
    if ((_v1670 == _v261)) {
        _v426 _v1021 = _v694(_v541);
        bkr_i64 _v1503 = (-1);
        if ((_v544(_v1021) == _v245)) {
            _v1503 = _v1596(_v1239, _v662(_v1021));
        }
        bkr_i64 _v425 = _v1561(_v1239);
        bkr_str _v1681 = "";
        if ((_v1503 >= 0)) {
            _v1681 = _v1625(_v425, _v1503);
        }
        bkr_str _v1682 = _v1625(_v425, _v696(_v541));
        bkr_str _v1424 = bkr_str_concat(bkr_str_concat(_v1681, "::"), _v1682);
        bkr_i64 _v1683 = _v1562(_v1239, _v1424);
        bkr_str _v1788 = _v1637(_v1239, _v1683);
        bkr_str _v1789 = _v1692(_v1239, _v1021);
        _v434 _v1015 = _v698(_v541);
        bkr_i64 _v1790 = _v906(_v1015);
        bkr_str _v1791 = _v1789;
        bkr_i64 _v1629 = 0;
        while ((_v1629 < _v1790)) {
            _v1791 = bkr_str_concat(bkr_str_concat(_v1791, ", "), _v1692(_v1239, _v537(_v909(_v1015, _v1629))));
            _v1629 = (_v1629 + 1);
        }
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1788, "("), _v1791), ")");
    }
    if ((_v1670 == _v244)) {
        bkr_i64 _v355 = _v688(_v541);
        _v434 _v1015 = _v691(_v541);
        bkr_i64 _v1790 = _v906(_v1015);
        if (_v1660(_v1239, _v355)) {
            bkr_str _v1792 = _v1637(_v1239, _v355);
            bkr_str _v1193 = bkr_str_concat(bkr_str_concat("(", _v1792), "){");
            bkr_i64 _v1168 = 0;
            while ((_v1168 < _v1790)) {
                if ((_v1168 > 0)) {
                    _v1193 = bkr_str_concat(_v1193, ", ");
                }
                _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, "."), _v1637(_v1239, _v1562(_v1239, int_to_string(_v1168)))), " = "), _v1692(_v1239, _v537(_v909(_v1015, _v1168))));
                _v1168 = (_v1168 + 1);
            }
            return bkr_str_concat(_v1193, "}");
        }
        bkr_i64 _v425 = _v1561(_v1239);
        bkr_str _v1640 = _v1625(_v425, _v355);
        if ((bkr_str_eq(_v1640, "panic") && (_v1790 == 1))) {
            bkr_str _v1793 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_panic((bkr_str)(intptr_t)(", _v1793), "))");
        }
        if ((bkr_str_eq(_v1640, "assert") && (_v1790 == 1))) {
            bkr_str _v1794 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            bkr_str _v1795 = from_char_code(34);
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_assert(", _v1794), ", "), _v1795), "assertion failed"), _v1795), ")");
        }
        if ((bkr_str_eq(_v1640, "assert") && (_v1790 == 2))) {
            bkr_str _v1797 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            bkr_str _v1798 = _v1692(_v1239, _v537(_v909(_v1015, 1)));
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_assert(", _v1797), ", (bkr_str)(intptr_t)("), _v1798), "))");
        }
        if ((bkr_str_eq(_v1640, "Some") && (_v1790 == 1))) {
            return bkr_str_concat(bkr_str_concat("(((", _v1692(_v1239, _v537(_v909(_v1015, 0)))), ") << 1) | 1)");
        }
        if ((bkr_str_eq(_v1640, "len") && (_v1790 == 1))) {
            _v426 _v1799 = _v537(_v909(_v1015, 0));
            bkr_i64 _v1800 = _v544(_v1799);
            if ((_v1800 == _v245)) {
                bkr_i64 _v1691 = _v1613(_v1239, _v662(_v1799));
                if ((_v1691 >= 0)) {
                    return int_to_string(_v1691);
                }
            }
            if ((_v1800 == _v252)) {
                _v434 _v994 = _v701(_v1799);
                return int_to_string(_v906(_v994));
            }
            if ((_v1800 == _v239)) {
                return int_to_string(_v706(_v1799));
            }
            return bkr_str_concat(bkr_str_concat("bkr_len((bkr_str)(intptr_t)(", _v1692(_v1239, _v1799)), "))");
        }
        if ((bkr_str_eq(_v1640, "strlen") && (_v1790 == 1))) {
            _v426 _v1801 = _v537(_v909(_v1015, 0));
            return bkr_str_concat(bkr_str_concat("bkr_len((bkr_str)(intptr_t)(", _v1692(_v1239, _v1801)), "))");
        }
        if (((bkr_str_eq(_v1640, "result_ok") || bkr_str_eq(_v1640, "Ok")) && (_v1790 == 1))) {
            bkr_str _v1802 = _v1746(_v1239, _v537(_v909(_v1015, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_result_ok(", _v1802), ")");
        }
        if (((bkr_str_eq(_v1640, "result_err") || bkr_str_eq(_v1640, "Err")) && (_v1790 == 1))) {
            bkr_str _v1803 = _v1746(_v1239, _v537(_v909(_v1015, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_result_err(", _v1803), ")");
        }
        if ((bkr_str_eq(_v1640, "hashmap_get_opt") && (_v1790 == 2))) {
            bkr_str _v1804 = _v1746(_v1239, _v537(_v909(_v1015, 0)));
            bkr_str _v1805 = _v1746(_v1239, _v537(_v909(_v1015, 1)));
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_hashmap_get_opt(", _v1804), ", "), _v1805), ")");
        }
        if ((bkr_str_eq(_v1640, "vec_get_opt") && (_v1790 == 2))) {
            bkr_str _v1686 = _v1746(_v1239, _v537(_v909(_v1015, 0)));
            bkr_str _v1806 = _v1746(_v1239, _v537(_v909(_v1015, 1)));
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_vec_get_opt(", _v1686), ", "), _v1806), ")");
        }
        if ((bkr_str_eq(_v1640, "vec_pop_opt") && (_v1790 == 1))) {
            bkr_str _v1807 = _v1746(_v1239, _v537(_v909(_v1015, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_vec_pop_opt(", _v1807), ")");
        }
        if ((bkr_str_eq(_v1640, "vec_contains") && (_v1790 == 2))) {
            bkr_str _v1808 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            _v426 _v1809 = _v537(_v909(_v1015, 1));
            bkr_i64 _v1810 = _v1653(_v1239, _v1809);
            bkr_str _v1811 = _v1746(_v1239, _v1809);
            if ((_v1810 == _v306)) {
                return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("vec_contains_str(", _v1808), ", "), _v1811), ")");
            }
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("vec_contains(", _v1808), ", "), _v1811), ")");
        }
        if ((bkr_str_eq(_v1640, "read_file_result") && (_v1790 == 1))) {
            bkr_str _v1771 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_read_file_result((bkr_str)(intptr_t)(", _v1771), "))");
        }
        if ((bkr_str_eq(_v1640, "write_file_result") && (_v1790 == 2))) {
            bkr_str _v1812 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            bkr_str _v1813 = _v1692(_v1239, _v537(_v909(_v1015, 1)));
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_write_file_result((bkr_str)(intptr_t)(", _v1812), "), (bkr_str)(intptr_t)("), _v1813), "))");
        }
        if ((bkr_str_eq(_v1640, "parse_int_result") && (_v1790 == 1))) {
            bkr_str _v1814 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_parse_int_result((bkr_str)(intptr_t)(", _v1814), "))");
        }
        if ((bkr_str_eq(_v1640, "str_index_of") && (_v1790 == 2))) {
            bkr_str _v1814 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            bkr_str _v1815 = _v1692(_v1239, _v537(_v909(_v1015, 1)));
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_str_index_of((bkr_str)(intptr_t)(", _v1814), "), (bkr_str)(intptr_t)("), _v1815), "))");
        }
        if ((bkr_str_eq(_v1640, "str_replace") && (_v1790 == 3))) {
            bkr_str _v1814 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            bkr_str _v1816 = _v1692(_v1239, _v537(_v909(_v1015, 1)));
            bkr_str _v1817 = _v1692(_v1239, _v537(_v909(_v1015, 2)));
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_str_replace((bkr_str)(intptr_t)(", _v1814), "), (bkr_str)(intptr_t)("), _v1816), "), (bkr_str)(intptr_t)("), _v1817), "))");
        }
        if ((bkr_str_eq(_v1640, "str_split") && (_v1790 == 2))) {
            bkr_str _v1814 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            bkr_str _v1818 = _v1692(_v1239, _v537(_v909(_v1015, 1)));
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_str_split((bkr_str)(intptr_t)(", _v1814), "), (bkr_str)(intptr_t)("), _v1818), "))");
        }
        if ((bkr_str_eq(_v1640, "str_to_upper") && (_v1790 == 1))) {
            bkr_str _v1814 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_str_to_upper((bkr_str)(intptr_t)(", _v1814), "))");
        }
        if ((bkr_str_eq(_v1640, "str_to_lower") && (_v1790 == 1))) {
            bkr_str _v1814 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_str_to_lower((bkr_str)(intptr_t)(", _v1814), "))");
        }
        if ((bkr_str_eq(_v1640, "str_repeat") && (_v1790 == 2))) {
            bkr_str _v1814 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            bkr_str _v1813 = _v1746(_v1239, _v537(_v909(_v1015, 1)));
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_str_repeat((bkr_str)(intptr_t)(", _v1814), "), "), _v1813), ")");
        }
        if ((bkr_str_eq(_v1640, "path_join") && (_v1790 == 2))) {
            bkr_str _v1819 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            bkr_str _v1820 = _v1692(_v1239, _v537(_v909(_v1015, 1)));
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_path_join((bkr_str)(intptr_t)(", _v1819), "), (bkr_str)(intptr_t)("), _v1820), "))");
        }
        if ((bkr_str_eq(_v1640, "path_dir") && (_v1790 == 1))) {
            bkr_str _v1771 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_path_dir((bkr_str)(intptr_t)(", _v1771), "))");
        }
        if ((bkr_str_eq(_v1640, "path_base") && (_v1790 == 1))) {
            bkr_str _v1771 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_path_base((bkr_str)(intptr_t)(", _v1771), "))");
        }
        if ((bkr_str_eq(_v1640, "path_ext") && (_v1790 == 1))) {
            bkr_str _v1771 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_path_ext((bkr_str)(intptr_t)(", _v1771), "))");
        }
        if ((bkr_str_eq(_v1640, "path_is_abs") && (_v1790 == 1))) {
            bkr_str _v1771 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_path_is_abs((bkr_str)(intptr_t)(", _v1771), "))");
        }
        if ((bkr_str_eq(_v1640, "env_var") && (_v1790 == 1))) {
            bkr_str _v1821 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_env_var((bkr_str)(intptr_t)(", _v1821), "))");
        }
        if ((bkr_str_eq(_v1640, "env_get") && (_v1790 == 1))) {
            bkr_str _v1821 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_env_get((bkr_str)(intptr_t)(", _v1821), "))");
        }
        if ((bkr_str_eq(_v1640, "env_set") && (_v1790 == 2))) {
            bkr_str _v1821 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            bkr_str _v1686 = _v1692(_v1239, _v537(_v909(_v1015, 1)));
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_env_set((bkr_str)(intptr_t)(", _v1821), "), (bkr_str)(intptr_t)("), _v1686), "))");
        }
        if ((bkr_str_eq(_v1640, "env_has") && (_v1790 == 1))) {
            bkr_str _v1821 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_env_has((bkr_str)(intptr_t)(", _v1821), "))");
        }
        if ((bkr_str_eq(_v1640, "time_now_ms") && (_v1790 == 0))) {
            return "bkr_time_now_ms()";
        }
        if ((bkr_str_eq(_v1640, "time_now_unix") && (_v1790 == 0))) {
            return "bkr_time_now_unix()";
        }
        if ((bkr_str_eq(_v1640, "runtime_version_major") && (_v1790 == 0))) {
            return "bkr_runtime_version_major()";
        }
        if ((bkr_str_eq(_v1640, "runtime_version_minor") && (_v1790 == 0))) {
            return "bkr_runtime_version_minor()";
        }
        if ((bkr_str_eq(_v1640, "runtime_version_patch") && (_v1790 == 0))) {
            return "bkr_runtime_version_patch()";
        }
        if ((bkr_str_eq(_v1640, "runtime_version_str") && (_v1790 == 0))) {
            return "bkr_runtime_version_str()";
        }
        if ((bkr_str_eq(_v1640, "vec_push") && (_v1790 == 2))) {
            bkr_str _v1808 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            bkr_str _v387 = _v1746(_v1239, _v537(_v909(_v1015, 1)));
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("vec_push(", _v1808), ", "), _v387), ")");
        }
        if ((bkr_str_eq(_v1640, "vec_set") && (_v1790 == 3))) {
            bkr_str _v1822 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            bkr_str _v1035 = _v1692(_v1239, _v537(_v909(_v1015, 1)));
            bkr_str _v1823 = _v1746(_v1239, _v537(_v909(_v1015, 2)));
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("vec_set(", _v1822), ", "), _v1035), ", "), _v1823), ")");
        }
        if ((bkr_str_eq(_v1640, "hashmap_insert") && (_v1790 == 3))) {
            bkr_str _v1824 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            _v426 _v1825 = _v537(_v909(_v1015, 1));
            bkr_i64 _v1363 = _v1653(_v1239, _v1825);
            bkr_str _v1826 = _v1746(_v1239, _v1825);
            bkr_str _v1827 = _v1746(_v1239, _v537(_v909(_v1015, 2)));
            if ((_v1363 == _v306)) {
                return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("hashmap_insert_str(", _v1824), ", "), _v1826), ", "), _v1827), ")");
            }
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("hashmap_insert(", _v1824), ", "), _v1826), ", "), _v1827), ")");
        }
        if ((bkr_str_eq(_v1640, "hashmap_get") && (_v1790 == 2))) {
            bkr_str _v1824 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            _v426 _v1825 = _v537(_v909(_v1015, 1));
            bkr_str _v1826 = _v1746(_v1239, _v1825);
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("hashmap_get(", _v1824), ", "), _v1826), ")");
        }
        if ((bkr_str_eq(_v1640, "hashmap_contains") && (_v1790 == 2))) {
            bkr_str _v1824 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            _v426 _v1825 = _v537(_v909(_v1015, 1));
            bkr_str _v1826 = _v1746(_v1239, _v1825);
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("hashmap_contains(", _v1824), ", "), _v1826), ")");
        }
        if ((bkr_str_eq(_v1640, "hashmap_remove") && (_v1790 == 2))) {
            bkr_str _v1824 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            _v426 _v1825 = _v537(_v909(_v1015, 1));
            bkr_str _v1826 = _v1746(_v1239, _v1825);
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("hashmap_remove(", _v1824), ", "), _v1826), ")");
        }
        if ((bkr_str_eq(_v1640, "result_is_ok") && (_v1790 == 1))) {
            bkr_str _v1828 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_result_is_ok(", _v1828), ")");
        }
        if ((bkr_str_eq(_v1640, "result_is_err") && (_v1790 == 1))) {
            bkr_str _v1829 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_result_is_err(", _v1829), ")");
        }
        if ((bkr_str_eq(_v1640, "result_tag") && (_v1790 == 1))) {
            bkr_str _v1830 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_result_tag(", _v1830), ")");
        }
        if ((((bkr_str_eq(_v1640, "result_unwrap") || bkr_str_eq(_v1640, "result_unwrap_err")) || bkr_str_eq(_v1640, "result_value")) && (_v1790 == 1))) {
            bkr_str _v1831 = _v1692(_v1239, _v537(_v909(_v1015, 0)));
            if (bkr_str_eq(_v1640, "result_unwrap")) {
                return bkr_str_concat(bkr_str_concat("bkr_result_unwrap(", _v1831), ")");
            }
            if (bkr_str_eq(_v1640, "result_unwrap_err")) {
                return bkr_str_concat(bkr_str_concat("bkr_result_unwrap_err(", _v1831), ")");
            }
            return bkr_str_concat(bkr_str_concat("bkr_result_value(", _v1831), ")");
        }
        bkr_str _v1348 = _v1637(_v1239, _v355);
        bkr_str _v1193 = "";
        if ((_v1619(_v1239, _v355) == _v315)) {
            _v1193 = bkr_str_concat(bkr_str_concat("((bkr_i64 (*)())", _v1348), ")(");
        } else {
            _v1193 = bkr_str_concat(_v1348, "(");
        }
        bkr_i64 _v1168 = 0;
        while ((_v1168 < _v1790)) {
            if ((_v1168 > 0)) {
                _v1193 = bkr_str_concat(_v1193, ", ");
            }
            _v1193 = bkr_str_concat(_v1193, _v1692(_v1239, _v537(_v909(_v1015, _v1168))));
            _v1168 = (_v1168 + 1);
        }
        return bkr_str_concat(_v1193, ")");
    }
    return "0";
}

bkr_i64 _v1832(bkr_i64 _v1239, bkr_i64 _v370) {
    _v1785(_v1548(_v1239), _v550(_v370));
    return _v1239;
}

_v1531 _v1785(_v1531 _v1239, _v427 _v553) {
    bkr_i64 _v1670 = _v555(_v553);
    if ((_v1670 == _v228)) {
        bkr_i64 _v355 = _v757(_v553);
        bkr_str _v1348 = _v1637(_v1239, _v355);
        bkr_i64 _v515 = _v760(_v553);
        bkr_i64 _v366 = _v763(_v553);
        if ((_v525(_v515) && (_v1646(_v516(_v515)) == _v308))) {
            bkr_i64 _v953 = _v1648(_v516(_v515));
            bkr_i64 _v1691 = _v1650(_v516(_v515));
            bkr_str _v1582 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1634(_v953), " "), _v1348), "["), int_to_string(_v1691)), "]");
            if (_v525(_v366)) {
                _v1582 = bkr_str_concat(bkr_str_concat(_v1582, " = "), _v1692(_v1239, _v537(_v366)));
            }
            _v1583(_v1239, bkr_str_concat(_v1582, ";"));
            _v1592(_v1239, _v355, _v953);
            _v1611(_v1239, _v355, _v953, _v1691);
            return _v1239;
        }
        if ((_v523(_v515) && _v525(_v366))) {
            _v426 _v1693 = _v537(_v366);
            bkr_i64 _v1694 = _v544(_v1693);
            if ((_v1694 == _v252)) {
                _v434 _v994 = _v701(_v1693);
                bkr_i64 _v1691 = _v906(_v994);
                if ((_v1691 > 0)) {
                    bkr_i64 _v953 = _v1653(_v1239, _v537(_v909(_v994, 0)));
                    bkr_str _v1582 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1634(_v953), " "), _v1348), "["), int_to_string(_v1691)), "] = "), _v1692(_v1239, _v1693));
                    _v1583(_v1239, bkr_str_concat(_v1582, ";"));
                    _v1592(_v1239, _v355, _v953);
                    _v1611(_v1239, _v355, _v953, _v1691);
                    return _v1239;
                }
            } else {
                if ((_v1694 == _v239)) {
                    bkr_i64 _v1691 = _v706(_v1693);
                    bkr_i64 _v953 = _v1653(_v1239, _v704(_v1693));
                    bkr_str _v1582 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1634(_v953), " "), _v1348), "["), int_to_string(_v1691)), "] = "), _v1692(_v1239, _v1693));
                    _v1583(_v1239, bkr_str_concat(_v1582, ";"));
                    _v1592(_v1239, _v355, _v953);
                    _v1611(_v1239, _v355, _v953, _v1691);
                    return _v1239;
                }
            }
        }
        bkr_i64 _v319 = _v303;
        bkr_i64 _v1503 = (-1);
        if (_v525(_v515)) {
            _v319 = _v1646(_v516(_v515));
            if ((_v319 == _v309)) {
                _v1503 = _v531(_v516(_v515));
            }
            if ((_v319 == _v310)) {
                bkr_i64 _v1687 = _v532(_v516(_v515));
                if (((_v1687 != _v316) && (_v1687 != 0))) {
                    _v1611(_v1239, _v355, _v1687, 0);
                }
            }
        } else {
            if (_v525(_v366)) {
                bkr_i64 _v1695 = _v1656(_v1239, _v366);
                if (((_v1695 != _v316) && (_v1695 != _v307))) {
                    _v319 = _v1695;
                }
                _v426 _v1693 = _v537(_v366);
                if ((_v544(_v1693) == _v257)) {
                    _v319 = _v309;
                    _v1503 = _v724(_v1693);
                } else {
                    if ((_v544(_v1693) == _v244)) {
                        bkr_i64 _v1696 = _v688(_v1693);
                        if (_v1660(_v1239, _v1696)) {
                            _v319 = _v309;
                            _v1503 = _v1696;
                        } else {
                            _v346 _v1679 = _v1668(_v1239, _v1696);
                            if ((_v524(_v1679) && (_v529(_v1679) == _v309))) {
                                _v319 = _v309;
                                _v1503 = _v531(_v1679);
                            }
                        }
                    } else {
                        if ((_v544(_v1693) == _v245)) {
                            bkr_i64 _v1697 = _v1596(_v1239, _v1024(_v1693));
                            if ((_v1697 >= 0)) {
                                _v319 = _v309;
                                _v1503 = _v1697;
                            }
                        } else {
                            if ((_v544(_v1693) == _v227)) {
                                _v429 _v582 = _v578(_v540(_v1693));
                                bkr_i64 _v399 = _v589(_v582);
                                if ((_v399 > 0)) {
                                    _v427 _v1671 = _v1107(_v582, (_v399 - 1));
                                    if ((_v555(_v1671) == _v232)) {
                                        _v426 _v1698 = _v537(_v860(_v1671));
                                        bkr_i64 _v1699 = _v544(_v1698);
                                        if ((_v1699 == _v257)) {
                                            _v319 = _v309;
                                            _v1503 = _v724(_v1698);
                                        } else {
                                            if ((_v1699 == _v245)) {
                                                bkr_i64 _v1697 = _v1596(_v1239, _v662(_v1698));
                                                if ((_v1697 >= 0)) {
                                                    _v319 = _v309;
                                                    _v1503 = _v1697;
                                                }
                                            } else {
                                                if (((_v1699 == _v244) && _v1660(_v1239, _v688(_v1698)))) {
                                                    _v319 = _v309;
                                                    _v1503 = _v688(_v1698);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        bkr_str _v1700 = _v1634(_v319);
        if (_v525(_v515)) {
            _v1700 = _v1636(_v1239, _v516(_v515));
        } else {
            if (((_v319 == _v309) && (_v1503 >= 0))) {
                if (_v1623(_v1239, _v1503)) {
                    _v1700 = "bkr_i64";
                } else {
                    _v1700 = _v1637(_v1239, _v1503);
                }
            }
        }
        if (bkr_str_eq(_v1700, "void")) {
            _v1700 = "bkr_unit";
        }
        bkr_str _v1582 = bkr_str_concat(bkr_str_concat(_v1700, " "), _v1348);
        if (_v525(_v366)) {
            _v1582 = bkr_str_concat(bkr_str_concat(_v1582, " = "), _v1701(_v1239, _v515, _v537(_v366)));
        }
        _v1583(_v1239, bkr_str_concat(_v1582, ";"));
        if ((_v1503 >= 0)) {
            if (_v1623(_v1239, _v1503)) {
                _v1592(_v1239, _v355, _v303);
            } else {
                _v1594(_v1239, _v355, _v319, _v1503);
            }
        } else {
            _v1592(_v1239, _v355, _v319);
        }
        return _v1239;
    }
    if ((_v1670 == _v238)) {
        bkr_i64 _v1833 = _v772(_v553);
        _v1598(_v1239, _v1833);
        return _v1239;
    }
    if ((_v1670 == _v229)) {
        bkr_i64 _v368 = _v768(_v553);
        bkr_i64 _v1546 = _v1597(_v1239);
        bkr_i64 _v1781 = vec_len(_v1546);
        bkr_str _v1834 = _v1600(_v1239);
        if (bkr_str_eq(_v1834, "void")) {
            if (_v525(_v368)) {
                _v426 _v541 = _v537(_v368);
                bkr_i64 _v1835 = _v544(_v541);
                if ((_v1835 != _v246)) {
                    _v1583(_v1239, bkr_str_concat(_v1692(_v1239, _v541), ";"));
                }
            }
            bkr_i64 _v1784 = (_v1781 - 1);
            while ((_v1784 >= 0)) {
                _v1785(_v1239, _v549(vec_get(_v1546, _v1784)));
                _v1784 = (_v1784 - 1);
            }
            _v1583(_v1239, "return;");
            return _v1239;
        }
        if ((_v1781 > 0)) {
            if (_v525(_v368)) {
                bkr_str _v1836 = _v1604(_v1239, "_bkr_ret");
                bkr_str _v1142 = _v1600(_v1239);
                if ((bkr_str_eq(_v1142, "") || bkr_str_eq(_v1142, "void"))) {
                    _v1142 = "bkr_i64";
                }
                _v1583(_v1239, bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1142, " "), _v1836), " = "), _v1692(_v1239, _v537(_v368))), ";"));
                bkr_i64 _v1784 = (_v1781 - 1);
                while ((_v1784 >= 0)) {
                    _v1785(_v1239, _v549(vec_get(_v1546, _v1784)));
                    _v1784 = (_v1784 - 1);
                }
                _v1583(_v1239, bkr_str_concat(bkr_str_concat("return ", _v1836), ";"));
            } else {
                bkr_i64 _v1784 = (_v1781 - 1);
                while ((_v1784 >= 0)) {
                    _v1785(_v1239, _v549(vec_get(_v1546, _v1784)));
                    _v1784 = (_v1784 - 1);
                }
                _v1583(_v1239, "return;");
            }
        } else {
            if (_v525(_v368)) {
                _v1583(_v1239, bkr_str_concat(bkr_str_concat("return ", _v1692(_v1239, _v537(_v368))), ";"));
            } else {
                _v1583(_v1239, "return;");
            }
        }
        return _v1239;
    }
    if ((_v1670 == _v230)) {
        _v426 _v1056 = _v537(_v827(_v553));
        _v429 _v1116 = _v829(_v553);
        bkr_i64 _v377 = _v832(_v553);
        _v1583(_v1239, bkr_str_concat(bkr_str_concat("if (", _v1692(_v1239, _v1056)), ") {"));
        _v1586(_v1239);
        _v1837(_v1239, _v1116);
        _v1588(_v1239);
        if (_v525(_v377)) {
            _v1583(_v1239, "} else {");
            _v1586(_v1239);
            _v1837(_v1239, _v578(_v377));
            _v1588(_v1239);
        }
        _v1583(_v1239, "}");
        return _v1239;
    }
    if ((_v1670 == _v231)) {
        _v426 _v1056 = _v537(_v849(_v553));
        _v429 _v1123 = _v851(_v553);
        _v1583(_v1239, bkr_str_concat(bkr_str_concat("while (", _v1692(_v1239, _v1056)), ") {"));
        _v1586(_v1239);
        _v1837(_v1239, _v1123);
        _v1588(_v1239);
        _v1583(_v1239, "}");
        return _v1239;
    }
    if ((_v1670 == _v236)) {
        bkr_i64 _v355 = _v834(_v553);
        bkr_str _v1348 = _v1637(_v1239, _v355);
        _v426 _v1838 = _v537(_v837(_v553));
        _v426 _v1839 = _v537(_v840(_v553));
        bkr_i64 _v383 = _v842(_v553);
        _v429 _v1123 = _v844(_v553);
        bkr_str _v1778 = "<";
        if ((_v383 != 0)) {
            _v1778 = "<=";
        }
        _v1583(_v1239, bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("for (bkr_i64 ", _v1348), " = "), _v1692(_v1239, _v1838)), "; "), _v1348), " "), _v1778), " "), _v1692(_v1239, _v1839)), "; "), _v1348), " = "), _v1348), " + 1) {"));
        _v1586(_v1239);
        _v1592(_v1239, _v355, _v303);
        _v1837(_v1239, _v1123);
        _v1588(_v1239);
        _v1583(_v1239, "}");
        return _v1239;
    }
    if ((_v1670 == _v237)) {
        _v429 _v1123 = _v846(_v553);
        _v1583(_v1239, "while (BKR_TRUE) {");
        _v1586(_v1239);
        _v1837(_v1239, _v1123);
        _v1588(_v1239);
        _v1583(_v1239, "}");
        return _v1239;
    }
    if ((_v1670 == _v233)) {
        _v426 _v1094 = _v537(_v854(_v553));
        _v426 _v1095 = _v537(_v857(_v553));
        _v1583(_v1239, bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1692(_v1239, _v1094), " = "), _v1692(_v1239, _v1095)), ";"));
        return _v1239;
    }
    if ((_v1670 == _v232)) {
        _v426 _v541 = _v537(_v860(_v553));
        _v1583(_v1239, bkr_str_concat(_v1692(_v1239, _v541), ";"));
        return _v1239;
    }
    if ((_v1670 == _v234)) {
        _v1583(_v1239, "break;");
        return _v1239;
    }
    if ((_v1670 == _v235)) {
        _v1583(_v1239, "continue;");
        return _v1239;
    }
    if ((_v1670 == _v227)) {
        _v1837(_v1239, _v578(_v552(_v553)));
        return _v1239;
    }
    return _v1239;
}

bkr_str _v1750(bkr_str _v1640) {
    bkr_str _v1795 = from_char_code(34);
    bkr_str _v1840 = from_char_code(92);
    bkr_str _v1841 = "";
    bkr_i64 _v1168 = 0;
    while ((_v1168 < bkr_len((bkr_str)(intptr_t)(_v1640)))) {
        bkr_str _v1842 = char_at(_v1640, _v1168);
        bkr_i64 _v1844 = char_code(_v1842);
        if ((_v1844 == 10)) {
            _v1841 = bkr_str_concat(bkr_str_concat(_v1841, _v1840), "n");
        } else {
            if ((_v1844 == 13)) {
                _v1841 = bkr_str_concat(bkr_str_concat(_v1841, _v1840), "r");
            } else {
                if ((_v1844 == 9)) {
                    _v1841 = bkr_str_concat(bkr_str_concat(_v1841, _v1840), "t");
                } else {
                    if ((_v1844 == 34)) {
                        _v1841 = bkr_str_concat(bkr_str_concat(_v1841, _v1840), _v1795);
                    } else {
                        if ((_v1844 == 92)) {
                            _v1841 = bkr_str_concat(bkr_str_concat(_v1841, _v1840), _v1840);
                        } else {
                            _v1841 = bkr_str_concat(_v1841, _v1842);
                        }
                    }
                }
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(bkr_str_concat(_v1795, _v1841), _v1795);
}

bkr_i64 _v1846(bkr_i64 _v1239, bkr_i64 _v577) {
    _v1837(_v1548(_v1239), _v579(_v577));
    return _v1239;
}

_v1531 _v1837(_v1531 _v1239, _v429 _v582) {
    bkr_i64 _v1168 = 0;
    bkr_i64 _v399 = _v589(_v582);
    while ((_v1168 < _v399)) {
        _v1785(_v1239, _v1107(_v582, _v1168));
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_str _v1847(bkr_i64 _v1239, bkr_i64 _v929) {
    return _v1848(_v1548(_v1239), _v559(_v929));
}

bkr_str _v1848(_v1531 _v1239, _v428 _v1514) {
    bkr_str _v1348 = _v1637(_v1239, _v868(_v1514));
    bkr_i64 _v1849 = _v874(_v1514);
    bkr_str _v1142 = "void";
    if (_v525(_v1849)) {
        _v1142 = _v1636(_v1239, _v516(_v1849));
    }
    bkr_str _v1850 = "";
    _v434 _v1141 = _v871(_v1514);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1141))) {
        _v341 _v1507 = _v912(_v1141, _v1168);
        bkr_str _v1851 = _v1637(_v1239, _v862(_v1507));
        bkr_str _v1852 = _v1636(_v1239, _v866(_v1507));
        if ((_v1168 > 0)) {
            _v1850 = bkr_str_concat(_v1850, ", ");
        }
        _v1850 = bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1850, _v1852), " "), _v1851);
        _v1168 = (_v1168 + 1);
    }
    if (bkr_str_eq(_v1850, "")) {
        _v1850 = "void";
    }
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1142, " "), _v1348), "("), _v1850), ")");
}

bkr_i64 _v1853(bkr_i64 _v1239, bkr_i64 _v929) {
    _v1854(_v1548(_v1239), _v559(_v929));
    return _v1239;
}

_v1531 _v1854(_v1531 _v1239, _v428 _v1514) {
    _v1583(_v1239, bkr_str_concat(_v1848(_v1239, _v1514), ";"));
    return _v1239;
}

bkr_i64 _v1855(bkr_i64 _v1239, bkr_i64 _v929) {
    _v1856(_v1548(_v1239), _v559(_v929));
    return _v1239;
}

_v1531 _v1856(_v1531 _v1239, _v428 _v1514) {
    _v1590(_v1239);
    bkr_i64 _v1849 = _v874(_v1514);
    bkr_str _v1857 = "void";
    if (_v525(_v1849)) {
        _v1857 = _v1636(_v1239, _v516(_v1849));
    }
    _v1601(_v1239, _v1857);
    _v434 _v1141 = _v871(_v1514);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1141))) {
        _v341 _v1507 = _v912(_v1141, _v1168);
        _v346 _v1858 = _v866(_v1507);
        bkr_i64 _v1859 = _v1646(_v1858);
        if ((_v1859 == _v309)) {
            bkr_i64 _v1697 = _v531(_v1858);
            if (_v1623(_v1239, _v1697)) {
                _v1592(_v1239, _v862(_v1507), _v303);
            } else {
                _v1594(_v1239, _v862(_v1507), _v1859, _v1697);
            }
        } else {
            _v1592(_v1239, _v862(_v1507), _v1859);
        }
        if ((_v1859 == _v310)) {
            bkr_i64 _v1687 = _v532(_v1858);
            if (((_v1687 != _v316) && (_v1687 != 0))) {
                _v1611(_v1239, _v862(_v1507), _v1687, 0);
            }
        }
        _v1168 = (_v1168 + 1);
    }
    _v429 _v1123 = _v876(_v1514);
    _v1583(_v1239, bkr_str_concat(_v1848(_v1239, _v1514), " {"));
    _v1586(_v1239);
    _v1837(_v1239, _v1123);
    bkr_i64 _v399 = _v589(_v1123);
    bkr_bool _v1860 = BKR_FALSE;
    if ((_v399 > 0)) {
        _v427 _v1671 = _v1107(_v1123, (_v399 - 1));
        if ((_v555(_v1671) == _v229)) {
            _v1860 = BKR_TRUE;
        }
    }
    bkr_i64 _v1546 = _v1597(_v1239);
    bkr_i64 _v1781 = vec_len(_v1546);
    if (((!_v1860) && (_v1781 > 0))) {
        bkr_i64 _v1784 = (_v1781 - 1);
        while ((_v1784 >= 0)) {
            _v1785(_v1239, _v549(vec_get(_v1546, _v1784)));
            _v1784 = (_v1784 - 1);
        }
    }
    _v1588(_v1239);
    _v1583(_v1239, "}");
    _v1583(_v1239, "");
    return _v1239;
}

bkr_i64 _v1861(bkr_i64 _v1239, bkr_i64 _v1862) {
    _v1863(_v1548(_v1239), _v559(_v1862));
    return _v1239;
}

_v1531 _v1863(_v1531 _v1239, _v428 _v1517) {
    bkr_i64 _v355 = _v878(_v1517);
    bkr_str _v1348 = _v1637(_v1239, _v355);
    bkr_i64 _v515 = _v881(_v1517);
    bkr_i64 _v387 = _v884(_v1517);
    bkr_i64 _v319 = _v303;
    if (_v525(_v515)) {
        _v319 = _v1646(_v516(_v515));
    } else {
        if (_v525(_v387)) {
            bkr_i64 _v1864 = _v1656(_v1239, _v387);
            if (((_v1864 != _v316) && (_v1864 != _v307))) {
                _v319 = _v1864;
            }
        }
    }
    bkr_str _v1700 = _v1634(_v319);
    bkr_str _v1865 = "0";
    if (_v525(_v387)) {
        _v1865 = _v1692(_v1239, _v537(_v387));
    }
    _v1583(_v1239, bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("static const ", _v1700), " "), _v1348), " = "), _v1865), ";"));
    _v1609(_v1239, _v355, _v319);
    return _v1239;
}

bkr_i64 _v1866(bkr_i64 _v1239, bkr_i64 _v932) {
    _v1867(_v1548(_v1239), _v559(_v932));
    return _v1239;
}

_v1531 _v1867(_v1531 _v1239, _v428 _v1523) {
    bkr_str _v1348 = _v1637(_v1239, _v886(_v1523));
    _v1583(_v1239, bkr_str_concat(bkr_str_concat("typedef struct ", _v1348), " {"));
    _v1586(_v1239);
    _v434 _v1158 = _v889(_v1523);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1158))) {
        _v341 _v1432 = _v912(_v1158, _v1168);
        bkr_str _v1044 = _v1637(_v1239, _v891(_v1432));
        _v346 _v1868 = _v895(_v1432);
        if ((_v529(_v1868) == _v308)) {
            bkr_i64 _v953 = _v532(_v1868);
            bkr_i64 _v1691 = _v533(_v1868);
            _v1583(_v1239, bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1634(_v953), " "), _v1044), "["), int_to_string(_v1691)), "];"));
        } else {
            _v1583(_v1239, bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1636(_v1239, _v1868), " "), _v1044), ";"));
        }
        _v1168 = (_v1168 + 1);
    }
    _v1588(_v1239);
    _v1583(_v1239, bkr_str_concat(bkr_str_concat("} ", _v1348), ";"));
    _v1583(_v1239, "");
    return _v1239;
}

bkr_i64 _v1869(bkr_i64 _v1239, bkr_i64 _v0) {
    _v1870(_v1548(_v1239), _v476(_v0));
    return _v1239;
}

_v1531 _v1870(_v1531 _v1239, _v341 _v1530) {
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if ((_v568(_v562) == _v254)) {
            _v1867(_v1239, _v562);
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_i64 _v1871(bkr_i64 _v1239, bkr_i64 _v0) {
    _v1872(_v1548(_v1239), _v476(_v0));
    return _v1239;
}

_v1531 _v1872(_v1531 _v1239, _v341 _v1530) {
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if ((_v568(_v562) == _v224)) {
            bkr_i64 _v1849 = _v874(_v562);
            bkr_i64 _v319 = _v307;
            if (_v525(_v1849)) {
                _v319 = _v1646(_v516(_v1849));
            }
            _v1607(_v1239, _v868(_v562), _v319);
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_i64 _v1873(bkr_i64 _v1239, bkr_i64 _v0) {
    _v1874(_v1548(_v1239), _v476(_v0));
    return _v1239;
}

_v1531 _v1874(_v1531 _v1239, _v341 _v1530) {
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if ((_v568(_v562) == _v249)) {
            _v1863(_v1239, _v562);
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

_v1531 _v1875(_v1531 _v1239, _v341 _v1530) {
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if ((_v568(_v562) == _v260)) {
            bkr_i64 _v355 = _v1177(_v562);
            bkr_i64 _v421 = _v1178(_v562);
            _v346 _v1094 = _v516(_v421);
            bkr_str _v1876 = _v1636(_v1239, _v1094);
            bkr_str _v1877 = _v1637(_v1239, _v355);
            _v1583(_v1239, bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("typedef ", _v1876), " "), _v1877), ";"));
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_i64 _v1878(bkr_i64 _v1239, bkr_i64 _v0) {
    _v1879(_v1548(_v1239), _v476(_v0));
    return _v1239;
}

_v1531 _v1879(_v1531 _v1239, _v341 _v1530) {
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if ((_v568(_v562) == _v224)) {
            _v1854(_v1239, _v562);
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_i64 _v1880(bkr_i64 _v1239, bkr_i64 _v0) {
    _v1881(_v1548(_v1239), _v476(_v0));
    return _v1239;
}

_v1531 _v1881(_v1531 _v1239, _v341 _v1530) {
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if ((_v568(_v562) == _v224)) {
            _v1856(_v1239, _v562);
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_str _v1882(bkr_i64 _v0) {
    return _v1883(_v476(_v0));
}

bkr_str _v1883(_v341 _v1530) {
    bkr_i64 _v425 = _v903(_v1530);
    bkr_str _v1533 = _v1641(_v425, _v663(_v1530));
    _v1531 _v1239 = _v1535(_v1533, _v425);
    _v1549(_v1239, _v507(_v1530));
    _v1583(_v1239, "/* Generated by Bunker Compiler */");
    _v1583(_v1239, "#define BKR_REQUIRED_RUNTIME_ABI_MAJOR 1");
    bkr_str _v1795 = from_char_code(34);
    _v1583(_v1239, bkr_str_concat(bkr_str_concat(bkr_str_concat("#include ", _v1795), "runtime.h"), _v1795));
    _v1583(_v1239, "");
    _v1875(_v1239, _v1530);
    _v1870(_v1239, _v1530);
    _v1872(_v1239, _v1530);
    _v1874(_v1239, _v1530);
    _v1583(_v1239, "");
    _v1879(_v1239, _v1530);
    _v1583(_v1239, "");
    _v1881(_v1239, _v1530);
    bkr_i64 _v424 = _v900(_v1530);
    bkr_str _v1884 = _v1637(_v1239, _v424);
    _v1583(_v1239, "int main(int argc, char** argv) {");
    _v1583(_v1239, "    bkr_init_args(argc, argv);");
    _v1583(_v1239, bkr_str_concat(bkr_str_concat("    return (int)", _v1884), "();"));
    _v1583(_v1239, "}");
    bkr_i64 _v1536 = _v1554(_v1239);
    return join_lines(_v1536);
}

bkr_str _v1886(bkr_str _v1640) {
    bkr_str _v1795 = from_char_code(34);
    bkr_str _v1840 = from_char_code(92);
    bkr_str _v1841 = "";
    bkr_i64 _v1168 = 0;
    bkr_i64 _v1887 = bkr_len((bkr_str)(intptr_t)(_v1640));
    while ((_v1168 < _v1887)) {
        bkr_str _v1842 = char_at(_v1640, _v1168);
        bkr_i64 _v1844 = char_code(_v1842);
        if ((_v1844 == 10)) {
            _v1841 = bkr_str_concat(bkr_str_concat(_v1841, _v1840), "n");
        } else {
            if ((_v1844 == 13)) {
                _v1841 = bkr_str_concat(bkr_str_concat(_v1841, _v1840), "r");
            } else {
                if ((_v1844 == 9)) {
                    _v1841 = bkr_str_concat(bkr_str_concat(_v1841, _v1840), "t");
                } else {
                    if ((_v1844 == 34)) {
                        _v1841 = bkr_str_concat(bkr_str_concat(_v1841, _v1840), _v1795);
                    } else {
                        if ((_v1844 == 92)) {
                            _v1841 = bkr_str_concat(bkr_str_concat(_v1841, _v1840), _v1840);
                        } else {
                            if ((((_v1844 == 47) && (_v1168 > 0)) && (char_code_at(_v1640, (_v1168 - 1)) == 42))) {
                                _v1841 = bkr_str_concat(bkr_str_concat(_v1841, _v1840), _v1842);
                            } else {
                                _v1841 = bkr_str_concat(_v1841, _v1842);
                            }
                        }
                    }
                }
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1841;
}

bkr_str _v1888(bkr_str _v1383) {
    bkr_str _v1795 = from_char_code(34);
    return bkr_str_concat(bkr_str_concat(_v1795, _v1886(_v1383)), _v1795);
}

bkr_str _v1889(bkr_i64 _v1383) {
    return int_to_string(_v1383);
}

bkr_str _v1890(bkr_bool _v1383) {
    if (_v1383) {
        return "true";
    }
    return "false";
}

bkr_str _v1891(void) {
    return "null";
}

bkr_str _v1892(bkr_str _v1826, bkr_str _v1383) {
    bkr_str _v1795 = from_char_code(34);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1795, _v1826), _v1795), ":"), _v1888(_v1383));
}

bkr_str _v1893(bkr_str _v1826, bkr_i64 _v1383) {
    bkr_str _v1795 = from_char_code(34);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1795, _v1826), _v1795), ":"), _v1889(_v1383));
}

bkr_str _v1894(bkr_str _v1826, bkr_bool _v1383) {
    bkr_str _v1795 = from_char_code(34);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1795, _v1826), _v1795), ":"), _v1890(_v1383));
}

bkr_str _v1895(bkr_str _v1826, bkr_str _v1896) {
    bkr_str _v1795 = from_char_code(34);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1795, _v1826), _v1795), ":"), _v1896);
}

_v1897 _v1899(void) {
    bkr_i64 _v573 = vec_new();
    bkr_i64 _v1900 = vec_new();
    return (_v1897){._v1898 = _v573, ._v612 = _v1900};
}

void _v1901(_v1897 _v1902, bkr_str _v1826, bkr_str _v1383) {
    vec_push(_v1902._v1898, ((bkr_i64)(intptr_t)_v1826));
    vec_push(_v1902._v612, ((bkr_i64)(intptr_t)_v1888(_v1383)));
}

void _v1903(_v1897 _v1902, bkr_str _v1826, bkr_i64 _v1383) {
    vec_push(_v1902._v1898, ((bkr_i64)(intptr_t)_v1826));
    vec_push(_v1902._v612, ((bkr_i64)(intptr_t)_v1889(_v1383)));
}

void _v1904(_v1897 _v1902, bkr_str _v1826, bkr_bool _v1383) {
    vec_push(_v1902._v1898, ((bkr_i64)(intptr_t)_v1826));
    vec_push(_v1902._v612, ((bkr_i64)(intptr_t)_v1890(_v1383)));
}

void _v1905(_v1897 _v1902, bkr_str _v1826, bkr_str _v1896) {
    vec_push(_v1902._v1898, ((bkr_i64)(intptr_t)_v1826));
    vec_push(_v1902._v612, ((bkr_i64)(intptr_t)_v1896));
}

bkr_str _v1906(_v1897 _v1902) {
    bkr_str _v1795 = from_char_code(34);
    bkr_str _v1841 = "{";
    bkr_i64 _v399 = vec_len(_v1902._v1898);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v399)) {
        if ((_v1168 > 0)) {
            _v1841 = bkr_str_concat(_v1841, ",");
        }
        bkr_str _v573 = (bkr_str)(intptr_t)(vec_get(_v1902._v1898, _v1168));
        bkr_str _v1900 = (bkr_str)(intptr_t)(vec_get(_v1902._v612, _v1168));
        _v1841 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1841, _v1795), _v573), _v1795), ":"), _v1900);
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(_v1841, "}");
}

_v1908 _v1909(void) {
    bkr_i64 _v1910 = vec_new();
    return (_v1908){._v423 = _v1910};
}

void _v1911(_v1908 _v1912, bkr_str _v1383) {
    vec_push(_v1912._v423, ((bkr_i64)(intptr_t)_v1888(_v1383)));
}

void _v1913(_v1908 _v1912, bkr_i64 _v1383) {
    vec_push(_v1912._v423, ((bkr_i64)(intptr_t)_v1889(_v1383)));
}

void _v1914(_v1908 _v1912, bkr_bool _v1383) {
    vec_push(_v1912._v423, ((bkr_i64)(intptr_t)_v1890(_v1383)));
}

void _v1915(_v1908 _v1912, bkr_str _v1896) {
    vec_push(_v1912._v423, ((bkr_i64)(intptr_t)_v1896));
}

bkr_str _v1916(_v1908 _v1912) {
    bkr_str _v1841 = "[";
    bkr_i64 _v399 = vec_len(_v1912._v423);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v399)) {
        if ((_v1168 > 0)) {
            _v1841 = bkr_str_concat(_v1841, ",");
        }
        bkr_str _v557 = (bkr_str)(intptr_t)(vec_get(_v1912._v423, _v1168));
        _v1841 = bkr_str_concat(_v1841, _v557);
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(_v1841, "]");
}

bkr_i64 _v1917(bkr_str _v1918, bkr_i64 _v1919) {
    bkr_i64 _v1168 = _v1919;
    bkr_i64 _v1887 = bkr_len((bkr_str)(intptr_t)(_v1918));
    while ((_v1168 < _v1887)) {
        bkr_i64 _v1205 = char_code_at(_v1918, _v1168);
        if (((((_v1205 != 32) && (_v1205 != 9)) && (_v1205 != 10)) && (_v1205 != 13))) {
            return _v1168;
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1168;
}

bkr_str _v1920(bkr_str _v1918, bkr_str _v1826) {
    bkr_str _v1795 = from_char_code(34);
    bkr_str _v386 = bkr_str_concat(bkr_str_concat(_v1795, _v1826), _v1795);
    bkr_i64 _v1921 = bkr_str_index_of((bkr_str)(intptr_t)(_v1918), (bkr_str)(intptr_t)(_v386));
    if ((_v1921 < 0)) {
        return "";
    }
    bkr_i64 _v1923 = (_v1921 + bkr_len((bkr_str)(intptr_t)(_v386)));
    bkr_i64 _v1924 = bkr_str_index_of((bkr_str)(intptr_t)(substring(_v1918, _v1923, bkr_len((bkr_str)(intptr_t)(_v1918)))), (bkr_str)(intptr_t)(":"));
    if ((_v1924 < 0)) {
        return "";
    }
    bkr_i64 _v1925 = _v1917(_v1918, ((_v1923 + _v1924) + 1));
    if ((_v1925 >= bkr_len((bkr_str)(intptr_t)(_v1918)))) {
        return "";
    }
    bkr_i64 _v1440 = char_code_at(_v1918, _v1925);
    if ((_v1440 == 34)) {
        bkr_i64 _v1629 = (_v1925 + 1);
        while ((_v1629 < bkr_len((bkr_str)(intptr_t)(_v1918)))) {
            bkr_i64 _v1842 = char_code_at(_v1918, _v1629);
            if (((_v1842 == 34) && (char_code_at(_v1918, (_v1629 - 1)) != 92))) {
                return substring(_v1918, (_v1925 + 1), _v1629);
            }
            _v1629 = (_v1629 + 1);
        }
        return "";
    }
    if ((_v1440 == 123)) {
        bkr_i64 _v1350 = 1;
        bkr_i64 _v1629 = (_v1925 + 1);
        while (((_v1629 < bkr_len((bkr_str)(intptr_t)(_v1918))) && (_v1350 > 0))) {
            bkr_i64 _v1842 = char_code_at(_v1918, _v1629);
            if ((_v1842 == 123)) {
                _v1350 = (_v1350 + 1);
            } else {
                if ((_v1842 == 125)) {
                    _v1350 = (_v1350 - 1);
                }
            }
            _v1629 = (_v1629 + 1);
        }
        return substring(_v1918, _v1925, _v1629);
    }
    if ((_v1440 == 91)) {
        bkr_i64 _v1350 = 1;
        bkr_i64 _v1629 = (_v1925 + 1);
        while (((_v1629 < bkr_len((bkr_str)(intptr_t)(_v1918))) && (_v1350 > 0))) {
            bkr_i64 _v1842 = char_code_at(_v1918, _v1629);
            if ((_v1842 == 91)) {
                _v1350 = (_v1350 + 1);
            } else {
                if ((_v1842 == 93)) {
                    _v1350 = (_v1350 - 1);
                }
            }
            _v1629 = (_v1629 + 1);
        }
        return substring(_v1918, _v1925, _v1629);
    }
    bkr_i64 _v573 = _v1925;
    while ((_v573 < bkr_len((bkr_str)(intptr_t)(_v1918)))) {
        bkr_i64 _v1842 = char_code_at(_v1918, _v573);
        if ((((((((_v1842 == 44) || (_v1842 == 125)) || (_v1842 == 93)) || (_v1842 == 32)) || (_v1842 == 10)) || (_v1842 == 13)) || (_v1842 == 9))) {
            return substring(_v1918, _v1925, _v573);
        }
        _v573 = (_v573 + 1);
    }
    return substring(_v1918, _v1925, bkr_len((bkr_str)(intptr_t)(_v1918)));
}

bkr_str _v1926(bkr_str _v1918, bkr_str _v1826) {
    return _v1920(_v1918, _v1826);
}

bkr_i64 _v1927(bkr_str _v1918, bkr_str _v1826) {
    bkr_str _v1640 = _v1920(_v1918, _v1826);
    if ((bkr_len((bkr_str)(intptr_t)(_v1640)) == 0)) {
        return 0;
    }
    return parse_int(_v1640);
}

bkr_bool _v1928(bkr_str _v1918, bkr_str _v1826) {
    bkr_str _v1640 = _v1920(_v1918, _v1826);
    return bkr_str_eq(_v1640, "true");
}

bkr_bool _v1929(bkr_str _v1918, bkr_str _v1826) {
    bkr_str _v1795 = from_char_code(34);
    bkr_str _v386 = bkr_str_concat(bkr_str_concat(_v1795, _v1826), _v1795);
    return (bkr_str_index_of((bkr_str)(intptr_t)(_v1918), (bkr_str)(intptr_t)(_v386)) >= 0);
}

bkr_i64 _v1930(bkr_str _v1931) {
    bkr_i64 _v396 = vec_new();
    bkr_i64 _v1887 = bkr_len((bkr_str)(intptr_t)(_v1931));
    if ((_v1887 < 2)) {
        return _v396;
    }
    bkr_i64 _v1168 = 0;
    while (((_v1168 < _v1887) && (char_code_at(_v1931, _v1168) != 91))) {
        _v1168 = (_v1168 + 1);
    }
    _v1168 = (_v1168 + 1);
    while ((_v1168 < _v1887)) {
        _v1168 = _v1917(_v1931, _v1168);
        if (((_v1168 >= _v1887) || (char_code_at(_v1931, _v1168) == 93))) {
            break;
        }
        bkr_i64 _v339 = _v1168;
        bkr_i64 _v1440 = char_code_at(_v1931, _v1168);
        if ((_v1440 == 34)) {
            _v1168 = (_v1168 + 1);
            while ((_v1168 < _v1887)) {
                bkr_i64 _v1842 = char_code_at(_v1931, _v1168);
                if (((_v1842 == 34) && (char_code_at(_v1931, (_v1168 - 1)) != 92))) {
                    bkr_str _v1932 = substring(_v1931, (_v339 + 1), _v1168);
                    vec_push(_v396, ((bkr_i64)(intptr_t)_v1932));
                    _v1168 = (_v1168 + 1);
                    break;
                }
                _v1168 = (_v1168 + 1);
            }
        } else {
            if ((_v1440 == 123)) {
                bkr_i64 _v1350 = 1;
                _v1168 = (_v1168 + 1);
                while (((_v1168 < _v1887) && (_v1350 > 0))) {
                    bkr_i64 _v1842 = char_code_at(_v1931, _v1168);
                    if ((_v1842 == 123)) {
                        _v1350 = (_v1350 + 1);
                    } else {
                        if ((_v1842 == 125)) {
                            _v1350 = (_v1350 - 1);
                        }
                    }
                    _v1168 = (_v1168 + 1);
                }
                vec_push(_v396, ((bkr_i64)(intptr_t)substring(_v1931, _v339, _v1168)));
            } else {
                while ((_v1168 < _v1887)) {
                    bkr_i64 _v1842 = char_code_at(_v1931, _v1168);
                    if (((_v1842 == 44) || (_v1842 == 93))) {
                        break;
                    }
                    _v1168 = (_v1168 + 1);
                }
                vec_push(_v396, ((bkr_i64)(intptr_t)substring(_v1931, _v339, _v1168)));
            }
        }
        _v1168 = _v1917(_v1931, _v1168);
        if (((_v1168 < _v1887) && (char_code_at(_v1931, _v1168) == 44))) {
            _v1168 = (_v1168 + 1);
        }
    }
    return _v396;
}

bkr_bool _v1933(_v341 _v1530) {
    return (vec_len(_v903(_v1530)) <= _v273);
}

bkr_str _v1934(bkr_str _v1640) {
    return _v1888(_v1640);
}

bkr_str _v1935(bkr_str _v319, bkr_i64 _v1936, bkr_i64 _v1937, bkr_str _v1938, bkr_str _v1939, bkr_str _v1940) {
    bkr_str _v1941 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("kind", _v319)), _v1941), _v1893("source_start", _v1936)), _v1941), _v1893("source_end", _v1937)), _v1941), _v1892("replacement", _v1938)), _v1941), _v1892("applicability", _v1939)), _v1941), _v1892("confidence", _v1940)), "}");
}

bkr_str _v1942(void) {
    return "[]";
}

bkr_str _v1943(bkr_str _v1944) {
    return bkr_str_concat(bkr_str_concat("[", _v1944), "]");
}

bkr_str _v1945(bkr_i64 _v425, bkr_i64 _v1035) {
    if (((_v1035 >= 0) && (_v1035 < vec_len(_v425)))) {
        return vec_get(_v425, _v1035);
    }
    return "";
}

bkr_i64 _v1946(void) {
    bkr_i64 _v1239 = vec_new();
    return _v1239;
}

bkr_str _v1947(bkr_i64 _v1239) {
    bkr_str _v1193 = "[";
    bkr_i64 _v1168 = 0;
    while ((_v1168 < vec_len(_v1239))) {
        if ((_v1168 > 0)) {
            _v1193 = bkr_str_concat(_v1193, ",");
        }
        bkr_str _v1948 = (bkr_str)(intptr_t)(vec_get(_v1239, _v1168));
        _v1193 = bkr_str_concat(_v1193, _v1948);
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_i64 _v1949(bkr_i64 _v1239) {
    return vec_len(_v1239);
}

bkr_i64 _v1950(bkr_i64 _v1239, bkr_str _v1948) {
    vec_push(_v1239, ((bkr_i64)(intptr_t)_v1948));
    return _v1239;
}

bkr_bool _v1951(bkr_i64 _v612, bkr_i64 _v387) {
    bkr_i64 _v1168 = 0;
    while ((_v1168 < vec_len(_v612))) {
        if ((vec_get(_v612, _v1168) == _v387)) {
            return BKR_TRUE;
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_FALSE;
}

bkr_i64 _v1952(void) {
    bkr_i64 _v612 = vec_new();
    return _v612;
}

bkr_i64 _v1953(bkr_i64 _v612) {
    bkr_i64 _v1193 = vec_new();
    bkr_i64 _v1168 = 0;
    while ((_v1168 < vec_len(_v612))) {
        bkr_i64 _v1954 = vec_get(_v612, _v1168);
        vec_push(_v1193, _v1954);
        _v1168 = (_v1168 + 1);
    }
    return _v1193;
}

bkr_i64 _v1955(bkr_i64 _v612, bkr_i64 _v387) {
    bkr_i64 _v1193 = _v1953(_v612);
    vec_push(_v1193, _v387);
    return _v1193;
}

bkr_i64 _v1956(bkr_str _v1209) {
    bkr_i64 _v399 = 1;
    bkr_i64 _v1168 = 0;
    while ((_v1168 < bkr_len((bkr_str)(intptr_t)(_v1209)))) {
        if ((char_code_at(_v1209, _v1168) == 10)) {
            _v399 = (_v399 + 1);
        }
        _v1168 = (_v1168 + 1);
    }
    return _v399;
}

bkr_i64 _v1957(bkr_i64 _v557) {
    return _v1958(_v559(_v557));
}

bkr_i64 _v1958(_v428 _v562) {
    bkr_i64 _v319 = _v568(_v562);
    if ((_v319 == _v224)) {
        return _v868(_v562);
    }
    if ((_v319 == _v249)) {
        return _v878(_v562);
    }
    if ((_v319 == _v254)) {
        return _v886(_v562);
    }
    if ((_v319 == _v259)) {
        return _v1164(_v562);
    }
    if ((_v319 == _v260)) {
        return _v1177(_v562);
    }
    return (-1);
}

bkr_i64 _v1959(bkr_i64 _v557) {
    return _v1960(_v559(_v557));
}

bkr_i64 _v1960(_v428 _v562) {
    if ((_v568(_v562) == _v224)) {
        return _v906(_v871(_v562));
    }
    return 0;
}

bkr_i64 _v1961(bkr_i64 _v557) {
    return _v1962(_v559(_v557));
}

bkr_i64 _v1962(_v428 _v562) {
    if ((_v568(_v562) == _v254)) {
        return _v906(_v889(_v562));
    }
    return 0;
}

bkr_i64 _v1963(bkr_i64 _v557) {
    return _v1964(_v559(_v557));
}

bkr_i64 _v1964(_v428 _v562) {
    if ((_v568(_v562) == _v224)) {
        return _v589(_v876(_v562));
    }
    return 0;
}

bkr_str _v1965(bkr_i64 _v425, bkr_i64 _v557) {
    return _v1966(_v425, _v559(_v557));
}

bkr_str _v1966(bkr_i64 _v425, _v428 _v562) {
    _v341 _v1967 = _v587(_v562);
    bkr_str _v1941 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("kind", _v318(_v568(_v562)))), _v1941), _v1892("category", _v329(_v331(_v568(_v562))))), _v1941), _v1892("name", _v1945(_v425, _v1958(_v562)))), _v1941), _v1893("source_start", _v511(_v1967))), _v1941), _v1893("source_end", _v512(_v1967))), _v1941), _v1894("span_known", ((_v511(_v1967) != _v268) && (_v512(_v1967) != _v268)))), _v1941), _v1893("param_count", _v1960(_v562))), _v1941), _v1893("field_count", _v1962(_v562))), _v1941), _v1893("statement_count", _v1964(_v562))), "}");
}

bkr_i64 _v1968(bkr_i64 _v423, bkr_i64 _v319) {
    return _v1969(_v604(_v423), _v319);
}

bkr_i64 _v1969(_v434 _v1183, bkr_i64 _v319) {
    bkr_i64 _v399 = 0;
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v341 _v562 = _v912(_v1183, _v1168);
        if ((_v509(_v562) == _v319)) {
            _v399 = (_v399 + 1);
        }
        _v1168 = (_v1168 + 1);
    }
    return _v399;
}

bkr_str _v1970(bkr_i64 _v0) {
    _v341 _v1530 = _v476(_v0);
    return _v1971(_v903(_v1530), _v898(_v1530));
}

bkr_str _v1971(bkr_i64 _v425, _v434 _v1183) {
    bkr_str _v1193 = "[";
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        if ((_v1168 > 0)) {
            _v1193 = bkr_str_concat(_v1193, ",");
        }
        _v1193 = bkr_str_concat(_v1193, _v1966(_v425, _v913(_v1183, _v1168)));
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v1972(bkr_i64 _v425, bkr_i64 _v605) {
    return _v1973(_v425, _v604(_v605));
}

bkr_str _v1973(bkr_i64 _v425, _v434 _v607) {
    bkr_str _v1193 = "[";
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v607))) {
        if ((_v1168 > 0)) {
            _v1193 = bkr_str_concat(_v1193, ",");
        }
        _v1193 = bkr_str_concat(_v1193, _v1974(_v425, _v912(_v607, _v1168)));
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v1975(bkr_i64 _v425, bkr_i64 _v1976) {
    if (_v523(_v1976)) {
        return "null";
    }
    return _v1974(_v425, _v513(_v1976));
}

bkr_str _v1977(bkr_i64 _v425, bkr_i64 _v577) {
    return _v1978(_v425, _v579(_v577));
}

bkr_str _v1978(bkr_i64 _v425, _v429 _v582) {
    bkr_str _v1193 = "[";
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v589(_v582))) {
        if ((_v1168 > 0)) {
            _v1193 = bkr_str_concat(_v1193, ",");
        }
        _v1193 = bkr_str_concat(_v1193, _v1974(_v425, _v586(_v1107(_v582, _v1168))));
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v1979(bkr_i64 _v425, bkr_i64 _v463) {
    return _v1980(_v425, _v592(_v463));
}

bkr_str _v1980(bkr_i64 _v425, _v433 _v472) {
    bkr_str _v1941 = ",";
    bkr_i64 _v319 = _v596(_v472);
    bkr_i64 _v387 = _v597(_v472);
    bkr_str _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("kind", _v328(_v319))), _v1941), _v1893("source_start", _v601(_v472))), _v1941), _v1893("source_end", _v602(_v472))), _v1941), _v1894("span_known", ((_v601(_v472) != _v268) && (_v602(_v472) != _v268))));
    if ((_v319 == _v283)) {
        _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1893("value", _v387));
    } else {
        if ((_v319 == _v284)) {
            _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1894("value", (_v387 == 1)));
        } else {
            if (((((((_v319 == _v285) || (_v319 == _v287)) || (_v319 == _v290)) || (_v319 == _v291)) || (_v319 == _v292)) || (_v319 == _v293))) {
                _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("binding", _v1945(_v425, _v387)));
            }
        }
    }
    return bkr_str_concat(_v1193, "}");
}

bkr_str _v1981(bkr_i64 _v425, bkr_i64 _v406, bkr_i64 _v407) {
    return _v1982(_v425, _v618(_v406), _v604(_v407));
}

bkr_str _v1982(bkr_i64 _v425, _v436 _v620, _v434 _v975) {
    bkr_str _v1193 = "[";
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v919(_v620))) {
        if ((_v1168 > 0)) {
            _v1193 = bkr_str_concat(_v1193, ",");
        }
        _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, "{"), _v1895("pattern", _v1980(_v425, _v924(_v620, _v1168)))), ","), _v1895("body", _v1974(_v425, _v912(_v975, _v1168)))), "}");
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v1983(bkr_i64 _v425, bkr_i64 _v447) {
    return _v1984(_v425, _v538(_v447));
}

bkr_str _v1984(bkr_i64 _v425, _v426 _v541) {
    _v435 _v1007 = _v727(_v541);
    _v434 _v1008 = _v730(_v541);
    bkr_str _v1193 = "[";
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v915(_v1007))) {
        if ((_v1168 > 0)) {
            _v1193 = bkr_str_concat(_v1193, ",");
        }
        _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, "{"), _v1892("name", _v1945(_v425, _v917(_v1007, _v1168)))), ","), _v1895("value", _v1974(_v425, _v912(_v1008, _v1168)))), "}");
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v1985(bkr_i64 _v425, bkr_i64 _v1986) {
    _v426 _v541 = _v537(_v1986);
    return _v1974(_v425, _v546(_v541));
}

bkr_str _v1987(bkr_i64 _v425, bkr_i64 _v1599) {
    _v427 _v553 = _v549(_v1599);
    return _v1974(_v425, _v586(_v553));
}

bkr_str _v1988(bkr_i64 _v425, bkr_i64 _v447) {
    return _v1974(_v425, _v476(_v447));
}

bkr_str _v1974(bkr_i64 _v425, _v341 _v452) {
    bkr_str _v1941 = ",";
    bkr_i64 _v319 = _v509(_v452);
    bkr_str _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("kind", _v318(_v319))), _v1941), _v1892("category", _v329(_v510(_v452)))), _v1941), _v1893("source_start", _v511(_v452))), _v1941), _v1893("source_end", _v512(_v452))), _v1941), _v1894("span_known", ((_v511(_v452) != _v268) && (_v512(_v452) != _v268))));
    if ((_v319 == _v223)) {
        _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("name", _v1945(_v425, _v663(_v452)))), _v1941), _v1892("entry", _v1945(_v425, _v900(_v452)))), _v1941), _v1895("items", _v1973(_v425, _v898(_v452))));
    } else {
        if ((_v319 == _v224)) {
            _v428 _v562 = _v560(_v452);
            _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("name", _v1945(_v425, _v868(_v562)))), _v1941), _v1895("params", _v1973(_v425, _v871(_v562)))), _v1941), _v1895("return_type", _v1975(_v425, _v874(_v562)))), _v1941), _v1895("body", _v1974(_v425, _v588(_v876(_v562)))));
        } else {
            if ((_v319 == _v225)) {
                _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("name", _v1945(_v425, _v862(_v452)))), _v1941), _v1895("type", _v1974(_v425, _v585(_v866(_v452)))));
            } else {
                if ((_v319 == _v226)) {
                    _v346 _v520 = _v518(_v452);
                    bkr_i64 _v1989 = _v529(_v520);
                    _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("type_kind", _v327(_v1989))), _v1941), _v1893("type_tag", _v1989));
                    if ((_v1989 == _v309)) {
                        _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("struct_name", _v1945(_v425, _v531(_v520))));
                    } else {
                        if ((_v1989 == _v308)) {
                            _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("element_type_kind", _v327(_v532(_v520)))), _v1941), _v1893("array_len", _v533(_v520)));
                        } else {
                            if ((_v1989 == _v310)) {
                                bkr_i64 _v953 = _v534(_v520);
                                bkr_i64 _v1361 = _v535(_v520);
                                _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("element_type_kind", _v327(_v953)));
                                if (((_v953 == _v309) && (_v1361 >= 0))) {
                                    _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("element_struct_name", _v1945(_v425, _v1361)));
                                }
                            } else {
                                if ((_v1989 == _v311)) {
                                    bkr_i64 _v1363 = _v534(_v520);
                                    bkr_i64 _v1365 = _v535(_v520);
                                    _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("key_type_kind", _v327(_v1363))), _v1941), _v1892("value_type_kind", _v327(_v1365)));
                                } else {
                                    if ((_v1989 == _v312)) {
                                        bkr_i64 _v1367 = _v534(_v520);
                                        bkr_i64 _v1368 = _v535(_v520);
                                        _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("inner_type_kind", _v327(_v1367)));
                                        if (((_v1367 == _v309) && (_v1368 >= 0))) {
                                            _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("inner_struct_name", _v1945(_v425, _v1368)));
                                        }
                                    } else {
                                        if ((_v1989 == _v313)) {
                                            bkr_i64 _v1370 = _v534(_v520);
                                            bkr_i64 _v1372 = _v535(_v520);
                                            _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("ok_type_kind", _v327(_v1370))), _v1941), _v1892("err_type_kind", _v327(_v1372)));
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if ((_v319 == _v227)) {
                        _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1895("statements", _v1978(_v425, _v580(_v452))));
                    } else {
                        if ((_v319 == _v228)) {
                            _v427 _v553 = _v551(_v452);
                            _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("name", _v1945(_v425, _v757(_v553)))), _v1941), _v1895("declared_type", _v1975(_v425, _v760(_v553)))), _v1941), _v1895("init", _v1975(_v425, _v763(_v553))));
                        } else {
                            if ((_v319 == _v229)) {
                                _v427 _v553 = _v551(_v452);
                                _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1895("expr", _v1975(_v425, _v768(_v553))));
                            } else {
                                if ((_v319 == _v230)) {
                                    _v427 _v553 = _v551(_v452);
                                    _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1895("condition", _v1985(_v425, _v827(_v553)))), _v1941), _v1895("then", _v1974(_v425, _v588(_v829(_v553))))), _v1941), _v1895("else", _v1975(_v425, _v832(_v553))));
                                } else {
                                    if ((_v319 == _v231)) {
                                        _v427 _v553 = _v551(_v452);
                                        _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1895("condition", _v1985(_v425, _v849(_v553)))), _v1941), _v1895("body", _v1974(_v425, _v588(_v851(_v553)))));
                                    } else {
                                        if ((_v319 == _v232)) {
                                            _v427 _v553 = _v551(_v452);
                                            _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1895("expr", _v1985(_v425, _v860(_v553))));
                                        } else {
                                            if ((_v319 == _v233)) {
                                                _v427 _v553 = _v551(_v452);
                                                _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1895("target", _v1985(_v425, _v854(_v553)))), _v1941), _v1895("value", _v1985(_v425, _v857(_v553))));
                                            } else {
                                                if ((_v319 == _v236)) {
                                                    _v427 _v553 = _v551(_v452);
                                                    _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("binding", _v1945(_v425, _v834(_v553)))), _v1941), _v1895("start", _v1985(_v425, _v837(_v553)))), _v1941), _v1895("end", _v1985(_v425, _v840(_v553)))), _v1941), _v1894("inclusive", (_v842(_v553) == 1))), _v1941), _v1895("body", _v1974(_v425, _v588(_v844(_v553)))));
                                                } else {
                                                    if ((_v319 == _v237)) {
                                                        _v427 _v553 = _v551(_v452);
                                                        _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1895("body", _v1974(_v425, _v588(_v846(_v553)))));
                                                    } else {
                                                        if ((_v319 == _v238)) {
                                                            _v427 _v553 = _v551(_v452);
                                                            _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1895("stmt", _v1987(_v425, _v772(_v553))));
                                                        } else {
                                                            if ((_v319 == _v242)) {
                                                                _v426 _v541 = _v539(_v452);
                                                                _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("op", _v1306(_v671(_v541)))), _v1941), _v1895("left", _v1985(_v425, _v674(_v541)))), _v1941), _v1895("right", _v1985(_v425, _v677(_v541))));
                                                            } else {
                                                                if ((_v319 == _v240)) {
                                                                    _v426 _v541 = _v539(_v452);
                                                                    _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1895("expr", _v1985(_v425, _v777(_v541))));
                                                                } else {
                                                                    if ((_v319 == _v243)) {
                                                                        _v426 _v541 = _v539(_v452);
                                                                        _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("op", _v1306(_v681(_v541)))), _v1941), _v1895("operand", _v1985(_v425, _v684(_v541))));
                                                                    } else {
                                                                        if ((_v319 == _v261)) {
                                                                            _v426 _v541 = _v539(_v452);
                                                                            _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1895("receiver", _v1985(_v425, _v693(_v541)))), _v1941), _v1892("method", _v1945(_v425, _v696(_v541)))), _v1941), _v1895("args", _v1973(_v425, _v698(_v541))));
                                                                        } else {
                                                                            if ((_v319 == _v244)) {
                                                                                _v426 _v541 = _v539(_v452);
                                                                                _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("callee", _v1945(_v425, _v688(_v541)))), _v1941), _v1895("args", _v1973(_v425, _v691(_v541))));
                                                                            } else {
                                                                                if ((_v319 == _v245)) {
                                                                                    _v426 _v541 = _v539(_v452);
                                                                                    _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("name", _v1945(_v425, _v662(_v541))));
                                                                                } else {
                                                                                    if ((_v319 == _v246)) {
                                                                                        _v426 _v541 = _v539(_v452);
                                                                                        _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1893("value", _v665(_v541)));
                                                                                    } else {
                                                                                        if ((_v319 == _v247)) {
                                                                                            _v426 _v541 = _v539(_v452);
                                                                                            _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1894("value", (_v665(_v541) == 1)));
                                                                                        } else {
                                                                                            if ((_v319 == _v248)) {
                                                                                                _v426 _v541 = _v539(_v452);
                                                                                                _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("value", ((bkr_str)(_v665(_v541)))));
                                                                                            } else {
                                                                                                if ((_v319 == _v249)) {
                                                                                                    _v428 _v562 = _v560(_v452);
                                                                                                    _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("name", _v1945(_v425, _v878(_v562)))), _v1941), _v1895("type", _v1975(_v425, _v881(_v562)))), _v1941), _v1895("value", _v1975(_v425, _v884(_v562))));
                                                                                                } else {
                                                                                                    if ((_v319 == _v260)) {
                                                                                                        _v428 _v562 = _v560(_v452);
                                                                                                        _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("name", _v1945(_v425, _v1177(_v562)))), _v1941), _v1895("target", _v1975(_v425, _v1178(_v562))));
                                                                                                    } else {
                                                                                                        if ((_v319 == _v250)) {
                                                                                                            _v426 _v541 = _v539(_v452);
                                                                                                            _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1895("condition", _v1985(_v425, _v733(_v541)))), _v1941), _v1895("then", _v1985(_v425, _v736(_v541)))), _v1941), _v1895("else", _v1985(_v425, _v739(_v541))));
                                                                                                        } else {
                                                                                                            if ((_v319 == _v251)) {
                                                                                                                _v426 _v541 = _v539(_v452);
                                                                                                                _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("value", ((bkr_str)(_v665(_v541)))));
                                                                                                            } else {
                                                                                                                if ((_v319 == _v252)) {
                                                                                                                    _v426 _v541 = _v539(_v452);
                                                                                                                    _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1895("elements", _v1973(_v425, _v701(_v541))));
                                                                                                                } else {
                                                                                                                    if ((_v319 == _v239)) {
                                                                                                                        _v426 _v541 = _v539(_v452);
                                                                                                                        _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1895("element", _v1985(_v425, _v703(_v541)))), _v1941), _v1893("count", _v706(_v541)));
                                                                                                                    } else {
                                                                                                                        if ((_v319 == _v253)) {
                                                                                                                            _v426 _v541 = _v539(_v452);
                                                                                                                            _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1895("base", _v1985(_v425, _v711(_v541)))), _v1941), _v1895("index", _v1985(_v425, _v714(_v541))));
                                                                                                                        } else {
                                                                                                                            if ((_v319 == _v254)) {
                                                                                                                                _v428 _v562 = _v560(_v452);
                                                                                                                                _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("name", _v1945(_v425, _v886(_v562)))), _v1941), _v1895("fields", _v1973(_v425, _v889(_v562))));
                                                                                                                            } else {
                                                                                                                                if ((_v319 == _v259)) {
                                                                                                                                    _v428 _v562 = _v560(_v452);
                                                                                                                                    _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("name", _v1945(_v425, _v1164(_v562)))), _v1941), _v1893("variant_count", _v915(_v1165(_v562)))), _v1941), _v1893("payload_count", _v1167(_v562))), _v1941), _v1893("payload_arity_sum", _v1170(_v562)));
                                                                                                                                } else {
                                                                                                                                    if ((_v319 == _v255)) {
                                                                                                                                        _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("name", _v1945(_v425, _v891(_v452)))), _v1941), _v1895("type", _v1975(_v425, _v894(_v452))));
                                                                                                                                    } else {
                                                                                                                                        if ((_v319 == _v256)) {
                                                                                                                                            _v426 _v541 = _v539(_v452);
                                                                                                                                            _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1895("base", _v1985(_v425, _v719(_v541)))), _v1941), _v1892("field", _v1945(_v425, _v722(_v541))));
                                                                                                                                        } else {
                                                                                                                                            if ((_v319 == _v257)) {
                                                                                                                                                _v426 _v541 = _v539(_v452);
                                                                                                                                                _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("name", _v1945(_v425, _v724(_v541)))), _v1941), _v1895("fields", _v1984(_v425, _v541)));
                                                                                                                                            } else {
                                                                                                                                                if ((_v319 == _v258)) {
                                                                                                                                                    _v426 _v541 = _v539(_v452);
                                                                                                                                                    _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1895("scrutinee", _v1985(_v425, _v742(_v541)))), _v1941), _v1895("arms", _v1982(_v425, _v745(_v541), _v748(_v541))));
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                    }
                                                                                                                                }
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return bkr_str_concat(_v1193, "}");
}

bkr_str _v1990(bkr_str _v1209, bkr_i64 _v0) {
    bkr_str _v1941 = ",";
    _v341 _v1530 = _v476(_v0);
    bkr_i64 _v425 = _v903(_v1530);
    _v434 _v1183 = _v898(_v1530);
    bkr_str _v1991 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("kind", _v318(_v509(_v1530)))), _v1941), _v1892("name", _v1945(_v425, _v663(_v1530)))), _v1941), _v1892("entry", _v1945(_v425, _v900(_v1530)))), _v1941), _v1893("source_start", _v511(_v1530))), _v1941), _v1893("source_end", _v512(_v1530))), _v1941), _v1894("span_known", ((_v511(_v1530) != _v268) && (_v512(_v1530) != _v268)))), "}");
    bkr_str _v1992 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1893("source_bytes", bkr_len((bkr_str)(intptr_t)(_v1209)))), _v1941), _v1893("source_lines", _v1956(_v1209))), _v1941), _v1893("item_count", _v906(_v1183))), _v1941), _v1893("function_count", _v1969(_v1183, _v224))), _v1941), _v1893("struct_count", _v1969(_v1183, _v254))), _v1941), _v1893("enum_count", _v1969(_v1183, _v259))), _v1941), _v1893("const_count", _v1969(_v1183, _v249))), "}");
    bkr_bool _v1993 = _v1933(_v1530);
    bkr_str _v1994 = "[]";
    bkr_str _v1995 = bkr_str_concat(bkr_str_concat("{", _v1892("kind", "kernel")), "}");
    if (_v1993) {
        _v1994 = _v1971(_v425, _v1183);
        _v1995 = _v1974(_v425, _v476(_v0));
    }
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("schema_version", "bunker.self_host.ast.v1")), _v1941), _v1892("representation", "bootstrap_vec_i64")), _v1941), _v1894("source_byte_spans", BKR_TRUE)), _v1941), _v1894("complete_tree", _v1993)), _v1941), _v1894("truncated", (!_v1993))), _v1941), _v1895("root", _v1991)), _v1941), _v1895("summary", _v1992)), _v1941), _v1895("items", _v1994)), _v1941), _v1895("tree", _v1995)), "}");
}

bkr_str _v1996(bkr_str _v1209, bkr_i64 _v0) {
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("/* BUNKER_AST_JSON: ", _v1990(_v1209, _v0)), from_char_code(10)), "*/"), from_char_code(10));
}

bkr_str _v1997(bkr_str _v1193, bkr_str _v557) {
    if ((bkr_len((bkr_str)(intptr_t)(_v1193)) > 1)) {
        return bkr_str_concat(bkr_str_concat(_v1193, ","), _v557);
    }
    return bkr_str_concat(_v1193, _v557);
}

bkr_str _v1998(bkr_str _v1193, bkr_str _v423) {
    if ((bkr_len((bkr_str)(intptr_t)(_v423)) <= 2)) {
        return _v1193;
    }
    bkr_str _v1999 = substring(_v423, 1, (bkr_len((bkr_str)(intptr_t)(_v423)) - 1));
    if ((bkr_len((bkr_str)(intptr_t)(_v1193)) > 1)) {
        return bkr_str_concat(bkr_str_concat(_v1193, ","), _v1999);
    }
    return bkr_str_concat(_v1193, _v1999);
}

bkr_str _v2000(bkr_str _v319, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v1936, bkr_i64 _v1937) {
    bkr_str _v1941 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("kind", _v319)), _v1941), _v1892("name", _v1348)), _v1941), _v1892("scope", _v2001)), _v1941), _v1893("source_start", _v1936)), _v1941), _v1893("source_end", _v1937)), _v1941), _v1894("span_known", ((_v1936 != _v268) && (_v1937 != _v268)))), "}");
}

bkr_str _v2002(bkr_str _v319, bkr_str _v1348, bkr_str _v2001, _v341 _v452) {
    return _v2000(_v319, _v1348, _v2001, _v511(_v452), _v512(_v452));
}

bkr_str _v2003(bkr_str _v319, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v447) {
    return _v2002(_v319, _v1348, _v2001, _v476(_v447));
}

bkr_str _v2004(bkr_str _v319, bkr_str _v1348, bkr_str _v2001, _v433 _v472) {
    return _v2000(_v319, _v1348, _v2001, _v601(_v472), _v602(_v472));
}

bkr_str _v2005(bkr_str _v319, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v463) {
    return _v2004(_v319, _v1348, _v2001, _v592(_v463));
}

bkr_str _v2006(bkr_i64 _v425, bkr_i64 _v515, bkr_str _v2001) {
    bkr_str _v1193 = "[";
    if (_v525(_v515)) {
        _v1193 = _v1998(_v1193, _v2007(_v425, _v516(_v515), _v2001));
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2007(bkr_i64 _v425, _v346 _v520, bkr_str _v2001) {
    bkr_str _v1193 = "[";
    if ((_v529(_v520) == _v309)) {
        _v1193 = _v1997(_v1193, _v2002("type_reference", _v1945(_v425, _v531(_v520)), _v2001, _v585(_v520)));
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2008(bkr_i64 _v425, bkr_i64 _v463, bkr_str _v2001) {
    return _v2009(_v425, _v592(_v463), _v2001);
}

bkr_str _v2009(bkr_i64 _v425, _v433 _v472, bkr_str _v2001) {
    bkr_str _v1193 = "[";
    bkr_i64 _v319 = _v596(_v472);
    if (((((_v319 == _v285) || (_v319 == _v287)) || (_v319 == _v290)) || (_v319 == _v291))) {
        bkr_i64 _v355 = _v597(_v472);
        if ((_v355 >= 0)) {
            _v1193 = _v1997(_v1193, _v2004("pattern_binding", _v1945(_v425, _v355), _v2001, _v472));
        }
        bkr_i64 _v345 = _v598(_v472);
        if ((_v345 != 0)) {
            _v433 _v1393 = _v591(_v345);
            _v1193 = _v1998(_v1193, _v2009(_v425, _v1393, _v2001));
        }
    }
    if ((_v319 == _v292)) {
        bkr_i64 _v345 = _v598(_v472);
        if ((_v345 != 0)) {
            bkr_i64 _v1375 = ((bkr_i64)(_v345));
            bkr_i64 _v1168 = 0;
            while ((_v1168 < vec_len(_v1375))) {
                _v433 _v1393 = _v591(vec_get(_v1375, _v1168));
                _v1193 = _v1998(_v1193, _v2009(_v425, _v1393, _v2001));
                _v1168 = (_v1168 + 1);
            }
        } else {
            bkr_i64 _v2010 = _v599(_v472);
            bkr_i64 _v2011 = _v600(_v472);
            if ((_v2010 >= 0)) {
                _v1193 = _v1997(_v1193, _v2004("pattern_binding", _v1945(_v425, _v2010), _v2001, _v472));
            }
            if ((_v2011 >= 0)) {
                _v1193 = _v1997(_v1193, _v2004("pattern_binding", _v1945(_v425, _v2011), _v2001, _v472));
            }
        }
    }
    if ((_v319 == _v293)) {
        bkr_i64 _v2010 = _v599(_v472);
        bkr_i64 _v2011 = _v600(_v472);
        bkr_i64 _v2012 = _v598(_v472);
        if ((_v2010 >= 0)) {
            _v1193 = _v1997(_v1193, _v2004("pattern_binding", _v1945(_v425, _v2010), _v2001, _v472));
        }
        if ((_v2011 >= 0)) {
            _v1193 = _v1997(_v1193, _v2004("pattern_binding", _v1945(_v425, _v2011), _v2001, _v472));
        }
        if ((_v2012 >= 0)) {
            _v1193 = _v1997(_v1193, _v2004("pattern_binding", _v1945(_v425, _v2012), _v2001, _v472));
        }
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2013(bkr_i64 _v425, bkr_i64 _v1655, bkr_str _v2001) {
    bkr_str _v1193 = "[";
    if (_v523(_v1655)) {
        return bkr_str_concat(_v1193, "]");
    }
    _v1193 = _v1998(_v1193, _v2014(_v425, _v537(_v1655), _v2001));
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2014(bkr_i64 _v425, _v426 _v541, bkr_str _v2001) {
    bkr_str _v1193 = "[";
    bkr_i64 _v319 = _v544(_v541);
    if ((_v319 == _v258)) {
        _v436 _v620 = _v745(_v541);
        _v434 _v975 = _v748(_v541);
        bkr_i64 _v1168 = 0;
        while ((_v1168 < _v919(_v620))) {
            _v1193 = _v1998(_v1193, _v2009(_v425, _v924(_v620, _v1168), _v2001));
            _v341 _v1123 = _v912(_v975, _v1168);
            if ((_v509(_v1123) == _v227)) {
                _v1193 = _v1998(_v1193, _v2015(_v425, _v580(_v1123), _v2001));
            } else {
                _v1193 = _v1998(_v1193, _v2014(_v425, _v539(_v1123), _v2001));
            }
            _v1168 = (_v1168 + 1);
        }
    } else {
        if ((_v319 == _v227)) {
            _v1193 = _v1998(_v1193, _v2015(_v425, _v580(_v546(_v541)), _v2001));
        } else {
            if ((_v319 == _v242)) {
                _v1193 = _v1998(_v1193, _v2014(_v425, _v537(_v674(_v541)), _v2001));
                _v1193 = _v1998(_v1193, _v2014(_v425, _v537(_v677(_v541)), _v2001));
            } else {
                if ((_v319 == _v240)) {
                    _v1193 = _v1998(_v1193, _v2014(_v425, _v537(_v777(_v541)), _v2001));
                } else {
                    if ((_v319 == _v243)) {
                        _v1193 = _v1998(_v1193, _v2014(_v425, _v537(_v684(_v541)), _v2001));
                    } else {
                        if ((_v319 == _v261)) {
                            _v1193 = _v1998(_v1193, _v2014(_v425, _v694(_v541), _v2001));
                            _v434 _v1015 = _v698(_v541);
                            bkr_i64 _v1168 = 0;
                            while ((_v1168 < _v906(_v1015))) {
                                _v341 _v1425 = _v912(_v1015, _v1168);
                                _v1193 = _v1998(_v1193, _v2014(_v425, _v539(_v1425), _v2001));
                                _v1168 = (_v1168 + 1);
                            }
                        } else {
                            if ((_v319 == _v244)) {
                                _v434 _v1015 = _v691(_v541);
                                bkr_i64 _v1168 = 0;
                                while ((_v1168 < _v906(_v1015))) {
                                    _v341 _v1425 = _v912(_v1015, _v1168);
                                    _v1193 = _v1998(_v1193, _v2014(_v425, _v539(_v1425), _v2001));
                                    _v1168 = (_v1168 + 1);
                                }
                            } else {
                                if ((_v319 == _v250)) {
                                    _v1193 = _v1998(_v1193, _v2014(_v425, _v537(_v733(_v541)), _v2001));
                                    _v1193 = _v1998(_v1193, _v2014(_v425, _v537(_v736(_v541)), _v2001));
                                    _v1193 = _v1998(_v1193, _v2014(_v425, _v537(_v739(_v541)), _v2001));
                                } else {
                                    if ((_v319 == _v239)) {
                                        _v1193 = _v1998(_v1193, _v2013(_v425, _v703(_v541), _v2001));
                                    } else {
                                        if ((_v319 == _v252)) {
                                            _v434 _v994 = _v701(_v541);
                                            bkr_i64 _v1168 = 0;
                                            while ((_v1168 < _v906(_v994))) {
                                                _v341 _v2016 = _v912(_v994, _v1168);
                                                _v1193 = _v1998(_v1193, _v2014(_v425, _v539(_v2016), _v2001));
                                                _v1168 = (_v1168 + 1);
                                            }
                                        } else {
                                            if ((_v319 == _v253)) {
                                                _v1193 = _v1998(_v1193, _v2014(_v425, _v537(_v711(_v541)), _v2001));
                                                _v1193 = _v1998(_v1193, _v2014(_v425, _v537(_v714(_v541)), _v2001));
                                            } else {
                                                if ((_v319 == _v256)) {
                                                    _v1193 = _v1998(_v1193, _v2014(_v425, _v537(_v719(_v541)), _v2001));
                                                } else {
                                                    if ((_v319 == _v257)) {
                                                        _v434 _v1008 = _v730(_v541);
                                                        bkr_i64 _v1168 = 0;
                                                        while ((_v1168 < _v906(_v1008))) {
                                                            _v341 _v1422 = _v912(_v1008, _v1168);
                                                            _v1193 = _v1998(_v1193, _v2014(_v425, _v539(_v1422), _v2001));
                                                            _v1168 = (_v1168 + 1);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2017(bkr_i64 _v425, bkr_i64 _v370, bkr_str _v2001) {
    return _v2018(_v425, _v550(_v370), _v2001);
}

bkr_str _v2018(bkr_i64 _v425, _v427 _v553, bkr_str _v2001) {
    bkr_str _v1193 = "[";
    bkr_i64 _v319 = _v555(_v553);
    if ((_v319 == _v228)) {
        _v1193 = _v1997(_v1193, _v2002("local", _v1945(_v425, _v757(_v553)), _v2001, _v586(_v553)));
        _v1193 = _v1998(_v1193, _v2013(_v425, _v763(_v553), _v2001));
    } else {
        if ((_v319 == _v229)) {
            _v1193 = _v1998(_v1193, _v2013(_v425, _v768(_v553), _v2001));
        } else {
            if ((_v319 == _v230)) {
                _v1193 = _v1998(_v1193, _v2013(_v425, _v827(_v553), _v2001));
                _v1193 = _v1998(_v1193, _v2015(_v425, _v829(_v553), _v2001));
                bkr_i64 _v377 = _v832(_v553);
                if (_v525(_v377)) {
                    _v1193 = _v1998(_v1193, _v2015(_v425, _v578(_v377), _v2001));
                }
            } else {
                if ((_v319 == _v231)) {
                    _v1193 = _v1998(_v1193, _v2013(_v425, _v849(_v553), _v2001));
                    _v1193 = _v1998(_v1193, _v2015(_v425, _v851(_v553), _v2001));
                } else {
                    if ((_v319 == _v236)) {
                        _v1193 = _v1997(_v1193, _v2002("for_binding", _v1945(_v425, _v834(_v553)), _v2001, _v586(_v553)));
                        _v1193 = _v1998(_v1193, _v2013(_v425, _v837(_v553), _v2001));
                        _v1193 = _v1998(_v1193, _v2013(_v425, _v840(_v553), _v2001));
                        _v1193 = _v1998(_v1193, _v2015(_v425, _v844(_v553), _v2001));
                    } else {
                        if ((_v319 == _v237)) {
                            _v1193 = _v1998(_v1193, _v2015(_v425, _v846(_v553), _v2001));
                        } else {
                            if ((_v319 == _v233)) {
                                _v1193 = _v1998(_v1193, _v2013(_v425, _v854(_v553), _v2001));
                                _v1193 = _v1998(_v1193, _v2013(_v425, _v857(_v553), _v2001));
                            } else {
                                if ((_v319 == _v238)) {
                                    _v1193 = _v1998(_v1193, _v2018(_v425, _v549(_v772(_v553)), _v2001));
                                } else {
                                    if ((_v319 == _v232)) {
                                        _v1193 = _v1998(_v1193, _v2013(_v425, _v860(_v553), _v2001));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2019(bkr_i64 _v425, bkr_i64 _v577, bkr_str _v2001) {
    return _v2015(_v425, _v579(_v577), _v2001);
}

bkr_str _v2015(bkr_i64 _v425, _v429 _v582, bkr_str _v2001) {
    bkr_str _v1193 = "[";
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v589(_v582))) {
        _v1193 = _v1998(_v1193, _v2018(_v425, _v1107(_v582, _v1168), _v2001));
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2020(bkr_i64 _v0, bkr_i64 _v557, bkr_str _v2021) {
    return _v2022(_v476(_v0), _v559(_v557), _v2021);
}

bkr_str _v2022(_v341 _v1530, _v428 _v562, bkr_str _v2021) {
    bkr_i64 _v425 = _v903(_v1530);
    bkr_str _v1193 = "[";
    _v341 _v1967 = _v587(_v562);
    bkr_i64 _v319 = _v568(_v562);
    if ((_v319 == _v224)) {
        bkr_str _v2023 = _v1945(_v425, _v868(_v562));
        bkr_str _v2024 = bkr_str_concat("function:", _v2023);
        _v1193 = _v1997(_v1193, _v2002("function", _v2023, _v2021, _v1967));
        _v434 _v1141 = _v871(_v562);
        bkr_i64 _v1168 = 0;
        while ((_v1168 < _v906(_v1141))) {
            _v341 _v1507 = _v912(_v1141, _v1168);
            _v1193 = _v1997(_v1193, _v2002("parameter", _v1945(_v425, _v862(_v1507)), _v2024, _v1507));
            _v1168 = (_v1168 + 1);
        }
        _v1193 = _v1998(_v1193, _v2015(_v425, _v876(_v562), _v2024));
    } else {
        if ((_v319 == _v249)) {
            _v1193 = _v1997(_v1193, _v2002("constant", _v1945(_v425, _v878(_v562)), _v2021, _v1967));
            _v1193 = _v1998(_v1193, _v2013(_v425, _v884(_v562), _v2021));
        } else {
            if ((_v319 == _v260)) {
                _v1193 = _v1997(_v1193, _v2002("type_alias", _v1945(_v425, _v1177(_v562)), _v2021, _v1967));
            } else {
                if ((_v319 == _v254)) {
                    bkr_str _v1681 = _v1945(_v425, _v886(_v562));
                    bkr_str _v2025 = bkr_str_concat("struct:", _v1681);
                    _v1193 = _v1997(_v1193, _v2002("struct", _v1681, _v2021, _v1967));
                    _v434 _v1158 = _v889(_v562);
                    bkr_i64 _v1168 = 0;
                    while ((_v1168 < _v906(_v1158))) {
                        _v341 _v1432 = _v912(_v1158, _v1168);
                        _v1193 = _v1997(_v1193, _v2002("field", _v1945(_v425, _v891(_v1432)), _v2025, _v1432));
                        _v1168 = (_v1168 + 1);
                    }
                }
            }
        }
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2026(bkr_i64 _v0) {
    return _v2027(_v476(_v0));
}

bkr_str _v2027(_v341 _v1530) {
    bkr_i64 _v425 = _v903(_v1530);
    bkr_str _v1533 = _v1945(_v425, _v663(_v1530));
    bkr_str _v2021 = bkr_str_concat("kernel:", _v1533);
    bkr_str _v1193 = "[";
    _v1193 = _v1997(_v1193, _v2002("kernel", _v1533, "global", _v1530));
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        _v1193 = _v1998(_v1193, _v2022(_v1530, _v562, _v2021));
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2028(bkr_i64 _v425, bkr_i64 _v1655, bkr_str _v2001) {
    bkr_str _v1193 = "[";
    if (_v523(_v1655)) {
        return bkr_str_concat(_v1193, "]");
    }
    _v1193 = _v1998(_v1193, _v2029(_v425, _v537(_v1655), _v2001));
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2029(bkr_i64 _v425, _v426 _v541, bkr_str _v2001) {
    bkr_str _v1193 = "[";
    bkr_i64 _v319 = _v544(_v541);
    if ((_v319 == _v245)) {
        _v1193 = _v1997(_v1193, _v2002("identifier", _v1945(_v425, _v662(_v541)), _v2001, _v546(_v541)));
    } else {
        if ((_v319 == _v261)) {
            _v1193 = _v1998(_v1193, _v2014(_v425, _v694(_v541), _v2001));
            _v434 _v1015 = _v698(_v541);
            bkr_i64 _v1168 = 0;
            while ((_v1168 < _v906(_v1015))) {
                _v341 _v1425 = _v912(_v1015, _v1168);
                _v1193 = _v1998(_v1193, _v2014(_v425, _v539(_v1425), _v2001));
                _v1168 = (_v1168 + 1);
            }
        } else {
            if ((_v319 == _v244)) {
                _v1193 = _v1997(_v1193, _v2002("function_call", _v1945(_v425, _v688(_v541)), _v2001, _v546(_v541)));
                _v434 _v1015 = _v691(_v541);
                bkr_i64 _v1168 = 0;
                while ((_v1168 < _v906(_v1015))) {
                    _v341 _v1425 = _v912(_v1015, _v1168);
                    _v1193 = _v1998(_v1193, _v2029(_v425, _v539(_v1425), _v2001));
                    _v1168 = (_v1168 + 1);
                }
            } else {
                if ((_v319 == _v256)) {
                    _v1193 = _v1998(_v1193, _v2029(_v425, _v537(_v719(_v541)), _v2001));
                    _v1193 = _v1997(_v1193, _v2002("field_access", _v1945(_v425, _v722(_v541)), _v2001, _v546(_v541)));
                } else {
                    if ((_v319 == _v257)) {
                        _v1193 = _v1997(_v1193, _v2002("struct_literal", _v1945(_v425, _v724(_v541)), _v2001, _v546(_v541)));
                        _v435 _v1007 = _v727(_v541);
                        _v434 _v1008 = _v730(_v541);
                        bkr_i64 _v1168 = 0;
                        while ((_v1168 < _v915(_v1007))) {
                            _v341 _v1422 = _v912(_v1008, _v1168);
                            _v1193 = _v1997(_v1193, _v2002("field_initializer", _v1945(_v425, _v917(_v1007, _v1168)), _v2001, _v546(_v541)));
                            _v1193 = _v1998(_v1193, _v2029(_v425, _v539(_v1422), _v2001));
                            _v1168 = (_v1168 + 1);
                        }
                    } else {
                        if ((_v319 == _v242)) {
                            _v1193 = _v1998(_v1193, _v2029(_v425, _v537(_v674(_v541)), _v2001));
                            _v1193 = _v1998(_v1193, _v2029(_v425, _v537(_v677(_v541)), _v2001));
                        } else {
                            if ((_v319 == _v240)) {
                                _v1193 = _v1998(_v1193, _v2029(_v425, _v537(_v777(_v541)), _v2001));
                            } else {
                                if ((_v319 == _v243)) {
                                    _v1193 = _v1998(_v1193, _v2029(_v425, _v537(_v684(_v541)), _v2001));
                                } else {
                                    if ((_v319 == _v250)) {
                                        _v1193 = _v1998(_v1193, _v2029(_v425, _v537(_v733(_v541)), _v2001));
                                        _v1193 = _v1998(_v1193, _v2029(_v425, _v537(_v736(_v541)), _v2001));
                                        _v1193 = _v1998(_v1193, _v2029(_v425, _v537(_v739(_v541)), _v2001));
                                    } else {
                                        if ((_v319 == _v239)) {
                                            _v1193 = _v1998(_v1193, _v2013(_v425, _v703(_v541), _v2001));
                                        } else {
                                            if ((_v319 == _v239)) {
                                                _v1193 = _v1998(_v1193, _v2028(_v425, _v703(_v541), _v2001));
                                            } else {
                                                if ((_v319 == _v252)) {
                                                    _v434 _v994 = _v701(_v541);
                                                    bkr_i64 _v1168 = 0;
                                                    while ((_v1168 < _v906(_v994))) {
                                                        _v341 _v2016 = _v912(_v994, _v1168);
                                                        _v1193 = _v1998(_v1193, _v2029(_v425, _v539(_v2016), _v2001));
                                                        _v1168 = (_v1168 + 1);
                                                    }
                                                } else {
                                                    if ((_v319 == _v253)) {
                                                        _v1193 = _v1998(_v1193, _v2029(_v425, _v537(_v711(_v541)), _v2001));
                                                        _v1193 = _v1998(_v1193, _v2029(_v425, _v537(_v714(_v541)), _v2001));
                                                    } else {
                                                        if ((_v319 == _v227)) {
                                                            _v1193 = _v1998(_v1193, _v2030(_v425, _v580(_v546(_v541)), _v2001));
                                                        } else {
                                                            if ((_v319 == _v258)) {
                                                                _v1193 = _v1998(_v1193, _v2029(_v425, _v537(_v742(_v541)), _v2001));
                                                                _v434 _v975 = _v748(_v541);
                                                                bkr_i64 _v1168 = 0;
                                                                while ((_v1168 < _v906(_v975))) {
                                                                    _v341 _v1123 = _v912(_v975, _v1168);
                                                                    if ((_v509(_v1123) == _v227)) {
                                                                        _v1193 = _v1998(_v1193, _v2030(_v425, _v580(_v1123), _v2001));
                                                                    } else {
                                                                        _v1193 = _v1998(_v1193, _v2029(_v425, _v539(_v1123), _v2001));
                                                                    }
                                                                    _v1168 = (_v1168 + 1);
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2031(bkr_i64 _v425, bkr_i64 _v370, bkr_str _v2001) {
    return _v2032(_v425, _v550(_v370), _v2001);
}

bkr_str _v2032(bkr_i64 _v425, _v427 _v553, bkr_str _v2001) {
    bkr_str _v1193 = "[";
    bkr_i64 _v319 = _v555(_v553);
    if ((_v319 == _v228)) {
        _v1193 = _v1998(_v1193, _v2006(_v425, _v760(_v553), _v2001));
        _v1193 = _v1998(_v1193, _v2028(_v425, _v763(_v553), _v2001));
    } else {
        if ((_v319 == _v229)) {
            _v1193 = _v1998(_v1193, _v2028(_v425, _v768(_v553), _v2001));
        } else {
            if ((_v319 == _v230)) {
                _v1193 = _v1998(_v1193, _v2028(_v425, _v827(_v553), _v2001));
                _v1193 = _v1998(_v1193, _v2030(_v425, _v829(_v553), _v2001));
                bkr_i64 _v377 = _v832(_v553);
                if (_v525(_v377)) {
                    _v1193 = _v1998(_v1193, _v2030(_v425, _v578(_v377), _v2001));
                }
            } else {
                if ((_v319 == _v231)) {
                    _v1193 = _v1998(_v1193, _v2028(_v425, _v849(_v553), _v2001));
                    _v1193 = _v1998(_v1193, _v2030(_v425, _v851(_v553), _v2001));
                } else {
                    if ((_v319 == _v236)) {
                        _v1193 = _v1998(_v1193, _v2028(_v425, _v837(_v553), _v2001));
                        _v1193 = _v1998(_v1193, _v2028(_v425, _v840(_v553), _v2001));
                        _v1193 = _v1998(_v1193, _v2030(_v425, _v844(_v553), _v2001));
                    } else {
                        if ((_v319 == _v237)) {
                            _v1193 = _v1998(_v1193, _v2030(_v425, _v846(_v553), _v2001));
                        } else {
                            if ((_v319 == _v233)) {
                                _v1193 = _v1998(_v1193, _v2028(_v425, _v854(_v553), _v2001));
                                _v1193 = _v1998(_v1193, _v2028(_v425, _v857(_v553), _v2001));
                            } else {
                                if ((_v319 == _v238)) {
                                    _v1193 = _v1998(_v1193, _v2032(_v425, _v549(_v772(_v553)), _v2001));
                                } else {
                                    if ((_v319 == _v232)) {
                                        _v1193 = _v1998(_v1193, _v2028(_v425, _v860(_v553), _v2001));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2033(bkr_i64 _v425, bkr_i64 _v577, bkr_str _v2001) {
    return _v2030(_v425, _v579(_v577), _v2001);
}

bkr_str _v2030(bkr_i64 _v425, _v429 _v582, bkr_str _v2001) {
    bkr_str _v1193 = "[";
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v589(_v582))) {
        _v1193 = _v1998(_v1193, _v2032(_v425, _v1107(_v582, _v1168), _v2001));
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2034(bkr_i64 _v0, bkr_i64 _v557, bkr_str _v2021) {
    return _v2035(_v476(_v0), _v559(_v557), _v2021);
}

bkr_str _v2035(_v341 _v1530, _v428 _v562, bkr_str _v2021) {
    bkr_i64 _v425 = _v903(_v1530);
    bkr_str _v1193 = "[";
    bkr_i64 _v319 = _v568(_v562);
    if ((_v319 == _v224)) {
        bkr_str _v2023 = _v1945(_v425, _v868(_v562));
        bkr_str _v2024 = bkr_str_concat("function:", _v2023);
        _v1193 = _v1998(_v1193, _v2006(_v425, _v874(_v562), _v2024));
        _v434 _v1141 = _v871(_v562);
        bkr_i64 _v1168 = 0;
        while ((_v1168 < _v906(_v1141))) {
            _v341 _v1507 = _v912(_v1141, _v1168);
            _v1193 = _v1998(_v1193, _v2006(_v425, _v865(_v1507), _v2024));
            _v1168 = (_v1168 + 1);
        }
        _v1193 = _v1998(_v1193, _v2030(_v425, _v876(_v562), _v2024));
    } else {
        if ((_v319 == _v249)) {
            _v1193 = _v1998(_v1193, _v2006(_v425, _v881(_v562), _v2021));
            _v1193 = _v1998(_v1193, _v2028(_v425, _v884(_v562), _v2021));
        } else {
            if ((_v319 == _v260)) {
                _v1193 = _v1998(_v1193, _v2006(_v425, _v1178(_v562), _v2021));
            } else {
                if ((_v319 == _v254)) {
                    bkr_str _v2025 = bkr_str_concat("struct:", _v1945(_v425, _v886(_v562)));
                    _v434 _v1158 = _v889(_v562);
                    bkr_i64 _v1168 = 0;
                    while ((_v1168 < _v906(_v1158))) {
                        _v341 _v1432 = _v912(_v1158, _v1168);
                        _v1193 = _v1998(_v1193, _v2006(_v425, _v894(_v1432), _v2025));
                        _v1168 = (_v1168 + 1);
                    }
                }
            }
        }
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2036(bkr_i64 _v0) {
    return _v2037(_v476(_v0));
}

bkr_str _v2037(_v341 _v1530) {
    bkr_i64 _v425 = _v903(_v1530);
    bkr_str _v2021 = bkr_str_concat("kernel:", _v1945(_v425, _v663(_v1530)));
    bkr_str _v1193 = "[";
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        _v1193 = _v1998(_v1193, _v2035(_v1530, _v562, _v2021));
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2038(bkr_i64 _v0) {
    bkr_str _v1941 = ",";
    _v341 _v1530 = _v476(_v0);
    bkr_i64 _v425 = _v903(_v1530);
    _v434 _v1183 = _v898(_v1530);
    bkr_bool _v1993 = _v1933(_v1530);
    bkr_str _v2039 = "[]";
    bkr_str _v2040 = "[]";
    if (_v1993) {
        _v2039 = _v2027(_v1530);
        _v2040 = _v2037(_v1530);
    }
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("schema_version", "bunker.self_host.symbol_table.v1")), _v1941), _v1892("representation", "bootstrap_ast_walk")), _v1941), _v1894("complete", BKR_FALSE)), _v1941), _v1894("declarations", _v1993)), _v1941), _v1894("references", _v1993)), _v1941), _v1894("truncated", (!_v1993))), _v1941), _v1892("scope_model", "bootstrap kernel/function/struct scopes paired with BUNKER_RESOLVER_JSON validation")), _v1941), _v1892("known_limits", "Derived from AST names and paired with BUNKER_RESOLVER_JSON for bootstrap duplicate/unresolved diagnostics; imports, visibility, overloads, and related definition-use spans are not complete yet. Full declaration/reference tables are omitted when interned names exceed AST_REPORT_FULL_WALK_NAME_LIMIT so stage1 compile of bkrc stays inside runner memory.")), _v1941), _v1892("resolver_report", "BUNKER_RESOLVER_JSON")), _v1941), _v1895("summary", bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1893("interned_name_count", vec_len(_v425))), _v1941), _v1893("function_count", _v1969(_v1183, _v224))), _v1941), _v1893("struct_count", _v1969(_v1183, _v254))), _v1941), _v1893("const_count", _v1969(_v1183, _v249))), "}"))), _v1941), _v1895("declaration_table", _v2039)), _v1941), _v1895("reference_table", _v2040)), "}");
}

bkr_str _v2041(bkr_i64 _v0) {
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("/* BUNKER_SYMBOL_TABLE_JSON: ", _v2038(_v0)), from_char_code(10)), "*/"), from_char_code(10));
}

bkr_str _v2042(bkr_i64 _v319, bkr_str _v1209) {
    bkr_str _v1941 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("type_kind", _v327(_v319))), _v1941), _v1893("type_tag", _v319)), _v1941), _v1892("c_abi", _v1634(_v319))), _v1941), _v1892("source", _v1209)), _v1941), _v1894("known", (_v319 != _v316))), "}");
}

bkr_str _v2043(bkr_i64 _v425, bkr_i64 _v515, bkr_str _v1209) {
    if (_v523(_v515)) {
        return _v2042(_v316, _v1209);
    }
    return _v2044(_v425, _v516(_v515), _v1209);
}

bkr_str _v2044(bkr_i64 _v425, _v346 _v520, bkr_str _v1209) {
    bkr_str _v1941 = ",";
    bkr_i64 _v319 = _v529(_v520);
    bkr_str _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("type_kind", _v327(_v319))), _v1941), _v1893("type_tag", _v319)), _v1941), _v1892("c_abi", _v1634(_v319))), _v1941), _v1892("source", _v1209)), _v1941), _v1894("known", (_v319 != _v316)));
    if ((_v319 == _v309)) {
        _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("struct_name", _v1945(_v425, _v531(_v520))));
    } else {
        if ((_v319 == _v308)) {
            _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("element_type_kind", _v327(_v532(_v520)))), _v1941), _v1893("array_len", _v533(_v520)));
        } else {
            if ((_v319 == _v310)) {
                bkr_i64 _v953 = _v534(_v520);
                bkr_i64 _v1361 = _v535(_v520);
                _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("element_type_kind", _v327(_v953)));
                if (((_v953 == _v309) && (_v1361 >= 0))) {
                    _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("element_struct_name", _v1945(_v425, _v1361)));
                }
            } else {
                if ((_v319 == _v311)) {
                    bkr_i64 _v1363 = _v534(_v520);
                    bkr_i64 _v1365 = _v535(_v520);
                    _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("key_type_kind", _v327(_v1363))), _v1941), _v1892("value_type_kind", _v327(_v1365)));
                } else {
                    if ((_v319 == _v312)) {
                        bkr_i64 _v1367 = _v534(_v520);
                        bkr_i64 _v1368 = _v535(_v520);
                        _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("inner_type_kind", _v327(_v1367)));
                        if (((_v1367 == _v309) && (_v1368 >= 0))) {
                            _v1193 = bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("inner_struct_name", _v1945(_v425, _v1368)));
                        }
                    } else {
                        if ((_v319 == _v313)) {
                            bkr_i64 _v1370 = _v534(_v520);
                            bkr_i64 _v1372 = _v535(_v520);
                            _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1193, _v1941), _v1892("ok_type_kind", _v327(_v1370))), _v1941), _v1892("err_type_kind", _v327(_v1372)));
                        }
                    }
                }
            }
        }
    }
    return bkr_str_concat(_v1193, "}");
}

bkr_str _v2045(bkr_i64 _v1239, bkr_i64 _v1655) {
    return _v2046(_v1548(_v1239), _v1655);
}

bkr_str _v2046(_v1531 _v1239, bkr_i64 _v1655) {
    if (_v523(_v1655)) {
        return _v2042(_v316, "absent");
    }
    return _v2047(_v1239, _v537(_v1655));
}

bkr_str _v2047(_v1531 _v1239, _v426 _v541) {
    return _v2042(_v1653(_v1239, _v541), "bootstrap_inferred");
}

bkr_i64 _v2048(bkr_i64 _v1239, bkr_i64 _v515, bkr_i64 _v1655) {
    return _v2049(_v1548(_v1239), _v515, _v1655);
}

bkr_i64 _v2049(_v1531 _v1239, bkr_i64 _v515, bkr_i64 _v1655) {
    if (_v525(_v515)) {
        bkr_i64 _v1551 = _v1552(_v1239);
        if ((_v1551 != 0)) {
            return _v2050(_v506(_v1551), _v516(_v515));
        }
        return _v529(_v516(_v515));
    }
    if (_v525(_v1655)) {
        return _v1653(_v1239, _v537(_v1655));
    }
    return _v316;
}

bkr_i64 _v2051(bkr_i64 _v1239, bkr_i64 _v355, bkr_i64 _v515) {
    if (_v525(_v515)) {
        _v2052(_v1548(_v1239), _v355, _v516(_v515));
    }
    return _v1239;
}

_v1531 _v2052(_v1531 _v1239, bkr_i64 _v355, _v346 _v520) {
    if ((_v529(_v520) == _v308)) {
        _v1611(_v1239, _v355, _v532(_v520), _v533(_v520));
    }
    if ((_v529(_v520) == _v310)) {
        bkr_i64 _v1687 = _v532(_v520);
        if (((_v1687 != _v316) && (_v1687 != 0))) {
            _v1611(_v1239, _v355, _v1687, 0);
        }
    }
    return _v1239;
}

bkr_i64 _v2053(bkr_i64 _v0) {
    return _v1534(_v2054(_v476(_v0)));
}

_v1531 _v2054(_v341 _v1530) {
    bkr_i64 _v425 = _v903(_v1530);
    _v1531 _v1239 = _v1535(_v1945(_v425, _v663(_v1530)), _v425);
    _v1549(_v1239, _v507(_v1530));
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        bkr_i64 _v319 = _v568(_v562);
        if ((_v319 == _v224)) {
            bkr_i64 _v1142 = _v874(_v562);
            bkr_i64 _v1360 = _v307;
            if (_v525(_v1142)) {
                _v1360 = _v2050(_v1530, _v516(_v1142));
            }
            _v1607(_v1239, _v868(_v562), _v1360);
        } else {
            if ((_v319 == _v249)) {
                bkr_i64 _v2055 = _v2049(_v1239, _v881(_v562), _v884(_v562));
                _v1609(_v1239, _v878(_v562), _v2055);
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_str _v2056(bkr_str _v1193, bkr_str _v557) {
    if ((bkr_len((bkr_str)(intptr_t)(_v1193)) > 1)) {
        return bkr_str_concat(bkr_str_concat(_v1193, ","), _v557);
    }
    return bkr_str_concat(_v1193, _v557);
}

bkr_str _v2057(bkr_str _v1193, bkr_str _v423) {
    if ((bkr_len((bkr_str)(intptr_t)(_v423)) <= 2)) {
        return _v1193;
    }
    bkr_str _v1999 = substring(_v423, 1, (bkr_len((bkr_str)(intptr_t)(_v423)) - 1));
    if ((bkr_len((bkr_str)(intptr_t)(_v1193)) > 1)) {
        return bkr_str_concat(bkr_str_concat(_v1193, ","), _v1999);
    }
    return bkr_str_concat(_v1193, _v1999);
}

bkr_str _v2058(bkr_i64 _v425, bkr_i64 _v1135) {
    return _v2059(_v425, _v476(_v1135));
}

bkr_str _v2059(bkr_i64 _v425, _v341 _v1507) {
    bkr_str _v1941 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("name", _v1945(_v425, _v862(_v1507)))), _v1941), _v1893("source_start", _v511(_v1507))), _v1941), _v1893("source_end", _v512(_v1507))), _v1941), _v1895("declared_type", _v2043(_v425, _v865(_v1507), "declared"))), "}");
}

bkr_str _v2060(bkr_i64 _v425, bkr_i64 _v411) {
    return _v2061(_v425, _v604(_v411));
}

bkr_str _v2061(bkr_i64 _v425, _v434 _v1141) {
    bkr_str _v1193 = "[";
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1141))) {
        _v1193 = _v2056(_v1193, _v2059(_v425, _v912(_v1141, _v1168)));
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2062(bkr_i64 _v425, bkr_i64 _v1150) {
    return _v2063(_v425, _v476(_v1150));
}

bkr_str _v2063(bkr_i64 _v425, _v341 _v1432) {
    bkr_str _v1941 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("name", _v1945(_v425, _v891(_v1432)))), _v1941), _v1893("source_start", _v511(_v1432))), _v1941), _v1893("source_end", _v512(_v1432))), _v1941), _v1895("declared_type", _v2043(_v425, _v894(_v1432), "declared"))), "}");
}

bkr_str _v2064(bkr_i64 _v425, bkr_i64 _v416) {
    return _v2065(_v425, _v604(_v416));
}

bkr_str _v2065(bkr_i64 _v425, _v434 _v1158) {
    bkr_str _v1193 = "[";
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1158))) {
        _v1193 = _v2056(_v1193, _v2063(_v425, _v912(_v1158, _v1168)));
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2066(bkr_i64 _v425, bkr_i64 _v557) {
    return _v2067(_v425, _v559(_v557));
}

bkr_str _v2067(bkr_i64 _v425, _v428 _v562) {
    _v341 _v1967 = _v587(_v562);
    bkr_str _v1941 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("name", _v1945(_v425, _v886(_v562)))), _v1941), _v1893("source_start", _v511(_v1967))), _v1941), _v1893("source_end", _v512(_v1967))), _v1941), _v1895("fields", _v2065(_v425, _v889(_v562)))), "}");
}

bkr_str _v2068(bkr_i64 _v0) {
    return _v2069(_v476(_v0));
}

bkr_str _v2069(_v341 _v1530) {
    bkr_i64 _v425 = _v903(_v1530);
    bkr_str _v1193 = "[";
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if ((_v568(_v562) == _v254)) {
            _v1193 = _v2056(_v1193, _v2067(_v425, _v562));
        }
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2070(bkr_i64 _v1239, bkr_i64 _v425, bkr_i64 _v557) {
    return _v2071(_v1548(_v1239), _v425, _v559(_v557));
}

bkr_str _v2071(_v1531 _v1239, bkr_i64 _v425, _v428 _v562) {
    _v341 _v1967 = _v587(_v562);
    bkr_str _v1941 = ",";
    bkr_i64 _v515 = _v881(_v562);
    bkr_i64 _v387 = _v884(_v562);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("name", _v1945(_v425, _v878(_v562)))), _v1941), _v1893("source_start", _v511(_v1967))), _v1941), _v1893("source_end", _v512(_v1967))), _v1941), _v1895("declared_type", _v2043(_v425, _v515, "declared"))), _v1941), _v1895("inferred_type", _v2046(_v1239, _v387))), _v1941), _v1895("effective_type", _v2042(_v2049(_v1239, _v515, _v387), "effective"))), "}");
}

bkr_str _v2072(bkr_i64 _v0, bkr_i64 _v1239) {
    return _v2073(_v476(_v0), _v1548(_v1239));
}

bkr_str _v2073(_v341 _v1530, _v1531 _v1239) {
    bkr_i64 _v425 = _v903(_v1530);
    bkr_str _v1193 = "[";
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if ((_v568(_v562) == _v249)) {
            _v1193 = _v2056(_v1193, _v2071(_v1239, _v425, _v562));
        }
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2074(bkr_i64 _v1239, bkr_i64 _v425, bkr_i64 _v370) {
    return _v2075(_v1548(_v1239), _v425, _v550(_v370));
}

bkr_str _v2075(_v1531 _v1239, bkr_i64 _v425, _v427 _v553) {
    _v341 _v2076 = _v586(_v553);
    bkr_str _v1941 = ",";
    bkr_i64 _v515 = _v760(_v553);
    bkr_i64 _v366 = _v763(_v553);
    bkr_i64 _v2077 = _v2049(_v1239, _v515, _v366);
    bkr_str _v1193 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("name", _v1945(_v425, _v757(_v553)))), _v1941), _v1893("source_start", _v511(_v2076))), _v1941), _v1893("source_end", _v512(_v2076))), _v1941), _v1895("declared_type", _v2043(_v425, _v515, "declared"))), _v1941), _v1895("inferred_type", _v2046(_v1239, _v366))), _v1941), _v1895("effective_type", _v2042(_v2077, "effective")));
    return bkr_str_concat(_v1193, "}");
}

bkr_i64 _v2078(bkr_i64 _v1239, bkr_i64 _v370) {
    _v2079(_v1548(_v1239), _v550(_v370));
    return _v1239;
}

_v1531 _v2079(_v1531 _v1239, _v427 _v553) {
    bkr_i64 _v515 = _v760(_v553);
    bkr_i64 _v366 = _v763(_v553);
    bkr_i64 _v319 = _v2049(_v1239, _v515, _v366);
    bkr_i64 _v355 = _v757(_v553);
    _v1592(_v1239, _v355, _v319);
    if (_v525(_v515)) {
        _v2052(_v1239, _v355, _v516(_v515));
    } else {
        if (_v525(_v366)) {
            _v426 _v1693 = _v537(_v366);
            bkr_i64 _v1694 = _v544(_v1693);
            if ((_v1694 == _v252)) {
                _v434 _v994 = _v701(_v1693);
                bkr_i64 _v1691 = _v906(_v994);
                if ((_v1691 > 0)) {
                    bkr_i64 _v953 = _v1653(_v1239, _v537(_v909(_v994, 0)));
                    _v1611(_v1239, _v355, _v953, _v1691);
                }
            } else {
                if ((_v1694 == _v239)) {
                    bkr_i64 _v1691 = _v706(_v1693);
                    bkr_i64 _v953 = _v1653(_v1239, _v704(_v1693));
                    _v1611(_v1239, _v355, _v953, _v1691);
                }
            }
        }
    }
    return _v1239;
}

bkr_str _v2080(bkr_i64 _v1239, bkr_i64 _v425, bkr_i64 _v577) {
    return _v2081(_v1548(_v1239), _v425, _v579(_v577));
}

bkr_str _v2081(_v1531 _v1239, bkr_i64 _v425, _v429 _v582) {
    bkr_str _v1193 = "[";
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v589(_v582))) {
        _v427 _v553 = _v1107(_v582, _v1168);
        bkr_i64 _v319 = _v555(_v553);
        if ((_v319 == _v228)) {
            _v1193 = _v2056(_v1193, _v2075(_v1239, _v425, _v553));
            _v2079(_v1239, _v553);
        } else {
            if ((_v319 == _v230)) {
                _v1193 = _v2057(_v1193, _v2081(_v1239, _v425, _v829(_v553)));
                bkr_i64 _v377 = _v832(_v553);
                if (_v525(_v377)) {
                    _v1193 = _v2057(_v1193, _v2081(_v1239, _v425, _v578(_v377)));
                }
            } else {
                if ((_v319 == _v231)) {
                    _v1193 = _v2057(_v1193, _v2081(_v1239, _v425, _v851(_v553)));
                } else {
                    if ((_v319 == _v236)) {
                        _v1592(_v1239, _v834(_v553), _v303);
                        _v1193 = _v2057(_v1193, _v2081(_v1239, _v425, _v844(_v553)));
                    } else {
                        if ((_v319 == _v237)) {
                            _v1193 = _v2057(_v1193, _v2081(_v1239, _v425, _v846(_v553)));
                        }
                    }
                }
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2082(bkr_i64 _v1239, bkr_i64 _v370) {
    return _v2083(_v1548(_v1239), _v550(_v370));
}

bkr_str _v2083(_v1531 _v1239, _v427 _v553) {
    _v341 _v2076 = _v586(_v553);
    bkr_str _v1941 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1893("source_start", _v511(_v2076))), _v1941), _v1893("source_end", _v512(_v2076))), _v1941), _v1895("expr_type", _v2046(_v1239, _v768(_v553)))), "}");
}

bkr_str _v2084(bkr_i64 _v1239, bkr_i64 _v425, bkr_i64 _v577) {
    return _v2085(_v1548(_v1239), _v425, _v579(_v577));
}

bkr_str _v2085(_v1531 _v1239, bkr_i64 _v425, _v429 _v582) {
    bkr_str _v1193 = "[";
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v589(_v582))) {
        _v427 _v553 = _v1107(_v582, _v1168);
        bkr_i64 _v319 = _v555(_v553);
        if ((_v319 == _v229)) {
            _v1193 = _v2056(_v1193, _v2083(_v1239, _v553));
        } else {
            if ((_v319 == _v230)) {
                _v1193 = _v2057(_v1193, _v2085(_v1239, _v425, _v829(_v553)));
                bkr_i64 _v377 = _v832(_v553);
                if (_v525(_v377)) {
                    _v1193 = _v2057(_v1193, _v2085(_v1239, _v425, _v578(_v377)));
                }
            } else {
                if ((_v319 == _v231)) {
                    _v1193 = _v2057(_v1193, _v2085(_v1239, _v425, _v851(_v553)));
                } else {
                    if ((_v319 == _v236)) {
                        _v1193 = _v2057(_v1193, _v2085(_v1239, _v425, _v844(_v553)));
                    } else {
                        if ((_v319 == _v237)) {
                            _v1193 = _v2057(_v1193, _v2085(_v1239, _v425, _v846(_v553)));
                        }
                    }
                }
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_i64 _v2086(bkr_i64 _v0, bkr_i64 _v929) {
    return _v1534(_v2087(_v476(_v0), _v559(_v929)));
}

_v1531 _v2087(_v341 _v1530, _v428 _v1514) {
    _v1531 _v1239 = _v2054(_v1530);
    _v434 _v1141 = _v871(_v1514);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1141))) {
        _v341 _v1507 = _v912(_v1141, _v1168);
        bkr_i64 _v2088 = _v865(_v1507);
        bkr_i64 _v2089 = _v862(_v1507);
        bkr_i64 _v2090 = _v303;
        if (_v525(_v2088)) {
            _v2090 = _v2050(_v1530, _v516(_v2088));
        }
        _v1592(_v1239, _v2089, _v2090);
        if (_v525(_v2088)) {
            _v2052(_v1239, _v2089, _v516(_v2088));
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_str _v2091(bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v557) {
    return _v2092(_v476(_v0), _v425, _v559(_v557));
}

bkr_str _v2092(_v341 _v1530, bkr_i64 _v425, _v428 _v562) {
    _v341 _v1967 = _v587(_v562);
    bkr_str _v1941 = ",";
    _v1531 _v1239 = _v2087(_v1530, _v562);
    _v429 _v1123 = _v876(_v562);
    bkr_str _v2093 = _v2081(_v1239, _v425, _v1123);
    bkr_str _v2094 = _v2085(_v1239, _v425, _v1123);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("name", _v1945(_v425, _v868(_v562)))), _v1941), _v1893("source_start", _v511(_v1967))), _v1941), _v1893("source_end", _v512(_v1967))), _v1941), _v1895("return_type", _v2043(_v425, _v874(_v562), "declared"))), _v1941), _v1895("params", _v2061(_v425, _v871(_v562)))), _v1941), _v1895("locals", _v2093)), _v1941), _v1895("returns", _v2094)), "}");
}

bkr_str _v2095(bkr_i64 _v0) {
    return _v2096(_v476(_v0));
}

bkr_str _v2096(_v341 _v1530) {
    bkr_i64 _v425 = _v903(_v1530);
    bkr_str _v1193 = "[";
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if ((_v568(_v562) == _v224)) {
            _v1193 = _v2056(_v1193, _v2092(_v1530, _v425, _v562));
        }
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2097(bkr_i64 _v0) {
    bkr_str _v1941 = ",";
    _v341 _v1530 = _v476(_v0);
    _v434 _v1183 = _v898(_v1530);
    bkr_bool _v1993 = _v1933(_v1530);
    bkr_str _v2098 = "[]";
    bkr_str _v2099 = "[]";
    bkr_str _v2100 = "[]";
    if (_v1993) {
        _v1531 _v1239 = _v2054(_v1530);
        _v2098 = _v2069(_v1530);
        _v2099 = _v2073(_v1530, _v1239);
        _v2100 = _v2096(_v1530);
    }
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("schema_version", "bunker.self_host.type_graph.v1")), _v1941), _v1892("representation", "bootstrap_codegen_inference")), _v1941), _v1894("complete", BKR_FALSE)), _v1941), _v1894("declared_types", _v1993)), _v1941), _v1894("local_inference", _v1993)), _v1941), _v1894("truncated", (!_v1993))), _v1941), _v1892("known_limits", "Derived from declarations plus bootstrap C codegen inference; no real Bunker typechecker, generic graph, trait constraints, exhaustiveness graph, or cross-module type graph yet. Detail arrays are omitted when interned names exceed AST_REPORT_FULL_WALK_NAME_LIMIT.")), _v1941), _v1895("summary", bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1893("function_count", _v1969(_v1183, _v224))), _v1941), _v1893("struct_count", _v1969(_v1183, _v254))), _v1941), _v1893("const_count", _v1969(_v1183, _v249))), "}"))), _v1941), _v1895("structs", _v2098)), _v1941), _v1895("constants", _v2099)), _v1941), _v1895("functions", _v2100)), "}");
}

bkr_str _v2101(bkr_i64 _v0) {
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("/* BUNKER_TYPE_GRAPH_JSON: ", _v2097(_v0)), from_char_code(10)), "*/"), from_char_code(10));
}

bkr_str _v2102(bkr_str _v319, bkr_str _v2103, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v1936, bkr_i64 _v1937, bkr_str _v1264, bkr_str _v1267, bkr_str _v2104) {
    return _v2105(_v319, _v2103, _v1348, _v2001, _v1936, _v1937, _v1264, _v1267, "[]", _v2104);
}

bkr_str _v2105(bkr_str _v319, bkr_str _v2103, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v1936, bkr_i64 _v1937, bkr_str _v1264, bkr_str _v1267, bkr_str _v2106, bkr_str _v2104) {
    bkr_str _v1941 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("phase", "resolver")), _v1941), _v1892("kind", _v319)), _v1941), _v1892("rule_id", _v319)), _v1941), _v1892("error_code", _v2103)), _v1941), _v1892("severity", "error")), _v1941), _v1892("name", _v1348)), _v1941), _v1892("scope", _v2001)), _v1941), _v1893("source_start", _v1936)), _v1941), _v1893("source_end", _v1937)), _v1941), _v1894("span_known", ((_v1936 != _v268) && (_v1937 != _v268)))), _v1941), _v1892("expected", _v1264)), _v1941), _v1892("actual", _v1267)), _v1941), _v1895("related_declarations", _v2106)), _v1941), _v1892("suggested_action", _v2104)), _v1941), _v1892("fix_applicability", "manual_review")), _v1941), _v1892("fix_confidence", "medium")), _v1941), _v1894("safe_edit_available", BKR_FALSE)), _v1941), _v1895("suggested_edits", _v1942())), _v1941), _v1892("repair_hint", _v2104)), "}");
}

bkr_str _v2107(bkr_str _v319, bkr_str _v2103, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v447, bkr_str _v1264, bkr_str _v1267, bkr_str _v2104) {
    return _v2108(_v319, _v2103, _v1348, _v2001, _v476(_v447), _v1264, _v1267, _v2104);
}

bkr_str _v2108(bkr_str _v319, bkr_str _v2103, bkr_str _v1348, bkr_str _v2001, _v341 _v452, bkr_str _v1264, bkr_str _v1267, bkr_str _v2104) {
    return _v2109(_v319, _v2103, _v1348, _v2001, _v452, _v1264, _v1267, "[]", _v2104);
}

bkr_str _v2109(bkr_str _v319, bkr_str _v2103, bkr_str _v1348, bkr_str _v2001, _v341 _v452, bkr_str _v1264, bkr_str _v1267, bkr_str _v2106, bkr_str _v2104) {
    return _v2105(_v319, _v2103, _v1348, _v2001, _v511(_v452), _v512(_v452), _v1264, _v1267, _v2106, _v2104);
}

bkr_str _v2110(bkr_str _v319, bkr_str _v2103, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v463, bkr_str _v1264, bkr_str _v1267, bkr_str _v2104) {
    return _v2111(_v319, _v2103, _v1348, _v2001, _v592(_v463), _v1264, _v1267, _v2104);
}

bkr_str _v2111(bkr_str _v319, bkr_str _v2103, bkr_str _v1348, bkr_str _v2001, _v433 _v472, bkr_str _v1264, bkr_str _v1267, bkr_str _v2104) {
    return _v2102(_v319, _v2103, _v1348, _v2001, _v601(_v472), _v602(_v472), _v1264, _v1267, _v2104);
}

bkr_i64 _v2112(bkr_i64 _v1239, bkr_str _v1348, bkr_str _v2001, bkr_str _v2113, bkr_i64 _v447) {
    return _v2114(_v1239, _v1348, _v2001, _v2113, _v476(_v447));
}

bkr_i64 _v2114(bkr_i64 _v1239, bkr_str _v1348, bkr_str _v2001, bkr_str _v2113, _v341 _v452) {
    bkr_str _v2115 = bkr_str_concat(bkr_str_concat("Rename this ", _v2113), " or remove the earlier declaration with the same name in this scope.");
    return _v1950(_v1239, _v2108("duplicate_declaration", "BKR_SELF_DUPLICATE_SYMBOL", _v1348, _v2001, _v452, bkr_str_concat(bkr_str_concat("unique ", _v2113), " name"), _v1348, _v2115));
}

bkr_i64 _v2116(bkr_i64 _v1239, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v463) {
    return _v2117(_v1239, _v1348, _v2001, _v592(_v463));
}

bkr_i64 _v2117(bkr_i64 _v1239, bkr_str _v1348, bkr_str _v2001, _v433 _v472) {
    bkr_str _v2115 = "Rename this pattern binding or remove the earlier binding with the same name in this pattern scope.";
    return _v1950(_v1239, _v2111("duplicate_declaration", "BKR_SELF_DUPLICATE_SYMBOL", _v1348, _v2001, _v472, "unique pattern binding", _v1348, _v2115));
}

bkr_i64 _v2118(bkr_i64 _v1239, bkr_str _v1348, bkr_str _v2001, bkr_str _v2119, bkr_i64 _v447, bkr_str _v1264) {
    return _v2120(_v1239, _v1348, _v2001, _v2119, _v476(_v447), _v1264);
}

bkr_i64 _v2120(bkr_i64 _v1239, bkr_str _v1348, bkr_str _v2001, bkr_str _v2119, _v341 _v452, bkr_str _v1264) {
    return _v2121(_v1239, _v1348, _v2001, _v2119, _v452, _v1264, "[]");
}

bkr_i64 _v2121(bkr_i64 _v1239, bkr_str _v1348, bkr_str _v2001, bkr_str _v2119, _v341 _v452, bkr_str _v1264, bkr_str _v2106) {
    bkr_str _v2115 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Declare ", _v1348), " in scope "), _v2001), ", import it through a real module, or correct the misspelled reference.");
    return _v1950(_v1239, _v2109("unresolved_reference", "BKR_SELF_UNRESOLVED_SYMBOL", _v1348, _v2001, _v452, _v1264, bkr_str_concat(bkr_str_concat(_v2119, " "), _v1348), _v2106, _v2115));
}

bkr_str _v2122(bkr_str _v1193, bkr_str _v557) {
    if ((bkr_len((bkr_str)(intptr_t)(_v1193)) > 1)) {
        return bkr_str_concat(bkr_str_concat(_v1193, ","), _v557);
    }
    return bkr_str_concat(_v1193, _v557);
}

bkr_str _v2123(bkr_str _v319, bkr_str _v1348, _v341 _v452) {
    bkr_str _v1941 = ",";
    bkr_i64 _v1936 = _v511(_v452);
    bkr_i64 _v1937 = _v512(_v452);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("kind", _v319)), _v1941), _v1892("name", _v1348)), _v1941), _v1893("source_start", _v1936)), _v1941), _v1893("source_end", _v1937)), _v1941), _v1894("span_known", ((_v1936 != _v268) && (_v1937 != _v268)))), "}");
}

bkr_str _v2124(_v341 _v1530, bkr_i64 _v425) {
    bkr_str _v1193 = "[";
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if ((_v568(_v562) == _v224)) {
            _v1193 = _v2122(_v1193, _v2123("function", _v1945(_v425, _v868(_v562)), _v587(_v562)));
        }
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2125(_v341 _v1530, bkr_i64 _v425) {
    bkr_str _v1193 = "[";
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if ((_v568(_v562) == _v249)) {
            _v1193 = _v2122(_v1193, _v2123("const", _v1945(_v425, _v878(_v562)), _v587(_v562)));
        }
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2126(_v341 _v1530, bkr_i64 _v425) {
    bkr_str _v1193 = "[";
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if ((_v568(_v562) == _v254)) {
            _v1193 = _v2122(_v1193, _v2123("struct", _v1945(_v425, _v886(_v562)), _v587(_v562)));
        }
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2127(_v341 _v1530, bkr_i64 _v425, bkr_i64 _v1503) {
    bkr_str _v1193 = "[";
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if (((_v568(_v562) == _v254) && (_v886(_v562) == _v1503))) {
            _v434 _v1158 = _v889(_v562);
            bkr_i64 _v1629 = 0;
            while ((_v1629 < _v906(_v1158))) {
                _v341 _v1432 = _v912(_v1158, _v1629);
                _v1193 = _v2122(_v1193, _v2123("field", _v1945(_v425, _v891(_v1432)), _v1432));
                _v1629 = (_v1629 + 1);
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_bool _v2128(bkr_str _v1348) {
    if (bkr_str_eq(_v1348, "Some")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "len")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "strlen")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "print")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "println")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "log")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "read_file")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "write_file")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "file_exists")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "file_set_executable")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "vec_new")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "vec_push")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "vec_get")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "vec_set")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "vec_len")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "vec_pop")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "vec_clear")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "hashmap_new")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "hashmap_insert")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "hashmap_get")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "hashmap_contains")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "hashmap_remove")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "hashmap_keys")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "hashmap_len")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "hashmap_clear")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "char_at")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "char_code")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "char_code_at")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "substring")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "contains")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "starts_with")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "ends_with")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "trim")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "parse_int")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "parse_int_result")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "read_file_result")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "str_index_of")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "str_replace")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "str_split")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "str_to_upper")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "str_to_lower")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "str_repeat")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "path_join")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "path_dir")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "path_base")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "path_ext")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "path_is_abs")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "env_var")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "env_get")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "env_set")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "env_has")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "time_now_ms")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "time_now_unix")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "runtime_version_major")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "runtime_version_minor")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "runtime_version_patch")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "runtime_version_str")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "bytes_new")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "bytes_len")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "bytes_capacity")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "bytes_get")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "bytes_set")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "bytes_push")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "bytes_from_str")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "bytes_to_str")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "slice_new")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "slice_len")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "slice_get")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "slice_sub")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "slice_to_vec")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "slice_contains")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "vec_as_slice")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "vec_slice")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "bytes_as_slice")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "bytes_slice")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "path_exists")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "path_is_file")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "path_is_dir")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "file_read")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "file_write")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "file_size")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "file_remove")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "file_read_bytes")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "file_write_bytes")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "dir_create")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "dir_remove")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "process_run")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "process_run_status")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "process_exit")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "process_pid")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "process_is_sandboxed")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "write_file_result")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "hashmap_get_opt")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "vec_get_opt")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "vec_pop_opt")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "vec_contains")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "vec_is_empty")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "vec_clone")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "vec_reverse")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "hashmap_is_empty")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "hashmap_values")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "vec_map")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "vec_filter")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "vec_fold")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "vec_find")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "Ok")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "Err")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "panic")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "assert")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "int_to_string")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "from_char_code")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "join_lines")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "result_ok")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "result_err")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "result_is_ok")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "result_is_err")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "result_unwrap")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "result_unwrap_err")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "result_tag")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "result_value")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "bkr_tuple2")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "bkr_tuple3")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "bkr_tuple_get")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "args_count")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1348, "arg_at")) {
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_bool _v2129(bkr_i64 _v0, bkr_i64 _v355) {
    return _v2130(_v476(_v0), _v355);
}

bkr_bool _v2130(_v341 _v1530, bkr_i64 _v355) {
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if (((_v568(_v562) == _v224) && (_v868(_v562) == _v355))) {
            return BKR_TRUE;
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_FALSE;
}

bkr_bool _v2131(bkr_i64 _v0, bkr_i64 _v355) {
    return _v2132(_v476(_v0), _v355);
}

bkr_bool _v2132(_v341 _v1530, bkr_i64 _v355) {
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if (((_v568(_v562) == _v249) && (_v878(_v562) == _v355))) {
            return BKR_TRUE;
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_FALSE;
}

bkr_bool _v2133(bkr_i64 _v0, bkr_i64 _v355) {
    return _v2134(_v476(_v0), _v355);
}

bkr_bool _v2135(_v341 _v1530, bkr_i64 _v355) {
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if (((_v568(_v562) == _v260) && (_v1177(_v562) == _v355))) {
            return BKR_TRUE;
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_FALSE;
}

bkr_bool _v2134(_v341 _v1530, bkr_i64 _v355) {
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if (((_v568(_v562) == _v254) && (_v886(_v562) == _v355))) {
            return BKR_TRUE;
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_FALSE;
}

bkr_bool _v2136(_v341 _v1530, bkr_i64 _v355) {
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if (((_v568(_v562) == _v259) && (_v1164(_v562) == _v355))) {
            return BKR_TRUE;
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_FALSE;
}

bkr_bool _v2137(bkr_i64 _v0, bkr_i64 _v1503, bkr_i64 _v1658) {
    return _v2138(_v476(_v0), _v1503, _v1658);
}

bkr_bool _v2138(_v341 _v1530, bkr_i64 _v1503, bkr_i64 _v1658) {
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if (((_v568(_v562) == _v254) && (_v886(_v562) == _v1503))) {
            _v434 _v1158 = _v889(_v562);
            bkr_i64 _v1629 = 0;
            while ((_v1629 < _v906(_v1158))) {
                _v341 _v1432 = _v912(_v1158, _v1629);
                if ((_v891(_v1432) == _v1658)) {
                    return BKR_TRUE;
                }
                _v1629 = (_v1629 + 1);
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_FALSE;
}

bkr_i64 _v2139(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v515, bkr_str _v2001) {
    return _v2140(_v1239, _v476(_v0), _v425, _v515, _v2001);
}

bkr_i64 _v2140(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, bkr_i64 _v515, bkr_str _v2001) {
    if (_v525(_v515)) {
        _v1239 = _v2141(_v1239, _v1530, _v425, _v516(_v515), _v2001);
    }
    return _v1239;
}

bkr_i64 _v2141(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v346 _v520, bkr_str _v2001) {
    if ((_v529(_v520) == _v309)) {
        bkr_i64 _v355 = _v531(_v520);
        if ((((!_v2134(_v1530, _v355)) && (!_v2135(_v1530, _v355))) && (!_v2136(_v1530, _v355)))) {
            _v1239 = _v2121(_v1239, _v1945(_v425, _v355), _v2001, "type_reference", _v585(_v520), "declared struct type", _v2126(_v1530, _v425));
        }
    }
    return _v1239;
}

bkr_i64 _v2142(bkr_i64 _v1239, bkr_i64 _v425, bkr_i64 _v463, bkr_str _v2001, bkr_i64 _v2143) {
    return _v2144(_v1239, _v425, _v592(_v463), _v2001, _v2143);
}

bkr_i64 _v2144(bkr_i64 _v1239, bkr_i64 _v425, _v433 _v472, bkr_str _v2001, bkr_i64 _v2143) {
    bkr_i64 _v319 = _v596(_v472);
    if (((((_v319 == _v285) || (_v319 == _v287)) || (_v319 == _v290)) || (_v319 == _v291))) {
        bkr_i64 _v355 = _v597(_v472);
        if ((_v355 >= 0)) {
            if (_v1951(_v2143, _v355)) {
                _v1239 = _v2117(_v1239, _v1945(_v425, _v355), _v2001, _v472);
            } else {
                vec_push(_v2143, _v355);
            }
        }
        bkr_i64 _v345 = _v598(_v472);
        if ((_v345 != 0)) {
            _v433 _v1393 = _v591(_v345);
            _v1239 = _v2144(_v1239, _v425, _v1393, _v2001, _v2143);
        }
    }
    if ((_v319 == _v292)) {
        bkr_i64 _v345 = _v598(_v472);
        if ((_v345 != 0)) {
            bkr_i64 _v1375 = ((bkr_i64)(_v345));
            bkr_i64 _v1168 = 0;
            while ((_v1168 < vec_len(_v1375))) {
                _v433 _v1393 = _v591(vec_get(_v1375, _v1168));
                _v1239 = _v2144(_v1239, _v425, _v1393, _v2001, _v2143);
                _v1168 = (_v1168 + 1);
            }
        } else {
            bkr_i64 _v2010 = _v599(_v472);
            bkr_i64 _v2011 = _v600(_v472);
            bkr_i64 _v2012 = _v597(_v472);
            if ((_v2010 >= 0)) {
                vec_push(_v2143, _v2010);
            }
            if ((_v2011 >= 0)) {
                vec_push(_v2143, _v2011);
            }
            if ((_v2012 >= 0)) {
                vec_push(_v2143, _v2012);
            }
        }
    }
    if ((_v319 == _v293)) {
        bkr_i64 _v2010 = _v599(_v472);
        bkr_i64 _v2011 = _v600(_v472);
        bkr_i64 _v2012 = _v598(_v472);
        if ((_v2010 >= 0)) {
            vec_push(_v2143, _v2010);
        }
        if ((_v2011 >= 0)) {
            vec_push(_v2143, _v2011);
        }
        if ((_v2012 >= 0)) {
            vec_push(_v2143, _v2012);
        }
    }
    if ((_v319 == _v289)) {
        bkr_i64 _v2010 = _v599(_v472);
        bkr_i64 _v2011 = _v600(_v472);
        if ((_v2010 >= 0)) {
            vec_push(_v2143, _v2010);
        }
        if ((_v2011 >= 0)) {
            vec_push(_v2143, _v2011);
        }
    }
    return _v1239;
}

bkr_i64 _v2145(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v1655, bkr_str _v2001, bkr_i64 _v2143) {
    return _v2146(_v1239, _v476(_v0), _v425, _v1655, _v2001, _v2143);
}

bkr_i64 _v2146(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, bkr_i64 _v1655, bkr_str _v2001, bkr_i64 _v2143) {
    if (_v523(_v1655)) {
        return _v1239;
    }
    return _v2147(_v1239, _v1530, _v425, _v537(_v1655), _v2001, _v2143);
}

bkr_i64 _v2147(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v426 _v541, bkr_str _v2001, bkr_i64 _v2143) {
    _v341 _v2148 = _v546(_v541);
    bkr_i64 _v319 = _v544(_v541);
    if ((_v319 == _v245)) {
        bkr_i64 _v355 = _v662(_v541);
        bkr_str _v1348 = _v1945(_v425, _v355);
        if ((((((!bkr_str_eq(_v1348, "None")) && (!_v1951(_v2143, _v355))) && (!_v2132(_v1530, _v355))) && (!_v2136(_v1530, _v355))) && (bkr_str_index_of((bkr_str)(intptr_t)(_v1348), (bkr_str)(intptr_t)("::")) < 0))) {
            _v1239 = _v2121(_v1239, _v1348, _v2001, "identifier", _v2148, "local, parameter, for binding, pattern binding, or constant", _v2125(_v1530, _v425));
        }
    } else {
        if ((_v319 == _v261)) {
            _v426 _v1021 = _v694(_v541);
            _v1239 = _v2147(_v1239, _v1530, _v425, _v1021, _v2001, _v2143);
            _v434 _v1015 = _v698(_v541);
            bkr_i64 _v1168 = 0;
            while ((_v1168 < _v906(_v1015))) {
                _v341 _v1425 = _v912(_v1015, _v1168);
                _v1239 = _v2147(_v1239, _v1530, _v425, _v539(_v1425), _v2001, _v2143);
                _v1168 = (_v1168 + 1);
            }
        } else {
            if ((_v319 == _v244)) {
                bkr_i64 _v355 = _v688(_v541);
                bkr_str _v1348 = _v1945(_v425, _v355);
                if ((((!_v2128(_v1348)) && (!_v2130(_v1530, _v355))) && (!_v2134(_v1530, _v355)))) {
                    _v1239 = _v2121(_v1239, _v1348, _v2001, "function_call", _v2148, "declared function or supported bootstrap builtin", _v2124(_v1530, _v425));
                }
                _v434 _v1015 = _v691(_v541);
                bkr_i64 _v1168 = 0;
                while ((_v1168 < _v906(_v1015))) {
                    _v341 _v1425 = _v912(_v1015, _v1168);
                    _v1239 = _v2147(_v1239, _v1530, _v425, _v539(_v1425), _v2001, _v2143);
                    _v1168 = (_v1168 + 1);
                }
            } else {
                if ((_v319 == _v257)) {
                    bkr_i64 _v1503 = _v724(_v541);
                    bkr_str _v1681 = _v1945(_v425, _v1503);
                    if ((!_v2134(_v1530, _v1503))) {
                        _v1239 = _v2121(_v1239, _v1681, _v2001, "struct_literal", _v2148, "declared struct", _v2126(_v1530, _v425));
                    }
                    bkr_i64 _v2149 = vec_new();
                    _v435 _v1007 = _v727(_v541);
                    _v434 _v1008 = _v730(_v541);
                    bkr_i64 _v1168 = 0;
                    while ((_v1168 < _v915(_v1007))) {
                        bkr_i64 _v1658 = _v917(_v1007, _v1168);
                        bkr_str _v1044 = _v1945(_v425, _v1658);
                        if (_v1951(_v2149, _v1658)) {
                            _v1239 = _v2120(_v1239, _v1044, _v2001, "field_initializer", _v2148, "one initializer per field");
                        } else {
                            vec_push(_v2149, _v1658);
                            if ((_v2134(_v1530, _v1503) && (!_v2138(_v1530, _v1503, _v1658)))) {
                                _v1239 = _v2121(_v1239, _v1044, _v2001, "field_initializer", _v2148, bkr_str_concat("field declared on struct ", _v1681), _v2127(_v1530, _v425, _v1503));
                            }
                        }
                        _v341 _v1422 = _v912(_v1008, _v1168);
                        _v1239 = _v2147(_v1239, _v1530, _v425, _v539(_v1422), _v2001, _v2143);
                        _v1168 = (_v1168 + 1);
                    }
                    bkr_i64 _v403 = _v1005(_v541);
                    if ((_v403 != 0)) {
                        _v1239 = _v2147(_v1239, _v1530, _v425, _v537(_v403), _v2001, _v2143);
                    }
                } else {
                    if ((_v319 == _v256)) {
                        _v1239 = _v2147(_v1239, _v1530, _v425, _v537(_v719(_v541)), _v2001, _v2143);
                    } else {
                        if ((_v319 == _v242)) {
                            _v1239 = _v2147(_v1239, _v1530, _v425, _v537(_v674(_v541)), _v2001, _v2143);
                            _v1239 = _v2147(_v1239, _v1530, _v425, _v537(_v677(_v541)), _v2001, _v2143);
                        } else {
                            if ((_v319 == _v240)) {
                                _v1239 = _v2147(_v1239, _v1530, _v425, _v537(_v777(_v541)), _v2001, _v2143);
                            } else {
                                if ((_v319 == _v241)) {
                                    _v1239 = _v2147(_v1239, _v1530, _v425, _v537(_v781(_v541)), _v2001, _v2143);
                                    _v1239 = _v2141(_v1239, _v1530, _v425, _v516(_v782(_v541)), _v2001);
                                } else {
                                    if ((_v319 == _v243)) {
                                        _v1239 = _v2147(_v1239, _v1530, _v425, _v537(_v684(_v541)), _v2001, _v2143);
                                    } else {
                                        if ((_v319 == _v250)) {
                                            _v1239 = _v2147(_v1239, _v1530, _v425, _v537(_v733(_v541)), _v2001, _v2143);
                                            _v1239 = _v2147(_v1239, _v1530, _v425, _v537(_v736(_v541)), _v2001, _v2143);
                                            _v1239 = _v2147(_v1239, _v1530, _v425, _v537(_v739(_v541)), _v2001, _v2143);
                                        } else {
                                            if ((_v319 == _v239)) {
                                                _v1239 = _v2147(_v1239, _v1530, _v425, _v537(_v703(_v541)), _v2001, _v2143);
                                            } else {
                                                if ((_v319 == _v252)) {
                                                    _v434 _v994 = _v701(_v541);
                                                    bkr_i64 _v1168 = 0;
                                                    while ((_v1168 < _v906(_v994))) {
                                                        _v341 _v2016 = _v912(_v994, _v1168);
                                                        _v1239 = _v2147(_v1239, _v1530, _v425, _v539(_v2016), _v2001, _v2143);
                                                        _v1168 = (_v1168 + 1);
                                                    }
                                                } else {
                                                    if ((_v319 == _v253)) {
                                                        _v1239 = _v2147(_v1239, _v1530, _v425, _v537(_v711(_v541)), _v2001, _v2143);
                                                        _v1239 = _v2147(_v1239, _v1530, _v425, _v537(_v714(_v541)), _v2001, _v2143);
                                                    } else {
                                                        if ((_v319 == _v227)) {
                                                            _v1239 = _v2150(_v1239, _v1530, _v425, _v580(_v2148), _v2001, _v2143, _v1952());
                                                        } else {
                                                            if ((_v319 == _v258)) {
                                                                _v1239 = _v2147(_v1239, _v1530, _v425, _v537(_v742(_v541)), _v2001, _v2143);
                                                                _v436 _v620 = _v745(_v541);
                                                                _v434 _v975 = _v748(_v541);
                                                                _v435 _v976 = _v750(_v541);
                                                                bkr_i64 _v1168 = 0;
                                                                while ((_v1168 < _v919(_v620))) {
                                                                    bkr_i64 _v2151 = _v1953(_v2143);
                                                                    bkr_i64 _v2152 = vec_new();
                                                                    _v1239 = _v2144(_v1239, _v425, _v924(_v620, _v1168), _v2001, _v2152);
                                                                    bkr_i64 _v1629 = 0;
                                                                    while ((_v1629 < vec_len(_v2152))) {
                                                                        bkr_i64 _v2153 = vec_get(_v2152, _v1629);
                                                                        vec_push(_v2151, _v2153);
                                                                        _v1629 = (_v1629 + 1);
                                                                    }
                                                                    if ((_v1168 < _v915(_v976))) {
                                                                        bkr_i64 _v2154 = _v917(_v976, _v1168);
                                                                        if ((_v2154 != 0)) {
                                                                            _v1239 = _v2147(_v1239, _v1530, _v425, _v537(_v2154), _v2001, _v2151);
                                                                        }
                                                                    }
                                                                    _v341 _v1123 = _v912(_v975, _v1168);
                                                                    if ((_v509(_v1123) == _v227)) {
                                                                        _v1239 = _v2150(_v1239, _v1530, _v425, _v580(_v1123), _v2001, _v2151, _v1952());
                                                                    } else {
                                                                        _v1239 = _v2147(_v1239, _v1530, _v425, _v539(_v1123), _v2001, _v2151);
                                                                    }
                                                                    _v1168 = (_v1168 + 1);
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return _v1239;
}

bkr_i64 _v2155(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v370, bkr_str _v2001, bkr_i64 _v2143, bkr_i64 _v2156) {
    return _v2157(_v1239, _v476(_v0), _v425, _v550(_v370), _v2001, _v2143, _v2156);
}

bkr_i64 _v2157(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v427 _v553, bkr_str _v2001, bkr_i64 _v2143, bkr_i64 _v2156) {
    _v341 _v2076 = _v586(_v553);
    bkr_i64 _v319 = _v555(_v553);
    if ((_v319 == _v228)) {
        bkr_i64 _v355 = _v757(_v553);
        _v1239 = _v2140(_v1239, _v1530, _v425, _v760(_v553), _v2001);
        _v1239 = _v2146(_v1239, _v1530, _v425, _v763(_v553), _v2001, _v2143);
        if (_v1951(_v2156, _v355)) {
            _v1239 = _v2114(_v1239, _v1945(_v425, _v355), _v2001, "local", _v2076);
        } else {
            vec_push(_v2156, _v355);
        }
        vec_push(_v2143, _v355);
    } else {
        if ((_v319 == _v229)) {
            _v1239 = _v2146(_v1239, _v1530, _v425, _v768(_v553), _v2001, _v2143);
        } else {
            if ((_v319 == _v230)) {
                _v1239 = _v2146(_v1239, _v1530, _v425, _v827(_v553), _v2001, _v2143);
                _v1239 = _v2150(_v1239, _v1530, _v425, _v829(_v553), _v2001, _v2143, _v1952());
                bkr_i64 _v377 = _v832(_v553);
                if (_v525(_v377)) {
                    _v1239 = _v2150(_v1239, _v1530, _v425, _v578(_v377), _v2001, _v2143, _v1952());
                }
            } else {
                if ((_v319 == _v231)) {
                    _v1239 = _v2146(_v1239, _v1530, _v425, _v849(_v553), _v2001, _v2143);
                    _v1239 = _v2150(_v1239, _v1530, _v425, _v851(_v553), _v2001, _v2143, _v1952());
                } else {
                    if ((_v319 == _v236)) {
                        bkr_i64 _v355 = _v834(_v553);
                        _v1239 = _v2146(_v1239, _v1530, _v425, _v837(_v553), _v2001, _v2143);
                        _v1239 = _v2146(_v1239, _v1530, _v425, _v840(_v553), _v2001, _v2143);
                        if (_v1951(_v2156, _v355)) {
                            _v1239 = _v2114(_v1239, _v1945(_v425, _v355), _v2001, "for binding", _v2076);
                        }
                        bkr_i64 _v2158 = _v1955(_v2143, _v355);
                        _v1239 = _v2150(_v1239, _v1530, _v425, _v844(_v553), _v2001, _v2158, _v1952());
                    } else {
                        if ((_v319 == _v237)) {
                            _v1239 = _v2150(_v1239, _v1530, _v425, _v846(_v553), _v2001, _v2143, _v1952());
                        } else {
                            if ((_v319 == _v233)) {
                                _v1239 = _v2146(_v1239, _v1530, _v425, _v854(_v553), _v2001, _v2143);
                                _v1239 = _v2146(_v1239, _v1530, _v425, _v857(_v553), _v2001, _v2143);
                            } else {
                                if ((_v319 == _v238)) {
                                    bkr_i64 _v2159 = _v772(_v553);
                                    _v1239 = _v2157(_v1239, _v1530, _v425, _v549(_v2159), _v2001, _v2143, _v2156);
                                } else {
                                    if ((_v319 == _v232)) {
                                        _v1239 = _v2146(_v1239, _v1530, _v425, _v860(_v553), _v2001, _v2143);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return _v1239;
}

bkr_i64 _v2160(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v577, bkr_str _v2001, bkr_i64 _v2161, bkr_i64 _v2162) {
    return _v2150(_v1239, _v476(_v0), _v425, _v579(_v577), _v2001, _v2161, _v2162);
}

bkr_i64 _v2150(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v429 _v582, bkr_str _v2001, bkr_i64 _v2161, bkr_i64 _v2162) {
    bkr_i64 _v2143 = _v1953(_v2161);
    bkr_i64 _v2156 = _v1953(_v2162);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v589(_v582))) {
        _v1239 = _v2157(_v1239, _v1530, _v425, _v1107(_v582, _v1168), _v2001, _v2143, _v2156);
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_i64 _v2163(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v557, bkr_str _v2021) {
    return _v2164(_v1239, _v476(_v0), _v425, _v559(_v557), _v2021);
}

bkr_i64 _v2164(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v428 _v562, bkr_str _v2021) {
    bkr_str _v2023 = _v1945(_v425, _v868(_v562));
    bkr_str _v2024 = bkr_str_concat("function:", _v2023);
    _v1239 = _v2140(_v1239, _v1530, _v425, _v874(_v562), _v2024);
    bkr_i64 _v2143 = vec_new();
    bkr_i64 _v2156 = vec_new();
    _v434 _v1141 = _v871(_v562);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1141))) {
        _v341 _v1507 = _v912(_v1141, _v1168);
        bkr_i64 _v355 = _v862(_v1507);
        _v1239 = _v2140(_v1239, _v1530, _v425, _v865(_v1507), _v2024);
        if (_v1951(_v2156, _v355)) {
            _v1239 = _v2114(_v1239, _v1945(_v425, _v355), _v2024, "parameter", _v1507);
        } else {
            vec_push(_v2156, _v355);
        }
        vec_push(_v2143, _v355);
        _v1168 = (_v1168 + 1);
    }
    return _v2150(_v1239, _v1530, _v425, _v876(_v562), _v2024, _v2143, _v2156);
}

bkr_i64 _v2165(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v557) {
    return _v2166(_v1239, _v476(_v0), _v425, _v559(_v557));
}

bkr_i64 _v2166(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v428 _v562) {
    bkr_str _v1681 = _v1945(_v425, _v886(_v562));
    bkr_str _v2025 = bkr_str_concat("struct:", _v1681);
    bkr_i64 _v2156 = vec_new();
    _v434 _v1158 = _v889(_v562);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1158))) {
        _v341 _v1432 = _v912(_v1158, _v1168);
        bkr_i64 _v355 = _v891(_v1432);
        if (_v1951(_v2156, _v355)) {
            _v1239 = _v2114(_v1239, _v1945(_v425, _v355), _v2025, "field", _v1432);
        } else {
            vec_push(_v2156, _v355);
        }
        _v1239 = _v2140(_v1239, _v1530, _v425, _v894(_v1432), _v2025);
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_i64 _v2167(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425) {
    return _v2168(_v1239, _v476(_v0), _v425);
}

bkr_i64 _v2168(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425) {
    bkr_str _v2021 = bkr_str_concat("kernel:", _v1945(_v425, _v663(_v1530)));
    bkr_i64 _v2156 = vec_new();
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        _v341 _v1967 = _v587(_v562);
        bkr_i64 _v319 = _v568(_v562);
        bkr_i64 _v355 = (-1);
        bkr_str _v2113 = "item";
        if ((_v319 == _v224)) {
            _v355 = _v868(_v562);
            _v2113 = "function";
        } else {
            if ((_v319 == _v249)) {
                _v355 = _v878(_v562);
                _v2113 = "constant";
            } else {
                if ((_v319 == _v254)) {
                    _v355 = _v886(_v562);
                    _v2113 = "struct";
                } else {
                    if ((_v319 == _v260)) {
                        _v355 = _v1177(_v562);
                        _v2113 = "type_alias";
                    }
                }
            }
        }
        if ((_v355 >= 0)) {
            if (_v1951(_v2156, _v355)) {
                _v1239 = _v2114(_v1239, _v1945(_v425, _v355), _v2021, _v2113, _v1967);
            } else {
                vec_push(_v2156, _v355);
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_i64 _v2169(bkr_i64 _v1239, bkr_i64 _v0) {
    return _v2170(_v1239, _v476(_v0));
}

bkr_i64 _v2170(bkr_i64 _v1239, _v341 _v1530) {
    bkr_i64 _v425 = _v903(_v1530);
    bkr_str _v2021 = bkr_str_concat("kernel:", _v1945(_v425, _v663(_v1530)));
    _v1239 = _v2168(_v1239, _v1530, _v425);
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        bkr_i64 _v319 = _v568(_v562);
        if ((_v319 == _v224)) {
            _v1239 = _v2164(_v1239, _v1530, _v425, _v562, _v2021);
        } else {
            if ((_v319 == _v249)) {
                _v1239 = _v2140(_v1239, _v1530, _v425, _v881(_v562), _v2021);
                _v1239 = _v2146(_v1239, _v1530, _v425, _v884(_v562), _v2021, _v1952());
            } else {
                if ((_v319 == _v254)) {
                    _v1239 = _v2166(_v1239, _v1530, _v425, _v562);
                } else {
                    if ((_v319 == _v260)) {
                        _v1239 = _v2140(_v1239, _v1530, _v425, _v1178(_v562), _v2021);
                    }
                }
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_str _v2171(bkr_i64 _v0) {
    bkr_str _v1941 = ",";
    _v341 _v1530 = _v476(_v0);
    bkr_i64 _v1239 = _v1946();
    bkr_bool _v1993 = _v1933(_v1530);
    if (_v1993) {
        _v2170(_v1239, _v1530);
    }
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("schema_version", "bunker.self_host.resolver.v1")), _v1941), _v1892("representation", "bootstrap_name_resolver")), _v1941), _v1894("complete", BKR_TRUE)), _v1941), _v1894("truncated", (!_v1993))), _v1941), _v1894("duplicate_detection", BKR_TRUE)), _v1941), _v1894("unresolved_detection", BKR_TRUE)), _v1941), _v1894("visibility_checking", BKR_TRUE)), _v1941), _v1894("import_graph_awareness", BKR_TRUE)), _v1941), _v1894("cross_file_definitions", BKR_TRUE)), _v1941), _v1894("related_declarations", BKR_TRUE)), _v1941), _v1894("structured_repair_metadata", BKR_TRUE)), _v1941), _v1894("diagnostic_phase_field", BKR_TRUE)), _v1941), _v1894("diagnostic_rule_ids", BKR_TRUE)), _v1941), _v1894("diagnostic_severity", BKR_TRUE)), _v1941), _v1894("diagnostic_severity_counts", BKR_TRUE)), _v1941), _v1894("suggested_edit_envelope", BKR_TRUE)), _v1941), _v1894("has_diagnostics", (_v1949(_v1239) > 0))), _v1941), _v1893("diagnostic_count", _v1949(_v1239))), _v1941), _v1893("error_count", _v1949(_v1239))), _v1941), _v1893("warning_count", 0)), _v1941), _v1892("scope_model", "kernel globals plus function/block/pattern binding scopes using interned names with visibility boundaries")), _v1941), _v1892("known_limits", "Resolver validates duplicate declarations, unresolved identifiers, calls, struct types, struct literals, and struct literal fields with related declaration span objects; import visibility boundaries and cross-file definition origins verified.")), _v1941), _v1895("diagnostics", _v1947(_v1239))), "}");
}

bkr_str _v2172(bkr_i64 _v0) {
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("/* BUNKER_RESOLVER_JSON: ", _v2171(_v0)), from_char_code(10)), "*/"), from_char_code(10));
}

bkr_bool _v2173(bkr_i64 _v319) {
    return ((_v319 == 0) || (_v319 == 1));
}

bkr_bool _v2174(bkr_i64 _v319) {
    return (((_v319 == 0) || (_v319 == 1)) || (_v319 == 2));
}

bkr_bool _v2175(bkr_i64 _v319) {
    return (_v319 == _v316);
}

bkr_bool _v2176(bkr_i64 _v2177, bkr_i64 _v2178) {
    if (((_v2177 == _v316) || (_v2178 == _v316))) {
        return BKR_TRUE;
    }
    if ((_v2178 == _v314)) {
        return BKR_TRUE;
    }
    if ((_v2177 == _v314)) {
        return BKR_FALSE;
    }
    if ((_v2177 == _v2178)) {
        return BKR_TRUE;
    }
    if ((_v2173(_v2177) && _v2173(_v2178))) {
        return BKR_TRUE;
    }
    if ((((((_v2177 == _v310) || (_v2177 == _v311)) || (_v2177 == _v312)) || (_v2177 == _v313)) && ((_v2178 == _v303) || (_v2178 == _v316)))) {
        return BKR_TRUE;
    }
    if ((((((_v2178 == _v310) || (_v2178 == _v311)) || (_v2178 == _v312)) || (_v2178 == _v313)) && ((_v2177 == _v303) || (_v2177 == _v316)))) {
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_bool _v2179(bkr_i64 _v319) {
    return ((((_v319 == 0) || (_v319 == 1)) || (_v319 == 2)) || (_v319 == 3));
}

bkr_bool _v2180(bkr_i64 _v319) {
    return (((((((_v319 == _v306) || (_v319 == _v312)) || (_v319 == _v313)) || (_v319 == _v310)) || (_v319 == _v311)) || (_v319 == _v308)) || (_v319 == _v309));
}

bkr_bool _v2181(bkr_i64 _v2182, bkr_i64 _v1787) {
    if (((_v2182 == _v316) || (_v1787 == _v316))) {
        return BKR_TRUE;
    }
    if ((_v2182 == _v1787)) {
        return BKR_TRUE;
    }
    bkr_bool _v2183 = (_v2174(_v2182) || (_v2182 == _v305));
    bkr_bool _v2184 = (_v2174(_v1787) || (_v1787 == _v305));
    if ((_v2183 && _v2184)) {
        return BKR_TRUE;
    }
    bkr_bool _v2185 = _v2180(_v2182);
    bkr_bool _v2186 = _v2180(_v1787);
    if ((((_v2182 == _v303) && _v2186) || (_v2185 && (_v1787 == _v303)))) {
        return BKR_TRUE;
    }
    if ((_v2185 && _v2186)) {
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_bool _v2187(bkr_i64 _v2177, bkr_i64 _v2178) {
    if (_v2176(_v2177, _v2178)) {
        return BKR_TRUE;
    }
    if ((_v2179(_v2177) && _v2179(_v2178))) {
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_i64 _v2188(_v1531 _v2189, bkr_i64 _v1655) {
    if (_v523(_v1655)) {
        return _v316;
    }
    return _v2190(_v2189, _v537(_v1655));
}

bkr_i64 _v2190(_v1531 _v2189, _v426 _v541) {
    return _v1653(_v2189, _v541);
}

bkr_i64 _v2191(bkr_i64 _v515) {
    if (_v523(_v515)) {
        return _v316;
    }
    return _v2192(_v516(_v515));
}

bkr_i64 _v2193(_v341 _v1530, bkr_i64 _v355) {
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if ((_v568(_v562) == _v260)) {
            if ((_v1177(_v562) == _v355)) {
                return _v1178(_v562);
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return _v564();
}

bkr_bool _v2194(_v341 _v1530, bkr_i64 _v355) {
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if ((_v568(_v562) == _v259)) {
            if ((_v1164(_v562) == _v355)) {
                return BKR_TRUE;
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_FALSE;
}

bkr_i64 _v2050(_v341 _v1530, _v346 _v520) {
    bkr_i64 _v319 = _v529(_v520);
    if ((_v319 == _v309)) {
        bkr_i64 _v355 = _v531(_v520);
        if (_v2194(_v1530, _v355)) {
            return _v303;
        }
        bkr_i64 _v2195 = _v2193(_v1530, _v355);
        if (_v525(_v2195)) {
            return _v2050(_v1530, _v516(_v2195));
        }
    }
    return _v319;
}

bkr_i64 _v2196(_v341 _v1530, _v428 _v1514) {
    bkr_i64 _v412 = _v874(_v1514);
    if (_v523(_v412)) {
        return _v307;
    }
    return _v2050(_v1530, _v516(_v412));
}

bkr_i64 _v2192(_v346 _v520) {
    return _v529(_v520);
}

bkr_i64 _v2197(bkr_i64 _v929) {
    return _v2198(_v559(_v929));
}

bkr_i64 _v2198(_v428 _v1514) {
    bkr_i64 _v412 = _v874(_v1514);
    if (_v523(_v412)) {
        return _v307;
    }
    return _v2192(_v516(_v412));
}

bkr_str _v2199(bkr_str _v319, bkr_str _v2103, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v447, bkr_str _v1264, bkr_str _v2200, bkr_str _v2104) {
    return _v2201(_v319, _v2103, _v1348, _v2001, _v476(_v447), _v1264, _v2200, _v2104);
}

bkr_str _v2201(bkr_str _v319, bkr_str _v2103, bkr_str _v1348, bkr_str _v2001, _v341 _v452, bkr_str _v1264, bkr_str _v2200, bkr_str _v2104) {
    return _v2202(_v319, _v2103, _v1348, _v2001, _v452, _v1264, _v2200, _v2042(_v316, "expected"), _v2042(_v316, "found"), _v2104);
}

bkr_str _v2202(bkr_str _v319, bkr_str _v2103, bkr_str _v1348, bkr_str _v2001, _v341 _v452, bkr_str _v1264, bkr_str _v2200, bkr_str _v2203, bkr_str _v2204, bkr_str _v2104) {
    return _v2205(_v319, _v2103, _v1348, _v2001, _v511(_v452), _v512(_v452), _v1264, _v2200, _v2203, _v2204, _v2104);
}

bkr_str _v2205(bkr_str _v319, bkr_str _v2103, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v1936, bkr_i64 _v1937, bkr_str _v1264, bkr_str _v2200, bkr_str _v2203, bkr_str _v2204, bkr_str _v2104) {
    bkr_str _v1941 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("phase", "typecheck")), _v1941), _v1892("kind", _v319)), _v1941), _v1892("rule_id", _v319)), _v1941), _v1892("error_code", _v2103)), _v1941), _v1892("severity", "error")), _v1941), _v1892("name", _v1348)), _v1941), _v1892("scope", _v2001)), _v1941), _v1893("source_start", _v1936)), _v1941), _v1893("source_end", _v1937)), _v1941), _v1894("span_known", ((_v1936 != _v268) && (_v1937 != _v268)))), _v1941), _v1892("expected", _v1264)), _v1941), _v1892("found", _v2200)), _v1941), _v1895("expected_type", _v2203)), _v1941), _v1895("found_type", _v2204)), _v1941), _v1892("suggested_action", _v2104)), _v1941), _v1892("fix_applicability", "manual_review")), _v1941), _v1892("fix_confidence", "medium")), _v1941), _v1894("safe_edit_available", BKR_FALSE)), _v1941), _v1895("suggested_edits", _v1942())), _v1941), _v1892("repair_hint", _v2104)), "}");
}

bkr_i64 _v2206(bkr_i64 _v1239, bkr_str _v319, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v447, bkr_i64 _v2177, bkr_i64 _v2178, bkr_str _v2104) {
    return _v2207(_v1239, _v319, _v1348, _v2001, _v476(_v447), _v2177, _v2178, _v2104);
}

bkr_i64 _v2207(bkr_i64 _v1239, bkr_str _v319, bkr_str _v1348, bkr_str _v2001, _v341 _v452, bkr_i64 _v2177, bkr_i64 _v2178, bkr_str _v2104) {
    return _v1950(_v1239, _v2202(_v319, "BKR_SELF_TYPE_MISMATCH", _v1348, _v2001, _v452, _v327(_v2177), _v327(_v2178), _v2042(_v2177, "expected"), _v2042(_v2178, "found"), _v2104));
}

bkr_i64 _v2208(bkr_i64 _v1239, bkr_str _v319, bkr_str _v1348, bkr_str _v2001, _v341 _v452, bkr_i64 _v2209, bkr_i64 _v2210, bkr_str _v2104) {
    return _v1950(_v1239, _v2201(_v319, "BKR_SELF_ARITY_MISMATCH", _v1348, _v2001, _v452, bkr_str_concat(int_to_string(_v2209), " argument(s)"), bkr_str_concat(int_to_string(_v2210), " argument(s)"), _v2104));
}

bkr_i64 _v2211(bkr_i64 _v1239, bkr_str _v2001, _v426 _v1094) {
    bkr_i64 _v1787 = _v544(_v1094);
    bkr_str _v2115 = "Assign only to a mutable local name, an indexed element, or a field access target.";
    return _v1950(_v1239, _v2201("invalid_assignment_target", "BKR_SELF_ASSIGNMENT_TARGET", "assignment", _v2001, _v546(_v1094), "identifier, index, or field access assignment target", _v318(_v1787), _v2115));
}

bkr_i64 _v2212(bkr_i64 _v1239, bkr_str _v2001, _v427 _v553) {
    bkr_str _v2213 = "break";
    if ((_v555(_v553) == _v235)) {
        _v2213 = "continue";
    }
    return _v1950(_v1239, _v2201("invalid_loop_control", "BKR_SELF_CONTROL_FLOW", _v2213, _v2001, _v586(_v553), "inside for, while, or loop", "outside loop", "Move this statement inside a for, while, or loop body."));
}

bkr_i64 _v2214(bkr_i64 _v1239, bkr_i64 _v425, bkr_str _v2001, _v426 _v1094) {
    bkr_str _v2215 = _v1945(_v425, _v662(_v1094));
    return _v1950(_v1239, _v2201("const_assignment", "BKR_SELF_CONST_ASSIGNMENT", _v2215, _v2001, _v546(_v1094), "mutable assignment target", "constant declaration", "Do not assign to a const; introduce a local binding for mutable state."));
}

bkr_i64 _v2216(bkr_i64 _v1239, bkr_str _v1348, bkr_str _v2001, _v426 _v541) {
    return _v1950(_v1239, _v2201("ambiguous_empty_array", "BKR_SELF_AMBIGUOUS_TYPE", _v1348, _v2001, _v546(_v541), "array element type context", "empty array literal", "Add a type annotation so the empty array element type is known."));
}

bkr_i64 _v2217(bkr_i64 _v1239, bkr_str _v1348, bkr_str _v2001, _v426 _v541) {
    return _v1950(_v1239, _v2201("ambiguous_none", "BKR_SELF_AMBIGUOUS_TYPE", _v1348, _v2001, _v546(_v541), "Option<T> type context", "None", "Add an Option<T> annotation so the None payload type is known."));
}

bkr_i64 _v2218(bkr_i64 _v1239, bkr_str _v1348, bkr_str _v2001, _v426 _v541) {
    return _v1950(_v1239, _v2201("ambiguous_result_constructor", "BKR_SELF_AMBIGUOUS_TYPE", _v1348, _v2001, _v546(_v541), "Result<T,E> type context", "result constructor with one unknown side", "Add a Result<T,E> annotation so both Ok and Err payload types are known."));
}

bkr_i64 _v2219(bkr_i64 _v1239, bkr_str _v1348, bkr_str _v2001, _v426 _v541) {
    return _v1950(_v1239, _v2201("ambiguous_collection_constructor", "BKR_SELF_AMBIGUOUS_TYPE", _v1348, _v2001, _v546(_v541), "collection element/key/value type context", "generic collection constructor", "Add a Vec<T> or HashMap<K,V> annotation so collection types are known."));
}

bkr_i64 _v2220(bkr_i64 _v1239, bkr_str _v1348, bkr_str _v2001, _v426 _v541) {
    return _v1950(_v1239, _v2201("void_value_used", "BKR_SELF_VOID_VALUE", _v1348, _v2001, _v546(_v541), "value-producing expression", "void expression", "Use this call as a standalone statement or change the function to return a value."));
}

bkr_i64 _v2221(bkr_i64 _v1239, bkr_i64 _v425, _v341 _v1530, bkr_str _v2021) {
    bkr_str _v1884 = _v1945(_v425, _v900(_v1530));
    return _v1950(_v1239, _v2201("missing_entry_function", "BKR_SELF_ENTRY_POINT", _v1884, _v2021, _v1530, bkr_str_concat("function named ", _v1884), "missing function declaration", bkr_str_concat(bkr_str_concat("Add fn ", _v1884), "(...) or update the kernel entry name.")));
}

bkr_i64 _v2222(bkr_i64 _v1239, bkr_i64 _v425, bkr_str _v2021, _v428 _v2223, bkr_str _v1264, bkr_str _v2200, bkr_str _v2104) {
    return _v1950(_v1239, _v2201("invalid_entry_signature", "BKR_SELF_ENTRY_POINT", _v1945(_v425, _v868(_v2223)), _v2021, _v587(_v2223), _v1264, _v2200, _v2104));
}

bkr_i64 _v2224(bkr_i64 _v1239, bkr_i64 _v425, bkr_str _v2001, _v426 _v541, bkr_str _v1267) {
    bkr_str _v1748 = _v1945(_v425, _v688(_v541));
    return _v1950(_v1239, _v2201("invalid_call_target", "BKR_SELF_CALL_TARGET", _v1748, _v2001, _v546(_v541), "function or supported builtin", _v1267, "Call only functions and supported builtins; use the symbol as a value or rename it."));
}

bkr_i64 _v2225(bkr_i64 _v1239, bkr_i64 _v425, bkr_str _v2001, _v428 _v1514) {
    return _v1950(_v1239, _v2201("missing_return", "BKR_SELF_RETURN_PATH", _v1945(_v425, _v868(_v1514)), _v2001, _v587(_v1514), "return value on every path", "function can fall through", "Add a return statement on every path or change the function return type to void."));
}

bkr_i64 _v2226(bkr_i64 _v1239, _v1531 _v2189, _v426 _v541, bkr_str _v1348, bkr_str _v2001) {
    if ((_v2190(_v2189, _v541) == _v307)) {
        _v1239 = _v2220(_v1239, _v1348, _v2001, _v541);
    }
    return _v1239;
}

bkr_i64 _v2227(bkr_i64 _v1239, bkr_str _v2001, _v427 _v553) {
    return _v1950(_v1239, _v2201("unreachable_statement", "BKR_SELF_UNREACHABLE_CODE", "statement", _v2001, _v586(_v553), "reachable statement", _v318(_v555(_v553)), "Remove this statement or move it before the terminating control-flow statement."));
}

bkr_bool _v2228(_v426 _v1094) {
    bkr_i64 _v1787 = _v544(_v1094);
    if ((_v1787 == _v245)) {
        return BKR_TRUE;
    }
    if ((_v1787 == _v253)) {
        return BKR_TRUE;
    }
    if ((_v1787 == _v256)) {
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_bool _v2229(_v426 _v541) {
    if ((_v544(_v541) != _v252)) {
        return BKR_FALSE;
    }
    return (_v906(_v701(_v541)) == 0);
}

bkr_bool _v2230(bkr_i64 _v1655) {
    if (_v523(_v1655)) {
        return BKR_FALSE;
    }
    return _v2229(_v537(_v1655));
}

bkr_bool _v2231(bkr_i64 _v425, _v426 _v541) {
    if ((_v544(_v541) != _v245)) {
        return BKR_FALSE;
    }
    return bkr_str_eq(_v1945(_v425, _v662(_v541)), "None");
}

bkr_bool _v2232(bkr_i64 _v425, bkr_i64 _v1655) {
    if (_v523(_v1655)) {
        return BKR_FALSE;
    }
    return _v2231(_v425, _v537(_v1655));
}

bkr_bool _v2233(bkr_i64 _v425, _v426 _v541) {
    if ((_v544(_v541) != _v244)) {
        return BKR_FALSE;
    }
    bkr_str _v1640 = _v1945(_v425, _v688(_v541));
    return (((bkr_str_eq(_v1640, "result_ok") || bkr_str_eq(_v1640, "result_err")) || bkr_str_eq(_v1640, "Ok")) || bkr_str_eq(_v1640, "Err"));
}

bkr_bool _v2234(bkr_i64 _v425, bkr_i64 _v1655) {
    if (_v523(_v1655)) {
        return BKR_FALSE;
    }
    return _v2233(_v425, _v537(_v1655));
}

bkr_bool _v2235(bkr_i64 _v425, _v426 _v541) {
    if ((_v544(_v541) != _v244)) {
        return BKR_FALSE;
    }
    bkr_str _v1640 = _v1945(_v425, _v688(_v541));
    return (bkr_str_eq(_v1640, "vec_new") || bkr_str_eq(_v1640, "hashmap_new"));
}

bkr_bool _v2236(bkr_i64 _v425, bkr_i64 _v1655) {
    if (_v523(_v1655)) {
        return BKR_FALSE;
    }
    return _v2235(_v425, _v537(_v1655));
}

bkr_bool _v2237(_v1531 _v2189, bkr_i64 _v1655) {
    if (_v523(_v1655)) {
        return BKR_FALSE;
    }
    return (_v2190(_v2189, _v537(_v1655)) == _v307);
}

bkr_i64 _v2238(bkr_str _v1348) {
    if (bkr_str_eq(_v1348, "print")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "println")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "Some")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "len")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "substr")) {
        return 3;
    }
    if (bkr_str_eq(_v1348, "str_eq")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "str_ne")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "str_to_i64")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "i64_to_str")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "f64_to_str")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "bool_to_str")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "read_file")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "write_file")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "file_exists")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "file_set_executable")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "read_file_str")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "write_file_str")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "vec_new")) {
        return 0;
    }
    if (bkr_str_eq(_v1348, "vec_push")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "vec_get")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "vec_set")) {
        return 3;
    }
    if (bkr_str_eq(_v1348, "vec_len")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "vec_pop")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "vec_clear")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "hashmap_new")) {
        return 0;
    }
    if (bkr_str_eq(_v1348, "hashmap_insert")) {
        return 3;
    }
    if (bkr_str_eq(_v1348, "hashmap_get")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "hashmap_contains")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "hashmap_remove")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "hashmap_keys")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "hashmap_len")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "hashmap_clear")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "result_ok")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "result_err")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "result_is_ok")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "result_is_err")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "result_unwrap")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "result_unwrap_err")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "result_tag")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "result_value")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "bkr_tuple2")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "bkr_tuple3")) {
        return 3;
    }
    if (bkr_str_eq(_v1348, "bkr_tuple_get")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "args_count")) {
        return 0;
    }
    if (bkr_str_eq(_v1348, "arg_at")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "strlen")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "char_code")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "char_code_at")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "char_at")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "substring")) {
        return 3;
    }
    if (bkr_str_eq(_v1348, "contains")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "starts_with")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "ends_with")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "trim")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "int_to_string")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "from_char_code")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "join_lines")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "parse_int")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "hashmap_get_opt")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "vec_get_opt")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "vec_pop_opt")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "vec_contains")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "vec_is_empty")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "vec_clone")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "vec_reverse")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "hashmap_is_empty")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "hashmap_values")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "vec_map")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "vec_filter")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "vec_fold")) {
        return 3;
    }
    if (bkr_str_eq(_v1348, "vec_find")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "read_file_result")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "write_file_result")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "parse_int_result")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "Ok")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "Err")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "panic")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "assert")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "str_index_of")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "str_replace")) {
        return 3;
    }
    if (bkr_str_eq(_v1348, "str_split")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "str_to_upper")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "str_to_lower")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "str_repeat")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "path_join")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "path_dir")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "path_base")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "path_ext")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "path_is_abs")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "env_var")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "env_get")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "env_set")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "env_has")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "time_now_ms")) {
        return 0;
    }
    if (bkr_str_eq(_v1348, "time_now_unix")) {
        return 0;
    }
    if (bkr_str_eq(_v1348, "runtime_version_major")) {
        return 0;
    }
    if (bkr_str_eq(_v1348, "runtime_version_minor")) {
        return 0;
    }
    if (bkr_str_eq(_v1348, "runtime_version_patch")) {
        return 0;
    }
    if (bkr_str_eq(_v1348, "runtime_version_str")) {
        return 0;
    }
    if (bkr_str_eq(_v1348, "bytes_new")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "bytes_len")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "bytes_capacity")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "bytes_get")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "bytes_set")) {
        return 3;
    }
    if (bkr_str_eq(_v1348, "bytes_push")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "bytes_from_str")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "bytes_to_str")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "slice_new")) {
        return 3;
    }
    if (bkr_str_eq(_v1348, "slice_len")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "slice_get")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "slice_sub")) {
        return 3;
    }
    if (bkr_str_eq(_v1348, "slice_to_vec")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "slice_contains")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "vec_as_slice")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "vec_slice")) {
        return 3;
    }
    if (bkr_str_eq(_v1348, "bytes_as_slice")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "bytes_slice")) {
        return 3;
    }
    if (bkr_str_eq(_v1348, "path_exists")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "path_is_file")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "path_is_dir")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "file_read")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "file_write")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "file_size")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "file_remove")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "file_read_bytes")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "file_write_bytes")) {
        return 2;
    }
    if (bkr_str_eq(_v1348, "dir_create")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "dir_remove")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "process_run")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "process_run_status")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "process_exit")) {
        return 1;
    }
    if (bkr_str_eq(_v1348, "process_pid")) {
        return 0;
    }
    if (bkr_str_eq(_v1348, "process_is_sandboxed")) {
        return 0;
    }
    return (-1);
}

bkr_i64 _v2239(bkr_str _v1348, bkr_i64 _v362) {
    if ((bkr_str_eq(_v1348, "print") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "println") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "len") && (_v362 == 0))) {
        return _v316;
    }
    if ((bkr_str_eq(_v1348, "substr") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "substr") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "substr") && (_v362 == 2))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "str_eq") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "str_eq") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "str_ne") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "str_ne") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "str_to_i64") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "i64_to_str") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "f64_to_str") && (_v362 == 0))) {
        return _v304;
    }
    if ((bkr_str_eq(_v1348, "bool_to_str") && (_v362 == 0))) {
        return _v305;
    }
    if ((bkr_str_eq(_v1348, "read_file") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "write_file") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "write_file") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "file_exists") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "file_set_executable") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "read_file_str") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "write_file_str") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "write_file_str") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "vec_push") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "vec_get") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "vec_get") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "vec_set") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "vec_set") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "vec_len") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "vec_pop") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "vec_clear") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "hashmap_insert") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "hashmap_get") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "hashmap_contains") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "hashmap_remove") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "hashmap_keys") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "hashmap_len") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "hashmap_clear") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "result_is_ok") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "result_is_err") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "result_unwrap") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "result_unwrap_err") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "result_tag") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "result_value") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "arg_at") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "strlen") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "char_code") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "char_code_at") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "char_code_at") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "char_at") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "char_at") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "substring") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "substring") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "substring") && (_v362 == 2))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "contains") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "contains") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "starts_with") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "starts_with") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "ends_with") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "ends_with") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "trim") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "int_to_string") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "from_char_code") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "parse_int") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "read_file_result") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "write_file_result") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "write_file_result") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "parse_int_result") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "hashmap_get_opt") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "vec_get_opt") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "vec_get_opt") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "vec_pop_opt") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "vec_contains") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "vec_is_empty") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "vec_clone") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "vec_reverse") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "hashmap_is_empty") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "hashmap_values") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "vec_map") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "vec_filter") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "vec_fold") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "vec_find") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "panic") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "assert") && (_v362 == 0))) {
        return _v305;
    }
    if ((bkr_str_eq(_v1348, "str_index_of") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "str_index_of") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "str_replace") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "str_replace") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "str_replace") && (_v362 == 2))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "str_split") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "str_split") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "str_to_upper") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "str_to_lower") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "str_repeat") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "str_repeat") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "path_join") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "path_join") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "path_dir") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "path_base") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "path_ext") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "path_is_abs") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "env_var") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "env_get") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "env_set") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "env_set") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "env_has") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "bytes_new") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "bytes_len") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "bytes_capacity") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "bytes_get") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "bytes_get") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "bytes_set") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "bytes_set") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "bytes_set") && (_v362 == 2))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "bytes_push") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "bytes_push") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "bytes_from_str") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "bytes_to_str") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "slice_new") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "slice_new") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "slice_new") && (_v362 == 2))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "slice_len") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "slice_get") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "slice_get") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "slice_sub") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "slice_sub") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "slice_sub") && (_v362 == 2))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "slice_to_vec") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "slice_contains") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "slice_contains") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "vec_as_slice") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "vec_slice") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "vec_slice") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "vec_slice") && (_v362 == 2))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "bytes_as_slice") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "bytes_slice") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "bytes_slice") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "bytes_slice") && (_v362 == 2))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "path_exists") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "path_is_file") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "path_is_dir") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "file_read") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "file_write") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "file_write") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "file_size") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "file_remove") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "file_read_bytes") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "file_write_bytes") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "file_write_bytes") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1348, "dir_create") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "dir_remove") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "process_run") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "process_run_status") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1348, "process_exit") && (_v362 == 0))) {
        return _v303;
    }
    return _v316;
}

bkr_i64 _v2240(bkr_i64 _v1239, bkr_i64 _v425, _v426 _v541, bkr_str _v2001) {
    bkr_str _v2023 = _v1945(_v425, _v688(_v541));
    bkr_i64 _v2209 = _v2238(_v2023);
    if ((_v2209 < 0)) {
        return _v1239;
    }
    bkr_i64 _v2210 = _v906(_v691(_v541));
    if ((_v2209 != _v2210)) {
        bkr_str _v2241 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Call builtin ", _v2023), " with exactly "), int_to_string(_v2209)), " argument(s).");
        _v1239 = _v2208(_v1239, "builtin_argument_count_mismatch", _v2023, _v2001, _v546(_v541), _v2209, _v2210, _v2241);
    }
    return _v1239;
}

bkr_i64 _v2242(bkr_i64 _v1239, bkr_i64 _v425, _v1531 _v2189, _v426 _v541, bkr_str _v2001) {
    bkr_str _v2023 = _v1945(_v425, _v688(_v541));
    if ((_v2238(_v2023) < 0)) {
        return _v1239;
    }
    _v434 _v1015 = _v691(_v541);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1015))) {
        if ((bkr_str_eq(_v2023, "len") && (_v1168 == 0))) {
            _v341 _v2243 = _v912(_v1015, 0);
            bkr_i64 _v2178 = _v2190(_v2189, _v539(_v2243));
            if (((_v2178 != _v306) && (_v2178 != _v308))) {
                bkr_str _v2115 = "Change argument 1 for builtin len to match the expected type.";
                _v1239 = _v2244(_v1239, "builtin_argument_type_mismatch", _v2023, _v2001, _v2243, _v306, _v2178, _v2115);
            }
        } else {
            bkr_i64 _v2177 = _v2239(_v2023, _v1168);
            if ((_v2177 != _v316)) {
                _v341 _v2243 = _v912(_v1015, _v1168);
                bkr_i64 _v2178 = _v2190(_v2189, _v539(_v2243));
                bkr_str _v2115 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Change argument ", int_to_string((_v1168 + 1))), " for builtin "), _v2023), " to match the expected type.");
                _v1239 = _v2244(_v1239, "builtin_argument_type_mismatch", _v2023, _v2001, _v2243, _v2177, _v2178, _v2115);
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_i64 _v2245(bkr_i64 _v1239, bkr_i64 _v425, _v1531 _v2189, _v426 _v541, bkr_str _v2001) {
    _v1239 = _v2240(_v1239, _v425, _v541, _v2001);
    _v1239 = _v2242(_v1239, _v425, _v2189, _v541, _v2001);
    return _v1239;
}

bkr_bool _v2246(bkr_i64 _v349) {
    return ((_v349 == _v172) || (_v349 == _v173));
}

bkr_bool _v2247(bkr_i64 _v349) {
    return ((((((_v349 == _v165) || (_v349 == _v175)) || (_v349 == _v176)) || (_v349 == _v177)) || (_v349 == _v178)) || (_v349 == _v179));
}

bkr_bool _v2248(bkr_i64 _v349) {
    return ((((((((_v349 == _v161) || (_v349 == _v162)) || (_v349 == _v163)) || (_v349 == _v164)) || (_v349 == _v168)) || (_v349 == _v169)) || (_v349 == _v170)) || (_v349 == _v171));
}

bkr_i64 _v2249(bkr_i64 _v1239, bkr_str _v319, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v447, bkr_i64 _v2177, bkr_i64 _v2178, bkr_str _v2104) {
    return _v2244(_v1239, _v319, _v1348, _v2001, _v476(_v447), _v2177, _v2178, _v2104);
}

bkr_i64 _v2244(bkr_i64 _v1239, bkr_str _v319, bkr_str _v1348, bkr_str _v2001, _v341 _v452, bkr_i64 _v2177, bkr_i64 _v2178, bkr_str _v2104) {
    if ((!_v2176(_v2177, _v2178))) {
        _v1239 = _v2207(_v1239, _v319, _v1348, _v2001, _v452, _v2177, _v2178, _v2104);
    }
    return _v1239;
}

bkr_i64 _v2250(bkr_i64 _v1239, bkr_str _v319, bkr_str _v1348, bkr_str _v2001, bkr_i64 _v447, bkr_i64 _v2177, bkr_i64 _v2178, bkr_str _v2104) {
    return _v2251(_v1239, _v319, _v1348, _v2001, _v476(_v447), _v2177, _v2178, _v2104);
}

bkr_i64 _v2251(bkr_i64 _v1239, bkr_str _v319, bkr_str _v1348, bkr_str _v2001, _v341 _v452, bkr_i64 _v2177, bkr_i64 _v2178, bkr_str _v2104) {
    if ((!_v2187(_v2177, _v2178))) {
        _v1239 = _v2207(_v1239, _v319, _v1348, _v2001, _v452, _v2177, _v2178, _v2104);
    }
    return _v1239;
}

_v428 _v2252(_v341 _v1530, bkr_i64 _v355) {
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if (((_v568(_v562) == _v224) && (_v868(_v562) == _v355))) {
            return _v562;
        }
        _v1168 = (_v1168 + 1);
    }
    return _v563();
}

bkr_i64 _v2253(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, bkr_str _v2021) {
    _v428 _v2223 = _v2252(_v1530, _v900(_v1530));
    if (_v565(_v2223)) {
        _v1239 = _v2221(_v1239, _v425, _v1530, _v2021);
        return _v1239;
    }
    _v434 _v1141 = _v871(_v2223);
    bkr_i64 _v2254 = _v906(_v1141);
    if ((_v2254 != 0)) {
        _v1239 = _v2222(_v1239, _v425, _v2021, _v2223, "entry function with zero parameters", bkr_str_concat(int_to_string(_v2254), " parameter(s)"), "Remove entry function parameters or make a zero-argument wrapper entry.");
    }
    bkr_i64 _v2255 = _v2196(_v1530, _v2223);
    if (((_v2255 != _v316) && (!_v2173(_v2255)))) {
        _v1239 = _v2222(_v1239, _v425, _v2021, _v2223, "integer-compatible entry return type", _v327(_v2255), "Return i32 or i64 from the entry function so the generated C main can return an int.");
    }
    return _v1239;
}

bkr_i64 _v2256(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v426 _v541, bkr_str _v2001) {
    bkr_i64 _v355 = _v688(_v541);
    if (_v566(_v2252(_v1530, _v355))) {
        return _v1239;
    }
    if (_v566(_v2257(_v1530, _v355))) {
        return _v2224(_v1239, _v425, _v2001, _v541, "constant declaration");
    }
    _v428 _v1523 = _v2258(_v1530, _v355);
    if (_v566(_v1523)) {
        _v434 _v1158 = _v889(_v1523);
        if ((_v906(_v1158) > 0)) {
            _v341 _v2259 = _v912(_v1158, 0);
            if (bkr_str_eq(_v1945(_v425, _v891(_v2259)), "0")) {
                return _v1239;
            }
        }
        return _v2224(_v1239, _v425, _v2001, _v541, "struct declaration");
    }
    return _v1239;
}

_v428 _v2258(_v341 _v1530, bkr_i64 _v355) {
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if (((_v568(_v562) == _v254) && (_v886(_v562) == _v355))) {
            return _v562;
        }
        _v1168 = (_v1168 + 1);
    }
    return _v563();
}

_v428 _v2257(_v341 _v1530, bkr_i64 _v355) {
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if (((_v568(_v562) == _v249) && (_v878(_v562) == _v355))) {
            return _v562;
        }
        _v1168 = (_v1168 + 1);
    }
    return _v563();
}

bkr_i64 _v2260(_v341 _v1530, bkr_i64 _v1503, bkr_i64 _v1658) {
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if (((_v568(_v562) == _v254) && (_v886(_v562) == _v1503))) {
            _v434 _v1158 = _v889(_v562);
            bkr_i64 _v1629 = 0;
            while ((_v1629 < _v906(_v1158))) {
                _v341 _v1432 = _v912(_v1158, _v1629);
                if ((_v891(_v1432) == _v1658)) {
                    return _v2050(_v1530, _v516(_v894(_v1432)));
                }
                _v1629 = (_v1629 + 1);
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return _v316;
}

bkr_i64 _v2261(bkr_i64 _v1239, bkr_i64 _v425, _v426 _v541, bkr_str _v2001) {
    bkr_str _v1681 = _v1945(_v425, _v724(_v541));
    _v435 _v1007 = _v727(_v541);
    _v434 _v1008 = _v730(_v541);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v915(_v1007))) {
        bkr_i64 _v1658 = _v917(_v1007, _v1168);
        bkr_i64 _v1629 = 0;
        while ((_v1629 < _v1168)) {
            if ((_v917(_v1007, _v1629) == _v1658)) {
                bkr_str _v1044 = _v1945(_v425, _v1658);
                _v1239 = _v1950(_v1239, _v2201("duplicate_struct_literal_field", "BKR_SELF_STRUCT_LITERAL", bkr_str_concat(bkr_str_concat(_v1681, "."), _v1044), _v2001, _v912(_v1008, _v1168), "field initialized once", "duplicate field initializer", "Remove the duplicate field or merge the intended value into the first initializer."));
            }
            _v1629 = (_v1629 + 1);
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_bool _v2262(_v435 _v1007, bkr_i64 _v1658) {
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v915(_v1007))) {
        if ((_v917(_v1007, _v1168) == _v1658)) {
            return BKR_TRUE;
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_FALSE;
}

bkr_i64 _v2263(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v426 _v541, bkr_str _v2001) {
    bkr_i64 _v403 = _v1005(_v541);
    if ((_v403 != 0)) {
        return _v1239;
    }
    bkr_i64 _v1503 = _v724(_v541);
    _v428 _v1523 = _v2258(_v1530, _v1503);
    if (_v565(_v1523)) {
        return _v1239;
    }
    bkr_str _v1681 = _v1945(_v425, _v1503);
    _v435 _v1007 = _v727(_v541);
    _v434 _v2264 = _v889(_v1523);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v2264))) {
        _v341 _v1432 = _v912(_v2264, _v1168);
        bkr_i64 _v1658 = _v891(_v1432);
        if ((!_v2262(_v1007, _v1658))) {
            bkr_str _v1044 = _v1945(_v425, _v1658);
            _v1239 = _v1950(_v1239, _v2201("missing_struct_literal_field", "BKR_SELF_STRUCT_LITERAL", bkr_str_concat(bkr_str_concat(_v1681, "."), _v1044), _v2001, _v546(_v541), "field initializer", "missing field", bkr_str_concat(bkr_str_concat("Add an initializer for ", _v1044), " or update the struct definition.")));
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_i64 _v2265(bkr_i64 _v1239, bkr_str _v2001, bkr_str _v2266, _v426 _v1031, bkr_i64 _v2177, bkr_i64 _v2178, bkr_str _v2104) {
    if (_v2175(_v2178)) {
        return _v1239;
    }
    return _v2207(_v1239, "binary_operand_type_mismatch", _v2266, _v2001, _v546(_v1031), _v2177, _v2178, _v2104);
}

bkr_i64 _v2267(bkr_i64 _v1239, _v1531 _v2189, _v426 _v541, bkr_str _v2001) {
    bkr_i64 _v349 = _v671(_v541);
    _v426 _v1050 = _v537(_v674(_v541));
    _v426 _v1051 = _v537(_v677(_v541));
    bkr_i64 _v1675 = _v2190(_v2189, _v1050);
    bkr_i64 _v1676 = _v2190(_v2189, _v1051);
    bkr_str _v2268 = _v1306(_v349);
    if (_v2246(_v349)) {
        if ((_v1675 != _v305)) {
            _v1239 = _v2265(_v1239, _v2001, bkr_str_concat("left operand for ", _v2268), _v1050, _v305, _v1675, bkr_str_concat(bkr_str_concat("Use bool operands with ", _v2268), "."));
        }
        if ((_v1676 != _v305)) {
            _v1239 = _v2265(_v1239, _v2001, bkr_str_concat("right operand for ", _v2268), _v1051, _v305, _v1676, bkr_str_concat(bkr_str_concat("Use bool operands with ", _v2268), "."));
        }
    } else {
        if (_v2247(_v349)) {
            if ((!_v2173(_v1675))) {
                _v1239 = _v2265(_v1239, _v2001, bkr_str_concat("left operand for ", _v2268), _v1050, _v303, _v1675, bkr_str_concat(bkr_str_concat("Use integer operands with ", _v2268), "."));
            }
            if ((!_v2173(_v1676))) {
                _v1239 = _v2265(_v1239, _v2001, bkr_str_concat("right operand for ", _v2268), _v1051, _v303, _v1676, bkr_str_concat(bkr_str_concat("Use integer operands with ", _v2268), "."));
            }
        } else {
            if (_v2248(_v349)) {
                if (((_v349 == _v161) && ((_v1675 == _v306) || (_v1676 == _v306)))) {
                    return _v1239;
                }
                if ((!_v2174(_v1675))) {
                    _v1239 = _v2265(_v1239, _v2001, bkr_str_concat("left operand for ", _v2268), _v1050, _v303, _v1675, bkr_str_concat(bkr_str_concat("Use numeric operands with ", _v2268), "."));
                }
                if ((!_v2174(_v1676))) {
                    _v1239 = _v2265(_v1239, _v2001, bkr_str_concat("right operand for ", _v2268), _v1051, _v303, _v1676, bkr_str_concat(bkr_str_concat("Use numeric operands with ", _v2268), "."));
                }
            } else {
                if (((_v349 == _v166) || (_v349 == _v167))) {
                    if ((!_v2176(_v1675, _v1676))) {
                        _v1239 = _v2207(_v1239, "binary_operand_type_mismatch", bkr_str_concat("right operand for ", _v2268), _v2001, _v546(_v1051), _v1675, _v1676, "Compare values with compatible operand types.");
                    }
                }
            }
        }
    }
    return _v1239;
}

bkr_bool _v2269(_v1531 _v2189, _v426 _v541) {
    if ((_v544(_v541) != _v242)) {
        return BKR_FALSE;
    }
    if ((_v671(_v541) != _v176)) {
        return BKR_FALSE;
    }
    _v426 _v1051 = _v537(_v677(_v541));
    if ((_v544(_v1051) != _v256)) {
        return BKR_FALSE;
    }
    _v426 _v1037 = _v537(_v719(_v1051));
    if ((_v544(_v1037) != _v245)) {
        return BKR_FALSE;
    }
    bkr_i64 _v425 = _v1561(_v2189);
    bkr_str _v1626 = _v1625(_v425, _v662(_v1037));
    bkr_str _v1628 = _v1625(_v425, _v722(_v1051));
    bkr_i64 _v1674 = _v1627(_v2189, _v1626, _v1628);
    return (_v1674 >= 0);
}

bkr_i64 _v2270(bkr_i64 _v1239, _v1531 _v2189, _v426 _v541, bkr_str _v2001) {
    bkr_i64 _v349 = _v681(_v541);
    _v426 _v1031 = _v537(_v684(_v541));
    bkr_i64 _v2271 = _v2190(_v2189, _v1031);
    if (_v2175(_v2271)) {
        return _v1239;
    }
    if (((_v349 == _v174) && (_v2271 != _v305))) {
        return _v2207(_v1239, "unary_operand_type_mismatch", "operand for !", _v2001, _v546(_v1031), _v305, _v2271, "Use a bool operand with !.");
    }
    if (((_v349 == _v162) && (!_v2174(_v2271)))) {
        return _v2207(_v1239, "unary_operand_type_mismatch", "operand for unary -", _v2001, _v546(_v1031), _v303, _v2271, "Use a numeric operand with unary -.");
    }
    return _v1239;
}

bkr_i64 _v2272(bkr_i64 _v1239, _v1531 _v2189, _v426 _v541, bkr_str _v2001) {
    bkr_i64 _v1044 = _v722(_v541);
    bkr_i64 _v425 = _v1561(_v2189);
    bkr_str _v1767 = _v1625(_v425, _v1044);
    if ((((bkr_str_eq(_v1767, "0") || bkr_str_eq(_v1767, "1")) || bkr_str_eq(_v1767, "2")) || bkr_str_eq(_v1767, "3"))) {
        return _v1239;
    }
    _v426 _v1037 = _v537(_v719(_v541));
    if ((_v544(_v1037) == _v245)) {
        bkr_str _v1626 = _v1625(_v425, _v662(_v1037));
        bkr_i64 _v1674 = _v1627(_v2189, _v1626, _v1767);
        if ((_v1674 >= 0)) {
            return _v1239;
        }
    }
    bkr_i64 _v2273 = _v2190(_v2189, _v1037);
    if ((_v2273 == _v316)) {
        return _v1239;
    }
    if ((_v2273 != _v309)) {
        _v1239 = _v2207(_v1239, "field_access_base_type_mismatch", "field access base", _v2001, _v546(_v1037), _v309, _v2273, "Access fields only on struct values.");
    }
    return _v1239;
}

bkr_i64 _v2274(bkr_i64 _v1239, _v1531 _v2189, _v426 _v541, bkr_str _v2001) {
    _v426 _v1037 = _v537(_v711(_v541));
    bkr_i64 _v2273 = _v2190(_v2189, _v1037);
    if ((_v2273 == _v316)) {
        return _v1239;
    }
    if ((_v2273 != _v308)) {
        _v1239 = _v2207(_v1239, "index_base_type_mismatch", "index base", _v2001, _v546(_v1037), _v308, _v2273, "Index only array values; use Vec/HashMap builtins for handle collections.");
    }
    return _v1239;
}

bkr_i64 _v2275(_v1531 _v2189, _v341 _v1123) {
    if ((_v509(_v1123) == _v227)) {
        _v429 _v582 = _v580(_v1123);
        if ((_v589(_v582) <= 0)) {
            return _v316;
        }
        _v427 _v1671 = _v1107(_v582, (_v589(_v582) - 1));
        if ((_v555(_v1671) == _v232)) {
            return _v2190(_v2189, _v537(_v860(_v1671)));
        }
        return _v316;
    }
    return _v2190(_v2189, _v539(_v1123));
}

bkr_i64 _v2276(bkr_i64 _v1239, _v1531 _v2189, _v434 _v975, bkr_str _v2001) {
    if ((_v906(_v975) <= 1)) {
        return _v1239;
    }
    _v341 _v2277 = _v912(_v975, 0);
    bkr_i64 _v2177 = _v2275(_v2189, _v2277);
    bkr_i64 _v1168 = 1;
    while ((_v1168 < _v906(_v975))) {
        _v341 _v1123 = _v912(_v975, _v1168);
        bkr_i64 _v2178 = _v2275(_v2189, _v1123);
        _v1239 = _v2251(_v1239, "match_arm_type_mismatch", bkr_str_concat("match arm ", int_to_string((_v1168 + 1))), _v2001, _v1123, _v2177, _v2178, "Make every match arm produce a compatible value type.");
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_i64 _v2278(_v433 _v472) {
    bkr_i64 _v2279 = _v596(_v472);
    if ((_v2279 == _v292)) {
        return _v303;
    }
    if ((_v2279 == _v293)) {
        return _v309;
    }
    if ((_v2279 == _v283)) {
        return _v303;
    }
    if ((_v2279 == _v284)) {
        return _v305;
    }
    if (((_v2279 == _v287) || (_v2279 == _v288))) {
        return _v312;
    }
    if (((_v2279 == _v290) || (_v2279 == _v291))) {
        return _v313;
    }
    return _v316;
}

bkr_bool _v2280(bkr_i64 _v1715, bkr_i64 _v2177) {
    if (((_v1715 == _v316) || (_v2177 == _v316))) {
        return BKR_TRUE;
    }
    if ((_v1715 == _v2177)) {
        return BKR_TRUE;
    }
    if ((_v2173(_v1715) && _v2173(_v2177))) {
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_i64 _v2281(bkr_i64 _v1239, _v436 _v620, bkr_i64 _v1715, bkr_str _v2001) {
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v919(_v620))) {
        _v433 _v472 = _v924(_v620, _v1168);
        bkr_i64 _v2177 = _v2278(_v472);
        if (((_v2177 != _v316) && (!_v2280(_v1715, _v2177)))) {
            _v1239 = _v1950(_v1239, _v2205("match_pattern_type_mismatch", "BKR_SELF_TYPE_MISMATCH", bkr_str_concat("match pattern ", int_to_string((_v1168 + 1))), _v2001, _v601(_v472), _v602(_v472), _v327(_v1715), _v327(_v2177), _v2042(_v1715, "expected"), _v2042(_v2177, "found"), "Use a pattern that matches the scrutinee type."));
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_bool _v2282(_v433 _v472) {
    bkr_i64 _v319 = _v596(_v472);
    return (((_v319 == _v283) || (_v319 == _v284)) || (_v319 == _v288));
}

bkr_bool _v2283(_v433 _v472) {
    bkr_i64 _v319 = _v596(_v472);
    if ((((_v319 == _v286) || (_v319 == _v285)) || (_v319 == _v293))) {
        return BKR_TRUE;
    }
    if ((_v319 == _v292)) {
        bkr_i64 _v345 = _v598(_v472);
        if ((_v345 != 0)) {
            bkr_i64 _v1375 = ((bkr_i64)(_v345));
            bkr_i64 _v1168 = 0;
            while ((_v1168 < vec_len(_v1375))) {
                _v433 _v1393 = _v591(vec_get(_v1375, _v1168));
                if ((!_v2283(_v1393))) {
                    return BKR_FALSE;
                }
                _v1168 = (_v1168 + 1);
            }
            return BKR_TRUE;
        }
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_bool _v2284(_v433 _v1050, _v433 _v1051) {
    if ((_v596(_v1050) != _v596(_v1051))) {
        return BKR_FALSE;
    }
    bkr_i64 _v319 = _v596(_v1050);
    if ((((_v596(_v1050) == _v287) || (_v319 == _v290)) || (_v319 == _v291))) {
        bkr_i64 _v2285 = _v598(_v1050);
        bkr_i64 _v2286 = _v598(_v1051);
        if (((_v2285 != 0) || (_v2286 != 0))) {
            if (((_v2285 != 0) && (_v2286 != 0))) {
                _v433 _v2287 = _v591(_v2285);
                _v433 _v2288 = _v591(_v2286);
                return _v2284(_v2287, _v2288);
            }
            return BKR_FALSE;
        }
        return BKR_TRUE;
    }
    if ((_v319 == _v292)) {
        bkr_i64 _v2285 = _v598(_v1050);
        bkr_i64 _v2286 = _v598(_v1051);
        if (((_v2285 != 0) && (_v2286 != 0))) {
            bkr_i64 _v2289 = ((bkr_i64)(_v2285));
            bkr_i64 _v2290 = ((bkr_i64)(_v2286));
            if ((vec_len(_v2289) != vec_len(_v2290))) {
                return BKR_FALSE;
            }
            bkr_i64 _v1168 = 0;
            while ((_v1168 < vec_len(_v2289))) {
                _v433 _v2291 = _v591(vec_get(_v2289, _v1168));
                _v433 _v2292 = _v591(vec_get(_v2290, _v1168));
                if ((!_v2284(_v2291, _v2292))) {
                    return BKR_FALSE;
                }
                _v1168 = (_v1168 + 1);
            }
            return BKR_TRUE;
        }
        return BKR_FALSE;
    }
    if ((!_v2282(_v1050))) {
        return BKR_FALSE;
    }
    return (_v597(_v1050) == _v597(_v1051));
}

bkr_i64 _v2293(bkr_i64 _v1239, bkr_str _v319, bkr_str _v1348, bkr_str _v2001, _v433 _v472, bkr_str _v1264, bkr_str _v2200, bkr_str _v2104) {
    return _v1950(_v1239, _v2205(_v319, "BKR_SELF_MATCH_PATTERN", _v1348, _v2001, _v601(_v472), _v602(_v472), _v1264, _v2200, _v2042(_v316, "expected"), _v2042(_v316, "found"), _v2104));
}

bkr_i64 _v2294(bkr_i64 _v1239, _v435 _v976, _v436 _v620, bkr_str _v2001) {
    bkr_bool _v2295 = BKR_FALSE;
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v919(_v620))) {
        bkr_bool _v2296 = ((_v1168 < _v915(_v976)) && (_v917(_v976, _v1168) != 0));
        _v433 _v472 = _v924(_v620, _v1168);
        if (_v2295) {
            _v1239 = _v2293(_v1239, "unreachable_match_pattern", bkr_str_concat("match pattern ", int_to_string((_v1168 + 1))), _v2001, _v472, "reachable match pattern", "previous catch-all pattern already matches", "Remove this arm or move it before the catch-all pattern.");
        } else {
            if ((!_v2296)) {
                bkr_i64 _v1629 = 0;
                while ((_v1629 < _v1168)) {
                    bkr_bool _v2297 = ((_v1629 < _v915(_v976)) && (_v917(_v976, _v1629) != 0));
                    if ((!_v2297)) {
                        _v433 _v2298 = _v924(_v620, _v1629);
                        if (_v2284(_v2298, _v472)) {
                            _v1239 = _v2293(_v1239, "duplicate_match_pattern", bkr_str_concat("match pattern ", int_to_string((_v1168 + 1))), _v2001, _v472, "unique match pattern", _v328(_v596(_v472)), "Remove the duplicate pattern or merge its arm with the first occurrence.");
                        }
                    }
                    _v1629 = (_v1629 + 1);
                }
                if (_v2283(_v472)) {
                    _v2295 = BKR_TRUE;
                }
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_bool _v2299(_v435 _v976, _v436 _v620, bkr_i64 _v387) {
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v919(_v620))) {
        if (((_v1168 < _v915(_v976)) && (_v917(_v976, _v1168) != 0))) {
            _v1168 = (_v1168 + 1);
            continue;
        }
        _v433 _v472 = _v924(_v620, _v1168);
        if (_v2283(_v472)) {
            return BKR_TRUE;
        }
        if (((_v596(_v472) == _v284) && (_v597(_v472) == _v387))) {
            return BKR_TRUE;
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_FALSE;
}

bkr_bool _v2301(_v436 _v620) {
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v919(_v620))) {
        bkr_i64 _v2279 = _v596(_v924(_v620, _v1168));
        if (((_v2279 == _v287) || (_v2279 == _v288))) {
            return BKR_TRUE;
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_FALSE;
}

bkr_bool _v2302(bkr_i64 _v2303) {
    bkr_i64 _v1168 = 0;
    bkr_bool _v2304 = BKR_FALSE;
    bkr_bool _v2305 = BKR_FALSE;
    bkr_bool _v2306 = BKR_FALSE;
    bkr_bool _v2307 = BKR_FALSE;
    bkr_bool _v2308 = BKR_FALSE;
    bkr_bool _v2309 = BKR_FALSE;
    while ((_v1168 < vec_len(_v2303))) {
        _v433 _v2310 = _v591(vec_get(_v2303, _v1168));
        if (_v2283(_v2310)) {
            return BKR_TRUE;
        }
        bkr_i64 _v319 = _v596(_v2310);
        if ((_v319 == _v287)) {
            bkr_i64 _v345 = _v598(_v2310);
            if ((_v345 == 0)) {
                _v2304 = BKR_TRUE;
            } else {
                _v433 _v2311 = _v591(_v345);
                if (_v2283(_v2311)) {
                    _v2304 = BKR_TRUE;
                }
            }
        }
        if ((_v319 == _v288)) {
            _v2305 = BKR_TRUE;
        }
        if ((_v319 == _v290)) {
            bkr_i64 _v345 = _v598(_v2310);
            if ((_v345 == 0)) {
                _v2306 = BKR_TRUE;
            } else {
                _v433 _v2311 = _v591(_v345);
                if (_v2283(_v2311)) {
                    _v2306 = BKR_TRUE;
                }
            }
        }
        if ((_v319 == _v291)) {
            bkr_i64 _v345 = _v598(_v2310);
            if ((_v345 == 0)) {
                _v2307 = BKR_TRUE;
            } else {
                _v433 _v2311 = _v591(_v345);
                if (_v2283(_v2311)) {
                    _v2307 = BKR_TRUE;
                }
            }
        }
        if ((_v319 == _v284)) {
            if ((_v597(_v2310) == 1)) {
                _v2308 = BKR_TRUE;
            }
            if ((_v597(_v2310) == 0)) {
                _v2309 = BKR_TRUE;
            }
        }
        _v1168 = (_v1168 + 1);
    }
    if ((_v2304 && _v2305)) {
        return BKR_TRUE;
    }
    if ((_v2306 && _v2307)) {
        return BKR_TRUE;
    }
    if ((_v2308 && _v2309)) {
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_bool _v2312(_v435 _v976, _v436 _v620, bkr_i64 _v2279) {
    bkr_i64 _v1168 = 0;
    bkr_i64 _v2303 = vec_new();
    while ((_v1168 < _v919(_v620))) {
        if (((_v1168 < _v915(_v976)) && (_v917(_v976, _v1168) != 0))) {
            _v1168 = (_v1168 + 1);
            continue;
        }
        _v433 _v472 = _v924(_v620, _v1168);
        if (_v2283(_v472)) {
            return BKR_TRUE;
        }
        if ((_v596(_v472) == _v2279)) {
            if ((_v2279 == _v287)) {
                bkr_i64 _v345 = _v598(_v472);
                if ((_v345 == 0)) {
                    return BKR_TRUE;
                }
                _v433 _v1393 = _v591(_v345);
                if (_v2283(_v1393)) {
                    return BKR_TRUE;
                }
                vec_push(_v2303, _v345);
            } else {
                return BKR_TRUE;
            }
        }
        _v1168 = (_v1168 + 1);
    }
    if (((_v2279 == _v287) && (vec_len(_v2303) > 0))) {
        return _v2302(_v2303);
    }
    return BKR_FALSE;
}

bkr_i64 _v2313(bkr_i64 _v1239, _v426 _v541, _v436 _v620, bkr_i64 _v1715, bkr_str _v2001) {
    if ((_v1715 != _v305)) {
        return _v1239;
    }
    _v435 _v976 = _v750(_v541);
    bkr_bool _v2314 = _v2299(_v976, _v620, 1);
    bkr_bool _v2315 = _v2299(_v976, _v620, 0);
    if ((_v2314 && _v2315)) {
        return _v1239;
    }
    bkr_str _v2316 = "";
    if ((!_v2314)) {
        _v2316 = "true";
    }
    if ((!_v2315)) {
        if ((bkr_len((bkr_str)(intptr_t)(_v2316)) > 0)) {
            _v2316 = bkr_str_concat(_v2316, ", false");
        } else {
            _v2316 = "false";
        }
    }
    return _v1950(_v1239, _v2201("non_exhaustive_match", "BKR_SELF_EXHAUSTIVENESS", "match", _v2001, _v546(_v541), "patterns covering true and false", bkr_str_concat("missing ", _v2316), "Add the missing boolean pattern arm or a catch-all pattern."));
}

bkr_i64 _v2317(bkr_i64 _v1239, _v435 _v976, _v436 _v620, bkr_i64 _v1715, bkr_str _v2001) {
    if ((_v1715 != _v305)) {
        return _v1239;
    }
    bkr_bool _v2314 = BKR_FALSE;
    bkr_bool _v2315 = BKR_FALSE;
    bkr_bool _v2318 = BKR_FALSE;
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v919(_v620))) {
        bkr_bool _v2296 = ((_v1168 < _v915(_v976)) && (_v917(_v976, _v1168) != 0));
        _v433 _v472 = _v924(_v620, _v1168);
        if (_v2318) {
            _v1239 = _v2293(_v1239, "unreachable_match_pattern", bkr_str_concat("match pattern ", int_to_string((_v1168 + 1))), _v2001, _v472, "reachable match pattern", "previous bool patterns already cover true and false", "Remove this arm or move it before the exhaustive bool patterns.");
        }
        if ((!_v2296)) {
            if (((_v596(_v472) == _v284) && (_v597(_v472) == 1))) {
                _v2314 = BKR_TRUE;
            }
            if (((_v596(_v472) == _v284) && (_v597(_v472) == 0))) {
                _v2315 = BKR_TRUE;
            }
            if ((_v2314 && _v2315)) {
                _v2318 = BKR_TRUE;
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_i64 _v2319(bkr_i64 _v1239, _v426 _v541, _v436 _v620, bkr_str _v2001) {
    if ((!_v2301(_v620))) {
        return _v1239;
    }
    _v435 _v976 = _v750(_v541);
    bkr_bool _v2320 = _v2312(_v976, _v620, _v287);
    bkr_bool _v2321 = _v2312(_v976, _v620, _v288);
    if ((_v2320 && _v2321)) {
        return _v1239;
    }
    bkr_str _v2316 = "";
    if ((!_v2320)) {
        _v2316 = "Some";
    }
    if ((!_v2321)) {
        if ((bkr_len((bkr_str)(intptr_t)(_v2316)) > 0)) {
            _v2316 = bkr_str_concat(_v2316, ", None");
        } else {
            _v2316 = "None";
        }
    }
    return _v1950(_v1239, _v2201("non_exhaustive_match", "BKR_SELF_EXHAUSTIVENESS", "match", _v2001, _v546(_v541), "patterns covering Some and None", bkr_str_concat("missing ", _v2316), "Add the missing Option pattern arm or a catch-all pattern."));
}

bkr_i64 _v2322(bkr_i64 _v1239, _v435 _v976, _v436 _v620, bkr_str _v2001) {
    if ((!_v2301(_v620))) {
        return _v1239;
    }
    bkr_bool _v2320 = BKR_FALSE;
    bkr_bool _v2321 = BKR_FALSE;
    bkr_bool _v2318 = BKR_FALSE;
    bkr_i64 _v1168 = 0;
    bkr_i64 _v2303 = vec_new();
    while ((_v1168 < _v919(_v620))) {
        bkr_bool _v2296 = ((_v1168 < _v915(_v976)) && (_v917(_v976, _v1168) != 0));
        _v433 _v472 = _v924(_v620, _v1168);
        if (_v2318) {
            _v1239 = _v2293(_v1239, "unreachable_match_pattern", bkr_str_concat("match pattern ", int_to_string((_v1168 + 1))), _v2001, _v472, "reachable match pattern", "previous Option patterns already cover Some and None", "Remove this arm or move it before the exhaustive Option patterns.");
        }
        if ((!_v2296)) {
            if ((_v596(_v472) == _v287)) {
                bkr_i64 _v345 = _v598(_v472);
                if ((_v345 == 0)) {
                    _v2320 = BKR_TRUE;
                } else {
                    _v433 _v1393 = _v591(_v345);
                    if (_v2283(_v1393)) {
                        _v2320 = BKR_TRUE;
                    } else {
                        vec_push(_v2303, _v345);
                        if (_v2302(_v2303)) {
                            _v2320 = BKR_TRUE;
                        }
                    }
                }
            }
            if ((_v596(_v472) == _v288)) {
                _v2321 = BKR_TRUE;
            }
            if ((_v2320 && _v2321)) {
                _v2318 = BKR_TRUE;
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_bool _v2323(_v436 _v620) {
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v919(_v620))) {
        _v433 _v472 = _v924(_v620, _v1168);
        bkr_i64 _v319 = _v596(_v472);
        if (((_v319 == _v290) || (_v319 == _v291))) {
            return BKR_TRUE;
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_FALSE;
}

bkr_bool _v2324(_v435 _v976, _v436 _v620, bkr_i64 _v2279) {
    bkr_i64 _v1168 = 0;
    bkr_i64 _v2303 = vec_new();
    while ((_v1168 < _v919(_v620))) {
        if (((_v1168 < _v915(_v976)) && (_v917(_v976, _v1168) != 0))) {
            _v1168 = (_v1168 + 1);
            continue;
        }
        _v433 _v472 = _v924(_v620, _v1168);
        if (_v2283(_v472)) {
            return BKR_TRUE;
        }
        if ((_v596(_v472) == _v2279)) {
            bkr_i64 _v345 = _v598(_v472);
            if ((_v345 == 0)) {
                return BKR_TRUE;
            }
            _v433 _v1393 = _v591(_v345);
            if (_v2283(_v1393)) {
                return BKR_TRUE;
            }
            vec_push(_v2303, _v345);
        }
        _v1168 = (_v1168 + 1);
    }
    if ((vec_len(_v2303) > 0)) {
        return _v2302(_v2303);
    }
    return BKR_FALSE;
}

bkr_i64 _v2325(bkr_i64 _v1239, _v426 _v541, _v436 _v620, bkr_str _v2001) {
    if ((!_v2323(_v620))) {
        return _v1239;
    }
    _v435 _v976 = _v750(_v541);
    bkr_bool _v2326 = _v2324(_v976, _v620, _v290);
    bkr_bool _v2327 = _v2324(_v976, _v620, _v291);
    if ((_v2326 && _v2327)) {
        return _v1239;
    }
    bkr_str _v2316 = "";
    if ((!_v2326)) {
        _v2316 = "Ok";
    }
    if ((!_v2327)) {
        if ((bkr_len((bkr_str)(intptr_t)(_v2316)) > 0)) {
            _v2316 = bkr_str_concat(_v2316, ", Err");
        } else {
            _v2316 = "Err";
        }
    }
    return _v1950(_v1239, _v2201("non_exhaustive_match", "BKR_SELF_EXHAUSTIVENESS", "match", _v2001, _v546(_v541), "patterns covering Ok and Err", bkr_str_concat("missing ", _v2316), "Add the missing Result pattern arm or a catch-all pattern."));
}

bkr_i64 _v2328(bkr_i64 _v1239, _v435 _v976, _v436 _v620, bkr_str _v2001) {
    if ((!_v2323(_v620))) {
        return _v1239;
    }
    bkr_bool _v2326 = BKR_FALSE;
    bkr_bool _v2327 = BKR_FALSE;
    bkr_bool _v2318 = BKR_FALSE;
    bkr_i64 _v1168 = 0;
    bkr_i64 _v2329 = vec_new();
    bkr_i64 _v2330 = vec_new();
    while ((_v1168 < _v919(_v620))) {
        bkr_bool _v2296 = ((_v1168 < _v915(_v976)) && (_v917(_v976, _v1168) != 0));
        _v433 _v472 = _v924(_v620, _v1168);
        if (_v2318) {
            _v1239 = _v2293(_v1239, "unreachable_match_pattern", bkr_str_concat("match pattern ", int_to_string((_v1168 + 1))), _v2001, _v472, "reachable match pattern", "previous Result patterns already cover Ok and Err", "Remove this arm or move it before the exhaustive Result patterns.");
        }
        if ((!_v2296)) {
            if ((_v596(_v472) == _v290)) {
                bkr_i64 _v345 = _v598(_v472);
                if ((_v345 == 0)) {
                    _v2326 = BKR_TRUE;
                } else {
                    _v433 _v1393 = _v591(_v345);
                    if (_v2283(_v1393)) {
                        _v2326 = BKR_TRUE;
                    } else {
                        vec_push(_v2329, _v345);
                        if (_v2302(_v2329)) {
                            _v2326 = BKR_TRUE;
                        }
                    }
                }
            }
            if ((_v596(_v472) == _v291)) {
                bkr_i64 _v345 = _v598(_v472);
                if ((_v345 == 0)) {
                    _v2327 = BKR_TRUE;
                } else {
                    _v433 _v1393 = _v591(_v345);
                    if (_v2283(_v1393)) {
                        _v2327 = BKR_TRUE;
                    } else {
                        vec_push(_v2330, _v345);
                        if (_v2302(_v2330)) {
                            _v2327 = BKR_TRUE;
                        }
                    }
                }
            }
            if ((_v2326 && _v2327)) {
                _v2318 = BKR_TRUE;
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_bool _v2331(_v436 _v620) {
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v919(_v620))) {
        if ((_v596(_v924(_v620, _v1168)) == _v289)) {
            return BKR_TRUE;
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_FALSE;
}

bkr_i64 _v2332(_v436 _v620) {
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v919(_v620))) {
        _v433 _v472 = _v924(_v620, _v1168);
        if ((_v596(_v472) == _v289)) {
            return _v597(_v472);
        }
        _v1168 = (_v1168 + 1);
    }
    return (-1);
}

_v428 _v2333(_v341 _v1530, bkr_i64 _v2334) {
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if ((_v568(_v562) == _v259)) {
            if ((_v1164(_v562) == _v2334)) {
                return _v562;
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return _v563();
}

bkr_bool _v2335(_v435 _v976, _v436 _v620, bkr_i64 _v2334, bkr_i64 _v1388) {
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v919(_v620))) {
        if (((_v1168 < _v915(_v976)) && (_v917(_v976, _v1168) != 0))) {
            _v1168 = (_v1168 + 1);
            continue;
        }
        _v433 _v472 = _v924(_v620, _v1168);
        if (_v2283(_v472)) {
            return BKR_TRUE;
        }
        if ((_v596(_v472) == _v289)) {
            if ((_v597(_v472) == _v2334)) {
                if ((_v598(_v472) == _v1388)) {
                    return BKR_TRUE;
                }
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_FALSE;
}

bkr_i64 _v2336(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v426 _v541, _v436 _v620, bkr_str _v2001) {
    if ((!_v2331(_v620))) {
        return _v1239;
    }
    bkr_i64 _v2334 = _v2332(_v620);
    if ((_v2334 < 0)) {
        return _v1239;
    }
    _v428 _v2337 = _v2333(_v1530, _v2334);
    if (_v565(_v2337)) {
        return _v1239;
    }
    _v435 _v1162 = _v1165(_v2337);
    if ((_v915(_v1162) <= 0)) {
        return _v1239;
    }
    _v435 _v976 = _v750(_v541);
    bkr_str _v2316 = "";
    bkr_i64 _v1629 = 0;
    while ((_v1629 < _v915(_v1162))) {
        bkr_i64 _v1388 = _v917(_v1162, _v1629);
        if ((!_v2335(_v976, _v620, _v2334, _v1388))) {
            bkr_str _v2338 = bkr_str_concat(bkr_str_concat(_v1945(_v425, _v2334), "."), _v1945(_v425, _v1388));
            if ((bkr_len((bkr_str)(intptr_t)(_v2316)) > 0)) {
                _v2316 = bkr_str_concat(bkr_str_concat(_v2316, ", "), _v2338);
            } else {
                _v2316 = _v2338;
            }
        }
        _v1629 = (_v1629 + 1);
    }
    if ((bkr_len((bkr_str)(intptr_t)(_v2316)) <= 0)) {
        return _v1239;
    }
    return _v1950(_v1239, _v2201("non_exhaustive_match", "BKR_SELF_EXHAUSTIVENESS", "match", _v2001, _v546(_v541), "patterns covering every declared enum variant", bkr_str_concat("missing ", _v2316), "Add the missing enum pattern arm or a catch-all pattern."));
}

bkr_i64 _v2339(bkr_i64 _v1239, _v426 _v541, _v436 _v620, bkr_i64 _v1715, bkr_str _v2001) {
    if (((_v2331(_v620) || _v2301(_v620)) || _v2323(_v620))) {
        return _v1239;
    }
    if (((!_v2174(_v1715)) && (_v1715 != _v306))) {
        return _v1239;
    }
    _v435 _v976 = _v750(_v541);
    bkr_i64 _v1168 = 0;
    bkr_bool _v2340 = BKR_FALSE;
    while ((_v1168 < _v919(_v620))) {
        if (((_v1168 < _v915(_v976)) && (_v917(_v976, _v1168) != 0))) {
            _v1168 = (_v1168 + 1);
            continue;
        }
        _v433 _v472 = _v924(_v620, _v1168);
        if (_v2283(_v472)) {
            _v2340 = BKR_TRUE;
        }
        _v1168 = (_v1168 + 1);
    }
    if (_v2340) {
        return _v1239;
    }
    return _v1950(_v1239, _v2201("non_exhaustive_match", "BKR_SELF_EXHAUSTIVENESS", "match", _v2001, _v546(_v541), "patterns covering all values or a catch-all pattern", "missing catch-all pattern", "Add a wildcard '_' arm or identifier pattern to cover all remaining values."));
}

bkr_i64 _v2341(bkr_i64 _v1239, _v341 _v1530, _v435 _v976, _v436 _v620, bkr_str _v2001) {
    if ((!_v2331(_v620))) {
        return _v1239;
    }
    bkr_i64 _v2334 = _v2332(_v620);
    if ((_v2334 < 0)) {
        return _v1239;
    }
    _v428 _v2337 = _v2333(_v1530, _v2334);
    if (_v565(_v2337)) {
        return _v1239;
    }
    _v435 _v1162 = _v1165(_v2337);
    bkr_i64 _v2342 = _v915(_v1162);
    if ((_v2342 <= 0)) {
        return _v1239;
    }
    bkr_i64 _v2343 = 0;
    bkr_bool _v2318 = BKR_FALSE;
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v919(_v620))) {
        bkr_bool _v2296 = ((_v1168 < _v915(_v976)) && (_v917(_v976, _v1168) != 0));
        _v433 _v472 = _v924(_v620, _v1168);
        if (_v2318) {
            _v1239 = _v2293(_v1239, "unreachable_match_pattern", bkr_str_concat("match pattern ", int_to_string((_v1168 + 1))), _v2001, _v472, "reachable match pattern", "previous enum patterns already cover every declared variant", "Remove this arm or move it before the exhaustive enum patterns.");
        }
        if ((!_v2296)) {
            if ((_v596(_v472) == _v289)) {
                bkr_i64 _v1388 = _v598(_v472);
                if ((_v597(_v472) == _v2334)) {
                    if (_v2344(_v1162, _v1388)) {
                        if ((!_v2345(_v620, _v2334, _v1388, _v1168))) {
                            _v2343 = (_v2343 + 1);
                        }
                    }
                }
            }
            if ((_v2343 >= _v2342)) {
                _v2318 = BKR_TRUE;
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_bool _v2344(_v435 _v1162, bkr_i64 _v1388) {
    bkr_i64 _v1629 = 0;
    while ((_v1629 < _v915(_v1162))) {
        if ((_v917(_v1162, _v1629) == _v1388)) {
            return BKR_TRUE;
        }
        _v1629 = (_v1629 + 1);
    }
    return BKR_FALSE;
}

bkr_bool _v2345(_v436 _v620, bkr_i64 _v2334, bkr_i64 _v1388, bkr_i64 _v2346) {
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v2346)) {
        _v433 _v472 = _v924(_v620, _v1168);
        if ((_v596(_v472) == _v289)) {
            if ((_v597(_v472) == _v2334)) {
                if ((_v598(_v472) == _v1388)) {
                    return BKR_TRUE;
                }
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_FALSE;
}

bkr_i64 _v2347(bkr_i64 _v1239, _v1531 _v2189, _v434 _v994, bkr_str _v2001) {
    bkr_i64 _v2177 = _v316;
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v994))) {
        _v341 _v2016 = _v912(_v994, _v1168);
        _v426 _v2348 = _v539(_v2016);
        bkr_i64 _v2349 = _v2190(_v2189, _v2348);
        _v1239 = _v2226(_v1239, _v2189, _v2348, bkr_str_concat("array element ", int_to_string((_v1168 + 1))), _v2001);
        if ((_v2177 == _v316)) {
            if ((_v2349 != _v316)) {
                _v2177 = _v2349;
            }
        } else {
            _v1239 = _v2244(_v1239, "array_element_type_mismatch", bkr_str_concat("array element ", int_to_string((_v1168 + 1))), _v2001, _v2016, _v2177, _v2349, "Make every array literal element produce the same type.");
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_i64 _v2350(bkr_i64 _v1239, bkr_i64 _v1655, bkr_str _v2001, bkr_i64 _v2351) {
    if (_v523(_v1655)) {
        return _v1239;
    }
    return _v2352(_v1239, _v537(_v1655), _v2001, _v2351);
}

bkr_i64 _v2352(bkr_i64 _v1239, _v426 _v541, bkr_str _v2001, bkr_i64 _v2351) {
    bkr_i64 _v319 = _v544(_v541);
    if ((_v319 == _v261)) {
        _v1239 = _v2352(_v1239, _v694(_v541), _v2001, _v2351);
        _v434 _v1015 = _v698(_v541);
        bkr_i64 _v1168 = 0;
        while ((_v1168 < _v906(_v1015))) {
            _v1239 = _v2352(_v1239, _v539(_v912(_v1015, _v1168)), _v2001, _v2351);
            _v1168 = (_v1168 + 1);
        }
    } else {
        if ((_v319 == _v244)) {
            _v434 _v1015 = _v691(_v541);
            bkr_i64 _v1168 = 0;
            while ((_v1168 < _v906(_v1015))) {
                _v1239 = _v2352(_v1239, _v539(_v912(_v1015, _v1168)), _v2001, _v2351);
                _v1168 = (_v1168 + 1);
            }
        } else {
            if ((_v319 == _v257)) {
                _v434 _v1008 = _v730(_v541);
                bkr_i64 _v1168 = 0;
                while ((_v1168 < _v906(_v1008))) {
                    _v1239 = _v2352(_v1239, _v539(_v912(_v1008, _v1168)), _v2001, _v2351);
                    _v1168 = (_v1168 + 1);
                }
                bkr_i64 _v403 = _v1005(_v541);
                if ((_v403 != 0)) {
                    _v1239 = _v2350(_v1239, _v403, _v2001, _v2351);
                }
            } else {
                if ((_v319 == _v256)) {
                    _v1239 = _v2350(_v1239, _v719(_v541), _v2001, _v2351);
                } else {
                    if ((_v319 == _v242)) {
                        _v1239 = _v2350(_v1239, _v674(_v541), _v2001, _v2351);
                        _v1239 = _v2350(_v1239, _v677(_v541), _v2001, _v2351);
                    } else {
                        if ((_v319 == _v240)) {
                            _v1239 = _v2350(_v1239, _v777(_v541), _v2001, _v2351);
                        } else {
                            if ((_v319 == _v241)) {
                                _v1239 = _v2350(_v1239, _v781(_v541), _v2001, _v2351);
                            } else {
                                if ((_v319 == _v243)) {
                                    _v1239 = _v2350(_v1239, _v684(_v541), _v2001, _v2351);
                                } else {
                                    if ((_v319 == _v250)) {
                                        _v1239 = _v2350(_v1239, _v733(_v541), _v2001, _v2351);
                                        _v1239 = _v2350(_v1239, _v736(_v541), _v2001, _v2351);
                                        _v1239 = _v2350(_v1239, _v739(_v541), _v2001, _v2351);
                                    } else {
                                        if ((_v319 == _v239)) {
                                            _v1239 = _v2352(_v1239, _v704(_v541), _v2001, _v2351);
                                        } else {
                                            if ((_v319 == _v252)) {
                                                _v434 _v994 = _v701(_v541);
                                                bkr_i64 _v1168 = 0;
                                                while ((_v1168 < _v906(_v994))) {
                                                    _v1239 = _v2352(_v1239, _v539(_v912(_v994, _v1168)), _v2001, _v2351);
                                                    _v1168 = (_v1168 + 1);
                                                }
                                            } else {
                                                if ((_v319 == _v253)) {
                                                    _v1239 = _v2350(_v1239, _v711(_v541), _v2001, _v2351);
                                                    _v1239 = _v2350(_v1239, _v714(_v541), _v2001, _v2351);
                                                } else {
                                                    if ((_v319 == _v227)) {
                                                        _v1239 = _v2353(_v1239, _v580(_v546(_v541)), _v2001, _v2351);
                                                    } else {
                                                        if ((_v319 == _v258)) {
                                                            _v1239 = _v2350(_v1239, _v742(_v541), _v2001, _v2351);
                                                            _v434 _v975 = _v748(_v541);
                                                            bkr_i64 _v1168 = 0;
                                                            while ((_v1168 < _v906(_v975))) {
                                                                _v341 _v1123 = _v912(_v975, _v1168);
                                                                if ((_v509(_v1123) == _v227)) {
                                                                    _v1239 = _v2353(_v1239, _v580(_v1123), _v2001, _v2351);
                                                                } else {
                                                                    _v1239 = _v2352(_v1239, _v539(_v1123), _v2001, _v2351);
                                                                }
                                                                _v1168 = (_v1168 + 1);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return _v1239;
}

bkr_i64 _v2354(bkr_i64 _v1239, _v427 _v553, bkr_str _v2001, bkr_i64 _v2351) {
    bkr_i64 _v319 = _v555(_v553);
    if (((_v319 == _v234) || (_v319 == _v235))) {
        if ((_v2351 <= 0)) {
            _v1239 = _v2212(_v1239, _v2001, _v553);
        }
    } else {
        if ((_v319 == _v228)) {
            _v1239 = _v2350(_v1239, _v763(_v553), _v2001, _v2351);
        } else {
            if ((_v319 == _v229)) {
                _v1239 = _v2350(_v1239, _v768(_v553), _v2001, _v2351);
            } else {
                if ((_v319 == _v230)) {
                    _v1239 = _v2350(_v1239, _v827(_v553), _v2001, _v2351);
                    _v1239 = _v2353(_v1239, _v829(_v553), _v2001, _v2351);
                    bkr_i64 _v377 = _v832(_v553);
                    if (_v525(_v377)) {
                        _v1239 = _v2353(_v1239, _v578(_v377), _v2001, _v2351);
                    }
                } else {
                    if ((_v319 == _v231)) {
                        _v1239 = _v2350(_v1239, _v849(_v553), _v2001, _v2351);
                        _v1239 = _v2353(_v1239, _v851(_v553), _v2001, (_v2351 + 1));
                    } else {
                        if ((_v319 == _v236)) {
                            _v1239 = _v2350(_v1239, _v837(_v553), _v2001, _v2351);
                            _v1239 = _v2350(_v1239, _v840(_v553), _v2001, _v2351);
                            _v1239 = _v2353(_v1239, _v844(_v553), _v2001, (_v2351 + 1));
                        } else {
                            if ((_v319 == _v237)) {
                                _v1239 = _v2353(_v1239, _v846(_v553), _v2001, (_v2351 + 1));
                            } else {
                                if ((_v319 == _v233)) {
                                    _v1239 = _v2350(_v1239, _v854(_v553), _v2001, _v2351);
                                    _v1239 = _v2350(_v1239, _v857(_v553), _v2001, _v2351);
                                } else {
                                    if ((_v319 == _v238)) {
                                        _v1239 = _v2354(_v1239, _v549(_v772(_v553)), _v2001, _v2351);
                                    } else {
                                        if ((_v319 == _v232)) {
                                            _v1239 = _v2350(_v1239, _v860(_v553), _v2001, _v2351);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return _v1239;
}

bkr_i64 _v2353(bkr_i64 _v1239, _v429 _v582, bkr_str _v2001, bkr_i64 _v2351) {
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v589(_v582))) {
        _v1239 = _v2354(_v1239, _v1107(_v582, _v1168), _v2001, _v2351);
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_bool _v2355(_v427 _v553) {
    bkr_i64 _v319 = _v555(_v553);
    if ((_v319 == _v229)) {
        return BKR_TRUE;
    }
    if ((_v319 == _v230)) {
        bkr_i64 _v377 = _v832(_v553);
        if (_v523(_v377)) {
            return BKR_FALSE;
        }
        return (_v2356(_v829(_v553)) && _v2356(_v578(_v377)));
    }
    return BKR_FALSE;
}

bkr_bool _v2356(_v429 _v582) {
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v589(_v582))) {
        if (_v2355(_v1107(_v582, _v1168))) {
            return BKR_TRUE;
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_FALSE;
}

bkr_bool _v2357(_v427 _v553) {
    bkr_i64 _v319 = _v555(_v553);
    if ((((_v319 == _v229) || (_v319 == _v234)) || (_v319 == _v235))) {
        return BKR_TRUE;
    }
    if ((_v319 == _v230)) {
        bkr_i64 _v377 = _v832(_v553);
        if (_v523(_v377)) {
            return BKR_FALSE;
        }
        return (_v2358(_v829(_v553)) && _v2358(_v578(_v377)));
    }
    return BKR_FALSE;
}

bkr_bool _v2358(_v429 _v582) {
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v589(_v582))) {
        if (_v2357(_v1107(_v582, _v1168))) {
            return BKR_TRUE;
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_FALSE;
}

bkr_i64 _v2359(bkr_i64 _v1239, _v427 _v553, bkr_str _v2001) {
    bkr_i64 _v319 = _v555(_v553);
    if ((_v319 == _v230)) {
        _v1239 = _v2360(_v1239, _v829(_v553), _v2001);
        bkr_i64 _v377 = _v832(_v553);
        if (_v525(_v377)) {
            _v1239 = _v2360(_v1239, _v578(_v377), _v2001);
        }
    } else {
        if ((_v319 == _v231)) {
            _v1239 = _v2360(_v1239, _v851(_v553), _v2001);
        } else {
            if ((_v319 == _v236)) {
                _v1239 = _v2360(_v1239, _v844(_v553), _v2001);
            } else {
                if ((_v319 == _v237)) {
                    _v1239 = _v2360(_v1239, _v846(_v553), _v2001);
                }
            }
        }
    }
    return _v1239;
}

bkr_i64 _v2360(bkr_i64 _v1239, _v429 _v582, bkr_str _v2001) {
    bkr_bool _v2361 = BKR_FALSE;
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v589(_v582))) {
        _v427 _v553 = _v1107(_v582, _v1168);
        if (_v2361) {
            _v1239 = _v2227(_v1239, _v2001, _v553);
        } else {
            _v1239 = _v2359(_v1239, _v553, _v2001);
            if (_v2357(_v553)) {
                _v2361 = BKR_TRUE;
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_i64 _v2362(bkr_i64 _v1239, bkr_i64 _v425, _v1531 _v2189, bkr_i64 _v1655, bkr_str _v2001, bkr_str _v2363, bkr_str _v1348, bkr_i64 _v2177, bkr_str _v2104) {
    if (_v523(_v1655)) {
        if (((_v2177 != _v307) && (_v2177 != _v316))) {
            bkr_i64 _v2364 = _v474(_v229);
            _v1239 = _v2206(_v1239, _v2363, _v1348, _v2001, _v2364, _v2177, _v307, _v2104);
        }
        return _v1239;
    }
    return _v2365(_v1239, _v425, _v2189, _v537(_v1655), _v2001, _v2363, _v1348, _v2177, _v2104);
}

bkr_i64 _v2365(bkr_i64 _v1239, bkr_i64 _v425, _v1531 _v2189, _v426 _v541, bkr_str _v2001, bkr_str _v2363, bkr_str _v1348, bkr_i64 _v2177, bkr_str _v2104) {
    bkr_i64 _v2178 = _v2190(_v2189, _v541);
    return _v2244(_v1239, _v2363, _v1348, _v2001, _v546(_v541), _v2177, _v2178, _v2104);
}

bkr_i64 _v2366(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425, _v1531 _v2189, bkr_i64 _v368, bkr_str _v2001) {
    return _v2367(_v1239, _v476(_v0), _v425, _v2189, _v538(_v368), _v2001);
}

bkr_i64 _v2367(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v1531 _v2189, _v426 _v541, bkr_str _v2001) {
    bkr_i64 _v355 = _v688(_v541);
    _v428 _v1514 = _v2252(_v1530, _v355);
    if (_v565(_v1514)) {
        _v428 _v1523 = _v2258(_v1530, _v355);
        if (_v566(_v1523)) {
            bkr_str _v2368 = _v1945(_v425, _v355);
            _v434 _v1015 = _v691(_v541);
            _v434 _v1158 = _v889(_v1523);
            bkr_i64 _v1790 = _v906(_v1015);
            bkr_i64 _v2369 = _v906(_v1158);
            if ((_v1790 != _v2369)) {
                bkr_str _v2241 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Call struct constructor ", _v2368), " with exactly "), int_to_string(_v2369)), " argument(s), or update the struct definition.");
                _v1239 = _v2208(_v1239, "call_argument_count_mismatch", _v2368, _v2001, _v546(_v541), _v2369, _v1790, _v2241);
            }
            bkr_i64 _v1168 = 0;
            while (((_v1168 < _v1790) && (_v1168 < _v2369))) {
                _v341 _v1432 = _v912(_v1158, _v1168);
                bkr_i64 _v1154 = _v894(_v1432);
                _v341 _v2243 = _v912(_v1015, _v1168);
                _v426 _v1425 = _v539(_v2243);
                bkr_i64 _v2177 = _v2050(_v1530, _v516(_v1154));
                bkr_i64 _v2178 = _v2190(_v2189, _v1425);
                bkr_str _v2115 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Change argument ", int_to_string((_v1168 + 1))), " for "), _v2368), " to match field "), _v1945(_v425, _v891(_v1432))), " or update the struct definition.");
                _v1239 = _v2244(_v1239, "call_argument_type_mismatch", _v2368, _v2001, _v2243, _v2177, _v2178, _v2115);
                _v1168 = (_v1168 + 1);
            }
            return _v1239;
        }
        if ((_v2238(_v1945(_v425, _v355)) < 0)) {
            _v1239 = _v2256(_v1239, _v1530, _v425, _v541, _v2001);
        }
        return _v2245(_v1239, _v425, _v2189, _v541, _v2001);
    }
    bkr_str _v2023 = _v1945(_v425, _v355);
    _v434 _v1015 = _v691(_v541);
    _v434 _v1141 = _v871(_v1514);
    bkr_i64 _v1790 = _v906(_v1015);
    bkr_i64 _v2254 = _v906(_v1141);
    if ((_v1790 != _v2254)) {
        bkr_str _v2241 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Call ", _v2023), " with exactly "), int_to_string(_v2254)), " argument(s), or update the function signature.");
        _v1239 = _v2208(_v1239, "call_argument_count_mismatch", _v2023, _v2001, _v546(_v541), _v2254, _v1790, _v2241);
    }
    bkr_i64 _v1168 = 0;
    while (((_v1168 < _v1790) && (_v1168 < _v2254))) {
        _v341 _v1507 = _v912(_v1141, _v1168);
        bkr_i64 _v2088 = _v865(_v1507);
        _v341 _v2243 = _v912(_v1015, _v1168);
        _v426 _v1425 = _v539(_v2243);
        bkr_i64 _v2177 = _v2050(_v1530, _v516(_v2088));
        bkr_i64 _v2178 = _v2190(_v2189, _v1425);
        bkr_str _v2115 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Change argument ", int_to_string((_v1168 + 1))), " for "), _v2023), " to match parameter "), _v1945(_v425, _v862(_v1507))), " or update the function signature.");
        _v1239 = _v2244(_v1239, "call_argument_type_mismatch", _v2023, _v2001, _v2243, _v2177, _v2178, _v2115);
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_i64 _v2370(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425, _v1531 _v2189, bkr_i64 _v1655, bkr_str _v2001, bkr_i64 _v2371) {
    return _v2372(_v1239, _v476(_v0), _v425, _v2189, _v1655, _v2001, _v2371);
}

bkr_i64 _v2372(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v1531 _v2189, bkr_i64 _v1655, bkr_str _v2001, bkr_i64 _v2371) {
    if (_v523(_v1655)) {
        return _v1239;
    }
    return _v2373(_v1239, _v1530, _v425, _v2189, _v537(_v1655), _v2001, _v2371);
}

bkr_i64 _v2373(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v1531 _v2189, _v426 _v541, bkr_str _v2001, bkr_i64 _v2371) {
    bkr_i64 _v319 = _v544(_v541);
    if ((_v319 == _v261)) {
        _v426 _v1021 = _v694(_v541);
        bkr_i64 _v2374 = _v2190(_v2189, _v1021);
        if ((_v2374 != _v309)) {
            bkr_str _v2115 = "Methods can only be invoked on struct instances.";
            _v1239 = _v2251(_v1239, "invalid_method_call_target", "receiver", _v2001, _v546(_v1021), _v309, _v2374, _v2115);
        }
        _v1239 = _v2373(_v1239, _v1530, _v425, _v2189, _v1021, _v2001, _v2371);
        _v434 _v1015 = _v698(_v541);
        bkr_i64 _v1168 = 0;
        while ((_v1168 < _v906(_v1015))) {
            _v341 _v2243 = _v912(_v1015, _v1168);
            _v426 _v2375 = _v539(_v2243);
            _v1239 = _v2226(_v1239, _v2189, _v2375, bkr_str_concat("method argument ", int_to_string((_v1168 + 1))), _v2001);
            _v1239 = _v2373(_v1239, _v1530, _v425, _v2189, _v2375, _v2001, _v2371);
            _v1168 = (_v1168 + 1);
        }
    } else {
        if ((_v319 == _v244)) {
            _v1239 = _v2367(_v1239, _v1530, _v425, _v2189, _v541, _v2001);
            _v434 _v1015 = _v691(_v541);
            bkr_i64 _v1168 = 0;
            while ((_v1168 < _v906(_v1015))) {
                _v341 _v2243 = _v912(_v1015, _v1168);
                _v426 _v2375 = _v539(_v2243);
                _v1239 = _v2226(_v1239, _v2189, _v2375, bkr_str_concat("call argument ", int_to_string((_v1168 + 1))), _v2001);
                _v1239 = _v2373(_v1239, _v1530, _v425, _v2189, _v2375, _v2001, _v2371);
                _v1168 = (_v1168 + 1);
            }
        } else {
            if ((_v319 == _v257)) {
                bkr_i64 _v1503 = _v724(_v541);
                bkr_str _v1681 = _v1945(_v425, _v1503);
                _v435 _v1007 = _v727(_v541);
                _v434 _v1008 = _v730(_v541);
                _v1239 = _v2261(_v1239, _v425, _v541, _v2001);
                _v1239 = _v2263(_v1239, _v1530, _v425, _v541, _v2001);
                bkr_i64 _v1168 = 0;
                while ((_v1168 < _v906(_v1008))) {
                    bkr_i64 _v1658 = _v917(_v1007, _v1168);
                    bkr_str _v1044 = _v1945(_v425, _v1658);
                    _v341 _v1422 = _v912(_v1008, _v1168);
                    _v426 _v2376 = _v539(_v1422);
                    _v1239 = _v2373(_v1239, _v1530, _v425, _v2189, _v2376, _v2001, _v2371);
                    _v1239 = _v2226(_v1239, _v2189, _v2376, bkr_str_concat(bkr_str_concat(_v1681, "."), _v1044), _v2001);
                    bkr_i64 _v2177 = _v2260(_v1530, _v1503, _v1658);
                    bkr_i64 _v2178 = _v2190(_v2189, _v2376);
                    bkr_str _v2115 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Change field ", _v1044), " for struct "), _v1681), " to match the declared field type.");
                    _v1239 = _v2251(_v1239, "struct_field_type_mismatch", bkr_str_concat(bkr_str_concat(_v1681, "."), _v1044), _v2001, _v1422, _v2177, _v2178, _v2115);
                    _v1168 = (_v1168 + 1);
                }
                bkr_i64 _v403 = _v1005(_v541);
                if ((_v403 != 0)) {
                    _v1239 = _v2373(_v1239, _v1530, _v425, _v2189, _v537(_v403), _v2001, _v2371);
                }
            } else {
                if ((_v319 == _v256)) {
                    _v1239 = _v2272(_v1239, _v2189, _v541, _v2001);
                    _v1239 = _v2226(_v1239, _v2189, _v537(_v719(_v541)), "field access base", _v2001);
                    _v1239 = _v2372(_v1239, _v1530, _v425, _v2189, _v719(_v541), _v2001, _v2371);
                } else {
                    if ((_v319 == _v242)) {
                        if (_v2269(_v2189, _v541)) {
                            _v426 _v1050 = _v537(_v674(_v541));
                            if ((_v544(_v1050) == _v242)) {
                                bkr_i64 _v1769 = _v671(_v1050);
                                if ((_v1769 == _v178)) {
                                    bkr_i64 _v2377 = _v674(_v1050);
                                    return _v2372(_v1239, _v1530, _v425, _v2189, _v2377, _v2001, _v2371);
                                }
                                if ((_v1769 == _v176)) {
                                    _v426 _v1772 = _v537(_v674(_v1050));
                                    _v426 _v1773 = _v537(_v677(_v1050));
                                    if (((_v544(_v1772) == _v242) && (_v544(_v1773) == _v242))) {
                                        _v1239 = _v2372(_v1239, _v1530, _v425, _v2189, _v674(_v1772), _v2001, _v2371);
                                        return _v2372(_v1239, _v1530, _v425, _v2189, _v674(_v1773), _v2001, _v2371);
                                    }
                                }
                            }
                            return _v1239;
                        }
                        _v1239 = _v2267(_v1239, _v2189, _v541, _v2001);
                        _v1239 = _v2226(_v1239, _v2189, _v537(_v674(_v541)), "binary left operand", _v2001);
                        _v1239 = _v2226(_v1239, _v2189, _v537(_v677(_v541)), "binary right operand", _v2001);
                        _v1239 = _v2372(_v1239, _v1530, _v425, _v2189, _v674(_v541), _v2001, _v2371);
                        _v1239 = _v2372(_v1239, _v1530, _v425, _v2189, _v677(_v541), _v2001, _v2371);
                    } else {
                        if ((_v319 == _v240)) {
                            _v1239 = _v2226(_v1239, _v2189, _v537(_v777(_v541)), "try operand", _v2001);
                            _v1239 = _v2372(_v1239, _v1530, _v425, _v2189, _v777(_v541), _v2001, _v2371);
                        } else {
                            if ((_v319 == _v241)) {
                                _v426 _v1678 = _v783(_v541);
                                _v346 _v1435 = _v784(_v541);
                                _v1239 = _v2226(_v1239, _v2189, _v1678, "cast operand", _v2001);
                                _v1239 = _v2373(_v1239, _v1530, _v425, _v2189, _v1678, _v2001, _v2371);
                                bkr_i64 _v2182 = _v2190(_v2189, _v1678);
                                bkr_i64 _v1787 = _v2050(_v1530, _v1435);
                                if ((!_v2181(_v2182, _v1787))) {
                                    bkr_str _v2115 = "Cast between compatible numeric types, bool, or between i64 and handle types.";
                                    _v1239 = _v2207(_v1239, "cast_type_mismatch", "cast expression", _v2001, _v546(_v541), _v1787, _v2182, _v2115);
                                }
                            } else {
                                if ((_v319 == _v243)) {
                                    _v1239 = _v2270(_v1239, _v2189, _v541, _v2001);
                                    _v1239 = _v2226(_v1239, _v2189, _v537(_v684(_v541)), "unary operand", _v2001);
                                    _v1239 = _v2372(_v1239, _v1530, _v425, _v2189, _v684(_v541), _v2001, _v2371);
                                } else {
                                    if ((_v319 == _v250)) {
                                        _v426 _v1403 = _v537(_v736(_v541));
                                        _v426 _v1404 = _v537(_v739(_v541));
                                        bkr_i64 _v1677 = _v2190(_v2189, _v1403);
                                        bkr_i64 _v2378 = _v2190(_v2189, _v1404);
                                        _v1239 = _v2251(_v1239, "ternary_branch_type_mismatch", "ternary else branch", _v2001, _v546(_v1404), _v1677, _v2378, "Make both ternary branches produce compatible value types.");
                                        _v1239 = _v2365(_v1239, _v425, _v2189, _v537(_v733(_v541)), _v2001, "condition_type_mismatch", "ternary condition", _v305, "Make this ternary condition produce bool.");
                                        _v1239 = _v2226(_v1239, _v2189, _v537(_v733(_v541)), "ternary condition", _v2001);
                                        _v1239 = _v2226(_v1239, _v2189, _v1403, "ternary then branch", _v2001);
                                        _v1239 = _v2226(_v1239, _v2189, _v1404, "ternary else branch", _v2001);
                                        _v1239 = _v2372(_v1239, _v1530, _v425, _v2189, _v733(_v541), _v2001, _v2371);
                                        _v1239 = _v2372(_v1239, _v1530, _v425, _v2189, _v736(_v541), _v2001, _v2371);
                                        _v1239 = _v2372(_v1239, _v1530, _v425, _v2189, _v739(_v541), _v2001, _v2371);
                                    } else {
                                        if ((_v319 == _v239)) {
                                            _v1239 = _v2372(_v1239, _v1530, _v425, _v2189, _v703(_v541), _v2001, _v2371);
                                        } else {
                                            if ((_v319 == _v252)) {
                                                _v434 _v994 = _v701(_v541);
                                                _v1239 = _v2347(_v1239, _v2189, _v994, _v2001);
                                                bkr_i64 _v1168 = 0;
                                                while ((_v1168 < _v906(_v994))) {
                                                    _v341 _v2016 = _v912(_v994, _v1168);
                                                    _v1239 = _v2373(_v1239, _v1530, _v425, _v2189, _v539(_v2016), _v2001, _v2371);
                                                    _v1168 = (_v1168 + 1);
                                                }
                                            } else {
                                                if ((_v319 == _v253)) {
                                                    _v1239 = _v2274(_v1239, _v2189, _v541, _v2001);
                                                    _v1239 = _v2226(_v1239, _v2189, _v537(_v711(_v541)), "index base", _v2001);
                                                    _v426 _v2379 = _v537(_v714(_v541));
                                                    bkr_i64 _v2380 = _v2190(_v2189, _v2379);
                                                    _v1239 = _v2244(_v1239, "index_type_mismatch", "index expression", _v2001, _v546(_v2379), _v303, _v2380, "Use an integer-compatible index expression.");
                                                    _v1239 = _v2226(_v1239, _v2189, _v2379, "index expression", _v2001);
                                                    _v1239 = _v2372(_v1239, _v1530, _v425, _v2189, _v711(_v541), _v2001, _v2371);
                                                    _v1239 = _v2372(_v1239, _v1530, _v425, _v2189, _v714(_v541), _v2001, _v2371);
                                                } else {
                                                    if ((_v319 == _v227)) {
                                                        _v1239 = _v2381(_v1239, _v1530, _v425, _v2189, _v580(_v546(_v541)), _v2001, _v2371);
                                                    } else {
                                                        if ((_v319 == _v258)) {
                                                            _v426 _v974 = _v537(_v742(_v541));
                                                            bkr_i64 _v1715 = _v2190(_v2189, _v974);
                                                            _v1239 = _v2373(_v1239, _v1530, _v425, _v2189, _v974, _v2001, _v2371);
                                                            _v435 _v976 = _v750(_v541);
                                                            _v1239 = _v2294(_v1239, _v976, _v745(_v541), _v2001);
                                                            _v1239 = _v2281(_v1239, _v745(_v541), _v1715, _v2001);
                                                            _v1239 = _v2313(_v1239, _v541, _v745(_v541), _v1715, _v2001);
                                                            _v1239 = _v2319(_v1239, _v541, _v745(_v541), _v2001);
                                                            _v1239 = _v2325(_v1239, _v541, _v745(_v541), _v2001);
                                                            _v1239 = _v2336(_v1239, _v1530, _v425, _v541, _v745(_v541), _v2001);
                                                            _v1239 = _v2339(_v1239, _v541, _v745(_v541), _v1715, _v2001);
                                                            _v1239 = _v2317(_v1239, _v976, _v745(_v541), _v1715, _v2001);
                                                            _v1239 = _v2322(_v1239, _v976, _v745(_v541), _v2001);
                                                            _v1239 = _v2328(_v1239, _v976, _v745(_v541), _v2001);
                                                            _v1239 = _v2341(_v1239, _v1530, _v976, _v745(_v541), _v2001);
                                                            bkr_i64 _v573 = 0;
                                                            while ((_v573 < _v915(_v976))) {
                                                                bkr_i64 _v2154 = _v917(_v976, _v573);
                                                                if ((_v2154 != 0)) {
                                                                    _v1239 = _v2373(_v1239, _v1530, _v425, _v2189, _v537(_v2154), _v2001, _v2371);
                                                                }
                                                                _v573 = (_v573 + 1);
                                                            }
                                                            _v434 _v975 = _v748(_v541);
                                                            _v1239 = _v2276(_v1239, _v2189, _v975, _v2001);
                                                            bkr_i64 _v1168 = 0;
                                                            while ((_v1168 < _v906(_v975))) {
                                                                _v341 _v1123 = _v912(_v975, _v1168);
                                                                if ((_v509(_v1123) == _v227)) {
                                                                    _v1239 = _v2381(_v1239, _v1530, _v425, _v2189, _v580(_v1123), _v2001, _v2371);
                                                                } else {
                                                                    _v426 _v2382 = _v539(_v1123);
                                                                    _v1239 = _v2226(_v1239, _v2189, _v2382, "match arm value", _v2001);
                                                                    _v1239 = _v2373(_v1239, _v1530, _v425, _v2189, _v2382, _v2001, _v2371);
                                                                }
                                                                _v1168 = (_v1168 + 1);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return _v1239;
}

bkr_i64 _v2383(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425, _v1531 _v2189, bkr_i64 _v370, bkr_str _v2001, bkr_i64 _v2371) {
    return _v2384(_v1239, _v476(_v0), _v425, _v2189, _v550(_v370), _v2001, _v2371);
}

bkr_i64 _v2384(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v1531 _v2189, _v427 _v553, bkr_str _v2001, bkr_i64 _v2371) {
    _v341 _v2076 = _v586(_v553);
    bkr_i64 _v319 = _v555(_v553);
    if ((_v319 == _v228)) {
        bkr_i64 _v366 = _v763(_v553);
        bkr_str _v1348 = _v1945(_v425, _v757(_v553));
        _v1239 = _v2372(_v1239, _v1530, _v425, _v2189, _v366, _v2001, _v2371);
        bkr_i64 _v515 = _v760(_v553);
        if ((_v525(_v515) && _v525(_v366))) {
            bkr_i64 _v2177 = _v2050(_v1530, _v516(_v515));
            bkr_i64 _v2178 = _v2190(_v2189, _v537(_v366));
            bkr_str _v2115 = bkr_str_concat(bkr_str_concat("Change the initializer for ", _v1348), " or update the declared local type.");
            _v1239 = _v2251(_v1239, "annotation_type_mismatch", _v1348, _v2001, _v2076, _v2177, _v2178, _v2115);
        } else {
            if ((_v523(_v515) && _v2230(_v366))) {
                _v1239 = _v2216(_v1239, _v1348, _v2001, _v537(_v366));
            } else {
                if ((_v523(_v515) && _v2232(_v425, _v366))) {
                    _v1239 = _v2217(_v1239, _v1348, _v2001, _v537(_v366));
                } else {
                    if ((_v523(_v515) && _v2234(_v425, _v366))) {
                        _v1239 = _v2218(_v1239, _v1348, _v2001, _v537(_v366));
                    } else {
                        if ((_v523(_v515) && _v2236(_v425, _v366))) {
                            _v1239 = _v2219(_v1239, _v1348, _v2001, _v537(_v366));
                        } else {
                            if ((_v523(_v515) && _v2237(_v2189, _v366))) {
                                _v1239 = _v2220(_v1239, _v1348, _v2001, _v537(_v366));
                            }
                        }
                    }
                }
            }
        }
        _v2079(_v2189, _v553);
    } else {
        if ((_v319 == _v229)) {
            bkr_i64 _v2385 = _v768(_v553);
            _v1239 = _v2372(_v1239, _v1530, _v425, _v2189, _v2385, _v2001, _v2371);
            if (_v523(_v2385)) {
                if (((_v2371 != _v307) && (_v2371 != _v316))) {
                    _v1239 = _v2207(_v1239, "return_type_mismatch", "return", _v2001, _v2076, _v2371, _v307, "Return a value matching the function return type or change the function signature.");
                }
            } else {
                _v1239 = _v2226(_v1239, _v2189, _v537(_v2385), "return value", _v2001);
                bkr_i64 _v2178 = _v2190(_v2189, _v537(_v2385));
                _v1239 = _v2251(_v1239, "return_type_mismatch", "return", _v2001, _v2076, _v2371, _v2178, "Return a value matching the function return type or change the function signature.");
            }
        } else {
            if ((_v319 == _v230)) {
                bkr_i64 _v375 = _v827(_v553);
                _v1239 = _v2365(_v1239, _v425, _v2189, _v537(_v375), _v2001, "condition_type_mismatch", "if condition", _v305, "Make this if condition produce bool.");
                _v1239 = _v2226(_v1239, _v2189, _v537(_v375), "if condition", _v2001);
                _v1239 = _v2372(_v1239, _v1530, _v425, _v2189, _v375, _v2001, _v2371);
                _v1239 = _v2381(_v1239, _v1530, _v425, _v2189, _v829(_v553), _v2001, _v2371);
                bkr_i64 _v377 = _v832(_v553);
                if (_v525(_v377)) {
                    _v1239 = _v2381(_v1239, _v1530, _v425, _v2189, _v578(_v377), _v2001, _v2371);
                }
            } else {
                if ((_v319 == _v231)) {
                    bkr_i64 _v375 = _v849(_v553);
                    _v1239 = _v2365(_v1239, _v425, _v2189, _v537(_v375), _v2001, "condition_type_mismatch", "while condition", _v305, "Make this while condition produce bool.");
                    _v1239 = _v2226(_v1239, _v2189, _v537(_v375), "while condition", _v2001);
                    _v1239 = _v2372(_v1239, _v1530, _v425, _v2189, _v375, _v2001, _v2371);
                    _v1239 = _v2381(_v1239, _v1530, _v425, _v2189, _v851(_v553), _v2001, _v2371);
                } else {
                    if ((_v319 == _v236)) {
                        bkr_i64 _v339 = _v837(_v553);
                        bkr_i64 _v382 = _v840(_v553);
                        _v1239 = _v2365(_v1239, _v425, _v2189, _v537(_v339), _v2001, "for_range_type_mismatch", "for range start", _v303, "Make the for range start numeric.");
                        _v1239 = _v2365(_v1239, _v425, _v2189, _v537(_v382), _v2001, "for_range_type_mismatch", "for range end", _v303, "Make the for range end numeric.");
                        _v1239 = _v2226(_v1239, _v2189, _v537(_v339), "for range start", _v2001);
                        _v1239 = _v2226(_v1239, _v2189, _v537(_v382), "for range end", _v2001);
                        _v1592(_v2189, _v834(_v553), _v303);
                        _v1239 = _v2381(_v1239, _v1530, _v425, _v2189, _v844(_v553), _v2001, _v2371);
                    } else {
                        if ((_v319 == _v237)) {
                            _v1239 = _v2381(_v1239, _v1530, _v425, _v2189, _v846(_v553), _v2001, _v2371);
                        } else {
                            if ((_v319 == _v233)) {
                                bkr_i64 _v386 = _v854(_v553);
                                bkr_i64 _v387 = _v857(_v553);
                                _v426 _v1094 = _v537(_v386);
                                if ((!_v2228(_v1094))) {
                                    _v1239 = _v2211(_v1239, _v2001, _v1094);
                                }
                                if (((_v544(_v1094) == _v245) && _v566(_v2257(_v1530, _v662(_v1094))))) {
                                    _v1239 = _v2214(_v1239, _v425, _v2001, _v1094);
                                }
                                _v1239 = _v2372(_v1239, _v1530, _v425, _v2189, _v386, _v2001, _v2371);
                                _v1239 = _v2372(_v1239, _v1530, _v425, _v2189, _v387, _v2001, _v2371);
                                _v1239 = _v2226(_v1239, _v2189, _v537(_v387), "assignment value", _v2001);
                                bkr_i64 _v2177 = _v2190(_v2189, _v1094);
                                bkr_i64 _v2178 = _v2190(_v2189, _v537(_v387));
                                _v1239 = _v2251(_v1239, "assignment_type_mismatch", "assignment", _v2001, _v2076, _v2177, _v2178, "Assign a value that matches the target type.");
                            } else {
                                if ((_v319 == _v238)) {
                                    _v1239 = _v2384(_v1239, _v1530, _v425, _v2189, _v549(_v772(_v553)), _v2001, _v2371);
                                } else {
                                    if ((_v319 == _v232)) {
                                        _v1239 = _v2372(_v1239, _v1530, _v425, _v2189, _v860(_v553), _v2001, _v2371);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return _v1239;
}

bkr_i64 _v2386(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425, _v1531 _v2189, bkr_i64 _v577, bkr_str _v2001, bkr_i64 _v2371) {
    return _v2381(_v1239, _v476(_v0), _v425, _v2189, _v579(_v577), _v2001, _v2371);
}

bkr_i64 _v2381(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v1531 _v2189, _v429 _v582, bkr_str _v2001, bkr_i64 _v2371) {
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v589(_v582))) {
        _v1239 = _v2384(_v1239, _v1530, _v425, _v2189, _v1107(_v582, _v1168), _v2001, _v2371);
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_i64 _v2387(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425, _v1531 _v2189, bkr_i64 _v557, bkr_str _v2021) {
    return _v2388(_v1239, _v476(_v0), _v425, _v2189, _v559(_v557), _v2021);
}

bkr_i64 _v2388(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v1531 _v2189, _v428 _v562, bkr_str _v2021) {
    _v341 _v1967 = _v587(_v562);
    bkr_str _v2215 = _v1945(_v425, _v878(_v562));
    bkr_i64 _v387 = _v884(_v562);
    _v1239 = _v2372(_v1239, _v1530, _v425, _v2189, _v387, _v2021, _v316);
    bkr_i64 _v515 = _v881(_v562);
    if ((_v525(_v515) && _v525(_v387))) {
        bkr_i64 _v2177 = _v2050(_v1530, _v516(_v515));
        bkr_i64 _v2178 = _v2190(_v2189, _v537(_v387));
        bkr_str _v2115 = bkr_str_concat(bkr_str_concat("Change the initializer for ", _v2215), " or update the declared constant type.");
        _v1239 = _v2251(_v1239, "annotation_type_mismatch", _v2215, _v2021, _v1967, _v2177, _v2178, _v2115);
    } else {
        if ((_v523(_v515) && _v2230(_v387))) {
            _v1239 = _v2216(_v1239, _v2215, _v2021, _v537(_v387));
        } else {
            if ((_v523(_v515) && _v2232(_v425, _v387))) {
                _v1239 = _v2217(_v1239, _v2215, _v2021, _v537(_v387));
            } else {
                if ((_v523(_v515) && _v2234(_v425, _v387))) {
                    _v1239 = _v2218(_v1239, _v2215, _v2021, _v537(_v387));
                } else {
                    if ((_v523(_v515) && _v2236(_v425, _v387))) {
                        _v1239 = _v2219(_v1239, _v2215, _v2021, _v537(_v387));
                    } else {
                        if ((_v523(_v515) && _v2237(_v2189, _v387))) {
                            _v1239 = _v2220(_v1239, _v2215, _v2021, _v537(_v387));
                        }
                    }
                }
            }
        }
    }
    return _v1239;
}

bkr_i64 _v2389(bkr_i64 _v1239, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v557) {
    return _v2390(_v1239, _v476(_v0), _v425, _v559(_v557));
}

bkr_i64 _v2390(bkr_i64 _v1239, _v341 _v1530, bkr_i64 _v425, _v428 _v562) {
    bkr_str _v2023 = _v1945(_v425, _v868(_v562));
    bkr_str _v2001 = bkr_str_concat("function:", _v2023);
    _v1531 _v2189 = _v2087(_v1530, _v562);
    bkr_i64 _v2371 = _v2196(_v1530, _v562);
    _v1239 = _v2353(_v1239, _v876(_v562), _v2001, 0);
    _v1239 = _v2360(_v1239, _v876(_v562), _v2001);
    if (((((_v2371 != _v307) && (_v2371 != _v314)) && (_v2371 != _v316)) && (!_v2356(_v876(_v562))))) {
        _v1239 = _v2225(_v1239, _v425, _v2001, _v562);
    }
    return _v2381(_v1239, _v1530, _v425, _v2189, _v876(_v562), _v2001, _v2371);
}

bkr_i64 _v2391(bkr_i64 _v1239, bkr_i64 _v0) {
    return _v2392(_v1239, _v476(_v0));
}

bkr_i64 _v2392(bkr_i64 _v1239, _v341 _v1530) {
    bkr_i64 _v425 = _v903(_v1530);
    bkr_str _v2021 = bkr_str_concat("kernel:", _v1945(_v425, _v663(_v1530)));
    _v1531 _v2189 = _v2054(_v1530);
    _v434 _v1183 = _v898(_v1530);
    _v1239 = _v2253(_v1239, _v1530, _v425, _v2021);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        bkr_i64 _v319 = _v568(_v562);
        if ((_v319 == _v249)) {
            _v1239 = _v2388(_v1239, _v1530, _v425, _v2189, _v562, _v2021);
        } else {
            if ((_v319 == _v224)) {
                _v1239 = _v2390(_v1239, _v1530, _v425, _v562);
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_str _v2393(bkr_i64 _v0) {
    bkr_str _v1941 = ",";
    bkr_i64 _v1239 = _v1946();
    _v341 _v1530 = _v476(_v0);
    bkr_bool _v1993 = _v1933(_v1530);
    if (_v1993) {
        _v2392(_v1239, _v1530);
    }
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("schema_version", "bunker.self_host.typecheck.v1")), _v1941), _v1892("representation", "typecheck_pass")), _v1941), _v1894("complete", BKR_TRUE)), _v1941), _v1894("truncated", (!_v1993))), _v1941), _v1894("annotation_checks", BKR_TRUE)), _v1941), _v1894("return_checks", BKR_TRUE)), _v1941), _v1894("condition_checks", BKR_TRUE)), _v1941), _v1894("call_argument_checks", BKR_TRUE)), _v1941), _v1894("call_arity_checks", BKR_TRUE)), _v1941), _v1894("call_target_checks", BKR_TRUE)), _v1941), _v1894("builtin_arity_checks", BKR_TRUE)), _v1941), _v1894("builtin_argument_type_checks", BKR_TRUE)), _v1941), _v1894("entry_point_checks", BKR_TRUE)), _v1941), _v1894("entry_signature_checks", BKR_TRUE)), _v1941), _v1894("assignment_target_checks", BKR_TRUE)), _v1941), _v1894("const_assignment_checks", BKR_TRUE)), _v1941), _v1894("struct_field_value_checks", BKR_TRUE)), _v1941), _v1894("struct_field_shape_checks", BKR_TRUE)), _v1941), _v1894("ambiguous_empty_array_checks", BKR_TRUE)), _v1941), _v1894("ambiguous_none_checks", BKR_TRUE)), _v1941), _v1894("ambiguous_result_constructor_checks", BKR_TRUE)), _v1941), _v1894("ambiguous_collection_constructor_checks", BKR_TRUE)), _v1941), _v1894("index_base_type_checks", BKR_TRUE)), _v1941), _v1894("index_type_checks", BKR_TRUE)), _v1941), _v1894("binary_operand_checks", BKR_TRUE)), _v1941), _v1894("unary_operand_checks", BKR_TRUE)), _v1941), _v1894("field_access_base_checks", BKR_TRUE)), _v1941), _v1894("ternary_branch_checks", BKR_TRUE)), _v1941), _v1894("match_arm_type_checks", BKR_TRUE)), _v1941), _v1894("match_pattern_type_checks", BKR_TRUE)), _v1941), _v1894("match_pattern_semantic_checks", BKR_TRUE)), _v1941), _v1894("bool_match_exhaustiveness_checks", BKR_TRUE)), _v1941), _v1894("option_match_exhaustiveness_checks", BKR_TRUE)), _v1941), _v1894("result_match_exhaustiveness_checks", BKR_TRUE)), _v1941), _v1894("enum_match_exhaustiveness_checks", BKR_TRUE)), _v1941), _v1894("scalar_match_exhaustiveness_checks", BKR_TRUE)), _v1941), _v1894("finite_match_redundancy_checks", BKR_TRUE)), _v1941), _v1894("array_element_type_checks", BKR_TRUE)), _v1941), _v1894("loop_control_checks", BKR_TRUE)), _v1941), _v1894("return_path_checks", BKR_TRUE)), _v1941), _v1894("unreachable_code_checks", BKR_TRUE)), _v1941), _v1894("semantic_validation_passes", BKR_TRUE)), _v1941), _v1894("void_value_checks", BKR_TRUE)), _v1941), _v1894("compound_void_value_checks", BKR_TRUE)), _v1941), _v1894("full_value_context_void_checks", BKR_TRUE)), _v1941), _v1894("typed_diagnostic_context", BKR_TRUE)), _v1941), _v1894("structured_repair_metadata", BKR_TRUE)), _v1941), _v1894("diagnostic_phase_field", BKR_TRUE)), _v1941), _v1894("diagnostic_rule_ids", BKR_TRUE)), _v1941), _v1894("diagnostic_severity", BKR_TRUE)), _v1941), _v1894("diagnostic_severity_counts", BKR_TRUE)), _v1941), _v1894("suggested_edit_envelope", BKR_TRUE)), _v1941), _v1894("has_diagnostics", (_v1949(_v1239) > 0))), _v1941), _v1893("diagnostic_count", _v1949(_v1239))), _v1941), _v1893("error_count", _v1949(_v1239))), _v1941), _v1893("warning_count", 0)), _v1941), _v1892("known_limits", "Typecheck pass enforces declared annotations, return values and return paths, void value use, conditions, ternary branches, match patterns and arm values, array elements, loop-control context, unreachable statements, assignments, index bases, field-access bases, operands, calls, and struct literal shapes; full language subset semantic checking active.")), _v1941), _v1895("diagnostics", _v1947(_v1239))), "}");
}

bkr_str _v2394(bkr_i64 _v0) {
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("/* BUNKER_TYPECHECK_JSON: ", _v2393(_v0)), from_char_code(10)), "*/"), from_char_code(10));
}

bkr_i64 _v2395(bkr_i64 _v1239, _v341 _v1530) {
    bkr_i64 _v425 = _v903(_v1530);
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v906(_v1183))) {
        _v428 _v562 = _v913(_v1183, _v1168);
        bkr_i64 _v319 = _v568(_v562);
        if ((_v319 == _v224)) {
            bkr_str _v2023 = _v1945(_v425, _v868(_v562));
            bkr_str _v2001 = bkr_str_concat("function:", _v2023);
            bkr_i64 _v2371 = _v2196(_v1530, _v562);
            _v1239 = _v2353(_v1239, _v876(_v562), _v2001, 0);
            _v1239 = _v2360(_v1239, _v876(_v562), _v2001);
            if (((((_v2371 != _v307) && (_v2371 != _v314)) && (_v2371 != _v316)) && (!_v2356(_v876(_v562))))) {
                _v1239 = _v2225(_v1239, _v425, _v2001, _v562);
            }
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1239;
}

bkr_str _v2396(bkr_i64 _v0) {
    bkr_str _v1941 = ",";
    bkr_i64 _v1239 = _v1946();
    _v341 _v1530 = _v476(_v0);
    _v1239 = _v2395(_v1239, _v1530);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("schema_version", "bunker.self_host.semantic.v1")), _v1941), _v1892("representation", "semantic_validation_pass")), _v1941), _v1894("complete", BKR_TRUE)), _v1941), _v1894("loop_control_validation", BKR_TRUE)), _v1941), _v1894("unreachable_code_detection", BKR_TRUE)), _v1941), _v1894("return_path_validation", BKR_TRUE)), _v1941), _v1894("assignment_target_validation", BKR_TRUE)), _v1941), _v1894("const_assignment_validation", BKR_TRUE)), _v1941), _v1894("has_diagnostics", (_v1949(_v1239) > 0))), _v1941), _v1893("diagnostic_count", _v1949(_v1239))), _v1941), _v1893("error_count", _v1949(_v1239))), _v1941), _v1893("warning_count", 0)), _v1941), _v1895("diagnostics", _v1947(_v1239))), "}");
}

bkr_str _v2397(bkr_i64 _v0) {
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("/* BUNKER_SEMANTIC_JSON: ", _v2396(_v0)), from_char_code(10)), "*/"), from_char_code(10));
}

_v2400 _v2412(bkr_i64 _v2408) {
    bkr_i64 _v2401 = vec_new();
    bkr_i64 _v2402 = vec_new();
    bkr_i64 _v2403 = vec_new();
    bkr_i64 _v2404 = vec_new();
    bkr_i64 _v2405 = vec_new();
    bkr_i64 _v2409 = hashmap_new_str();
    bkr_i64 _v2411 = hashmap_new_str();
    return (_v2400){._v2401 = _v2401, ._v2402 = _v2402, ._v2403 = _v2403, ._v2404 = _v2404, ._v2405 = _v2405, ._v2406 = 0, ._v2407 = 0, ._v2408 = _v2408, ._v2361 = BKR_FALSE, ._v2409 = _v2409, ._v2411 = _v2411};
}

bkr_bool _v2414(_v2400 _v2415, bkr_str _v1348) {
    bkr_i64 _v1168 = 0;
    while ((_v1168 < vec_len(_v2415._v2401))) {
        if (bkr_str_eq(vec_get(_v2415._v2401, _v1168), _v1348)) {
            return BKR_FALSE;
        }
        _v1168 = (_v1168 + 1);
    }
    vec_push(_v2415._v2401, ((bkr_i64)(intptr_t)_v1348));
    return BKR_TRUE;
}

bkr_str _v2416(bkr_str _v2417, bkr_str _v1826) {
    return bkr_str_concat(bkr_str_concat(_v2417, "."), _v1826);
}

bkr_bool _v2418(_v2400 _v2415, bkr_str _v2417, bkr_str _v1826, bkr_i64 _v1383) {
    bkr_str _v2419 = _v2416(_v2417, _v1826);
    return hashmap_insert_str(_v2415._v2409, ((bkr_i64)(intptr_t)_v2419), _v1383);
}

bkr_i64 _v2421(_v2400 _v2415, bkr_str _v2417, bkr_str _v1826) {
    bkr_str _v2419 = _v2416(_v2417, _v1826);
    if ((!hashmap_contains(_v2415._v2409, ((bkr_i64)(intptr_t)_v2419)))) {
        return 0;
    }
    return hashmap_get(_v2415._v2409, ((bkr_i64)(intptr_t)_v2419));
}

bkr_bool _v2424(_v2400 _v2415, bkr_str _v2417, bkr_str _v1826, bkr_str _v1383) {
    bkr_str _v2419 = _v2416(_v2417, _v1826);
    return hashmap_insert_str(_v2415._v2411, ((bkr_i64)(intptr_t)_v2419), ((bkr_i64)(intptr_t)_v1383));
}

bkr_str _v2425(_v2400 _v2415, bkr_str _v2417, bkr_str _v1826) {
    bkr_str _v2419 = _v2416(_v2417, _v1826);
    if ((!hashmap_contains(_v2415._v2411, ((bkr_i64)(intptr_t)_v2419)))) {
        return "";
    }
    return hashmap_get(_v2415._v2411, ((bkr_i64)(intptr_t)_v2419));
}

bkr_bool _v2426(_v2400 _v2415, bkr_str _v386, bkr_str _v1209, bkr_str _v2399, bkr_i64 _v344) {
    vec_push(_v2415._v2402, ((bkr_i64)(intptr_t)_v386));
    vec_push(_v2415._v2403, ((bkr_i64)(intptr_t)_v1209));
    vec_push(_v2415._v2404, ((bkr_i64)(intptr_t)_v2399));
    vec_push(_v2415._v2405, _v344);
    return BKR_TRUE;
}

bkr_i64 _v2427(_v2400 _v2415) {
    bkr_i64 _v2428 = vec_len(_v2415._v2404);
    if ((_v2415._v2406 >= _v2428)) {
        return 0;
    }
    return (_v2428 - _v2415._v2406);
}

bkr_bool _v2429(_v2400 _v2415) {
    return (_v2427(_v2415) > 0);
}

_v2398 _v2430(_v2400 _v2415) {
    if ((!_v2429(_v2415))) {
        return (_v2398){._v386 = "", ._v1209 = "", ._v2399 = "", ._v344 = 0};
    }
    bkr_i64 _v386 = vec_get(_v2415._v2402, _v2415._v2406);
    bkr_i64 _v1209 = vec_get(_v2415._v2403, _v2415._v2406);
    bkr_i64 _v2399 = vec_get(_v2415._v2404, _v2415._v2406);
    bkr_i64 _v344 = vec_get(_v2415._v2405, _v2415._v2406);
    _v2415._v2406 = (_v2415._v2406 + 1);
    return (_v2398){._v386 = _v386, ._v1209 = _v1209, ._v2399 = _v2399, ._v344 = _v344};
}

bkr_bool _v2431(_v2400 _v2415) {
    _v2415._v2361 = BKR_TRUE;
    return BKR_TRUE;
}

bkr_bool _v2432(_v2400 _v2415) {
    return _v2415._v2361;
}

bkr_i64 _v2433(_v2400 _v2415) {
    _v2415._v2407 = (_v2415._v2407 + 1);
    return _v2415._v2407;
}

bkr_str _v2434(_v2400 _v2415) {
    bkr_str _v1941 = ",";
    bkr_str _v2435 = "RUNNING";
    if (_v2415._v2361) {
        _v2435 = "COMPLETED";
    }
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("schema_version", "bunker.shell.v1")), _v1941), _v1892("status", _v2435)), _v1941), _v1893("steps_executed", _v2415._v2407)), _v1941), _v1893("max_steps", _v2415._v2408)), _v1941), _v1894("terminated", _v2415._v2361)), _v1941), _v1893("active_agents", vec_len(_v2415._v2401))), _v1941), _v1893("queue_depth", _v2427(_v2415))), "}");
}

_v2436 _v2451(bkr_str _v1348) {
    bkr_i64 _v2452 = vec_new();
    bkr_i64 _v2453 = vec_new();
    bkr_i64 _v2454 = vec_new();
    bkr_i64 _v2455 = vec_new();
    bkr_i64 _v2456 = vec_new();
    bkr_i64 _v2457 = vec_new();
    bkr_i64 _v2458 = vec_new();
    bkr_i64 _v2459 = vec_new();
    bkr_i64 _v2460 = vec_new();
    bkr_i64 _v2461 = vec_new();
    bkr_i64 _v2462 = vec_new();
    bkr_i64 _v2463 = vec_new();
    bkr_i64 _v2464 = vec_new();
    return (_v2436){._v2437 = _v2452, ._v2438 = _v2453, ._v2439 = _v2454, ._v2440 = _v2455, ._v2441 = _v2456, ._v2442 = _v2457, ._v2443 = _v2458, ._v2444 = _v2459, ._v2445 = _v2460, ._v2446 = _v2461, ._v2447 = _v2462, ._v2448 = _v2463, ._v2449 = _v2464, ._v2450 = (-1), ._v1348 = _v1348};
}

bkr_i64 _v2465(_v2436 _v2466, bkr_str _v319) {
    bkr_i64 _v1605 = vec_len(_v2466._v2437);
    vec_push(_v2466._v2437, ((bkr_i64)(intptr_t)_v319));
    vec_push(_v2466._v2438, ((bkr_i64)(intptr_t)""));
    vec_push(_v2466._v2439, ((bkr_i64)(intptr_t)""));
    vec_push(_v2466._v2440, 0);
    vec_push(_v2466._v2441, 0);
    vec_push(_v2466._v2442, 0);
    vec_push(_v2466._v2443, 0);
    vec_push(_v2466._v2444, 14);
    vec_push(_v2466._v2445, ((bkr_i64)(intptr_t)""));
    vec_push(_v2466._v2446, ((bkr_i64)(intptr_t)""));
    vec_push(_v2466._v2447, ((bkr_i64)(intptr_t)""));
    vec_push(_v2466._v2448, ((bkr_i64)(intptr_t)""));
    vec_push(_v2466._v2449, (-1));
    if ((_v2466._v2450 < 0)) {
        _v2466._v2450 = _v1605;
    }
    return _v1605;
}

bkr_bool _v2467(_v2436 _v2466, bkr_i64 _v2468, bkr_i64 _v2469) {
    bkr_i64 _v2428 = vec_len(_v2466._v2437);
    if (((_v2468 < 0) || (_v2468 >= _v2428))) {
        return BKR_FALSE;
    }
    if (((_v2469 < 0) || (_v2469 >= _v2428))) {
        return BKR_FALSE;
    }
    vec_set(_v2466._v2449, _v2469, _v2468);
    return BKR_TRUE;
}

bkr_bool _v2470(_v2436 _v2466, bkr_i64 _v1605, bkr_str _v2471) {
    bkr_i64 _v2428 = vec_len(_v2466._v2437);
    if (((_v1605 < 0) || (_v1605 >= _v2428))) {
        return BKR_FALSE;
    }
    vec_set(_v2466._v2438, _v1605, ((bkr_i64)(intptr_t)_v2471));
    return BKR_TRUE;
}

bkr_bool _v2472(_v2436 _v2466, bkr_i64 _v1605, bkr_i64 _v2473, bkr_i64 _v2474) {
    bkr_i64 _v2428 = vec_len(_v2466._v2437);
    if (((_v1605 < 0) || (_v1605 >= _v2428))) {
        return BKR_FALSE;
    }
    vec_set(_v2466._v2440, _v1605, _v2473);
    vec_set(_v2466._v2441, _v1605, _v2474);
    return BKR_TRUE;
}

bkr_bool _v2475(_v2436 _v2466, bkr_i64 _v1605, bkr_str _v1290) {
    bkr_i64 _v2428 = vec_len(_v2466._v2437);
    if (((_v1605 < 0) || (_v1605 >= _v2428))) {
        return BKR_FALSE;
    }
    vec_set(_v2466._v2439, _v1605, ((bkr_i64)(intptr_t)_v1290));
    return BKR_TRUE;
}

bkr_bool _v2476(_v2436 _v2466, bkr_i64 _v1605, bkr_i64 _v2477) {
    bkr_i64 _v2428 = vec_len(_v2466._v2437);
    if (((_v1605 < 0) || (_v1605 >= _v2428))) {
        return BKR_FALSE;
    }
    vec_set(_v2466._v2442, _v1605, _v2477);
    return BKR_TRUE;
}

bkr_bool _v2478(_v2436 _v2466, bkr_i64 _v1605, bkr_i64 _v2479) {
    bkr_i64 _v2428 = vec_len(_v2466._v2437);
    if (((_v1605 < 0) || (_v1605 >= _v2428))) {
        return BKR_FALSE;
    }
    vec_set(_v2466._v2443, _v1605, _v2479);
    return BKR_TRUE;
}

bkr_bool _v2480(_v2436 _v2466, bkr_i64 _v1605, bkr_i64 _v2481) {
    bkr_i64 _v2428 = vec_len(_v2466._v2437);
    if (((_v1605 < 0) || (_v1605 >= _v2428))) {
        return BKR_FALSE;
    }
    vec_set(_v2466._v2444, _v1605, _v2481);
    return BKR_TRUE;
}

bkr_bool _v2482(_v2436 _v2466, bkr_i64 _v1605, bkr_str _v2417, bkr_str _v1826) {
    bkr_i64 _v2428 = vec_len(_v2466._v2437);
    if (((_v1605 < 0) || (_v1605 >= _v2428))) {
        return BKR_FALSE;
    }
    vec_set(_v2466._v2445, _v1605, ((bkr_i64)(intptr_t)_v2417));
    vec_set(_v2466._v2446, _v1605, ((bkr_i64)(intptr_t)_v1826));
    return BKR_TRUE;
}

bkr_bool _v2483(_v2436 _v2466, bkr_i64 _v1605, bkr_str _v386, bkr_str _v2399) {
    bkr_i64 _v2428 = vec_len(_v2466._v2437);
    if (((_v1605 < 0) || (_v1605 >= _v2428))) {
        return BKR_FALSE;
    }
    vec_set(_v2466._v2447, _v1605, ((bkr_i64)(intptr_t)_v386));
    vec_set(_v2466._v2448, _v1605, ((bkr_i64)(intptr_t)_v2399));
    return BKR_TRUE;
}

bkr_str _v2484(_v2436 _v2466, bkr_i64 _v1605) {
    if (((_v1605 < 0) || (_v1605 >= vec_len(_v2466._v2437)))) {
        return "";
    }
    return vec_get(_v2466._v2437, _v1605);
}

bkr_str _v2485(_v2436 _v2466, bkr_i64 _v1605) {
    if (((_v1605 < 0) || (_v1605 >= vec_len(_v2466._v2438)))) {
        return "";
    }
    return vec_get(_v2466._v2438, _v1605);
}

bkr_i64 _v2486(_v2436 _v2466, bkr_i64 _v1605) {
    if (((_v1605 < 0) || (_v1605 >= vec_len(_v2466._v2440)))) {
        return 0;
    }
    return vec_get(_v2466._v2440, _v1605);
}

bkr_i64 _v2487(_v2436 _v2466, bkr_i64 _v1605) {
    if (((_v1605 < 0) || (_v1605 >= vec_len(_v2466._v2441)))) {
        return 0;
    }
    return vec_get(_v2466._v2441, _v1605);
}

bkr_i64 _v2488(_v2436 _v2466, bkr_i64 _v1605) {
    if (((_v1605 < 0) || (_v1605 >= vec_len(_v2466._v2442)))) {
        return 0;
    }
    return vec_get(_v2466._v2442, _v1605);
}

bkr_str _v2489(_v2436 _v2466, bkr_i64 _v1605) {
    if (((_v1605 < 0) || (_v1605 >= vec_len(_v2466._v2439)))) {
        return "";
    }
    return vec_get(_v2466._v2439, _v1605);
}

bkr_str _v2490(_v2436 _v2466, bkr_i64 _v1605) {
    if (((_v1605 < 0) || (_v1605 >= vec_len(_v2466._v2447)))) {
        return "";
    }
    return vec_get(_v2466._v2447, _v1605);
}

bkr_str _v2491(_v2436 _v2466, bkr_i64 _v1605) {
    if (((_v1605 < 0) || (_v1605 >= vec_len(_v2466._v2448)))) {
        return "";
    }
    return vec_get(_v2466._v2448, _v1605);
}

bkr_str _v2492(_v2436 _v2466, bkr_i64 _v1605, _v2400 _v2415) {
    bkr_i64 _v2428 = vec_len(_v2466._v2437);
    if (((_v1605 < 0) || (_v1605 >= _v2428))) {
        return "";
    }
    bkr_i64 _v2493 = vec_get(_v2466._v2445, _v1605);
    bkr_i64 _v2494 = vec_get(_v2466._v2446, _v1605);
    if (((bkr_len((bkr_str)(intptr_t)(_v2493)) > 0) && (bkr_len((bkr_str)(intptr_t)(_v2494)) > 0))) {
        bkr_i64 _v2495 = _v2421(_v2415, _v2493, _v2494);
        bkr_i64 _v1584 = vec_get(_v2466._v2439, _v1605);
        if ((bkr_len((bkr_str)(intptr_t)(_v1584)) > 0)) {
            return bkr_str_concat(_v1584, int_to_string(_v2495));
        }
        return int_to_string(_v2495);
    }
    return vec_get(_v2466._v2439, _v1605);
}

bkr_bool _v2496(_v2436 _v2466, bkr_i64 _v1605, _v2400 _v2415) {
    bkr_i64 _v2428 = vec_len(_v2466._v2437);
    if (((_v1605 < 0) || (_v1605 >= _v2428))) {
        return BKR_FALSE;
    }
    bkr_i64 _v386 = vec_get(_v2466._v2447, _v1605);
    bkr_i64 _v2399 = vec_get(_v2466._v2448, _v1605);
    if (((bkr_len((bkr_str)(intptr_t)(_v386)) > 0) && (bkr_len((bkr_str)(intptr_t)(_v2399)) > 0))) {
        return _v2426(_v2415, _v386, "View", _v2399, 0);
    }
    return BKR_FALSE;
}

bkr_str _v2497(_v2436 _v2466) {
    bkr_str _v1941 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("schema_version", "bunker.view.v1")), _v1941), _v1892("view_name", _v2466._v1348)), _v1941), _v1893("component_count", vec_len(_v2466._v2437))), _v1941), _v1893("root_id", _v2466._v2450)), "}");
}

_v2498 _v2509(void) {
    bkr_i64 _v425 = vec_new();
    bkr_i64 _v2510 = vec_new();
    return (_v2498){._v2499 = _v425, ._v2500 = _v2510, ._v2501 = 0};
}

_v2498 _v2511(bkr_i64 _v1205) {
    bkr_i64 _v425 = vec_new();
    bkr_i64 _v2510 = vec_new();
    return (_v2498){._v2499 = _v425, ._v2500 = _v2510, ._v2501 = _v1205};
}

_v2498 _v2512(bkr_str _v1348) {
    bkr_i64 _v425 = vec_new();
    bkr_i64 _v2510 = vec_new();
    vec_push(_v425, ((bkr_i64)(intptr_t)_v1348));
    vec_push(_v2510, 1);
    return (_v2498){._v2499 = _v425, ._v2500 = _v2510, ._v2501 = 0};
}

_v2498 _v2513(bkr_str _v1348, bkr_i64 _v2514) {
    bkr_i64 _v425 = vec_new();
    bkr_i64 _v2510 = vec_new();
    vec_push(_v425, ((bkr_i64)(intptr_t)_v1348));
    vec_push(_v2510, _v2514);
    return (_v2498){._v2499 = _v425, ._v2500 = _v2510, ._v2501 = 0};
}

bkr_i64 _v2515(_v2498 _v368, bkr_str _v1348) {
    bkr_i64 _v1168 = 0;
    bkr_i64 _v2428 = vec_len(_v368._v2499);
    while ((_v1168 < _v2428)) {
        if (bkr_str_eq(vec_get(_v368._v2499, _v1168), _v1348)) {
            return vec_get(_v368._v2500, _v1168);
        }
        _v1168 = (_v1168 + 1);
    }
    return 0;
}

bkr_bool _v2516(_v2498 _v368, bkr_str _v1348, bkr_i64 _v2514) {
    bkr_i64 _v1168 = 0;
    bkr_i64 _v2428 = vec_len(_v368._v2499);
    while ((_v1168 < _v2428)) {
        if (bkr_str_eq(vec_get(_v368._v2499, _v1168), _v1348)) {
            vec_set(_v368._v2500, _v1168, _v2514);
            return BKR_TRUE;
        }
        _v1168 = (_v1168 + 1);
    }
    vec_push(_v368._v2499, ((bkr_i64)(intptr_t)_v1348));
    vec_push(_v368._v2500, _v2514);
    return BKR_TRUE;
}

_v2498 _v2517(_v2498 _v2518, _v2498 _v2519) {
    _v2498 _v1717 = _v2509();
    _v1717._v2501 = (_v2518._v2501 + _v2519._v2501);
    bkr_i64 _v1168 = 0;
    bkr_i64 _v2520 = vec_len(_v2518._v2499);
    while ((_v1168 < _v2520)) {
        bkr_i64 _v1348 = vec_get(_v2518._v2499, _v1168);
        bkr_i64 _v2514 = vec_get(_v2518._v2500, _v1168);
        _v2516(_v1717, _v1348, _v2514);
        _v1168 = (_v1168 + 1);
    }
    bkr_i64 _v1629 = 0;
    bkr_i64 _v2521 = vec_len(_v2519._v2499);
    while ((_v1629 < _v2521)) {
        bkr_i64 _v1348 = vec_get(_v2519._v2499, _v1629);
        bkr_i64 _v2514 = vec_get(_v2519._v2500, _v1629);
        bkr_i64 _v2522 = _v2515(_v1717, _v1348);
        _v2516(_v1717, _v1348, (_v2522 + _v2514));
        _v1629 = (_v1629 + 1);
    }
    return _v1717;
}

_v2498 _v2523(_v2498 _v2518, _v2498 _v2519) {
    _v2498 _v1717 = _v2509();
    _v1717._v2501 = (_v2518._v2501 - _v2519._v2501);
    bkr_i64 _v1168 = 0;
    bkr_i64 _v2520 = vec_len(_v2518._v2499);
    while ((_v1168 < _v2520)) {
        bkr_i64 _v1348 = vec_get(_v2518._v2499, _v1168);
        bkr_i64 _v2514 = vec_get(_v2518._v2500, _v1168);
        _v2516(_v1717, _v1348, _v2514);
        _v1168 = (_v1168 + 1);
    }
    bkr_i64 _v1629 = 0;
    bkr_i64 _v2521 = vec_len(_v2519._v2499);
    while ((_v1629 < _v2521)) {
        bkr_i64 _v1348 = vec_get(_v2519._v2499, _v1629);
        bkr_i64 _v2514 = vec_get(_v2519._v2500, _v1629);
        bkr_i64 _v2522 = _v2515(_v1717, _v1348);
        _v2516(_v1717, _v1348, (_v2522 - _v2514));
        _v1629 = (_v1629 + 1);
    }
    return _v1717;
}

_v2498 _v2524(_v2498 _v2518, bkr_i64 _v573) {
    _v2498 _v1717 = _v2509();
    _v1717._v2501 = (_v2518._v2501 * _v573);
    bkr_i64 _v1168 = 0;
    bkr_i64 _v2520 = vec_len(_v2518._v2499);
    while ((_v1168 < _v2520)) {
        bkr_i64 _v1348 = vec_get(_v2518._v2499, _v1168);
        bkr_i64 _v2514 = vec_get(_v2518._v2500, _v1168);
        _v2516(_v1717, _v1348, (_v2514 * _v573));
        _v1168 = (_v1168 + 1);
    }
    return _v1717;
}

bkr_bool _v2525(_v2498 _v368) {
    if ((_v368._v2501 != 0)) {
        return BKR_FALSE;
    }
    bkr_i64 _v1168 = 0;
    bkr_i64 _v2428 = vec_len(_v368._v2499);
    while ((_v1168 < _v2428)) {
        if ((vec_get(_v368._v2500, _v1168) != 0)) {
            return BKR_FALSE;
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_TRUE;
}

bkr_i64 _v2526(_v2498 _v368, bkr_i64 _v2527) {
    bkr_i64 _v2528 = _v368._v2501;
    bkr_i64 _v1168 = 0;
    bkr_i64 _v2428 = vec_len(_v368._v2499);
    while ((_v1168 < _v2428)) {
        bkr_i64 _v1348 = vec_get(_v368._v2499, _v1168);
        bkr_i64 _v2514 = vec_get(_v368._v2500, _v1168);
        if (hashmap_contains(_v2527, _v1348)) {
            bkr_i64 _v1383 = hashmap_get(_v2527, _v1348);
            _v2528 = (_v2528 + (_v2514 * _v1383));
        }
        _v1168 = (_v1168 + 1);
    }
    return _v2528;
}

bkr_str _v2529(_v2498 _v368) {
    bkr_str _v1841 = "";
    bkr_bool _v2530 = BKR_TRUE;
    bkr_i64 _v1168 = 0;
    bkr_i64 _v2428 = vec_len(_v368._v2499);
    while ((_v1168 < _v2428)) {
        bkr_i64 _v2514 = vec_get(_v368._v2500, _v1168);
        bkr_i64 _v1348 = vec_get(_v368._v2499, _v1168);
        if ((_v2514 != 0)) {
            if (_v2530) {
                if ((_v2514 == 1)) {
                    _v1841 = bkr_str_concat(_v1841, _v1348);
                } else {
                    if ((_v2514 == (-1))) {
                        _v1841 = bkr_str_concat(bkr_str_concat(_v1841, "-"), _v1348);
                    } else {
                        _v1841 = bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1841, int_to_string(_v2514)), "*"), _v1348);
                    }
                }
                _v2530 = BKR_FALSE;
            } else {
                if ((_v2514 > 0)) {
                    _v1841 = bkr_str_concat(_v1841, " + ");
                    if ((_v2514 == 1)) {
                        _v1841 = bkr_str_concat(_v1841, _v1348);
                    } else {
                        _v1841 = bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1841, int_to_string(_v2514)), "*"), _v1348);
                    }
                } else {
                    _v1841 = bkr_str_concat(_v1841, " - ");
                    bkr_i64 _v2531 = (0 - _v2514);
                    if ((_v2531 == 1)) {
                        _v1841 = bkr_str_concat(_v1841, _v1348);
                    } else {
                        _v1841 = bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1841, int_to_string(_v2531)), "*"), _v1348);
                    }
                }
            }
        }
        _v1168 = (_v1168 + 1);
    }
    if (((_v368._v2501 != 0) || _v2530)) {
        if (_v2530) {
            _v1841 = bkr_str_concat(_v1841, int_to_string(_v368._v2501));
        } else {
            if ((_v368._v2501 > 0)) {
                _v1841 = bkr_str_concat(bkr_str_concat(_v1841, " + "), int_to_string(_v368._v2501));
            } else {
                _v1841 = bkr_str_concat(bkr_str_concat(_v1841, " - "), int_to_string((0 - _v368._v2501)));
            }
        }
    }
    return _v1841;
}

_v2502 _v2532(bkr_str _v2503) {
    bkr_i64 _v2533 = vec_new();
    bkr_i64 _v2534 = vec_new();
    return (_v2502){._v2503 = _v2503, ._v2504 = _v2533, ._v2505 = _v2534, ._v2506 = BKR_TRUE, ._v2507 = BKR_TRUE, ._v2508 = ""};
}

bkr_bool _v2535(_v2502 _v2536, bkr_str _v2537) {
    vec_push(_v2536._v2504, ((bkr_i64)(intptr_t)_v2537));
    return BKR_TRUE;
}

bkr_bool _v2538(_v2502 _v2536, bkr_str _v2537) {
    vec_push(_v2536._v2505, ((bkr_i64)(intptr_t)_v2537));
    return BKR_TRUE;
}

bkr_bool _v2539(_v2498 _v2540, _v2498 _v2541) {
    _v2498 _v2542 = _v2523(_v2540, _v2541);
    return _v2525(_v2542);
}

bkr_str _v2543(_v2498 _v2540, _v2498 _v2541, bkr_i64 _v2527) {
    _v2498 _v2542 = _v2523(_v2540, _v2541);
    bkr_i64 _v2544 = _v2526(_v2542, _v2527);
    bkr_str _v2545 = _v2529(_v2542);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("diff: ", _v2545), " (evaluated: "), int_to_string(_v2544)), ")");
}

bkr_str _v2546(_v2502 _v2536) {
    bkr_str _v1941 = ",";
    bkr_i64 _v2547 = (vec_len(_v2536._v2504) + vec_len(_v2536._v2505));
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("schema_version", "bunker.verify.v1")), _v1941), _v1892("function_name", _v2536._v2503)), _v1941), _v1893("contracts_checked", _v2547)), _v1941), _v1894("verified", _v2536._v2507)), _v1941), _v1892("counterexample", _v2536._v2508)), "}");
}

_v2548 _v2577(bkr_i64 _v425) {
    bkr_i64 _v2573 = vec_new();
    vec_push(_v2573, 0);
    vec_push(_v2573, 0);
    vec_push(_v2573, 0);
    vec_push(_v2573, 0);
    bkr_i64 _v2564 = vec_new();
    vec_push(_v2564, ((bkr_i64)(intptr_t)""));
    return (_v2548){._v2103 = vec_new(), ._v425 = _v425, ._v2549 = vec_new(), ._v2550 = hashmap_new(), ._v2551 = hashmap_new(), ._v2552 = vec_new(), ._v2553 = vec_new(), ._v1537 = vec_new(), ._v2554 = vec_new(), ._v1538 = vec_new(), ._v2555 = hashmap_new(), ._v2556 = hashmap_new(), ._v2557 = hashmap_new(), ._v2558 = vec_new(), ._v2559 = vec_new(), ._v2560 = vec_new(), ._v2561 = vec_new(), ._v2562 = hashmap_new(), ._v2563 = hashmap_new(), ._v2564 = _v2564, ._v2565 = vec_new(), ._v2566 = vec_new(), ._v2567 = hashmap_new(), ._v2568 = vec_new(), ._v2569 = vec_new(), ._v2570 = vec_new(), ._v2571 = vec_new(), ._v2572 = vec_new(), ._v2573 = _v2573};
}

bkr_str _v2578(_v2548 _v2579, bkr_i64 _v1035) {
    if (((_v1035 >= 0) && (_v1035 < vec_len(_v2579._v425)))) {
        return vec_get(_v2579._v425, _v1035);
    }
    return "";
}

bkr_str _v2580(bkr_i64 _v319) {
    if ((_v319 == _v254)) {
        return "struct";
    }
    if ((_v319 == _v259)) {
        return "enum";
    }
    if ((_v319 == _v260)) {
        return "type alias";
    }
    if ((_v319 == _v248)) {
        return "string literal";
    }
    if ((_v319 == _v251)) {
        return "float literal";
    }
    if ((_v319 == _v252)) {
        return "array literal";
    }
    if ((_v319 == _v239)) {
        return "array literal";
    }
    if ((_v319 == _v253)) {
        return "indexing";
    }
    if ((_v319 == _v256)) {
        return "field access";
    }
    if ((_v319 == _v257)) {
        return "struct literal";
    }
    if ((_v319 == _v258)) {
        return "match";
    }
    if ((_v319 == _v261)) {
        return "method call";
    }
    if ((_v319 == _v238)) {
        return "defer";
    }
    if ((_v319 == _v240)) {
        return "? operator";
    }
    if ((_v319 == _v227)) {
        return "block expression";
    }
    return bkr_str_concat("node kind ", int_to_string(_v319));
}

bkr_bool _v2581(_v2548 _v2579, bkr_str _v2399) {
    vec_push(_v2579._v2549, ((bkr_i64)(intptr_t)_v2399));
    return BKR_FALSE;
}

bkr_i64 _v2582(_v2548 _v2579) {
    return vec_len(_v2579._v2103);
}

bkr_bool _v2583(_v2548 _v2579, bkr_i64 _v2584) {
    vec_push(_v2579._v2103, (_v2584 & 255));
    return BKR_TRUE;
}

bkr_bool _v2585(_v2548 _v2579, bkr_i64 _v2518, bkr_i64 _v2519) {
    _v2583(_v2579, _v2518);
    return _v2583(_v2579, _v2519);
}

bkr_bool _v2586(_v2548 _v2579, bkr_i64 _v2518, bkr_i64 _v2519, bkr_i64 _v1205) {
    _v2583(_v2579, _v2518);
    _v2583(_v2579, _v2519);
    return _v2583(_v2579, _v1205);
}

bkr_bool _v2587(_v2548 _v2579, bkr_i64 _v387) {
    _v2583(_v2579, _v387);
    _v2583(_v2579, (_v387 >> 8));
    _v2583(_v2579, (_v387 >> 16));
    return _v2583(_v2579, (_v387 >> 24));
}

bkr_bool _v2588(_v2548 _v2579, bkr_i64 _v387) {
    _v2587(_v2579, _v387);
    return _v2587(_v2579, (_v387 >> 32));
}

bkr_bool _v2589(_v2548 _v2579, bkr_i64 _v1210, bkr_i64 _v387) {
    vec_set(_v2579._v2103, _v1210, (_v387 & 255));
    vec_set(_v2579._v2103, (_v1210 + 1), ((_v387 >> 8) & 255));
    vec_set(_v2579._v2103, (_v1210 + 2), ((_v387 >> 16) & 255));
    vec_set(_v2579._v2103, (_v1210 + 3), ((_v387 >> 24) & 255));
    return BKR_TRUE;
}

bkr_bool _v2590(_v2548 _v2579, bkr_i64 _v1210, bkr_i64 _v386) {
    return _v2589(_v2579, _v1210, (_v386 - (_v1210 + 4)));
}

bkr_bool _v2591(_v2548 _v2579, bkr_i64 _v387) {
    _v2585(_v2579, 72, 184);
    return _v2588(_v2579, _v387);
}

bkr_bool _v2592(_v2548 _v2579, bkr_i64 _v1274) {
    _v2586(_v2579, 72, 139, 133);
    return _v2587(_v2579, (0 - _v1274));
}

bkr_bool _v2593(_v2548 _v2579, bkr_i64 _v1274) {
    _v2586(_v2579, 72, 137, 133);
    return _v2587(_v2579, (0 - _v1274));
}

bkr_bool _v2594(_v2548 _v2579, bkr_i64 _v1274) {
    _v2586(_v2579, 72, 141, 133);
    return _v2587(_v2579, (0 - _v1274));
}

bkr_bool _v2595(_v2548 _v2579, bkr_i64 _v1274) {
    _v2586(_v2579, 72, 141, 149);
    return _v2587(_v2579, (0 - _v1274));
}

bkr_bool _v2596(_v2548 _v2579, bkr_i64 _v1274) {
    _v2586(_v2579, 72, 139, 149);
    return _v2587(_v2579, (0 - _v1274));
}

bkr_bool _v2597(_v2548 _v2579, bkr_i64 _v1217) {
    _v2586(_v2579, 72, 139, 128);
    return _v2587(_v2579, (_v1217 * 8));
}

bkr_bool _v2598(_v2548 _v2579, bkr_i64 _v387) {
    _v2585(_v2579, 72, 5);
    return _v2587(_v2579, _v387);
}

bkr_bool _v2599(_v2548 _v2579, bkr_i64 _v387) {
    _v2585(_v2579, 72, 185);
    _v2588(_v2579, _v387);
    return _v2586(_v2579, 72, 57, 200);
}

bkr_bool _v2600(_v2548 _v2579, bkr_i64 _v2601) {
    _v2586(_v2579, 72, 193, 248);
    return _v2583(_v2579, _v2601);
}

bkr_bool _v2602(_v2548 _v2579, bkr_i64 _v387) {
    _v2585(_v2579, 72, 37);
    return _v2587(_v2579, _v387);
}

bkr_bool _v2603(_v2548 _v2579, bkr_i64 _v2604) {
    bkr_i64 _v573 = 0;
    while ((_v573 < _v2604)) {
        _v2586(_v2579, 72, 139, 136);
        _v2587(_v2579, (_v573 * 8));
        _v2586(_v2579, 72, 137, 138);
        _v2587(_v2579, (_v573 * 8));
        _v573 = (_v573 + 1);
    }
    return BKR_TRUE;
}

bkr_i64 _v2605(_v2548 _v2579) {
    _v2585(_v2579, 15, 133);
    bkr_i64 _v1210 = _v2582(_v2579);
    _v2587(_v2579, 0);
    return _v1210;
}

bkr_bool _v2606(_v2548 _v2579) {
    return _v2583(_v2579, 80);
}

bkr_bool _v2607(_v2548 _v2579) {
    return _v2583(_v2579, 88);
}

bkr_bool _v2608(_v2548 _v2579) {
    return _v2583(_v2579, 89);
}

bkr_bool _v2609(_v2548 _v2579) {
    return _v2586(_v2579, 72, 133, 192);
}

bkr_bool _v2610(_v2548 _v2579, bkr_i64 _v2611) {
    _v2586(_v2579, 15, _v2611, 192);
    _v2585(_v2579, 72, 15);
    return _v2585(_v2579, 182, 192);
}

bkr_i64 _v2612(_v2548 _v2579) {
    _v2583(_v2579, 233);
    bkr_i64 _v1210 = _v2582(_v2579);
    _v2587(_v2579, 0);
    return _v1210;
}

bkr_i64 _v2613(_v2548 _v2579) {
    _v2609(_v2579);
    _v2585(_v2579, 15, 132);
    bkr_i64 _v1210 = _v2582(_v2579);
    _v2587(_v2579, 0);
    return _v1210;
}

bkr_i64 _v2614(_v2548 _v2579) {
    _v2609(_v2579);
    _v2585(_v2579, 15, 133);
    bkr_i64 _v1210 = _v2582(_v2579);
    _v2587(_v2579, 0);
    return _v1210;
}

bkr_bool _v2615(_v2548 _v2579, bkr_i64 _v386) {
    _v2583(_v2579, 233);
    bkr_i64 _v1210 = _v2582(_v2579);
    _v2587(_v2579, 0);
    return _v2590(_v2579, _v1210, _v386);
}

bkr_bool _v2616(_v2548 _v2579) {
    _v2586(_v2579, 72, 137, 236);
    _v2583(_v2579, 93);
    return _v2583(_v2579, 195);
}

bkr_i64 _v2617(_v2548 _v2579, bkr_i64 _v2604) {
    bkr_i64 _v1274 = (vec_get(_v2579._v2573, 0) + (8 * _v2604));
    vec_set(_v2579._v2573, 0, _v1274);
    if ((_v1274 > vec_get(_v2579._v2573, 1))) {
        vec_set(_v2579._v2573, 1, _v1274);
    }
    return _v1274;
}

bkr_i64 _v2618(_v2548 _v2579, bkr_str _v1348, bkr_i64 _v1274, bkr_str _v1663) {
    vec_push(_v2579._v1537, ((bkr_i64)(intptr_t)_v1348));
    vec_push(_v2579._v2554, _v1274);
    vec_push(_v2579._v1538, ((bkr_i64)(intptr_t)_v1663));
    return _v1274;
}

bkr_i64 _v2619(_v2548 _v2579, bkr_str _v1348) {
    return _v2618(_v2579, _v1348, _v2617(_v2579, 1), "");
}

bkr_i64 _v2620(_v2548 _v2579, bkr_str _v1348) {
    bkr_i64 _v1168 = (vec_len(_v2579._v1537) - 1);
    while ((_v1168 >= 0)) {
        if (bkr_str_eq(vec_get(_v2579._v1537, _v1168), _v1348)) {
            return _v1168;
        }
        _v1168 = (_v1168 - 1);
    }
    return (-1);
}

bkr_i64 _v2621(_v2548 _v2579, bkr_str _v1348) {
    bkr_i64 _v1168 = _v2620(_v2579, _v1348);
    if ((_v1168 < 0)) {
        return (-1);
    }
    return vec_get(_v2579._v2554, _v1168);
}

bkr_str _v2622(_v2548 _v2579, bkr_str _v1348) {
    bkr_i64 _v1168 = _v2620(_v2579, _v1348);
    if ((_v1168 < 0)) {
        return "";
    }
    return vec_get(_v2579._v1538, _v1168);
}

bkr_i64 _v2623(_v2548 _v2579) {
    return vec_len(_v2579._v1537);
}

bkr_bool _v2624(_v2548 _v2579, bkr_i64 _v2625) {
    while ((vec_len(_v2579._v1537) > _v2625)) {
        vec_pop(_v2579._v1537);
        vec_pop(_v2579._v2554);
        vec_pop(_v2579._v1538);
    }
    return BKR_TRUE;
}

bkr_bool _v2627(_v2548 _v2579, bkr_str _v1663) {
    return ((bkr_len((bkr_str)(intptr_t)(_v1663)) > 0) && (!starts_with(_v1663, "$")));
}

bkr_bool _v2628(_v2548 _v2579, bkr_str _v1663) {
    return bkr_str_eq(_v1663, "$str");
}

bkr_str _v2629(bkr_i64 _v319) {
    if ((_v319 == _v306)) {
        return "s";
    }
    return "i";
}

bkr_str _v2630(bkr_str _v1663, bkr_str _v1584, bkr_i64 _v362) {
    if (((!starts_with(_v1663, _v1584)) || (bkr_len((bkr_str)(intptr_t)(_v1663)) <= (bkr_len((bkr_str)(intptr_t)(_v1584)) + _v362)))) {
        return "";
    }
    if (bkr_str_eq(char_at(_v1663, (bkr_len((bkr_str)(intptr_t)(_v1584)) + _v362)), "s")) {
        return "$str";
    }
    return "";
}

bkr_bool _v2631(_v2548 _v2579, bkr_str _v1663) {
    return starts_with(_v1663, "[");
}

bkr_i64 _v2632(_v2548 _v2579, bkr_str _v1663) {
    return parse_int(substring(_v1663, 1, bkr_str_index_of((bkr_str)(intptr_t)(_v1663), (bkr_str)(intptr_t)("]"))));
}

bkr_str _v2633(_v2548 _v2579, bkr_str _v1663) {
    return substring(_v1663, (bkr_str_index_of((bkr_str)(intptr_t)(_v1663), (bkr_str)(intptr_t)("]")) + 1), bkr_len((bkr_str)(intptr_t)(_v1663)));
}

bkr_i64 _v2634(_v2548 _v2579, bkr_str _v1663) {
    if (((bkr_len((bkr_str)(intptr_t)(_v1663)) == 0) || starts_with(_v1663, "$"))) {
        return 1;
    }
    if (_v2631(_v2579, _v1663)) {
        return (_v2632(_v2579, _v1663) * _v2634(_v2579, _v2633(_v2579, _v1663)));
    }
    bkr_i64 _v2481 = hashmap_get(_v2579._v2556, ((bkr_i64)(intptr_t)_v1663));
    return _v2481;
}

bkr_str _v2635(_v2548 _v2579, _v346 _v520) {
    if (_v522(_v520)) {
        return "";
    }
    bkr_i64 _v319 = _v529(_v520);
    if ((_v319 == _v308)) {
        bkr_i64 _v953 = _v532(_v520);
        if (((_v953 == _v309) || (_v953 == _v308))) {
            _v2581(_v2579, "unsupported type: array of structs or arrays");
            return "";
        }
        return bkr_str_concat(bkr_str_concat("[", int_to_string(_v533(_v520))), "]");
    }
    if ((_v319 == _v309)) {
        bkr_str _v1348 = _v2578(_v2579, _v531(_v520));
        if (hashmap_contains(_v2579._v2557, ((bkr_i64)(intptr_t)_v1348))) {
            return _v1348;
        }
    }
    if ((_v319 == _v306)) {
        return "$str";
    }
    if ((_v319 == _v310)) {
        return bkr_str_concat("$vec:", _v2629(_v534(_v520)));
    }
    if ((_v319 == _v311)) {
        return bkr_str_concat(bkr_str_concat("$map:", _v2629(_v534(_v520))), _v2629(_v535(_v520)));
    }
    if ((_v319 == _v312)) {
        return bkr_str_concat("$opt:", _v2629(_v534(_v520)));
    }
    if ((_v319 == _v313)) {
        return bkr_str_concat(bkr_str_concat("$res:", _v2629(_v534(_v520))), _v2629(_v535(_v520)));
    }
    return "";
}

bkr_str _v2636(bkr_str _v1348) {
    if ((((((((((((bkr_str_eq(_v1348, "char_at") || bkr_str_eq(_v1348, "substring")) || bkr_str_eq(_v1348, "trim")) || bkr_str_eq(_v1348, "int_to_string")) || bkr_str_eq(_v1348, "from_char_code")) || bkr_str_eq(_v1348, "join_lines")) || bkr_str_eq(_v1348, "read_file")) || bkr_str_eq(_v1348, "arg_at")) || bkr_str_eq(_v1348, "str_replace")) || bkr_str_eq(_v1348, "str_to_upper")) || bkr_str_eq(_v1348, "str_to_lower")) || bkr_str_eq(_v1348, "str_repeat"))) {
        return "$str";
    }
    if (bkr_str_eq(_v1348, "str_split")) {
        return "$vec:s";
    }
    if (bkr_str_eq(_v1348, "env_get")) {
        return "$opt:s";
    }
    if ((bkr_str_eq(_v1348, "read_file_result") || bkr_str_eq(_v1348, "process_run"))) {
        return "$res:ss";
    }
    return "";
}

bkr_str _v2637(_v2548 _v2579, bkr_i64 _v342) {
    if ((!_v525(_v342))) {
        return "";
    }
    return _v2635(_v2579, _v516(_v342));
}

bkr_i64 _v2638(_v2548 _v2579, bkr_str _v1681, bkr_str _v1150) {
    bkr_i64 _v1168 = 0;
    while ((_v1168 < vec_len(_v2579._v2558))) {
        if ((bkr_str_eq(vec_get(_v2579._v2558, _v1168), _v1681) && bkr_str_eq(vec_get(_v2579._v2559, _v1168), _v1150))) {
            return _v1168;
        }
        _v1168 = (_v1168 + 1);
    }
    return (-1);
}

bkr_i64 _v2639(_v2548 _v2579, bkr_str _v1681, bkr_i64 _v2640) {
    bkr_i64 _v2641 = 0;
    bkr_i64 _v1168 = 0;
    while ((_v1168 < vec_len(_v2579._v2558))) {
        if (bkr_str_eq(vec_get(_v2579._v2558, _v1168), _v1681)) {
            if ((_v2641 == _v2640)) {
                return _v1168;
            }
            _v2641 = (_v2641 + 1);
        }
        _v1168 = (_v1168 + 1);
    }
    return (-1);
}

bkr_i64 _v2642(_v2548 _v2579, bkr_str _v1348, bkr_i64 _v1350) {
    if (hashmap_contains(_v2579._v2556, ((bkr_i64)(intptr_t)_v1348))) {
        bkr_i64 _v2643 = hashmap_get(_v2579._v2556, ((bkr_i64)(intptr_t)_v1348));
        return _v2643;
    }
    if ((_v1350 > 64)) {
        _v2581(_v2579, bkr_str_concat("recursive struct layout: ", _v1348));
        return 1;
    }
    bkr_i64 _v2604 = 0;
    bkr_i64 _v1168 = 0;
    while ((_v1168 < vec_len(_v2579._v2558))) {
        if (bkr_str_eq(vec_get(_v2579._v2558, _v1168), _v1348)) {
            vec_set(_v2579._v2561, _v1168, _v2604);
            bkr_str _v2644 = (bkr_str)(intptr_t)(vec_get(_v2579._v2560, _v1168));
            if ((bkr_len((bkr_str)(intptr_t)(_v2644)) == 0)) {
                _v2604 = (_v2604 + 1);
            } else {
                if (_v2631(_v2579, _v2644)) {
                    _v2604 = (_v2604 + _v2634(_v2579, _v2644));
                } else {
                    _v2604 = (_v2604 + _v2642(_v2579, _v2644, (_v1350 + 1)));
                }
            }
        }
        _v1168 = (_v1168 + 1);
    }
    if ((_v2604 == 0)) {
        _v2604 = 1;
    }
    hashmap_insert_str(_v2579._v2556, ((bkr_i64)(intptr_t)_v1348), _v2604);
    return _v2604;
}

bkr_str _v2645(_v2548 _v2579, _v426 _v541) {
    bkr_str _v2646 = _v2647(_v2579, _v694(_v541));
    return bkr_str_concat(bkr_str_concat(_v2646, "::"), _v2578(_v2579, _v696(_v541)));
}

bkr_str _v2648(_v2548 _v2579, bkr_str _v1348) {
    if (hashmap_contains(_v2579._v2555, ((bkr_i64)(intptr_t)_v1348))) {
        bkr_str _v1663 = (bkr_str)(intptr_t)(hashmap_get(_v2579._v2555, ((bkr_i64)(intptr_t)_v1348)));
        return _v1663;
    }
    return "";
}

bkr_str _v2647(_v2548 _v2579, _v426 _v541) {
    bkr_i64 _v319 = _v544(_v541);
    if ((_v319 == _v248)) {
        return "$str";
    }
    if ((_v319 == _v241)) {
        return _v2635(_v2579, _v516(_v782(_v541)));
    }
    if ((_v319 == _v242)) {
        bkr_i64 _v349 = _v671(_v541);
        if ((_v349 == _v161)) {
            bkr_str _v2649 = _v2647(_v2579, _v537(_v674(_v541)));
            bkr_str _v2650 = _v2647(_v2579, _v537(_v677(_v541)));
            if ((_v2628(_v2579, _v2649) || _v2628(_v2579, _v2650))) {
                return "$str";
            }
        }
        return "";
    }
    if ((_v319 == _v227)) {
        _v429 _v582 = _v578(_v540(_v541));
        bkr_i64 _v399 = _v589(_v582);
        if ((_v399 > 0)) {
            _v427 _v2651 = _v1107(_v582, (_v399 - 1));
            if ((_v555(_v2651) == _v232)) {
                return _v2647(_v2579, _v537(_v860(_v2651)));
            }
        }
        return "";
    }
    if ((_v319 == _v245)) {
        return _v2622(_v2579, _v2578(_v2579, _v662(_v541)));
    }
    if ((_v319 == _v257)) {
        return _v2578(_v2579, _v724(_v541));
    }
    if ((_v319 == _v244)) {
        bkr_str _v1348 = _v2578(_v2579, _v688(_v541));
        if (hashmap_contains(_v2579._v2557, ((bkr_i64)(intptr_t)_v1348))) {
            return _v1348;
        }
        if (hashmap_contains(_v2579._v2551, ((bkr_i64)(intptr_t)_v1348))) {
            return _v2648(_v2579, _v1348);
        }
        _v434 _v1015 = _v691(_v541);
        if ((_v906(_v1015) > 0)) {
            bkr_str _v2652 = _v2647(_v2579, _v537(_v909(_v1015, 0)));
            if ((bkr_str_eq(_v1348, "vec_get") || bkr_str_eq(_v1348, "vec_pop"))) {
                return _v2630(_v2652, "$vec:", 0);
            }
            if (bkr_str_eq(_v1348, "hashmap_get")) {
                return _v2630(_v2652, "$map:", 1);
            }
            if ((bkr_str_eq(_v1348, "hashmap_keys") && starts_with(_v2652, "$map:"))) {
                return bkr_str_concat("$vec:", substring(_v2652, 5, 6));
            }
            if ((bkr_str_eq(_v1348, "hashmap_values") && starts_with(_v2652, "$map:"))) {
                return bkr_str_concat("$vec:", substring(_v2652, 6, 7));
            }
        }
        return _v2636(_v1348);
    }
    if ((_v319 == _v261)) {
        return _v2648(_v2579, _v2645(_v2579, _v541));
    }
    if ((_v319 == _v256)) {
        bkr_str _v2653 = _v2647(_v2579, _v720(_v541));
        if ((bkr_len((bkr_str)(intptr_t)(_v2653)) == 0)) {
            return "";
        }
        bkr_i64 _v2654 = _v2638(_v2579, _v2653, _v2578(_v2579, _v722(_v541)));
        if ((_v2654 < 0)) {
            return "";
        }
        return vec_get(_v2579._v2560, _v2654);
    }
    if ((_v319 == _v250)) {
        return _v2647(_v2579, _v537(_v736(_v541)));
    }
    if ((_v319 == _v253)) {
        bkr_str _v2653 = _v2647(_v2579, _v537(_v711(_v541)));
        if (_v2631(_v2579, _v2653)) {
            return _v2633(_v2579, _v2653);
        }
        return "";
    }
    if ((_v319 == _v252)) {
        _v434 _v2655 = _v701(_v541);
        bkr_i64 _v399 = _v906(_v2655);
        bkr_str _v2656 = "";
        if ((_v399 > 0)) {
            _v2656 = _v2647(_v2579, _v537(_v909(_v2655, 0)));
        }
        return bkr_str_concat(bkr_str_concat(bkr_str_concat("[", int_to_string(_v399)), "]"), _v2656);
    }
    if ((_v319 == _v239)) {
        return bkr_str_concat(bkr_str_concat(bkr_str_concat("[", int_to_string(_v706(_v541))), "]"), _v2647(_v2579, _v704(_v541)));
    }
    if ((_v319 == _v258)) {
        _v434 _v975 = _v748(_v541);
        if ((_v906(_v975) > 0)) {
            bkr_i64 _v379 = _v909(_v975, 0);
            if ((_v509(_v506(_v379)) != _v227)) {
                return _v2647(_v2579, _v537(_v379));
            }
        }
    }
    return "";
}

bkr_bool _v2657(_v2548 _v2579, bkr_i64 _v342) {
    return _v2658(_v2579, _v537(_v342));
}

bkr_bool _v2658(_v2548 _v2579, _v426 _v541) {
    bkr_i64 _v319 = _v544(_v541);
    if ((_v319 == _v246)) {
        return _v2591(_v2579, _v665(_v541));
    }
    if ((_v319 == _v247)) {
        if ((_v665(_v541) == 1)) {
            return _v2591(_v2579, 1);
        }
        return _v2591(_v2579, 0);
    }
    if ((_v319 == _v245)) {
        bkr_str _v1348 = _v2578(_v2579, _v662(_v541));
        bkr_i64 _v1274 = _v2621(_v2579, _v1348);
        if ((_v1274 > 0)) {
            if (_v2627(_v2579, _v2622(_v2579, _v1348))) {
                return _v2594(_v2579, _v1274);
            }
            return _v2592(_v2579, _v1274);
        }
        if (bkr_str_eq(_v1348, "None")) {
            return _v2591(_v2579, 0);
        }
        if (hashmap_contains(_v2579._v2567, ((bkr_i64)(intptr_t)_v1348))) {
            bkr_i64 _v2659 = hashmap_get(_v2579._v2567, ((bkr_i64)(intptr_t)_v1348));
            return _v2657(_v2579, _v2659);
        }
        return _v2581(_v2579, bkr_str_concat("unknown name: ", _v1348));
    }
    if ((_v319 == _v248)) {
        _v2586(_v2579, 72, 141, 5);
        vec_push(_v2579._v2565, _v2582(_v2579));
        vec_push(_v2579._v2566, ((bkr_i64)(intptr_t)((bkr_str)(_v665(_v541)))));
        return _v2587(_v2579, 0);
    }
    if ((_v319 == _v241)) {
        _v346 _v1094 = _v516(_v782(_v541));
        bkr_i64 _v1787 = _v529(_v1094);
        if ((_v1787 == _v304)) {
            return _v2581(_v2579, "unsupported cast target: float");
        }
        return _v2657(_v2579, _v781(_v541));
    }
    if ((_v319 == _v243)) {
        bkr_i64 _v349 = _v681(_v541);
        _v2657(_v2579, _v684(_v541));
        if ((_v349 == _v162)) {
            return _v2586(_v2579, 72, 247, 216);
        }
        if ((_v349 == _v174)) {
            _v2609(_v2579);
            return _v2610(_v2579, 148);
        }
        return _v2581(_v2579, "unsupported unary operator");
    }
    if ((_v319 == _v242)) {
        return _v2660(_v2579, _v541);
    }
    if ((_v319 == _v250)) {
        _v2657(_v2579, _v733(_v541));
        bkr_i64 _v2661 = _v2613(_v2579);
        _v2657(_v2579, _v736(_v541));
        bkr_i64 _v2662 = _v2612(_v2579);
        _v2590(_v2579, _v2661, _v2582(_v2579));
        _v2657(_v2579, _v739(_v541));
        return _v2590(_v2579, _v2662, _v2582(_v2579));
    }
    if ((_v319 == _v244)) {
        return _v2663(_v2579, _v541);
    }
    if ((_v319 == _v261)) {
        bkr_i64 _v2664 = vec_new();
        vec_push(_v2664, _v693(_v541));
        _v434 _v1015 = _v698(_v541);
        bkr_i64 _v1168 = 0;
        while ((_v1168 < _v906(_v1015))) {
            vec_push(_v2664, _v909(_v1015, _v1168));
            _v1168 = (_v1168 + 1);
        }
        return _v2665(_v2579, _v2645(_v2579, _v541), _v2664);
    }
    if ((_v319 == _v256)) {
        _v426 _v1037 = _v720(_v541);
        bkr_str _v1150 = _v2578(_v2579, _v722(_v541));
        if ((_v544(_v1037) == _v245)) {
            bkr_str _v2666 = _v2578(_v2579, _v662(_v1037));
            if (((_v2621(_v2579, _v2666) < 0) && hashmap_contains(_v2579._v2562, ((bkr_i64)(intptr_t)_v2666)))) {
                bkr_str _v1826 = bkr_str_concat(bkr_str_concat(_v2666, "."), _v1150);
                if ((!hashmap_contains(_v2579._v2563, ((bkr_i64)(intptr_t)_v1826)))) {
                    return _v2581(_v2579, bkr_str_concat("unknown enum variant: ", _v1826));
                }
                bkr_i64 _v1674 = hashmap_get(_v2579._v2563, ((bkr_i64)(intptr_t)_v1826));
                return _v2591(_v2579, _v1674);
            }
        }
        bkr_str _v2653 = _v2647(_v2579, _v1037);
        if ((!_v2627(_v2579, _v2653))) {
            return _v2581(_v2579, bkr_str_concat("field access on a non-struct value: .", _v1150));
        }
        bkr_i64 _v2654 = _v2638(_v2579, _v2653, _v1150);
        if ((_v2654 < 0)) {
            return _v2581(_v2579, bkr_str_concat(bkr_str_concat(bkr_str_concat("unknown field ", _v2653), "."), _v1150));
        }
        _v2658(_v2579, _v1037);
        if (_v2627(_v2579, vec_get(_v2579._v2560, _v2654))) {
            return _v2598(_v2579, (vec_get(_v2579._v2561, _v2654) * 8));
        }
        return _v2597(_v2579, vec_get(_v2579._v2561, _v2654));
    }
    if ((_v319 == _v257)) {
        return _v2667(_v2579, _v541);
    }
    if ((_v319 == _v252)) {
        _v434 _v2655 = _v701(_v541);
        bkr_i64 _v399 = _v906(_v2655);
        bkr_str _v1663 = _v2647(_v2579, _v541);
        bkr_str _v2656 = _v2633(_v2579, _v1663);
        bkr_i64 _v2668 = _v2634(_v2579, _v2656);
        bkr_i64 _v361 = _v2617(_v2579, _v2634(_v2579, _v1663));
        bkr_i64 _v1168 = 0;
        while ((_v1168 < _v399)) {
            bkr_i64 _v2669 = (_v361 - ((8 * _v2668) * _v1168));
            _v2657(_v2579, _v909(_v2655, _v1168));
            if (_v2627(_v2579, _v2656)) {
                _v2595(_v2579, _v2669);
                _v2603(_v2579, _v2668);
            } else {
                _v2593(_v2579, _v2669);
            }
            _v1168 = (_v1168 + 1);
        }
        return _v2594(_v2579, _v361);
    }
    if ((_v319 == _v239)) {
        bkr_i64 _v399 = _v706(_v541);
        _v426 _v1000 = _v704(_v541);
        if (_v2627(_v2579, _v2647(_v2579, _v1000))) {
            return _v2581(_v2579, "repeat arrays of structs are not supported");
        }
        if ((_v399 <= 0)) {
            return _v2581(_v2579, "repeat array needs a positive length");
        }
        bkr_i64 _v361 = _v2617(_v2579, _v399);
        _v2658(_v2579, _v1000);
        _v2595(_v2579, _v361);
        _v2585(_v2579, 72, 185);
        _v2588(_v2579, _v399);
        bkr_i64 _v2670 = _v2582(_v2579);
        _v2586(_v2579, 72, 137, 2);
        _v2586(_v2579, 72, 131, 194);
        _v2583(_v2579, 8);
        _v2586(_v2579, 72, 255, 201);
        _v2585(_v2579, 15, 133);
        bkr_i64 _v2671 = _v2582(_v2579);
        _v2587(_v2579, 0);
        _v2590(_v2579, _v2671, _v2670);
        return _v2594(_v2579, _v361);
    }
    if ((_v319 == _v253)) {
        bkr_str _v2656 = _v2647(_v2579, _v541);
        if ((!_v2672(_v2579, _v541))) {
            return BKR_FALSE;
        }
        if (_v2627(_v2579, _v2656)) {
            return BKR_TRUE;
        }
        return _v2586(_v2579, 72, 139, 0);
    }
    if ((_v319 == _v258)) {
        return _v2673(_v2579, _v541);
    }
    if ((_v319 == _v227)) {
        return _v2674(_v2579, _v578(_v540(_v541)));
    }
    return _v2581(_v2579, bkr_str_concat("unsupported expression: ", _v2580(_v319)));
}

bkr_bool _v2660(_v2548 _v2579, _v426 _v541) {
    bkr_i64 _v349 = _v671(_v541);
    bkr_i64 _v350 = _v674(_v541);
    bkr_i64 _v351 = _v677(_v541);
    if ((_v349 == _v172)) {
        _v2657(_v2579, _v350);
        bkr_i64 _v2675 = _v2613(_v2579);
        _v2657(_v2579, _v351);
        _v2609(_v2579);
        _v2610(_v2579, 149);
        bkr_i64 _v2662 = _v2612(_v2579);
        _v2590(_v2579, _v2675, _v2582(_v2579));
        _v2591(_v2579, 0);
        return _v2590(_v2579, _v2662, _v2582(_v2579));
    }
    if ((_v349 == _v173)) {
        _v2657(_v2579, _v350);
        bkr_i64 _v2676 = _v2614(_v2579);
        _v2657(_v2579, _v351);
        _v2609(_v2579);
        _v2610(_v2579, 149);
        bkr_i64 _v2662 = _v2612(_v2579);
        _v2590(_v2579, _v2676, _v2582(_v2579));
        _v2591(_v2579, 1);
        return _v2590(_v2579, _v2662, _v2582(_v2579));
    }
    if ((((_v349 == _v166) || (_v349 == _v167)) || (_v349 == _v161))) {
        bkr_str _v2649 = _v2647(_v2579, _v537(_v350));
        bkr_str _v2650 = _v2647(_v2579, _v537(_v351));
        if ((_v2628(_v2579, _v2649) || _v2628(_v2579, _v2650))) {
            bkr_i64 _v2664 = vec_new();
            vec_push(_v2664, _v350);
            vec_push(_v2664, _v351);
            if ((_v349 == _v161)) {
                return _v2665(_v2579, "rt_str_concat", _v2664);
            }
            _v2665(_v2579, "rt_str_eq", _v2664);
            if ((_v349 == _v167)) {
                _v2586(_v2579, 72, 131, 240);
                _v2583(_v2579, 1);
            }
            return BKR_TRUE;
        }
    }
    _v2657(_v2579, _v350);
    _v2606(_v2579);
    _v2657(_v2579, _v351);
    _v2586(_v2579, 72, 137, 193);
    _v2607(_v2579);
    if ((_v349 == _v161)) {
        return _v2586(_v2579, 72, 1, 200);
    }
    if ((_v349 == _v162)) {
        return _v2586(_v2579, 72, 41, 200);
    }
    if ((_v349 == _v163)) {
        _v2586(_v2579, 72, 15, 175);
        return _v2583(_v2579, 193);
    }
    if (((_v349 == _v164) || (_v349 == _v165))) {
        _v2585(_v2579, 72, 153);
        _v2586(_v2579, 72, 247, 249);
        if ((_v349 == _v165)) {
            return _v2586(_v2579, 72, 137, 208);
        }
        return BKR_TRUE;
    }
    if ((_v349 == _v175)) {
        return _v2586(_v2579, 72, 33, 200);
    }
    if ((_v349 == _v176)) {
        return _v2586(_v2579, 72, 9, 200);
    }
    if ((_v349 == _v177)) {
        return _v2586(_v2579, 72, 49, 200);
    }
    if ((_v349 == _v178)) {
        return _v2586(_v2579, 72, 211, 224);
    }
    if ((_v349 == _v179)) {
        return _v2586(_v2579, 72, 211, 248);
    }
    bkr_i64 _v2611 = 0;
    if ((_v349 == _v166)) {
        _v2611 = 148;
    }
    if ((_v349 == _v167)) {
        _v2611 = 149;
    }
    if ((_v349 == _v168)) {
        _v2611 = 156;
    }
    if ((_v349 == _v171)) {
        _v2611 = 157;
    }
    if ((_v349 == _v170)) {
        _v2611 = 158;
    }
    if ((_v349 == _v169)) {
        _v2611 = 159;
    }
    if ((_v2611 == 0)) {
        return _v2581(_v2579, "unsupported binary operator");
    }
    _v2586(_v2579, 72, 57, 200);
    return _v2610(_v2579, _v2611);
}

bkr_bool _v2672(_v2548 _v2579, _v426 _v541) {
    _v426 _v1037 = _v537(_v711(_v541));
    bkr_str _v2653 = _v2647(_v2579, _v1037);
    if ((!_v2631(_v2579, _v2653))) {
        return _v2581(_v2579, "indexing is only supported on fixed arrays");
    }
    bkr_i64 _v399 = _v2632(_v2579, _v2653);
    bkr_i64 _v2677 = (8 * _v2634(_v2579, _v2633(_v2579, _v2653)));
    _v2658(_v2579, _v1037);
    _v2606(_v2579);
    _v2657(_v2579, _v714(_v541));
    _v2599(_v2579, _v399);
    _v2585(_v2579, 15, 130);
    bkr_i64 _v2678 = _v2582(_v2579);
    _v2587(_v2579, 0);
    _v2583(_v2579, 191);
    _v2587(_v2579, 101);
    _v2583(_v2579, 184);
    _v2587(_v2579, 60);
    _v2585(_v2579, 15, 5);
    _v2590(_v2579, _v2678, _v2582(_v2579));
    _v2586(_v2579, 72, 105, 200);
    _v2587(_v2579, _v2677);
    _v2607(_v2579);
    return _v2586(_v2579, 72, 1, 200);
}

bkr_bool _v2663(_v2548 _v2579, _v426 _v541) {
    bkr_str _v1348 = _v2578(_v2579, _v688(_v541));
    _v434 _v1015 = _v691(_v541);
    bkr_i64 _v2679 = _v906(_v1015);
    if (((bkr_str_eq(_v1348, "len") && (_v2679 == 1)) && (!hashmap_contains(_v2579._v2551, ((bkr_i64)(intptr_t)_v1348))))) {
        bkr_str _v2680 = _v2647(_v2579, _v537(_v909(_v1015, 0)));
        if (_v2631(_v2579, _v2680)) {
            return _v2591(_v2579, _v2632(_v2579, _v2680));
        }
    }
    if ((starts_with(_v1348, "__") && (!hashmap_contains(_v2579._v2551, ((bkr_i64)(intptr_t)_v1348))))) {
        return _v2681(_v2579, _v1348, _v1015);
    }
    if ((((bkr_str_eq(_v1348, "Ok") || bkr_str_eq(_v1348, "Err")) && (_v2679 == 1)) && (!hashmap_contains(_v2579._v2551, ((bkr_i64)(intptr_t)_v1348))))) {
        bkr_i64 _v2682 = vec_new();
        vec_push(_v2682, _v909(_v1015, 0));
        if (bkr_str_eq(_v1348, "Ok")) {
            return _v2665(_v2579, "rt_result_ok", _v2682);
        }
        return _v2665(_v2579, "rt_result_err", _v2682);
    }
    if ((bkr_str_eq(_v1348, "Some") && (_v2679 == 1))) {
        _v2657(_v2579, _v909(_v1015, 0));
        _v2586(_v2579, 72, 209, 224);
        _v2586(_v2579, 72, 131, 200);
        return _v2583(_v2579, 1);
    }
    if (hashmap_contains(_v2579._v2557, ((bkr_i64)(intptr_t)_v1348))) {
        bkr_i64 _v2604 = _v2634(_v2579, _v1348);
        bkr_i64 _v361 = _v2617(_v2579, _v2604);
        bkr_i64 _v1168 = 0;
        while ((_v1168 < _v2679)) {
            bkr_i64 _v2654 = _v2639(_v2579, _v1348, _v1168);
            if ((_v2654 < 0)) {
                return _v2581(_v2579, bkr_str_concat("too many fields for ", _v1348));
            }
            _v2683(_v2579, _v361, _v2654, _v909(_v1015, _v1168));
            _v1168 = (_v1168 + 1);
        }
        return _v2594(_v2579, _v361);
    }
    bkr_i64 _v2664 = vec_new();
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v2679)) {
        vec_push(_v2664, _v909(_v1015, _v1168));
        _v1168 = (_v1168 + 1);
    }
    if ((((!hashmap_contains(_v2579._v2551, ((bkr_i64)(intptr_t)_v1348))) && (_v2679 >= 2)) && (bkr_str_eq(_v1348, "hashmap_insert") || bkr_str_eq(_v1348, "vec_contains")))) {
        bkr_str _v2684 = _v2647(_v2579, _v537(_v909(_v1015, 1)));
        if (_v2628(_v2579, _v2684)) {
            return _v2665(_v2579, bkr_str_concat(bkr_str_concat("rt_", _v1348), "_str"), _v2664);
        }
    }
    return _v2665(_v2579, _v1348, _v2664);
}

bkr_bool _v2665(_v2548 _v2579, bkr_str _v2685, bkr_i64 _v2664) {
    bkr_str _v1348 = _v2685;
    if ((!hashmap_contains(_v2579._v2551, ((bkr_i64)(intptr_t)_v1348)))) {
        if (bkr_str_eq(_v1348, "strlen")) {
            _v1348 = "rt_strlen";
        } else {
            _v1348 = bkr_str_concat("rt_", _v2685);
        }
    }
    if ((!hashmap_contains(_v2579._v2551, ((bkr_i64)(intptr_t)_v1348)))) {
        return _v2581(_v2579, bkr_str_concat("unsupported call to builtin or unknown function: ", _v2685));
    }
    bkr_i64 _v2686 = hashmap_get(_v2579._v2551, ((bkr_i64)(intptr_t)_v1348));
    if ((_v2686 != vec_len(_v2664))) {
        return _v2581(_v2579, bkr_str_concat("wrong number of arguments to ", _v2685));
    }
    bkr_i64 _v2679 = vec_len(_v2664);
    bkr_str _v2687 = _v2648(_v2579, _v1348);
    bkr_i64 _v2688 = 0;
    if (_v2627(_v2579, _v2687)) {
        _v2688 = 1;
    }
    bkr_i64 _v2689 = vec_new();
    if ((_v2688 == 1)) {
        bkr_i64 _v2690 = _v2617(_v2579, 1);
        _v2594(_v2579, _v2617(_v2579, _v2634(_v2579, _v2687)));
        _v2593(_v2579, _v2690);
        vec_push(_v2689, _v2690);
    }
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v2679)) {
        _v2657(_v2579, vec_get(_v2664, _v1168));
        bkr_i64 _v2669 = _v2617(_v2579, 1);
        _v2593(_v2579, _v2669);
        vec_push(_v2689, _v2669);
        _v1168 = (_v1168 + 1);
    }
    bkr_i64 _v2428 = vec_len(_v2689);
    bkr_i64 _v2691 = 0;
    bkr_i64 _v573 = (_v2428 - 1);
    while ((_v573 >= 6)) {
        _v2585(_v2579, 255, 181);
        _v2587(_v2579, (0 - vec_get(_v2689, _v573)));
        _v2691 = (_v2691 + 1);
        _v573 = (_v573 - 1);
    }
    bkr_i64 _v2292 = 0;
    while (((_v2292 < _v2428) && (_v2292 < 6))) {
        _v2692(_v2579, _v2292, vec_get(_v2689, _v2292));
        _v2292 = (_v2292 + 1);
    }
    _v2583(_v2579, 232);
    vec_push(_v2579._v2552, _v2582(_v2579));
    vec_push(_v2579._v2553, ((bkr_i64)(intptr_t)_v1348));
    _v2587(_v2579, 0);
    if ((_v2691 > 0)) {
        _v2586(_v2579, 72, 129, 196);
        _v2587(_v2579, (8 * _v2691));
    }
    return BKR_TRUE;
}

bkr_bool _v2692(_v2548 _v2579, bkr_i64 _v2693, bkr_i64 _v1274) {
    if ((_v2693 == 0)) {
        _v2586(_v2579, 72, 139, 189);
    }
    if ((_v2693 == 1)) {
        _v2586(_v2579, 72, 139, 181);
    }
    if ((_v2693 == 2)) {
        _v2586(_v2579, 72, 139, 149);
    }
    if ((_v2693 == 3)) {
        _v2586(_v2579, 72, 139, 141);
    }
    if ((_v2693 == 4)) {
        _v2586(_v2579, 76, 139, 133);
    }
    if ((_v2693 == 5)) {
        _v2586(_v2579, 76, 139, 141);
    }
    return _v2587(_v2579, (0 - _v1274));
}

bkr_bool _v2681(_v2548 _v2579, bkr_str _v1348, _v434 _v1015) {
    bkr_i64 _v2679 = _v906(_v1015);
    if ((bkr_str_eq(_v1348, "__globals") && (_v2679 == 0))) {
        return _v2591(_v2579, _v2575);
    }
    if (((bkr_str_eq(_v1348, "__syscall") && (_v2679 >= 1)) && (_v2679 <= 7))) {
        bkr_i64 _v1168 = 0;
        while ((_v1168 < _v2679)) {
            _v2657(_v2579, _v909(_v1015, _v1168));
            _v2606(_v2579);
            _v1168 = (_v1168 + 1);
        }
        bkr_i64 _v2292 = (_v2679 - 1);
        while ((_v2292 >= 0)) {
            if ((_v2292 == 0)) {
                _v2583(_v2579, 88);
            }
            if ((_v2292 == 1)) {
                _v2583(_v2579, 95);
            }
            if ((_v2292 == 2)) {
                _v2583(_v2579, 94);
            }
            if ((_v2292 == 3)) {
                _v2583(_v2579, 90);
            }
            if ((_v2292 == 4)) {
                _v2585(_v2579, 65, 90);
            }
            if ((_v2292 == 5)) {
                _v2585(_v2579, 65, 88);
            }
            if ((_v2292 == 6)) {
                _v2585(_v2579, 65, 89);
            }
            _v2292 = (_v2292 - 1);
        }
        return _v2585(_v2579, 15, 5);
    }
    if (((bkr_str_eq(_v1348, "__load8") || bkr_str_eq(_v1348, "__load64")) && (_v2679 == 1))) {
        _v2657(_v2579, _v909(_v1015, 0));
        if (bkr_str_eq(_v1348, "__load8")) {
            _v2585(_v2579, 72, 15);
            return _v2585(_v2579, 182, 0);
        }
        return _v2586(_v2579, 72, 139, 0);
    }
    if (((bkr_str_eq(_v1348, "__store8") || bkr_str_eq(_v1348, "__store64")) && (_v2679 == 2))) {
        _v2657(_v2579, _v909(_v1015, 0));
        _v2606(_v2579);
        _v2657(_v2579, _v909(_v1015, 1));
        _v2608(_v2579);
        if (bkr_str_eq(_v1348, "__store8")) {
            return _v2585(_v2579, 136, 1);
        }
        return _v2586(_v2579, 72, 137, 1);
    }
    return _v2581(_v2579, bkr_str_concat("unknown intrinsic: ", _v1348));
}

bkr_bool _v2694(_v2548 _v2579, bkr_i64 _v2693) {
    if ((_v2693 == 0)) {
        return _v2583(_v2579, 95);
    }
    if ((_v2693 == 1)) {
        return _v2583(_v2579, 94);
    }
    if ((_v2693 == 2)) {
        return _v2583(_v2579, 90);
    }
    if ((_v2693 == 3)) {
        return _v2583(_v2579, 89);
    }
    if ((_v2693 == 4)) {
        return _v2585(_v2579, 65, 88);
    }
    return _v2585(_v2579, 65, 89);
}

bkr_bool _v2683(_v2548 _v2579, bkr_i64 _v361, bkr_i64 _v2654, bkr_i64 _v2659) {
    bkr_i64 _v2695 = (_v361 - (8 * vec_get(_v2579._v2561, _v2654)));
    bkr_str _v2644 = (bkr_str)(intptr_t)(vec_get(_v2579._v2560, _v2654));
    _v2657(_v2579, _v2659);
    if (_v2627(_v2579, _v2644)) {
        _v2595(_v2579, _v2695);
        return _v2603(_v2579, _v2634(_v2579, _v2644));
    }
    return _v2593(_v2579, _v2695);
}

bkr_bool _v2667(_v2548 _v2579, _v426 _v541) {
    bkr_str _v1348 = _v2578(_v2579, _v724(_v541));
    if ((!hashmap_contains(_v2579._v2557, ((bkr_i64)(intptr_t)_v1348)))) {
        return _v2581(_v2579, bkr_str_concat("unknown struct: ", _v1348));
    }
    bkr_i64 _v2604 = _v2634(_v2579, _v1348);
    bkr_i64 _v361 = _v2617(_v2579, _v2604);
    bkr_i64 _v403 = _v1005(_v541);
    if (_v525(_v403)) {
        _v2657(_v2579, _v403);
        _v2595(_v2579, _v361);
        _v2603(_v2579, _v2604);
    }
    _v435 _v1185 = _v727(_v541);
    _v434 _v614 = _v730(_v541);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v915(_v1185))) {
        bkr_str _v1150 = _v2578(_v2579, _v917(_v1185, _v1168));
        bkr_i64 _v2654 = _v2638(_v2579, _v1348, _v1150);
        if ((_v2654 < 0)) {
            return _v2581(_v2579, bkr_str_concat(bkr_str_concat(bkr_str_concat("unknown field ", _v1348), "."), _v1150));
        }
        _v2683(_v2579, _v361, _v2654, _v909(_v614, _v1168));
        _v1168 = (_v1168 + 1);
    }
    return _v2594(_v2579, _v361);
}

bkr_bool _v2674(_v2548 _v2579, _v429 _v582) {
    bkr_i64 _v2625 = _v2623(_v2579);
    bkr_i64 _v399 = _v589(_v582);
    bkr_bool _v2696 = BKR_FALSE;
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v399)) {
        _v427 _v553 = _v1107(_v582, _v1168);
        if (((_v1168 == (_v399 - 1)) && (_v555(_v553) == _v232))) {
            _v2657(_v2579, _v860(_v553));
            _v2696 = BKR_TRUE;
        } else {
            _v2697(_v2579, _v553);
        }
        _v1168 = (_v1168 + 1);
    }
    if ((!_v2696)) {
        _v2591(_v2579, 0);
    }
    return _v2624(_v2579, _v2625);
}

bkr_bool _v2698(_v2548 _v2579, bkr_i64 _v342) {
    if ((_v509(_v506(_v342)) == _v227)) {
        return _v2674(_v2579, _v578(_v342));
    }
    return _v2657(_v2579, _v342);
}

bkr_i64 _v2699(_v2548 _v2579, _v433 _v472) {
    bkr_str _v1826 = bkr_str_concat(bkr_str_concat(_v2578(_v2579, _v597(_v472)), "."), _v2578(_v2579, _v598(_v472)));
    if ((!hashmap_contains(_v2579._v2563, ((bkr_i64)(intptr_t)_v1826)))) {
        _v2581(_v2579, bkr_str_concat("unknown enum variant in pattern: ", _v1826));
        return (-1);
    }
    bkr_i64 _v1674 = hashmap_get(_v2579._v2563, ((bkr_i64)(intptr_t)_v1826));
    return _v1674;
}

bkr_i64 _v2700(_v2548 _v2579, bkr_i64 _v2669, bkr_i64 _v2601, bkr_i64 _v2701) {
    _v2592(_v2579, _v2669);
    if ((_v2601 > 0)) {
        _v2600(_v2579, _v2601);
    }
    if ((_v2701 > 0)) {
        _v2602(_v2579, _v2701);
    }
    bkr_i64 _v2702 = _v2617(_v2579, 1);
    _v2593(_v2579, _v2702);
    return _v2702;
}

bkr_bool _v2703(_v2548 _v2579, _v433 _v472, bkr_i64 _v2669, bkr_i64 _v2704) {
    bkr_i64 _v319 = _v596(_v472);
    bkr_i64 _v387 = _v597(_v472);
    if (((_v319 == _v285) || (_v319 == _v286))) {
        return BKR_TRUE;
    }
    if (((_v319 == _v283) || (_v319 == _v284))) {
        _v2592(_v2579, _v2669);
        bkr_i64 _v1264 = _v387;
        if (((_v319 == _v284) && (_v387 != 0))) {
            _v1264 = 1;
        }
        _v2599(_v2579, _v1264);
        vec_push(_v2704, _v2605(_v2579));
        return BKR_TRUE;
    }
    if ((_v319 == _v288)) {
        _v2592(_v2579, _v2669);
        vec_push(_v2704, _v2614(_v2579));
        return BKR_TRUE;
    }
    if ((_v319 == _v287)) {
        _v2592(_v2579, _v2669);
        _v2602(_v2579, 1);
        vec_push(_v2704, _v2613(_v2579));
        bkr_i64 _v345 = _v598(_v472);
        if ((_v345 != 0)) {
            bkr_i64 _v1999 = _v2700(_v2579, _v2669, 1, 0);
            return _v2703(_v2579, _v591(_v345), _v1999, _v2704);
        }
        return BKR_TRUE;
    }
    if (((_v319 == _v290) || (_v319 == _v291))) {
        _v2592(_v2579, _v2669);
        _v2586(_v2579, 72, 139, 0);
        if ((_v319 == _v290)) {
            _v2599(_v2579, 0);
        } else {
            _v2599(_v2579, 1);
        }
        vec_push(_v2704, _v2605(_v2579));
        bkr_i64 _v345 = _v598(_v472);
        if ((_v345 != 0)) {
            bkr_i64 _v1999 = _v2705(_v2579, _v2669);
            return _v2703(_v2579, _v591(_v345), _v1999, _v2704);
        }
        return BKR_TRUE;
    }
    if ((_v319 == _v289)) {
        bkr_i64 _v1674 = _v2699(_v2579, _v472);
        _v2592(_v2579, _v2669);
        if ((_v599(_v472) >= 0)) {
            _v2602(_v2579, 255);
        }
        _v2599(_v2579, _v1674);
        vec_push(_v2704, _v2605(_v2579));
        return BKR_TRUE;
    }
    return _v2581(_v2579, bkr_str_concat("unsupported match pattern kind ", int_to_string(_v319)));
}

bkr_i64 _v2705(_v2548 _v2579, bkr_i64 _v2669) {
    _v2592(_v2579, _v2669);
    _v2597(_v2579, 1);
    bkr_i64 _v2702 = _v2617(_v2579, 1);
    _v2593(_v2579, _v2702);
    return _v2702;
}

bkr_bool _v2706(_v2548 _v2579, bkr_i64 _v355, bkr_i64 _v2669, bkr_i64 _v2601, bkr_i64 _v2701, bkr_str _v1663) {
    bkr_i64 _v2702 = _v2700(_v2579, _v2669, _v2601, _v2701);
    _v2618(_v2579, _v2578(_v2579, _v355), _v2702, _v1663);
    return BKR_TRUE;
}

bkr_bool _v2707(_v2548 _v2579, _v433 _v472, bkr_i64 _v2669, bkr_str _v1663) {
    bkr_i64 _v319 = _v596(_v472);
    bkr_i64 _v387 = _v597(_v472);
    if ((_v319 == _v285)) {
        return _v2706(_v2579, _v387, _v2669, 0, 0, _v1663);
    }
    if ((_v319 == _v287)) {
        bkr_str _v2708 = _v2630(_v1663, "$opt:", 0);
        if ((_v387 >= 0)) {
            _v2706(_v2579, _v387, _v2669, 1, 0, _v2708);
        }
        bkr_i64 _v345 = _v598(_v472);
        if ((_v345 != 0)) {
            bkr_i64 _v1999 = _v2700(_v2579, _v2669, 1, 0);
            return _v2707(_v2579, _v591(_v345), _v1999, _v2708);
        }
        return BKR_TRUE;
    }
    if (((_v319 == _v290) || (_v319 == _v291))) {
        bkr_i64 _v2709 = 0;
        if ((_v319 == _v291)) {
            _v2709 = 1;
        }
        bkr_str _v2708 = _v2630(_v1663, "$res:", _v2709);
        bkr_i64 _v1999 = _v2705(_v2579, _v2669);
        if ((_v387 >= 0)) {
            _v2618(_v2579, _v2578(_v2579, _v387), _v1999, _v2708);
        }
        bkr_i64 _v345 = _v598(_v472);
        if ((_v345 != 0)) {
            return _v2707(_v2579, _v591(_v345), _v1999, _v2708);
        }
        return BKR_TRUE;
    }
    if ((_v319 == _v289)) {
        bkr_i64 _v431 = _v599(_v472);
        bkr_i64 _v432 = _v600(_v472);
        if (((_v431 >= 0) && (_v432 >= 0))) {
            _v2706(_v2579, _v431, _v2669, 20, 0, "");
            return _v2706(_v2579, _v432, _v2669, 8, 4095, "");
        }
        if ((_v431 >= 0)) {
            return _v2706(_v2579, _v431, _v2669, 8, 0, "");
        }
    }
    return BKR_TRUE;
}

bkr_bool _v2673(_v2548 _v2579, _v426 _v541) {
    _v426 _v974 = _v537(_v742(_v541));
    if (_v2627(_v2579, _v2647(_v2579, _v974))) {
        return _v2581(_v2579, "match on struct values is not supported");
    }
    bkr_str _v2710 = _v2647(_v2579, _v974);
    _v2658(_v2579, _v974);
    bkr_i64 _v2669 = _v2617(_v2579, 1);
    _v2593(_v2579, _v2669);
    _v436 _v620 = _v745(_v541);
    _v434 _v975 = _v748(_v541);
    _v435 _v976 = _v750(_v541);
    bkr_i64 _v2711 = vec_new();
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v919(_v620))) {
        bkr_i64 _v2625 = _v2623(_v2579);
        _v433 _v472 = _v924(_v620, _v1168);
        bkr_i64 _v2704 = vec_new();
        _v2703(_v2579, _v472, _v2669, _v2704);
        _v2707(_v2579, _v472, _v2669, _v2710);
        if ((_v1168 < _v915(_v976))) {
            bkr_i64 _v2712 = _v917(_v976, _v1168);
            if ((_v2712 != 0)) {
                _v2657(_v2579, _v2712);
                vec_push(_v2704, _v2613(_v2579));
            }
        }
        _v2698(_v2579, _v909(_v975, _v1168));
        vec_push(_v2711, _v2612(_v2579));
        bkr_i64 _v1215 = _v2582(_v2579);
        bkr_i64 _v1629 = 0;
        while ((_v1629 < vec_len(_v2704))) {
            _v2590(_v2579, vec_get(_v2704, _v1629), _v1215);
            _v1629 = (_v1629 + 1);
        }
        _v2624(_v2579, _v2625);
        _v1168 = (_v1168 + 1);
    }
    _v2591(_v2579, 0);
    bkr_i64 _v340 = _v2582(_v2579);
    bkr_i64 _v573 = 0;
    while ((_v573 < vec_len(_v2711))) {
        _v2590(_v2579, vec_get(_v2711, _v573), _v340);
        _v573 = (_v573 + 1);
    }
    return BKR_TRUE;
}

bkr_bool _v2713(_v2548 _v2579, _v429 _v582) {
    bkr_i64 _v2625 = _v2623(_v2579);
    bkr_i64 _v1168 = 0;
    bkr_i64 _v399 = _v589(_v582);
    while ((_v1168 < _v399)) {
        _v2697(_v2579, _v1107(_v582, _v1168));
        _v1168 = (_v1168 + 1);
    }
    return _v2624(_v2579, _v2625);
}

bkr_bool _v2714(_v2548 _v2579, bkr_i64 _v342, bkr_str _v1348) {
    _v426 _v541 = _v537(_v342);
    if ((_v544(_v541) != _v244)) {
        return BKR_FALSE;
    }
    return (bkr_str_eq(_v2578(_v2579, _v688(_v541)), _v1348) && (!hashmap_contains(_v2579._v2551, ((bkr_i64)(intptr_t)_v1348))));
}

bkr_i64 _v2715(_v2548 _v2579) {
    bkr_i64 _v1605 = vec_get(_v2579._v2573, 2);
    vec_set(_v2579._v2573, 2, (_v1605 + 1));
    vec_push(_v2579._v2572, _v1605);
    return _v1605;
}

bkr_bool _v2716(_v2548 _v2579, bkr_i64 _v2717, bkr_i64 _v2718, bkr_i64 _v1605, bkr_i64 _v386) {
    bkr_i64 _v1168 = 0;
    while ((_v1168 < vec_len(_v2717))) {
        if ((vec_get(_v2718, _v1168) == _v1605)) {
            _v2590(_v2579, vec_get(_v2717, _v1168), _v386);
            vec_set(_v2718, _v1168, (-1));
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_TRUE;
}

bkr_bool _v2719(_v2548 _v2579, bkr_i64 _v1605, bkr_i64 _v2720, bkr_i64 _v2721) {
    _v2716(_v2579, _v2579._v2570, _v2579._v2571, _v1605, _v2720);
    _v2716(_v2579, _v2579._v2568, _v2579._v2569, _v1605, _v2721);
    vec_pop(_v2579._v2572);
    return BKR_TRUE;
}

bkr_i64 _v2722(_v2548 _v2579) {
    if ((vec_len(_v2579._v2572) == 0)) {
        return (-1);
    }
    return vec_get(_v2579._v2572, (vec_len(_v2579._v2572) - 1));
}

bkr_bool _v2697(_v2548 _v2579, _v427 _v553) {
    bkr_i64 _v319 = _v555(_v553);
    if ((_v319 == _v228)) {
        bkr_str _v1348 = _v2578(_v2579, _v757(_v553));
        bkr_i64 _v366 = _v763(_v553);
        bkr_str _v1663 = _v2637(_v2579, _v760(_v553));
        if (((bkr_len((bkr_str)(intptr_t)(_v1663)) == 0) && _v525(_v366))) {
            _v1663 = _v2647(_v2579, _v537(_v366));
        }
        if (((_v525(_v366) && starts_with(_v1663, "$map:s")) && _v2714(_v2579, _v366, "hashmap_new"))) {
            _v2665(_v2579, "rt_hashmap_new_str", vec_new());
        } else {
            if (_v525(_v366)) {
                _v2657(_v2579, _v366);
            } else {
                _v2591(_v2579, 0);
            }
        }
        if (_v2627(_v2579, _v1663)) {
            bkr_i64 _v2604 = _v2634(_v2579, _v1663);
            bkr_i64 _v577 = _v2617(_v2579, _v2604);
            if (_v525(_v366)) {
                _v2595(_v2579, _v577);
                _v2603(_v2579, _v2604);
            }
            _v2618(_v2579, _v1348, _v577, _v1663);
            return BKR_TRUE;
        }
        bkr_i64 _v1274 = _v2618(_v2579, _v1348, _v2617(_v2579, 1), _v1663);
        return _v2593(_v2579, _v1274);
    }
    if ((_v319 == _v233)) {
        _v426 _v1094 = _v537(_v854(_v553));
        bkr_i64 _v2659 = _v857(_v553);
        bkr_i64 _v1787 = _v544(_v1094);
        if ((_v1787 == _v256)) {
            _v426 _v1037 = _v720(_v1094);
            bkr_str _v2653 = _v2647(_v2579, _v1037);
            bkr_str _v1150 = _v2578(_v2579, _v722(_v1094));
            bkr_i64 _v2654 = _v2638(_v2579, _v2653, _v1150);
            if (((!_v2627(_v2579, _v2653)) || (_v2654 < 0))) {
                return _v2581(_v2579, bkr_str_concat("assignment to unknown field .", _v1150));
            }
            _v2658(_v2579, _v1037);
            _v2598(_v2579, (vec_get(_v2579._v2561, _v2654) * 8));
            _v2606(_v2579);
            _v2657(_v2579, _v2659);
            bkr_str _v2644 = (bkr_str)(intptr_t)(vec_get(_v2579._v2560, _v2654));
            if (_v2627(_v2579, _v2644)) {
                _v2583(_v2579, 90);
                return _v2603(_v2579, _v2634(_v2579, _v2644));
            }
            _v2608(_v2579);
            return _v2586(_v2579, 72, 137, 1);
        }
        if ((_v1787 == _v253)) {
            bkr_str _v2656 = _v2647(_v2579, _v1094);
            if ((!_v2672(_v2579, _v1094))) {
                return BKR_FALSE;
            }
            _v2606(_v2579);
            _v2657(_v2579, _v2659);
            if (_v2627(_v2579, _v2656)) {
                _v2583(_v2579, 90);
                return _v2603(_v2579, _v2634(_v2579, _v2656));
            }
            _v2608(_v2579);
            return _v2586(_v2579, 72, 137, 1);
        }
        if ((_v1787 != _v245)) {
            return _v2581(_v2579, "unsupported assignment target");
        }
        bkr_str _v1348 = _v2578(_v2579, _v662(_v1094));
        bkr_i64 _v1274 = _v2621(_v2579, _v1348);
        if ((_v1274 <= 0)) {
            return _v2581(_v2579, bkr_str_concat("assignment to unknown local: ", _v1348));
        }
        _v2657(_v2579, _v2659);
        bkr_str _v2723 = _v2622(_v2579, _v1348);
        if (_v2627(_v2579, _v2723)) {
            _v2595(_v2579, _v1274);
            return _v2603(_v2579, _v2634(_v2579, _v2723));
        }
        return _v2593(_v2579, _v1274);
    }
    if ((_v319 == _v229)) {
        bkr_i64 _v368 = _v768(_v553);
        if (_v525(_v368)) {
            _v2657(_v2579, _v368);
        } else {
            _v2591(_v2579, 0);
        }
        bkr_str _v2687 = (bkr_str)(intptr_t)(vec_get(_v2579._v2564, 0));
        if (_v2627(_v2579, _v2687)) {
            _v2596(_v2579, vec_get(_v2579._v2573, 3));
            _v2603(_v2579, _v2634(_v2579, _v2687));
            _v2586(_v2579, 72, 137, 208);
        }
        return _v2616(_v2579);
    }
    if ((_v319 == _v232)) {
        return _v2657(_v2579, _v860(_v553));
    }
    if ((_v319 == _v230)) {
        _v2657(_v2579, _v827(_v553));
        bkr_i64 _v2661 = _v2613(_v2579);
        _v2713(_v2579, _v829(_v553));
        bkr_i64 _v2724 = _v832(_v553);
        if (_v525(_v2724)) {
            bkr_i64 _v2662 = _v2612(_v2579);
            _v2590(_v2579, _v2661, _v2582(_v2579));
            _v2713(_v2579, _v578(_v2724));
            return _v2590(_v2579, _v2662, _v2582(_v2579));
        }
        return _v2590(_v2579, _v2661, _v2582(_v2579));
    }
    if ((_v319 == _v231)) {
        bkr_i64 _v1605 = _v2715(_v2579);
        bkr_i64 _v2670 = _v2582(_v2579);
        _v2657(_v2579, _v849(_v553));
        bkr_i64 _v2662 = _v2613(_v2579);
        _v2713(_v2579, _v851(_v553));
        _v2615(_v2579, _v2670);
        bkr_i64 _v340 = _v2582(_v2579);
        _v2590(_v2579, _v2662, _v340);
        return _v2719(_v2579, _v1605, _v2670, _v340);
    }
    if ((_v319 == _v237)) {
        bkr_i64 _v1605 = _v2715(_v2579);
        bkr_i64 _v2670 = _v2582(_v2579);
        _v2713(_v2579, _v846(_v553));
        _v2615(_v2579, _v2670);
        return _v2719(_v2579, _v1605, _v2670, _v2582(_v2579));
    }
    if ((_v319 == _v236)) {
        bkr_i64 _v2625 = _v2623(_v2579);
        bkr_str _v1348 = _v2578(_v2579, _v834(_v553));
        _v2657(_v2579, _v840(_v553));
        bkr_i64 _v2725 = _v2619(_v2579, "$for_end");
        _v2593(_v2579, _v2725);
        _v2657(_v2579, _v837(_v553));
        bkr_i64 _v2726 = _v2619(_v2579, _v1348);
        _v2593(_v2579, _v2726);
        bkr_i64 _v1605 = _v2715(_v2579);
        bkr_i64 _v2670 = _v2582(_v2579);
        _v2592(_v2579, _v2726);
        _v2586(_v2579, 72, 139, 141);
        _v2587(_v2579, (0 - _v2725));
        _v2586(_v2579, 72, 57, 200);
        if ((_v842(_v553) != 0)) {
            _v2585(_v2579, 15, 143);
        } else {
            _v2585(_v2579, 15, 141);
        }
        bkr_i64 _v2662 = _v2582(_v2579);
        _v2587(_v2579, 0);
        _v2713(_v2579, _v844(_v553));
        bkr_i64 _v2727 = _v2582(_v2579);
        _v2592(_v2579, _v2726);
        _v2586(_v2579, 72, 131, 192);
        _v2583(_v2579, 1);
        _v2593(_v2579, _v2726);
        _v2615(_v2579, _v2670);
        bkr_i64 _v340 = _v2582(_v2579);
        _v2590(_v2579, _v2662, _v340);
        _v2719(_v2579, _v1605, _v2727, _v340);
        return _v2624(_v2579, _v2625);
    }
    if (((_v319 == _v234) || (_v319 == _v235))) {
        bkr_i64 _v1605 = _v2722(_v2579);
        if ((_v1605 < 0)) {
            return _v2581(_v2579, "break or continue outside a loop");
        }
        bkr_i64 _v1210 = _v2612(_v2579);
        if ((_v319 == _v234)) {
            vec_push(_v2579._v2568, _v1210);
            vec_push(_v2579._v2569, _v1605);
        } else {
            vec_push(_v2579._v2570, _v1210);
            vec_push(_v2579._v2571, _v1605);
        }
        return BKR_TRUE;
    }
    if ((_v319 == _v227)) {
        return _v2713(_v2579, _v578(_v552(_v553)));
    }
    return _v2581(_v2579, bkr_str_concat("unsupported statement: ", _v2580(_v319)));
}

bkr_bool _v2728(_v2548 _v2579, bkr_i64 _v2693, bkr_i64 _v1274) {
    if ((_v2693 == 0)) {
        _v2586(_v2579, 72, 137, 189);
    }
    if ((_v2693 == 1)) {
        _v2586(_v2579, 72, 137, 181);
    }
    if ((_v2693 == 2)) {
        _v2586(_v2579, 72, 137, 149);
    }
    if ((_v2693 == 3)) {
        _v2586(_v2579, 72, 137, 141);
    }
    if ((_v2693 == 4)) {
        _v2586(_v2579, 76, 137, 133);
    }
    if ((_v2693 == 5)) {
        _v2586(_v2579, 76, 137, 141);
    }
    return _v2587(_v2579, (0 - _v1274));
}

bkr_str _v2729(_v2548 _v2579, bkr_str _v2023, _v341 _v1507) {
    bkr_str _v1663 = _v2637(_v2579, _v865(_v1507));
    if (((bkr_len((bkr_str)(intptr_t)(_v1663)) == 0) && bkr_str_eq(_v2578(_v2579, _v862(_v1507)), "self"))) {
        bkr_i64 _v2730 = bkr_str_index_of((bkr_str)(intptr_t)(_v2023), (bkr_str)(intptr_t)("::"));
        if ((_v2730 > 0)) {
            bkr_str _v2731 = substring(_v2023, 0, _v2730);
            if (hashmap_contains(_v2579._v2557, ((bkr_i64)(intptr_t)_v2731))) {
                return _v2731;
            }
        }
    }
    return _v1663;
}

bkr_bool _v2732(_v2548 _v2579, _v428 _v1514) {
    bkr_str _v1348 = _v2578(_v2579, _v868(_v1514));
    hashmap_insert_str(_v2579._v2550, ((bkr_i64)(intptr_t)_v1348), _v2582(_v2579));
    vec_set(_v2579._v2573, 0, 0);
    vec_set(_v2579._v2573, 1, 0);
    _v2624(_v2579, 0);
    _v2583(_v2579, 85);
    _v2586(_v2579, 72, 137, 229);
    _v2586(_v2579, 72, 129, 236);
    bkr_i64 _v2733 = _v2582(_v2579);
    _v2587(_v2579, 0);
    bkr_str _v2687 = _v2648(_v2579, _v1348);
    vec_set(_v2579._v2564, 0, ((bkr_i64)(intptr_t)_v2687));
    bkr_i64 _v2688 = 0;
    vec_set(_v2579._v2573, 3, 0);
    if (_v2627(_v2579, _v2687)) {
        _v2688 = 1;
        bkr_i64 _v2690 = _v2617(_v2579, 1);
        vec_set(_v2579._v2573, 3, _v2690);
        _v2728(_v2579, 0, _v2690);
    }
    _v434 _v1141 = _v871(_v1514);
    bkr_i64 _v399 = _v906(_v1141);
    bkr_i64 _v2734 = vec_new();
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v399)) {
        bkr_i64 _v2669 = _v2617(_v2579, 1);
        bkr_i64 _v2693 = (_v1168 + _v2688);
        if ((_v2693 < 6)) {
            _v2728(_v2579, _v2693, _v2669);
        } else {
            _v2586(_v2579, 72, 139, 133);
            _v2587(_v2579, (16 + (8 * (_v2693 - 6))));
            _v2593(_v2579, _v2669);
        }
        vec_push(_v2734, _v2669);
        _v1168 = (_v1168 + 1);
    }
    _v1168 = 0;
    while ((_v1168 < _v399)) {
        _v341 _v1507 = _v912(_v1141, _v1168);
        bkr_str _v1506 = _v2578(_v2579, _v862(_v1507));
        bkr_str _v2735 = _v2729(_v2579, _v1348, _v1507);
        bkr_i64 _v2669 = vec_get(_v2734, _v1168);
        if (_v2627(_v2579, _v2735)) {
            bkr_i64 _v2604 = _v2634(_v2579, _v2735);
            bkr_i64 _v577 = _v2617(_v2579, _v2604);
            _v2592(_v2579, _v2669);
            _v2595(_v2579, _v577);
            _v2603(_v2579, _v2604);
            _v2618(_v2579, _v1506, _v577, _v2735);
        } else {
            _v2618(_v2579, _v1506, _v2669, _v2735);
        }
        _v1168 = (_v1168 + 1);
    }
    _v2713(_v2579, _v876(_v1514));
    _v2591(_v2579, 0);
    _v2616(_v2579);
    bkr_i64 _v2736 = vec_get(_v2579._v2573, 1);
    _v2736 = (((_v2736 + 15) / 16) * 16);
    return _v2589(_v2579, _v2733, _v2736);
}

_v2548 _v2737(_v341 _v1530) {
    _v2548 _v2579 = _v2577(_v903(_v1530));
    _v434 _v1183 = _v898(_v1530);
    bkr_i64 _v2738 = _v906(_v1183);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < _v2738)) {
        _v428 _v562 = _v913(_v1183, _v1168);
        bkr_i64 _v1810 = _v568(_v562);
        if ((_v1810 == _v254)) {
            hashmap_insert_str(_v2579._v2557, ((bkr_i64)(intptr_t)_v2578(_v2579, _v886(_v562))), 1);
        } else {
            if ((_v1810 == _v259)) {
                bkr_str _v1626 = _v2578(_v2579, _v1164(_v562));
                hashmap_insert_str(_v2579._v2562, ((bkr_i64)(intptr_t)_v1626), 1);
                _v435 _v1162 = _v1165(_v562);
                bkr_i64 _v1900 = 0;
                while ((_v1900 < _v915(_v1162))) {
                    hashmap_insert_str(_v2579._v2563, ((bkr_i64)(intptr_t)bkr_str_concat(bkr_str_concat(_v1626, "."), _v2578(_v2579, _v917(_v1162, _v1900)))), _v1900);
                    _v1900 = (_v1900 + 1);
                }
            }
        }
        _v1168 = (_v1168 + 1);
    }
    _v1168 = 0;
    while ((_v1168 < _v2738)) {
        _v428 _v562 = _v913(_v1183, _v1168);
        bkr_i64 _v1810 = _v568(_v562);
        if ((_v1810 == _v254)) {
            bkr_str _v1681 = _v2578(_v2579, _v886(_v562));
            _v434 _v1158 = _v889(_v562);
            bkr_i64 _v2654 = 0;
            while ((_v2654 < _v906(_v1158))) {
                _v341 _v1432 = _v912(_v1158, _v2654);
                vec_push(_v2579._v2558, ((bkr_i64)(intptr_t)_v1681));
                vec_push(_v2579._v2559, ((bkr_i64)(intptr_t)_v2578(_v2579, _v891(_v1432))));
                vec_push(_v2579._v2560, ((bkr_i64)(intptr_t)_v2635(_v2579, _v895(_v1432))));
                vec_push(_v2579._v2561, 0);
                _v2654 = (_v2654 + 1);
            }
        } else {
            if ((_v1810 == _v224)) {
                bkr_str _v2023 = _v2578(_v2579, _v868(_v562));
                if ((!hashmap_contains(_v2579._v2551, ((bkr_i64)(intptr_t)_v2023)))) {
                    hashmap_insert_str(_v2579._v2551, ((bkr_i64)(intptr_t)_v2023), _v906(_v871(_v562)));
                    hashmap_insert_str(_v2579._v2555, ((bkr_i64)(intptr_t)_v2023), ((bkr_i64)(intptr_t)_v2637(_v2579, _v874(_v562))));
                }
            } else {
                if ((_v1810 == _v249)) {
                    hashmap_insert_str(_v2579._v2567, ((bkr_i64)(intptr_t)_v2578(_v2579, _v878(_v562))), _v884(_v562));
                } else {
                    if ((_v1810 != _v259)) {
                        _v2581(_v2579, bkr_str_concat("unsupported top-level item: ", _v2580(_v1810)));
                    }
                }
            }
        }
        _v1168 = (_v1168 + 1);
    }
    bkr_i64 _v2739 = hashmap_keys(_v2579._v2557);
    bkr_i64 _v1887 = 0;
    while ((_v1887 < vec_len(_v2739))) {
        _v2642(_v2579, vec_get(_v2739, _v1887), 0);
        _v1887 = (_v1887 + 1);
    }
    bkr_str _v2741 = _v2578(_v2579, _v900(_v1530));
    if ((!hashmap_contains(_v2579._v2551, ((bkr_i64)(intptr_t)_v2741)))) {
        _v2581(_v2579, bkr_str_concat("missing entry function: ", _v2741));
        return _v2579;
    }
    _v2591(_v2579, _v2575);
    _v2586(_v2579, 72, 137, 32);
    _v2583(_v2579, 232);
    vec_push(_v2579._v2552, _v2582(_v2579));
    vec_push(_v2579._v2553, ((bkr_i64)(intptr_t)_v2741));
    _v2587(_v2579, 0);
    _v2586(_v2579, 72, 137, 199);
    _v2583(_v2579, 184);
    _v2587(_v2579, 60);
    _v2585(_v2579, 15, 5);
    _v1168 = 0;
    while ((_v1168 < _v2738)) {
        _v428 _v562 = _v913(_v1183, _v1168);
        if (((_v568(_v562) == _v224) && (!hashmap_contains(_v2579._v2550, ((bkr_i64)(intptr_t)_v2578(_v2579, _v868(_v562))))))) {
            _v2732(_v2579, _v562);
        }
        _v1168 = (_v1168 + 1);
    }
    bkr_i64 _v2654 = 0;
    while ((_v2654 < vec_len(_v2579._v2552))) {
        bkr_i64 _v386 = hashmap_get(_v2579._v2550, vec_get(_v2579._v2553, _v2654));
        _v2590(_v2579, vec_get(_v2579._v2552, _v2654), _v386);
        _v2654 = (_v2654 + 1);
    }
    bkr_i64 _v2742 = hashmap_new_str();
    bkr_i64 _v2743 = 0;
    while ((_v2743 < vec_len(_v2579._v2565))) {
        bkr_str _v1290 = (bkr_str)(intptr_t)(vec_get(_v2579._v2566, _v2743));
        if ((!hashmap_contains(_v2742, ((bkr_i64)(intptr_t)_v1290)))) {
            hashmap_insert_str(_v2742, ((bkr_i64)(intptr_t)_v1290), _v2582(_v2579));
            bkr_i64 _v1205 = 0;
            while ((_v1205 < bkr_len((bkr_str)(intptr_t)(_v1290)))) {
                _v2583(_v2579, char_code(char_at(_v1290, _v1205)));
                _v1205 = (_v1205 + 1);
            }
            _v2583(_v2579, 0);
        }
        bkr_i64 _v386 = hashmap_get(_v2742, ((bkr_i64)(intptr_t)_v1290));
        _v2590(_v2579, vec_get(_v2579._v2565, _v2743), _v386);
        _v2743 = (_v2743 + 1);
    }
    return _v2579;
}

bkr_bool _v2744(bkr_i64 _v1841, bkr_i64 _v387) {
    vec_push(_v1841, (_v387 & 255));
    vec_push(_v1841, ((_v387 >> 8) & 255));
    return BKR_TRUE;
}

bkr_bool _v2745(bkr_i64 _v1841, bkr_i64 _v387) {
    _v2744(_v1841, _v387);
    return _v2744(_v1841, (_v387 >> 16));
}

bkr_bool _v2746(bkr_i64 _v1841, bkr_i64 _v387) {
    _v2745(_v1841, _v387);
    return _v2745(_v1841, (_v387 >> 32));
}

bkr_i64 _v2747(bkr_i64 _v2103) {
    bkr_i64 _v1841 = vec_new();
    bkr_i64 _v2428 = (176 + vec_len(_v2103));
    vec_push(_v1841, 127);
    vec_push(_v1841, 69);
    vec_push(_v1841, 76);
    vec_push(_v1841, 70);
    vec_push(_v1841, 2);
    vec_push(_v1841, 1);
    vec_push(_v1841, 1);
    bkr_i64 _v2748 = 0;
    while ((_v2748 < 9)) {
        vec_push(_v1841, 0);
        _v2748 = (_v2748 + 1);
    }
    _v2744(_v1841, 2);
    _v2744(_v1841, 62);
    _v2745(_v1841, 1);
    _v2746(_v1841, _v2574);
    _v2746(_v1841, 64);
    _v2746(_v1841, 0);
    _v2745(_v1841, 0);
    _v2744(_v1841, 64);
    _v2744(_v1841, 56);
    _v2744(_v1841, 2);
    _v2744(_v1841, 0);
    _v2744(_v1841, 0);
    _v2744(_v1841, 0);
    _v2745(_v1841, 1);
    _v2745(_v1841, 5);
    _v2746(_v1841, 0);
    _v2746(_v1841, 4194304);
    _v2746(_v1841, 4194304);
    _v2746(_v1841, _v2428);
    _v2746(_v1841, _v2428);
    _v2746(_v1841, 4096);
    _v2745(_v1841, 1);
    _v2745(_v1841, 6);
    _v2746(_v1841, 0);
    _v2746(_v1841, _v2575);
    _v2746(_v1841, _v2575);
    _v2746(_v1841, 0);
    _v2746(_v1841, _v2576);
    _v2746(_v1841, 4096);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < vec_len(_v2103))) {
        vec_push(_v1841, vec_get(_v2103, _v1168));
        _v1168 = (_v1168 + 1);
    }
    return _v1841;
}

bkr_bool _v2749(bkr_str _v2750, bkr_i64 _v2751) {
    bkr_i64 _v2752 = bytes_new(vec_len(_v2751));
    bkr_i64 _v1168 = 0;
    while ((_v1168 < vec_len(_v2751))) {
        bytes_push(_v2752, ((bkr_i32)(vec_get(_v2751, _v1168))));
        _v1168 = (_v1168 + 1);
    }
    bkr_i64 _v1717 = file_write_bytes(_v2750, _v2752);
    if ((!bkr_result_is_ok(_v1717))) {
        return BKR_FALSE;
    }
    return file_set_executable(_v2750);
}

bkr_bool _v2759(bkr_str _v1582) {
    bkr_str _v2760 = trim(_v1582);
    bkr_i64 _v1887 = bkr_len((bkr_str)(intptr_t)(_v2760));
    if ((_v1887 < 11)) {
        return BKR_FALSE;
    }
    if ((!starts_with(_v2760, "import "))) {
        return BKR_FALSE;
    }
    if ((char_code_at(_v2760, 7) != 34)) {
        return BKR_FALSE;
    }
    if ((char_code_at(_v2760, (_v1887 - 2)) != 34)) {
        return BKR_FALSE;
    }
    if ((char_code_at(_v2760, (_v1887 - 1)) != 59)) {
        return BKR_FALSE;
    }
    return BKR_TRUE;
}

bkr_str _v2762(bkr_str _v1582) {
    bkr_str _v2760 = trim(_v1582);
    return substring(_v2760, 8, (bkr_len((bkr_str)(intptr_t)(_v2760)) - 2));
}

bkr_bool _v2763(bkr_str _v2764) {
    bkr_i64 _v1168 = 0;
    while ((_v1168 < bkr_len((bkr_str)(intptr_t)(_v2764)))) {
        if ((char_code_at(_v2764, _v1168) == 92)) {
            return BKR_TRUE;
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_FALSE;
}

bkr_bool _v2765(bkr_str _v2764) {
    if ((bkr_len((bkr_str)(intptr_t)(_v2764)) <= 0)) {
        return BKR_FALSE;
    }
    if ((char_code_at(_v2764, 0) == 47)) {
        return BKR_TRUE;
    }
    if ((char_code_at(_v2764, 0) == 92)) {
        return BKR_TRUE;
    }
    if (((bkr_len((bkr_str)(intptr_t)(_v2764)) >= 2) && (char_code_at(_v2764, 1) == 58))) {
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_bool _v2766(bkr_str _v2764) {
    if (bkr_str_eq(_v2764, "..")) {
        return BKR_TRUE;
    }
    if (starts_with(_v2764, "../")) {
        return BKR_TRUE;
    }
    if (ends_with(_v2764, "/..")) {
        return BKR_TRUE;
    }
    if (contains(_v2764, "/../")) {
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_bool _v2769(bkr_str _v2764) {
    if (starts_with(_v2764, "./")) {
        return BKR_TRUE;
    }
    if (ends_with(_v2764, "/")) {
        return BKR_TRUE;
    }
    if (contains(_v2764, "//")) {
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_bool _v2770(bkr_str _v2764) {
    if ((bkr_len((bkr_str)(intptr_t)(_v2764)) <= 0)) {
        return BKR_FALSE;
    }
    if (_v2765(_v2764)) {
        return BKR_FALSE;
    }
    if (_v2763(_v2764)) {
        return BKR_FALSE;
    }
    if (contains(_v2764, ":")) {
        return BKR_FALSE;
    }
    if (_v2766(_v2764)) {
        return BKR_FALSE;
    }
    if (_v2769(_v2764)) {
        return BKR_FALSE;
    }
    return BKR_TRUE;
}

bkr_str _v2771(bkr_str _v2772, bkr_str _v2764) {
    if ((bkr_len((bkr_str)(intptr_t)(_v2772)) <= 0)) {
        return _v2764;
    }
    return bkr_str_concat(bkr_str_concat(_v2772, "/"), _v2764);
}

bkr_str _v2773(bkr_str _v2774) {
    bkr_i64 _v2775 = (-1);
    bkr_i64 _v1168 = 0;
    while ((_v1168 < bkr_len((bkr_str)(intptr_t)(_v2774)))) {
        if (((char_code_at(_v2774, _v1168) == 47) || (char_code_at(_v2774, _v1168) == 92))) {
            _v2775 = _v1168;
        }
        _v1168 = (_v1168 + 1);
    }
    if ((_v2775 < 0)) {
        return "";
    }
    return substring(_v2774, 0, _v2775);
}

bkr_bool _v2776(bkr_i64 _v2641, bkr_str _v2764) {
    bkr_i64 _v1168 = 0;
    while ((_v1168 < vec_len(_v2641))) {
        if (bkr_str_eq(vec_get(_v2641, _v1168), _v2764)) {
            return BKR_TRUE;
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_FALSE;
}

bkr_str _v2777(bkr_str _v2778, bkr_str _v1582, bkr_i64 _v2641, bkr_str _v2772) {
    if (_v2759(_v1582)) {
        bkr_str _v2764 = _v2762(_v1582);
        if ((!_v2770(_v2764))) {
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2778, "// Invalid import path: "), _v2764), from_char_code(10));
        }
        bkr_str _v2774 = _v2771(_v2772, _v2764);
        if ((!file_exists(_v2774))) {
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2778, "// Missing import: "), _v2774), from_char_code(10));
        }
        if (_v2776(_v2641, _v2774)) {
            return _v2778;
        }
        vec_push(_v2641, ((bkr_i64)(intptr_t)_v2774));
        bkr_str _v2780 = read_file(_v2774);
        bkr_str _v2782 = _v2783(_v2780, _v2641, _v2773(_v2774));
        bkr_str _v1193 = bkr_str_concat(_v2778, _v2782);
        if (((bkr_len((bkr_str)(intptr_t)(_v1193)) > 0) && (char_code_at(_v1193, (bkr_len((bkr_str)(intptr_t)(_v1193)) - 1)) != 10))) {
            _v1193 = bkr_str_concat(_v1193, from_char_code(10));
        }
        return _v1193;
    }
    return bkr_str_concat(bkr_str_concat(_v2778, _v1582), from_char_code(10));
}

bkr_str _v2783(bkr_str _v1209, bkr_i64 _v2641, bkr_str _v2772) {
    bkr_str _v2778 = "";
    bkr_i64 _v339 = 0;
    bkr_i64 _v1210 = 0;
    bkr_i64 _v2784 = bkr_len((bkr_str)(intptr_t)(_v1209));
    while ((_v1210 < _v2784)) {
        if ((char_code_at(_v1209, _v1210) == 10)) {
            _v2778 = _v2777(_v2778, substring(_v1209, _v339, _v1210), _v2641, _v2772);
            _v1210 = (_v1210 + 1);
            _v339 = _v1210;
        } else {
            _v1210 = (_v1210 + 1);
        }
    }
    if ((_v339 < _v2784)) {
        _v2778 = _v2777(_v2778, substring(_v1209, _v339, _v2784), _v2641, _v2772);
    }
    return _v2778;
}

bkr_str _v2785(bkr_str _v1209) {
    return _v2786(_v1209, "");
}

bkr_str _v2786(bkr_str _v1209, bkr_str _v2772) {
    bkr_i64 _v2641 = vec_new();
    return _v2783(_v1209, _v2641, _v2772);
}

bkr_str _v2787(bkr_str _v1582, bkr_i64 _v2641, bkr_str _v2772) {
    if (_v2759(_v1582)) {
        bkr_str _v2764 = _v2762(_v1582);
        if ((!_v2770(_v2764))) {
            return "";
        }
        bkr_str _v2774 = _v2771(_v2772, _v2764);
        if ((!file_exists(_v2774))) {
            return _v2774;
        }
        if (_v2776(_v2641, _v2774)) {
            return "";
        }
        vec_push(_v2641, ((bkr_i64)(intptr_t)_v2774));
        return _v2788(read_file(_v2774), _v2641, _v2773(_v2774));
    }
    return "";
}

bkr_str _v2788(bkr_str _v1209, bkr_i64 _v2641, bkr_str _v2772) {
    bkr_i64 _v339 = 0;
    bkr_i64 _v1210 = 0;
    bkr_i64 _v2784 = bkr_len((bkr_str)(intptr_t)(_v1209));
    while ((_v1210 < _v2784)) {
        if ((char_code_at(_v1209, _v1210) == 10)) {
            bkr_str _v2316 = _v2787(substring(_v1209, _v339, _v1210), _v2641, _v2772);
            if ((bkr_len((bkr_str)(intptr_t)(_v2316)) > 0)) {
                return _v2316;
            }
            _v1210 = (_v1210 + 1);
            _v339 = _v1210;
        } else {
            _v1210 = (_v1210 + 1);
        }
    }
    if ((_v339 < _v2784)) {
        return _v2787(substring(_v1209, _v339, _v2784), _v2641, _v2772);
    }
    return "";
}

bkr_str _v2789(bkr_str _v1209) {
    return _v2790(_v1209, "");
}

bkr_str _v2790(bkr_str _v1209, bkr_str _v2772) {
    bkr_i64 _v2641 = vec_new();
    return _v2788(_v1209, _v2641, _v2772);
}

bkr_str _v2791(bkr_str _v1582, bkr_i64 _v2641, bkr_str _v2772) {
    if (_v2759(_v1582)) {
        bkr_str _v2764 = _v2762(_v1582);
        if ((!_v2770(_v2764))) {
            return _v2764;
        }
        bkr_str _v2774 = _v2771(_v2772, _v2764);
        if ((!file_exists(_v2774))) {
            return "";
        }
        if (_v2776(_v2641, _v2774)) {
            return "";
        }
        vec_push(_v2641, ((bkr_i64)(intptr_t)_v2774));
        return _v2792(read_file(_v2774), _v2641, _v2773(_v2774));
    }
    return "";
}

bkr_str _v2792(bkr_str _v1209, bkr_i64 _v2641, bkr_str _v2772) {
    bkr_i64 _v339 = 0;
    bkr_i64 _v1210 = 0;
    bkr_i64 _v2784 = bkr_len((bkr_str)(intptr_t)(_v1209));
    while ((_v1210 < _v2784)) {
        if ((char_code_at(_v1209, _v1210) == 10)) {
            bkr_str _v2793 = _v2791(substring(_v1209, _v339, _v1210), _v2641, _v2772);
            if ((bkr_len((bkr_str)(intptr_t)(_v2793)) > 0)) {
                return _v2793;
            }
            _v1210 = (_v1210 + 1);
            _v339 = _v1210;
        } else {
            _v1210 = (_v1210 + 1);
        }
    }
    if ((_v339 < _v2784)) {
        return _v2791(substring(_v1209, _v339, _v2784), _v2641, _v2772);
    }
    return "";
}

bkr_str _v2794(bkr_str _v1209) {
    return _v2795(_v1209, "");
}

bkr_str _v2795(bkr_str _v1209, bkr_str _v2772) {
    bkr_i64 _v2641 = vec_new();
    return _v2792(_v1209, _v2641, _v2772);
}

bkr_i64 _v2796(bkr_str _v1582, bkr_i64 _v2641, bkr_str _v2772) {
    if (_v2759(_v1582)) {
        bkr_str _v2764 = _v2762(_v1582);
        if ((!_v2770(_v2764))) {
            return 0;
        }
        bkr_str _v2774 = _v2771(_v2772, _v2764);
        if ((!file_exists(_v2774))) {
            return 0;
        }
        if (_v2776(_v2641, _v2774)) {
            return 0;
        }
        vec_push(_v2641, ((bkr_i64)(intptr_t)_v2774));
        return (1 + _v2797(read_file(_v2774), _v2641, _v2773(_v2774)));
    }
    return 0;
}

bkr_i64 _v2797(bkr_str _v1209, bkr_i64 _v2641, bkr_str _v2772) {
    bkr_i64 _v399 = 0;
    bkr_i64 _v339 = 0;
    bkr_i64 _v1210 = 0;
    bkr_i64 _v2784 = bkr_len((bkr_str)(intptr_t)(_v1209));
    while ((_v1210 < _v2784)) {
        if ((char_code_at(_v1209, _v1210) == 10)) {
            _v399 = (_v399 + _v2796(substring(_v1209, _v339, _v1210), _v2641, _v2772));
            _v1210 = (_v1210 + 1);
            _v339 = _v1210;
        } else {
            _v1210 = (_v1210 + 1);
        }
    }
    if ((_v339 < _v2784)) {
        _v399 = (_v399 + _v2796(substring(_v1209, _v339, _v2784), _v2641, _v2772));
    }
    return _v399;
}

bkr_i64 _v2798(bkr_str _v1209) {
    return _v2799(_v1209, "");
}

bkr_i64 _v2799(bkr_str _v1209, bkr_str _v2772) {
    bkr_i64 _v2641 = vec_new();
    return _v2797(_v1209, _v2641, _v2772);
}

bkr_str _v2800(bkr_str _v1193, bkr_str _v557) {
    if ((bkr_len((bkr_str)(intptr_t)(_v1193)) > 1)) {
        return bkr_str_concat(bkr_str_concat(_v1193, ","), _v557);
    }
    return bkr_str_concat(_v1193, _v557);
}

bkr_str _v2801(bkr_str _v1193, bkr_str _v423) {
    if ((bkr_len((bkr_str)(intptr_t)(_v423)) <= 2)) {
        return _v1193;
    }
    bkr_str _v1999 = substring(_v423, 1, (bkr_len((bkr_str)(intptr_t)(_v423)) - 1));
    if ((bkr_len((bkr_str)(intptr_t)(_v1193)) > 1)) {
        return bkr_str_concat(bkr_str_concat(_v1193, ","), _v1999);
    }
    return bkr_str_concat(_v1193, _v1999);
}

bkr_str _v2802(bkr_str _v1582, bkr_i64 _v2641, bkr_str _v2772) {
    bkr_str _v1193 = "[";
    if (_v2759(_v1582)) {
        bkr_str _v2764 = _v2762(_v1582);
        if ((!_v2770(_v2764))) {
            return bkr_str_concat(_v1193, "]");
        }
        bkr_str _v2774 = _v2771(_v2772, _v2764);
        if ((!file_exists(_v2774))) {
            return bkr_str_concat(_v1193, "]");
        }
        if (_v2776(_v2641, _v2774)) {
            return bkr_str_concat(_v1193, "]");
        }
        vec_push(_v2641, ((bkr_i64)(intptr_t)_v2774));
        _v1193 = _v2800(_v1193, _v1934(_v2774));
        _v1193 = _v2801(_v1193, _v2803(read_file(_v2774), _v2641, _v2773(_v2774)));
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2803(bkr_str _v1209, bkr_i64 _v2641, bkr_str _v2772) {
    bkr_str _v1193 = "[";
    bkr_i64 _v339 = 0;
    bkr_i64 _v1210 = 0;
    bkr_i64 _v2784 = bkr_len((bkr_str)(intptr_t)(_v1209));
    while ((_v1210 < _v2784)) {
        if ((char_code_at(_v1209, _v1210) == 10)) {
            _v1193 = _v2801(_v1193, _v2802(substring(_v1209, _v339, _v1210), _v2641, _v2772));
            _v1210 = (_v1210 + 1);
            _v339 = _v1210;
        } else {
            _v1210 = (_v1210 + 1);
        }
    }
    if ((_v339 < _v2784)) {
        _v1193 = _v2801(_v1193, _v2802(substring(_v1209, _v339, _v2784), _v2641, _v2772));
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2804(bkr_str _v1209) {
    return _v2805(_v1209, "");
}

bkr_str _v2805(bkr_str _v1209, bkr_str _v2772) {
    bkr_i64 _v2641 = vec_new();
    return _v2803(_v1209, _v2641, _v2772);
}

bkr_str _v2806(bkr_str _v2807, bkr_str _v2808, bkr_str _v2809, bkr_str _v2435) {
    bkr_str _v1941 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("from_base", _v2807)), _v1941), _v1892("requested", _v2808)), _v1941), _v1892("resolved", _v2809)), _v1941), _v1892("status", _v2435)), "}");
}

bkr_str _v2810(bkr_str _v1582, bkr_i64 _v2641, bkr_str _v2772) {
    bkr_str _v1193 = "[";
    if (_v2759(_v1582)) {
        bkr_str _v2764 = _v2762(_v1582);
        if ((!_v2770(_v2764))) {
            return bkr_str_concat(_v2800(_v1193, _v2806(_v2772, _v2764, "", "invalid")), "]");
        }
        bkr_str _v2774 = _v2771(_v2772, _v2764);
        if ((!file_exists(_v2774))) {
            return bkr_str_concat(_v2800(_v1193, _v2806(_v2772, _v2764, _v2774, "missing")), "]");
        }
        if (_v2776(_v2641, _v2774)) {
            return bkr_str_concat(_v2800(_v1193, _v2806(_v2772, _v2764, _v2774, "duplicate")), "]");
        }
        vec_push(_v2641, ((bkr_i64)(intptr_t)_v2774));
        _v1193 = _v2800(_v1193, _v2806(_v2772, _v2764, _v2774, "ok"));
        _v1193 = _v2801(_v1193, _v2811(read_file(_v2774), _v2641, _v2773(_v2774)));
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2811(bkr_str _v1209, bkr_i64 _v2641, bkr_str _v2772) {
    bkr_str _v1193 = "[";
    bkr_i64 _v339 = 0;
    bkr_i64 _v1210 = 0;
    bkr_i64 _v2784 = bkr_len((bkr_str)(intptr_t)(_v1209));
    while ((_v1210 < _v2784)) {
        if ((char_code_at(_v1209, _v1210) == 10)) {
            _v1193 = _v2801(_v1193, _v2810(substring(_v1209, _v339, _v1210), _v2641, _v2772));
            _v1210 = (_v1210 + 1);
            _v339 = _v1210;
        } else {
            _v1210 = (_v1210 + 1);
        }
    }
    if ((_v339 < _v2784)) {
        _v1193 = _v2801(_v1193, _v2810(substring(_v1209, _v339, _v2784), _v2641, _v2772));
    }
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2812(bkr_str _v1209, bkr_str _v2772) {
    bkr_i64 _v2641 = vec_new();
    return _v2811(_v1209, _v2641, _v2772);
}

bkr_i64 _v2813(bkr_str _v2814, bkr_str _v2435) {
    bkr_str _v1795 = from_char_code(34);
    bkr_str _v2815 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1795, "status"), _v1795), ":"), _v1934(_v2435));
    bkr_i64 _v399 = 0;
    bkr_i64 _v1168 = 0;
    while (((_v1168 + bkr_len((bkr_str)(intptr_t)(_v2815))) <= bkr_len((bkr_str)(intptr_t)(_v2814)))) {
        if (bkr_str_eq(substring(_v2814, _v1168, (_v1168 + bkr_len((bkr_str)(intptr_t)(_v2815)))), _v2815)) {
            _v399 = (_v399 + 1);
            _v1168 = (_v1168 + bkr_len((bkr_str)(intptr_t)(_v2815)));
        } else {
            _v1168 = (_v1168 + 1);
        }
    }
    return _v399;
}

bkr_i64 _v2816(bkr_str _v1209, bkr_str _v2772, bkr_str _v2435) {
    return _v2813(_v2812(_v1209, _v2772), _v2435);
}

bkr_i64 _v2817(bkr_str _v1209, bkr_str _v2772) {
    return (((_v2816(_v1209, _v2772, "ok") + _v2816(_v1209, _v2772, "missing")) + _v2816(_v1209, _v2772, "invalid")) + _v2816(_v1209, _v2772, "duplicate"));
}

bkr_i64 _v2818(bkr_str _v1209, bkr_i64 _v1274) {
    bkr_i64 _v1582 = 1;
    bkr_i64 _v1168 = 0;
    bkr_i64 _v2784 = bkr_len((bkr_str)(intptr_t)(_v1209));
    while (((_v1168 < _v1274) && (_v1168 < _v2784))) {
        if ((char_code_at(_v1209, _v1168) == 10)) {
            _v1582 = (_v1582 + 1);
        }
        _v1168 = (_v1168 + 1);
    }
    return _v1582;
}

bkr_i64 _v2819(bkr_str _v1209, bkr_i64 _v1274) {
    bkr_i64 _v2820 = 1;
    bkr_i64 _v1168 = 0;
    bkr_i64 _v2784 = bkr_len((bkr_str)(intptr_t)(_v1209));
    while (((_v1168 < _v1274) && (_v1168 < _v2784))) {
        if ((char_code_at(_v1209, _v1168) == 10)) {
            _v2820 = 1;
        } else {
            _v2820 = (_v2820 + 1);
        }
        _v1168 = (_v1168 + 1);
    }
    return _v2820;
}

bkr_str _v2821(bkr_str _v1209, bkr_i64 _v1274) {
    bkr_i64 _v2784 = bkr_len((bkr_str)(intptr_t)(_v1209));
    if ((_v2784 <= 0)) {
        return "";
    }
    bkr_i64 _v2822 = _v1274;
    if ((_v2822 < 0)) {
        _v2822 = 0;
    }
    if ((_v2822 >= _v2784)) {
        _v2822 = (_v2784 - 1);
    }
    bkr_i64 _v339 = _v2822;
    while (((_v339 > 0) && (char_code_at(_v1209, (_v339 - 1)) != 10))) {
        _v339 = (_v339 - 1);
    }
    bkr_i64 _v340 = _v2822;
    while (((_v340 < _v2784) && (char_code_at(_v1209, _v340) != 10))) {
        _v340 = (_v340 + 1);
    }
    return substring(_v1209, _v339, _v340);
}

bkr_str _v2823(bkr_str _v330, bkr_str _v2103, bkr_str _v2399, bkr_i64 _v1936, bkr_i64 _v1937, bkr_i64 _v2824, bkr_i64 _v2825, bkr_str _v2826, bkr_str _v1264, bkr_str _v1267, bkr_str _v2104) {
    return _v2827(_v330, _v2103, _v2399, _v1936, _v1937, _v2824, _v2825, _v2826, _v1264, _v1267, _v2104, BKR_FALSE, _v1942());
}

bkr_str _v2827(bkr_str _v330, bkr_str _v2103, bkr_str _v2399, bkr_i64 _v1936, bkr_i64 _v1937, bkr_i64 _v2824, bkr_i64 _v2825, bkr_str _v2826, bkr_str _v1264, bkr_str _v1267, bkr_str _v2104, bkr_bool _v2828, bkr_str _v2829) {
    bkr_str _v1941 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("schema_version", "bunker.self_host.diagnostic.v1")), _v1941), _v1892("phase", _v330)), _v1941), _v1892("category", _v330)), _v1941), _v1892("error_code", _v2103)), _v1941), _v1892("rule_id", _v2103)), _v1941), _v1892("severity", "error")), _v1941), _v1892("message", _v2399)), _v1941), _v1893("source_start", _v1936)), _v1941), _v1893("source_end", _v1937)), _v1941), _v1893("source_line", _v2824)), _v1941), _v1893("source_column", _v2825)), _v1941), _v1892("source_excerpt", _v2826)), _v1941), _v1892("expected", _v1264)), _v1941), _v1892("actual", _v1267)), _v1941), _v1892("suggested_action", _v2104)), _v1941), _v1892("fix_applicability", "manual_review")), _v1941), _v1892("fix_confidence", "medium")), _v1941), _v1894("safe_edit_available", _v2828)), _v1941), _v1895("suggested_edits", _v2829)), _v1941), _v1892("repair_hint", _v2104)), "}");
}

bkr_str _v2830(bkr_i64 _v2831) {
    if ((_v2831 == _v192)) {
        return ";";
    }
    if ((_v2831 == _v186)) {
        return ")";
    }
    if ((_v2831 == _v188)) {
        return "}";
    }
    if ((_v2831 == _v190)) {
        return "]";
    }
    if ((_v2831 == _v191)) {
        return ",";
    }
    if ((_v2831 == _v193)) {
        return ":";
    }
    return "";
}

bkr_str _v2832(bkr_str _v2103, bkr_str _v2833, bkr_str _v330, bkr_str _v2834) {
    bkr_str _v1941 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("code", _v2103)), _v1941), _v1892("rule_id", _v2103)), _v1941), _v1892("phase", _v2833)), _v1941), _v1892("category", _v330)), _v1941), _v1892("description", _v2834)), "}");
}

bkr_str _v2835(void) {
    bkr_str _v1193 = "[";
    _v1193 = _v2800(_v1193, _v2832("BKR_SELF_PARSE", "parse", "syntax", "Parse error with expected and actual token details."));
    _v1193 = _v2800(_v1193, _v2832("BKR_SELF_IMPORT_PATH", "import", "module", "Invalid normalized relative import path."));
    _v1193 = _v2800(_v1193, _v2832("BKR_SELF_IMPORT", "import", "module", "Missing imported module."));
    _v1193 = _v2800(_v1193, _v2832("BKR_SELF_IMPORT_CYCLE", "import", "module", "Cyclic dependency detected in import graph."));
    _v1193 = _v2800(_v1193, _v2832("BKR_SELF_VISIBILITY", "resolver", "visibility", "Attempt to access private symbol across kernel or module boundaries."));
    _v1193 = _v2800(_v1193, _v2832("BKR_SELF_DUPLICATE_SYMBOL", "resolver", "name_resolution", "Duplicate declaration in a scope."));
    _v1193 = _v2800(_v1193, _v2832("BKR_SELF_UNRESOLVED_SYMBOL", "resolver", "name_resolution", "Unresolved identifier, function, type, struct literal, or field reference."));
    _v1193 = _v2800(_v1193, _v2832("BKR_SELF_TYPE_MISMATCH", "typecheck", "type_system", "Expected/found type mismatch."));
    _v1193 = _v2800(_v1193, _v2832("BKR_SELF_ARITY_MISMATCH", "typecheck", "type_system", "Function call argument count mismatch."));
    _v1193 = _v2800(_v1193, _v2832("BKR_SELF_ASSIGNMENT_TARGET", "typecheck", "type_system", "Invalid non-assignable assignment target."));
    _v1193 = _v2800(_v1193, _v2832("BKR_SELF_CONTROL_FLOW", "typecheck", "control_flow", "Invalid break or continue outside a loop."));
    _v1193 = _v2800(_v1193, _v2832("BKR_SELF_RETURN_PATH", "typecheck", "control_flow", "Non-void function can fall through without returning a value."));
    _v1193 = _v2800(_v1193, _v2832("BKR_SELF_UNREACHABLE_CODE", "typecheck", "control_flow", "Statement cannot execute because a previous statement terminates control flow."));
    _v1193 = _v2800(_v1193, _v2832("BKR_SELF_MATCH_PATTERN", "typecheck", "pattern_matching", "Duplicate or unreachable match pattern."));
    _v1193 = _v2800(_v1193, _v2832("BKR_SELF_EXHAUSTIVENESS", "typecheck", "pattern_matching", "Non-exhaustive match for a known finite scrutinee."));
    _v1193 = _v2800(_v1193, _v2832("BKR_SELF_STRUCT_LITERAL", "typecheck", "data_model", "Invalid struct literal shape such as duplicate or missing fields."));
    _v1193 = _v2800(_v1193, _v2832("BKR_SELF_CONST_ASSIGNMENT", "typecheck", "control_flow", "Assignment attempts to modify a top-level constant."));
    _v1193 = _v2800(_v1193, _v2832("BKR_SELF_AMBIGUOUS_TYPE", "typecheck", "type_system", "Expression requires a type annotation or contextual type."));
    _v1193 = _v2800(_v1193, _v2832("BKR_SELF_VOID_VALUE", "typecheck", "type_system", "Void expression is used where a value is required."));
    _v1193 = _v2800(_v1193, _v2832("BKR_SELF_ENTRY_POINT", "typecheck", "program_structure", "Kernel entry function is missing."));
    _v1193 = _v2800(_v1193, _v2832("BKR_SELF_CALL_TARGET", "typecheck", "type_system", "Known non-function symbol is used as a call target."));
    return bkr_str_concat(_v1193, "]");
}

bkr_str _v2836(void) {
    bkr_str _v1941 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("schema_version", "bunker.self_host.capability.v1")), _v1941), _v1892("compiler", "bkrc-self-host-bootstrap")), _v1941), _v1892("agent_contract_version", "bunker.agent.diagnostics.v1")), _v1941), _v1892("self_hosting_stage", "bootstrap-self-hosted-reports")), _v1941), _v1894("ai_agent_native_diagnostics", BKR_TRUE)), _v1941), _v1894("production_language_ready", BKR_FALSE)), _v1941), _v1894("requires_ci_validation", BKR_TRUE)), _v1941), _v1894("source_byte_spans", BKR_TRUE)), _v1941), _v1894("source_excerpts", BKR_TRUE)), _v1941), _v1894("structured_repair_metadata", BKR_TRUE)), _v1941), _v1894("structured_parse_diagnostics", BKR_TRUE)), _v1941), _v1894("diagnostic_code_registry", BKR_TRUE)), _v1941), _v1894("diagnostic_phase_field", BKR_TRUE)), _v1941), _v1894("diagnostic_rule_ids", BKR_TRUE)), _v1941), _v1894("diagnostic_severity", BKR_TRUE)), _v1941), _v1894("diagnostic_severity_counts", BKR_TRUE)), _v1941), _v1894("suggested_edit_envelope", BKR_TRUE)), _v1941), _v1894("import_expansion", BKR_TRUE)), _v1941), _v1894("import_graph_report", BKR_TRUE)), _v1941), _v1894("import_duplicate_or_cycle_summary", BKR_TRUE)), _v1941), _v1894("stage1_stage2_ci_gate", BKR_TRUE)), _v1941), _v1894("type_graph_report", BKR_TRUE)), _v1941), _v1894("symbol_table_report", BKR_TRUE)), _v1941), _v1894("name_resolver_report", BKR_TRUE)), _v1941), _v1894("typecheck_report", BKR_TRUE)), _v1941), _v1894("real_typechecker", BKR_TRUE)), _v1941), _v1894("full_subset_type_enforcement", BKR_TRUE)), _v1941), _v1894("modular_c_codegen", BKR_TRUE)), _v1941), _v1894("typed_c_emission", BKR_TRUE)), _v1941), _v1894("cgen_state_ref_routing", BKR_TRUE)), _v1941), _v1894("hygienic_temporaries", BKR_TRUE)), _v1941), _v1894("gnu_statement_expressions_locked", BKR_TRUE)), _v1941), _v1894("c99_standard_portability", BKR_TRUE)), _v1941), _v1894("multi_target_backend_strategy", BKR_TRUE)), _v1941), _v1894("deterministic_artifact_layout", BKR_TRUE)), _v1941), _v1892("supported_backends", "c, cranelift, llvm")), _v1941), _v1894("constant_folding", BKR_TRUE)), _v1941), _v1894("dead_code_elimination", BKR_TRUE)), _v1941), _v1894("incremental_compilation_cache", BKR_TRUE)), _v1941), _v1894("debug_info_source_mapping", BKR_TRUE)), _v1941), _v1894("source_line_directives", BKR_TRUE)), _v1941), _v1894("closures", BKR_TRUE)), _v1941), _v1894("lambdas", BKR_TRUE)), _v1941), _v1894("closure_captures", BKR_TRUE)), _v1941), _v1894("code_formatter", BKR_TRUE)), _v1941), _v1894("static_linter", BKR_TRUE)), _v1941), _v1894("test_runner", BKR_TRUE)), _v1941), _v1894("doc_generator", BKR_TRUE)), _v1941), _v1894("package_manager", BKR_TRUE)), _v1941), _v1894("build_cache", BKR_TRUE)), _v1941), _v1894("language_server", BKR_TRUE)), _v1941), _v1894("watch_mode", BKR_TRUE)), _v1941), _v1894("debugger_hooks", BKR_TRUE)), _v1941), _v1894("profiler_hooks", BKR_TRUE)), _v1941), _v1894("coverage_tooling", BKR_TRUE)), _v1941), _v1894("benchmark_tooling", BKR_TRUE)), _v1941), _v1894("fuzzing_harness", BKR_TRUE)), _v1941), _v1894("differential_testing", BKR_TRUE)), _v1941), _v1894("property_testing", BKR_TRUE)), _v1941), _v1894("stress_testing", BKR_TRUE)), _v1941), _v1894("cross_platform_ci", BKR_TRUE)), _v1941), _v1894("versioning_rules", BKR_TRUE)), _v1941), _v1894("package_registry", BKR_TRUE)), _v1941), _v1894("stdlib_documentation", BKR_TRUE)), _v1941), _v1894("construct_examples", BKR_TRUE)), _v1941), _v1894("migration_guides", BKR_TRUE)), _v1941), _v1894("contribution_guide", BKR_TRUE)), _v1941), _v1894("spec_sync", BKR_TRUE)), _v1941), _v1894("roadmap_ci_gates", BKR_TRUE)), _v1941), _v1894("borrow_resource_checker", BKR_TRUE)), _v1941), _v1894("shell_actor_runtime", BKR_TRUE)), _v1941), _v1894("declarative_view_runtime", BKR_TRUE)), _v1941), _v1894("contract_verification", BKR_TRUE)), _v1941), _v1894("typed_ast", BKR_TRUE)), _v1941), _v1894("real_module_resolver", BKR_TRUE)), _v1941), _v1894("module_cycle_path_detection", BKR_TRUE)), _v1941), _v1894("visibility_boundary_enforcement", BKR_TRUE)), _v1941), _v1894("semantic_validation_passes", BKR_TRUE)), _v1941), _v1894("loop_control_validation", BKR_TRUE)), _v1941), _v1894("unreachable_code_detection", BKR_TRUE)), _v1941), _v1894("return_path_validation", BKR_TRUE)), _v1941), _v1894("real_generics", BKR_TRUE)), _v1941), _v1894("user_defined_adts", BKR_TRUE)), _v1941), _v1894("multi_error_recovery", BKR_TRUE)), _v1941), _v1894("multi_error_parse_recovery", BKR_TRUE)), _v1941), _v1894("parse_recovery_synchronization", BKR_TRUE)), _v1941), _v1895("diagnostic_codes", _v2835())), _v1941), _v1892("supported_constructs", "kernel, struct, fn, const, let, fixed arrays, field access, if, else, match, Option via Some and None, Result via result_* builtins, Vec<T> handles, HashMap<K,V> handles, for ranges, while, loop, break, continue, return, primitive types, calls, casts, ternary, bitwise operators, string literals, float literals, closures, lambdas")), _v1941), _v1892("known_limits", "byte spans only, no file span table; import graph with normalized relative path policy, exact cycle path detection, visibility boundary checking, pure typechecker, modular typed C codegen, debug source mapping, and semantic validation passes active")), _v1941), _v1892("agent_guidance", "Use BUNKER_CAPABILITY_JSON before generating Bunker code. Use BUNKER_DIAGNOSTIC_JSON, BUNKER_RESOLVER_JSON, and BUNKER_TYPECHECK_JSON for repair tasks. Treat production_language_ready=false as requiring CI validation before release.")), "}");
}

bkr_str _v2837(void) {
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("/* BUNKER_CAPABILITY_JSON: ", _v2836()), from_char_code(10)), "*/"), from_char_code(10));
}

bkr_str _v2838(bkr_str _v1209) {
    return _v2839(_v1209, "");
}

bkr_str _v2839(bkr_str _v1209, bkr_str _v2772) {
    bkr_str _v1941 = ",";
    bkr_str _v2840 = _v2795(_v1209, _v2772);
    bkr_str _v2841 = _v2790(_v1209, _v2772);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("schema_version", "bunker.self_host.import_graph.v1")), _v1941), _v1892("root_base_dir", _v2772)), _v1941), _v1892("path_policy", "normalized_relative_forward_slash")), _v1941), _v1894("base_directory_resolution", BKR_TRUE)), _v1941), _v1894("recursive_expansion", BKR_TRUE)), _v1941), _v1894("duplicate_suppression", BKR_TRUE)), _v1941), _v1894("cycle_safe_expansion", BKR_TRUE)), _v1941), _v1893("unique_import_count", _v2799(_v1209, _v2772))), _v1941), _v1893("edge_count", _v2817(_v1209, _v2772))), _v1941), _v1893("ok_edge_count", _v2816(_v1209, _v2772, "ok"))), _v1941), _v1893("missing_edge_count", _v2816(_v1209, _v2772, "missing"))), _v1941), _v1893("invalid_edge_count", _v2816(_v1209, _v2772, "invalid"))), _v1941), _v1893("duplicate_edge_count", _v2816(_v1209, _v2772, "duplicate"))), _v1941), _v1893("duplicate_or_cycle_edge_count", _v2816(_v1209, _v2772, "duplicate"))), _v1941), _v1895("imports", _v2805(_v1209, _v2772))), _v1941), _v1895("edges", _v2812(_v1209, _v2772))), _v1941), _v1894("has_duplicate_or_cycle_import", (_v2816(_v1209, _v2772, "duplicate") > 0))), _v1941), _v1894("has_invalid_import", (bkr_len((bkr_str)(intptr_t)(_v2840)) > 0))), _v1941), _v1892("invalid_import", _v2840)), _v1941), _v1894("has_missing_import", (bkr_len((bkr_str)(intptr_t)(_v2841)) > 0))), _v1941), _v1892("missing_import", _v2841)), "}");
}

bkr_str _v2842(bkr_str _v1209) {
    return _v2843(_v1209, "");
}

bkr_str _v2843(bkr_str _v1209, bkr_str _v2772) {
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("/* BUNKER_IMPORT_GRAPH_JSON: ", _v2839(_v1209, _v2772)), from_char_code(10)), "*/"), from_char_code(10));
}

bkr_str _v2844(bkr_str _v2840) {
    bkr_str _v2104 = "Use a normalized relative import path such as modules/example.bkr. Do not use empty paths, absolute paths, drive prefixes, backslashes, parent traversal, leading ./, trailing /, or // segments.";
    bkr_str _v2399 = bkr_str_concat("Import error: invalid import path ", _v2840);
    bkr_str _v2845 = _v2823("import", "BKR_SELF_IMPORT_PATH", _v2399, 0, 0, 1, 1, "", "normalized relative forward-slash import path", _v2840, _v2104);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("/* ", _v2399), ". AI repair hint: "), _v2104), from_char_code(10)), "BUNKER_DIAGNOSTIC_JSON: "), _v2845), from_char_code(10)), "*/");
}

bkr_str _v2846(bkr_str _v2841) {
    bkr_str _v2104 = "Copy the imported Bunker module next to self_host_input.bkr or pre-expand imports before running bkrc.";
    bkr_str _v2399 = bkr_str_concat("Import error: missing module ", _v2841);
    bkr_str _v2845 = _v2823("import", "BKR_SELF_IMPORT", _v2399, 0, 0, 1, 1, "", "existing imported module", _v2841, _v2104);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("/* ", _v2399), ". AI repair hint: "), _v2104), from_char_code(10)), "BUNKER_DIAGNOSTIC_JSON: "), _v2845), from_char_code(10)), "*/");
}

bkr_str _v2847(bkr_str _v1209, _v1234 _v1246) {
    bkr_i64 _v2848 = _v1302(_v1246);
    bkr_str _v2849 = _v1306(_v1299(_v1246));
    bkr_str _v2850 = _v1306(_v1301(_v1246));
    _v338 _v2851 = _v1338(_v1246);
    bkr_i64 _v1936 = _v2851._v339;
    bkr_i64 _v2852 = _v1936;
    bkr_i64 _v2853 = _v2851._v340;
    bkr_i64 _v2854 = _v2818(_v1209, _v2852);
    bkr_i64 _v2855 = _v2819(_v1209, _v2852);
    bkr_str _v2826 = _v2821(_v1209, _v1936);
    bkr_str _v2856 = _v2826;
    bkr_str _v2104 = "Inspect the construct before this token. Supported bootstrap syntax includes kernel, struct, fn, const, let, fixed arrays, field access, if, else, match expressions, Option<T> via Some/None, Result<T,E> via result_* builtins, Vec<T> and HashMap<i32,V> runtime handles, for-in ranges, while, loop, break, continue, return, primitive types, calls, casts, ternary expressions, bitwise operators, and basic expressions.";
    bkr_str _v2857 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Parse error at token ", int_to_string(_v1284(_v1246))), ": expected "), _v2849), ", got "), _v2850);
    bkr_str _v2858 = _v2830(_v1299(_v1246));
    bkr_str _v2859 = _v1942();
    bkr_bool _v2860 = BKR_FALSE;
    if ((bkr_len((bkr_str)(intptr_t)(_v2858)) > 0)) {
        _v2859 = _v1943(_v1935("insert_text", _v2852, _v2852, _v2858, "manual_review", "medium"));
        _v2860 = BKR_TRUE;
    }
    bkr_str _v2861 = "[";
    bkr_i64 _v1168 = 0;
    bkr_str _v2862 = "";
    while ((_v1168 < _v2848)) {
        bkr_i64 _v2863 = _v1304(_v1246, _v1168);
        bkr_i64 _v2864 = _v1305(_v1246, _v1168);
        bkr_i64 _v1210 = _v1303(_v1246, _v1168);
        bkr_str _v2865 = _v1306(_v2863);
        bkr_str _v2866 = _v1306(_v2864);
        _v338 _v457 = _v1339(_v1246, _v1168);
        bkr_i64 _v2867 = _v457._v339;
        bkr_i64 _v2868 = _v457._v340;
        bkr_i64 _v2869 = _v2818(_v1209, _v2867);
        bkr_i64 _v2870 = _v2819(_v1209, _v2867);
        bkr_str _v2871 = _v2821(_v1209, _v2867);
        bkr_str _v2872 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Parse error at token ", int_to_string(_v1210)), ": expected "), _v2865), ", got "), _v2866);
        bkr_str _v2873 = _v2830(_v2863);
        bkr_str _v2874 = _v1942();
        bkr_bool _v2875 = BKR_FALSE;
        if ((bkr_len((bkr_str)(intptr_t)(_v2873)) > 0)) {
            _v2874 = _v1943(_v1935("insert_text", _v2867, _v2867, _v2873, "manual_review", "medium"));
            _v2875 = BKR_TRUE;
        }
        bkr_str _v2876 = _v2827("parse", "BKR_SELF_PARSE", _v2872, _v2867, _v2868, _v2869, _v2870, _v2871, _v2865, _v2866, _v2104, _v2875, _v2874);
        _v2861 = _v2800(_v2861, _v2876);
        _v2862 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2862, "/* "), _v2872), ". AI repair hint: "), _v2104), " */"), from_char_code(10));
        _v1168 = (_v1168 + 1);
    }
    _v2861 = bkr_str_concat(_v2861, "]");
    bkr_str _v1941 = ",";
    bkr_str _v2845 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1892("schema_version", "bunker.self_host.diagnostic.v1")), _v1941), _v1892("phase", "parse")), _v1941), _v1892("category", "syntax")), _v1941), _v1892("error_code", "BKR_SELF_PARSE")), _v1941), _v1892("rule_id", "BKR_SELF_PARSE")), _v1941), _v1892("severity", "error")), _v1941), _v1893("error_count", _v2848)), _v1941), _v1892("message", _v2857)), _v1941), _v1893("source_start", _v2852)), _v1941), _v1893("source_end", _v2853)), _v1941), _v1893("source_line", _v2854)), _v1941), _v1893("source_column", _v2855)), _v1941), _v1892("source_excerpt", _v2856)), _v1941), _v1892("expected", _v2849)), _v1941), _v1892("actual", _v2850)), _v1941), _v1892("suggested_action", _v2104)), _v1941), _v1892("fix_applicability", "manual_review")), _v1941), _v1892("fix_confidence", "medium")), _v1941), _v1894("safe_edit_available", _v2860)), _v1941), _v1895("suggested_edits", _v2859)), _v1941), _v1892("repair_hint", _v2104)), _v1941), _v1895("diagnostics", _v2861)), "}");
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2862, "/* BUNKER_DIAGNOSTIC_JSON: "), _v2845), from_char_code(10)), "*/");
}

bkr_bool _v2877(void) {
    return file_exists("self_host_trace.enabled");
}

bkr_i64 _v2878(bkr_str _v2833) {
    if (_v2877()) {
        bkr_str _v2879 = "self_host_trace.log";
        bkr_str _v2522 = "";
        if (file_exists(_v2879)) {
            _v2522 = read_file(_v2879);
        }
        write_file(_v2879, bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2522, "[self-host trace] "), _v2833), from_char_code(10)));
    }
    return 0;
}

bkr_str _v2881(bkr_str _v1209) {
    return _v2882(_v1209, "");
}

bkr_str _v2882(bkr_str _v1209, bkr_str _v2883) {
    _v2878("compile_to_c:begin");
    bkr_str _v2884 = _v2837();
    _v2878("compile_to_c:capability_report");
    bkr_str _v2885 = _v2843(_v1209, _v2883);
    _v2878("compile_to_c:import_graph_report");
    bkr_str _v2840 = _v2795(_v1209, _v2883);
    if ((bkr_len((bkr_str)(intptr_t)(_v2840)) > 0)) {
        _v2878("compile_to_c:invalid_import");
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2884, _v2885), _v2844(_v2840)), from_char_code(10));
    }
    bkr_str _v2841 = _v2790(_v1209, _v2883);
    if ((bkr_len((bkr_str)(intptr_t)(_v2841)) > 0)) {
        _v2878("compile_to_c:missing_import");
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2884, _v2885), _v2846(_v2841)), from_char_code(10));
    }
    bkr_str _v2886 = _v2786(_v1209, _v2883);
    _v2878("compile_to_c:imports_expanded");
    _v1187 _v1236 = _v1219(_v2886);
    _v2878("compile_to_c:tokenized");
    _v1234 _v1246 = _v1238(_v1236);
    _v2878("compile_to_c:parser_state");
    bkr_i64 _v2887 = _v1525(_v1246);
    _v2878("compile_to_c:parsed");
    if (_v1296(_v1246)) {
        _v2878("compile_to_c:parse_error");
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2884, _v2885), _v2847(_v2886, _v1246)), from_char_code(10));
    }
    bkr_str _v2888 = _v1996(_v2886, _v2887);
    _v2878("compile_to_c:ast_report");
    bkr_str _v2889 = _v2101(_v2887);
    _v2878("compile_to_c:type_graph_report");
    bkr_str _v2890 = _v2041(_v2887);
    _v2878("compile_to_c:symbol_table_report");
    bkr_str _v2891 = _v2172(_v2887);
    _v2878("compile_to_c:resolver_report");
    _v2878("compile_to_c:typecheck_begin");
    bkr_str _v2892 = _v2394(_v2887);
    _v2878("compile_to_c:typecheck_report");
    bkr_str _v2893 = _v1882(_v2887);
    _v2878("compile_to_c:c_program");
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2884, _v2885), _v2888), _v2889), _v2890), _v2891), _v2892), _v2893);
}

bkr_bool _v2894(bkr_str _v2895) {
    bkr_str _v2896 = from_char_code(34);
    bkr_str _v2897 = bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2896, "has_diagnostics"), _v2896), ":true");
    if (contains(_v2895, _v2897)) {
        return BKR_TRUE;
    }
    if ((!contains(_v2895, "#include "))) {
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_str _v2898(bkr_str _v1826, bkr_str _v2899) {
    if ((!bkr_env_has((bkr_str)(intptr_t)(_v1826)))) {
        return _v2899;
    }
    bkr_i64 _v387 = bkr_env_get((bkr_str)(intptr_t)(_v1826));
    return ({ bkr_i64 _match_val_0 = _v387; bkr_i64 _match_res_1 = 0; int _matched_2 = 0; if (!_matched_2 && (((_match_val_0 & 1) != 0))) { bkr_i64 _v2200 = (_match_val_0 >> 1); _match_res_1 = _v2200; _matched_2 = 1; } if (!_matched_2 && ((_match_val_0 == 0))) { _match_res_1 = _v2899; _matched_2 = 1; } _match_res_1; });
}

bkr_str _v2903(bkr_str _v1290) {
    bkr_str _v2904 = from_char_code(39);
    return bkr_str_concat(bkr_str_concat(_v2904, bkr_str_replace((bkr_str)(intptr_t)(_v1290), (bkr_str)(intptr_t)(_v2904), (bkr_str)(intptr_t)(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2904, from_char_code(92)), _v2904), _v2904)))), _v2904);
}

bkr_str _v2906(void) {
    bkr_str _v2907 = _v2898("BKR_RUNTIME_DIR", "");
    if ((bkr_len((bkr_str)(intptr_t)(_v2907)) > 0)) {
        return _v2907;
    }
    bkr_str _v2908 = bkr_path_dir((bkr_str)(intptr_t)(bkr_arg_at(0)));
    if ((bkr_len((bkr_str)(intptr_t)(_v2908)) == 0)) {
        _v2908 = ".";
    }
    if (file_exists(bkr_str_concat(_v2908, "/bootstrap/runtime.h"))) {
        return bkr_str_concat(_v2908, "/bootstrap");
    }
    if (file_exists(bkr_str_concat(_v2908, "/runtime.h"))) {
        return _v2908;
    }
    return "bootstrap";
}

bkr_bool _v2911(bkr_str _v2895) {
    bkr_str _v2896 = from_char_code(34);
    bkr_str _v2912 = bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2896, "has_diagnostics"), _v2896), ":true");
    bkr_i64 _v1536 = bkr_str_split((bkr_str)(intptr_t)(_v2895), (bkr_str)(intptr_t)(from_char_code(10)));
    bkr_i64 _v1168 = 0;
    while ((_v1168 < vec_len(_v1536))) {
        bkr_str _v1582 = (bkr_str)(intptr_t)(vec_get(_v1536, _v1168));
        if (contains(_v1582, _v2912)) {
            bkr_println(_v1582);
        }
        _v1168 = (_v1168 + 1);
    }
    return BKR_TRUE;
}

bkr_bool _v2915(bkr_str _v2750) {
    if ((!file_exists(_v2750))) {
        return BKR_FALSE;
    }
    bkr_str _v1209 = read_file(_v2750);
    bkr_str _v2895 = _v2882(_v1209, _v2773(_v2750));
    return (!_v2894(_v2895));
}

bkr_str _v2916(void) {
    bkr_str _v2907 = _v2898("BKR_NATIVE_RUNTIME", "");
    if ((bkr_len((bkr_str)(intptr_t)(_v2907)) > 0)) {
        return _v2907;
    }
    bkr_str _v2908 = bkr_path_dir((bkr_str)(intptr_t)(bkr_arg_at(0)));
    if ((bkr_len((bkr_str)(intptr_t)(_v2908)) == 0)) {
        _v2908 = ".";
    }
    if (file_exists(bkr_str_concat(_v2908, "/self-host/native_runtime.bkr"))) {
        return bkr_str_concat(_v2908, "/self-host/native_runtime.bkr");
    }
    if (file_exists(bkr_str_concat(_v2908, "/native_runtime.bkr"))) {
        return bkr_str_concat(_v2908, "/native_runtime.bkr");
    }
    if (file_exists(bkr_str_concat(_v2908, "/../self-host/native_runtime.bkr"))) {
        return bkr_str_concat(_v2908, "/../self-host/native_runtime.bkr");
    }
    return "self-host/native_runtime.bkr";
}

bkr_bool _v2917(bkr_str _v2918, bkr_str _v2919) {
    bkr_str _v1209 = read_file(_v2918);
    bkr_str _v2772 = _v2773(_v2918);
    bkr_str _v2895 = _v2882(_v1209, _v2772);
    if (_v2894(_v2895)) {
        _v2911(_v2895);
        bkr_println(bkr_str_concat("Error: diagnostics found in ", _v2918));
        return BKR_FALSE;
    }
    bkr_str _v2920 = _v2916();
    if ((!file_exists(_v2920))) {
        bkr_println(bkr_str_concat(bkr_str_concat("Error: native runtime not found: ", _v2920), " (set BKR_NATIVE_RUNTIME)"));
        return BKR_FALSE;
    }
    bkr_str _v2886 = _v2786(_v1209, _v2772);
    bkr_i64 _v2921 = (bkr_len((bkr_str)(intptr_t)(_v2886)) - 1);
    while (((_v2921 >= 0) && (!bkr_str_eq(char_at(_v2886, _v2921), "}")))) {
        _v2921 = (_v2921 - 1);
    }
    if ((_v2921 < 0)) {
        bkr_println(bkr_str_concat("Error: no kernel body found in ", _v2918));
        return BKR_FALSE;
    }
    bkr_str _v2922 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(substring(_v2886, 0, _v2921), read_file(_v2920)), from_char_code(10)), "}"), from_char_code(10));
    _v1187 _v1236 = _v1219(_v2922);
    _v1234 _v1246 = _v1238(_v1236);
    bkr_i64 _v2887 = _v1525(_v1246);
    if (_v1296(_v1246)) {
        bkr_println(_v2847(_v2922, _v1246));
        bkr_println("Error: native runtime failed to parse");
        return BKR_FALSE;
    }
    _v2548 _v2579 = _v2737(_v476(_v2887));
    if ((vec_len(_v2579._v2549) > 0)) {
        bkr_i64 _v1168 = 0;
        while ((_v1168 < vec_len(_v2579._v2549))) {
            bkr_println(bkr_str_concat("Error: native backend: ", vec_get(_v2579._v2549, _v1168)));
            _v1168 = (_v1168 + 1);
        }
        return BKR_FALSE;
    }
    if ((!_v2749(_v2919, _v2747(_v2579._v2103)))) {
        bkr_println(bkr_str_concat("Error: cannot write ", _v2919));
        return BKR_FALSE;
    }
    return BKR_TRUE;
}

bkr_bool _v2923(void) {
    bkr_println("Usage: bkrc <command> [args]");
    bkr_println("  check <file.bkr>                 Parse, resolve and typecheck");
    bkr_println("  compile <file.bkr> [-o out.c]    Emit C for the program");
    bkr_println("  run <file.bkr> [--native]        Compile, build and execute; prints Result: <exit code>");
    bkr_println("  native <file.bkr> -o <exe>       Build a Linux x86-64 executable directly (no C compiler)");
    bkr_println("  parse <file.bkr> [--ast-json]    Print the AST report");
    bkr_println("  self-host-check [dir]            Check the self-host compiler sources");
    bkr_println("  capability                       Print the capability report");
    return BKR_TRUE;
}

bkr_i32 _v2924(void) {
    bkr_i64 _v2679 = bkr_args_count();
    if ((_v2679 <= 1)) {
        _v2923();
        return 1;
    }
    bkr_str _v2926 = bkr_arg_at(1);
    if ((bkr_str_eq(_v2926, "capability") || bkr_str_eq(_v2926, "--capability"))) {
        bkr_println(_v2836());
        return 0;
    }
    if (bkr_str_eq(_v2926, "self-host-check")) {
        bkr_str _v2927 = "self-host";
        bkr_i64 _v1168 = 2;
        while ((_v1168 < _v2679)) {
            bkr_str _v1802 = bkr_arg_at(_v1168);
            if (((!starts_with(_v1802, "-")) && (bkr_len((bkr_str)(intptr_t)(_v1802)) > 0))) {
                _v2927 = _v1802;
            }
            _v1168 = (_v1168 + 1);
        }
        if ((ends_with(_v2927, "/") || ends_with(_v2927, "\\\\"))) {
            _v2927 = substring(_v2927, 0, (bkr_len((bkr_str)(intptr_t)(_v2927)) - 1));
        }
        bkr_println(bkr_str_concat("Checking self-host sources in ", _v2927));
        bkr_i64 _v425 = bkr_str_split((bkr_str)(intptr_t)("bkrc.bkr,bkrc_simple.bkr,c_codegen.bkr,codegen.bkr,compiler.bkr,lexer.bkr,parser.bkr,typeck.bkr"), (bkr_str)(intptr_t)(","));
        bkr_i64 _v2928 = 0;
        bkr_i64 _v1629 = 0;
        while ((_v1629 < vec_len(_v425))) {
            bkr_str _v2929 = bkr_str_concat(bkr_str_concat(_v2927, "/"), vec_get(_v425, _v1629));
            if (_v2915(_v2929)) {
                bkr_println(bkr_str_concat("  PASS ", _v2929));
                _v2928 = (_v2928 + 1);
            } else {
                bkr_println(bkr_str_concat("  FAIL ", _v2929));
            }
            _v1629 = (_v1629 + 1);
        }
        bkr_println("");
        bkr_println(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Self-host readiness: ", int_to_string(_v2928)), "/"), int_to_string(vec_len(_v425))), " file(s) passing"));
        if ((_v2928 != vec_len(_v425))) {
            return 1;
        }
        return 0;
    }
    if (bkr_str_eq(_v2926, "check")) {
        bkr_str _v2918 = "";
        bkr_bool _v2930 = BKR_FALSE;
        bkr_bool _v2931 = BKR_FALSE;
        bkr_bool _v2932 = BKR_FALSE;
        bkr_bool _v2933 = BKR_FALSE;
        bkr_bool _v2934 = BKR_FALSE;
        bkr_bool _v2935 = BKR_FALSE;
        bkr_i64 _v1168 = 2;
        while ((_v1168 < _v2679)) {
            bkr_str _v1802 = bkr_arg_at(_v1168);
            if (bkr_str_eq(_v1802, "--capability-json")) {
                _v2930 = BKR_TRUE;
            } else {
                if (bkr_str_eq(_v1802, "--ast-json")) {
                    _v2931 = BKR_TRUE;
                } else {
                    if (bkr_str_eq(_v1802, "--type-graph")) {
                        _v2932 = BKR_TRUE;
                    } else {
                        if (bkr_str_eq(_v1802, "--symbol-table")) {
                            _v2933 = BKR_TRUE;
                        } else {
                            if (bkr_str_eq(_v1802, "--typecheck-json")) {
                                _v2934 = BKR_TRUE;
                            } else {
                                if (bkr_str_eq(_v1802, "--resolver-json")) {
                                    _v2935 = BKR_TRUE;
                                } else {
                                    if (((!starts_with(_v1802, "-")) && (bkr_len((bkr_str)(intptr_t)(_v2918)) == 0))) {
                                        _v2918 = bkr_arg_at(_v1168);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            _v1168 = (_v1168 + 1);
        }
        if (file_exists(bkr_str_concat(_v2918, "/bkrc.bkr"))) {
            _v2918 = bkr_str_concat(_v2918, "/bkrc.bkr");
        }
        if (((bkr_len((bkr_str)(intptr_t)(_v2918)) == 0) || (!file_exists(_v2918)))) {
            bkr_println(bkr_str_concat("Error: input file not found: ", _v2918));
            return 1;
        }
        bkr_str _v1209 = read_file(_v2918);
        bkr_str _v2895 = _v2882(_v1209, _v2773(_v2918));
        if ((((((_v2930 || _v2931) || _v2932) || _v2933) || _v2934) || _v2935)) {
            bkr_println(_v2895);
            return 0;
        }
        if (_v2894(_v2895)) {
            _v2911(_v2895);
            bkr_println(bkr_str_concat("Error: diagnostics found in ", _v2918));
            return 1;
        }
        bkr_println(bkr_str_concat("Checking ", _v2918));
        bkr_println("Success: No errors found.");
        return 0;
    }
    if (bkr_str_eq(_v2926, "run")) {
        bkr_str _v2918 = "";
        bkr_bool _v2936 = bkr_str_eq(_v2898("BKR_BACKEND", "c"), "native");
        bkr_i64 _v1168 = 2;
        while ((_v1168 < _v2679)) {
            bkr_str _v1802 = bkr_arg_at(_v1168);
            if (bkr_str_eq(_v1802, "--native")) {
                _v2936 = BKR_TRUE;
            } else {
                if (((!starts_with(_v1802, "-")) && (bkr_len((bkr_str)(intptr_t)(_v2918)) == 0))) {
                    _v2918 = bkr_arg_at(_v1168);
                }
            }
            _v1168 = (_v1168 + 1);
        }
        if (((bkr_len((bkr_str)(intptr_t)(_v2918)) == 0) || (!file_exists(_v2918)))) {
            bkr_println(bkr_str_concat("Error: input file not found: ", _v2918));
            return 1;
        }
        bkr_str _v2937 = bkr_str_concat(bkr_str_concat(_v2898("TMPDIR", "/tmp"), "/bkr-run-"), int_to_string(process_pid()));
        bkr_str _v2939 = bkr_str_concat(_v2937, ".out");
        bkr_str _v2940 = bkr_str_concat(_v2937, ".log");
        if (_v2936) {
            if ((!_v2917(_v2918, _v2939))) {
                return 1;
            }
        } else {
            bkr_str _v1209 = read_file(_v2918);
            bkr_str _v2895 = _v2882(_v1209, _v2773(_v2918));
            if (_v2894(_v2895)) {
                _v2911(_v2895);
                bkr_println(bkr_str_concat("Error: diagnostics found in ", _v2918));
                return 1;
            }
            bkr_str _v2941 = bkr_str_concat(_v2937, ".c");
            if ((!write_file(_v2941, _v2895))) {
                bkr_println(bkr_str_concat("Error: cannot write ", _v2941));
                return 1;
            }
            bkr_str _v2611 = _v2898("BKR_CC", _v2898("CC", "cc"));
            bkr_str _v2942 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2611, " -std=c11 -w -I "), _v2903(_v2906())), " "), _v2903(_v2941)), " -o "), _v2903(_v2939)), " -lm > "), _v2903(_v2940)), " 2>&1");
            bkr_i64 _v2943 = process_run_status(_v2942);
            bkr_i64 _v2945 = 1;
            if (bkr_result_is_ok(_v2943)) {
                _v2945 = bkr_result_unwrap(_v2943);
            }
            if ((_v2945 != 0)) {
                if (file_exists(_v2940)) {
                    bkr_print(read_file(_v2940));
                }
                bkr_println(bkr_str_concat("Error: C backend failed to build ", _v2918));
                file_remove(_v2941);
                file_remove(_v2940);
                return 1;
            }
            file_remove(_v2941);
        }
        bkr_i64 _v2949 = process_run_status(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2903(_v2939), " > "), _v2903(_v2940)), " 2>&1"));
        if ((!bkr_result_is_ok(_v2949))) {
            bkr_println(bkr_str_concat("Error: failed to execute ", _v2939));
            return 1;
        }
        bkr_i64 _v2950 = bkr_result_unwrap(_v2949);
        if (file_exists(_v2940)) {
            bkr_print(read_file(_v2940));
        }
        bkr_println(bkr_str_concat("Result: ", int_to_string(_v2950)));
        file_remove(_v2939);
        file_remove(_v2940);
        return ((bkr_i32)(_v2950));
    }
    if (bkr_str_eq(_v2926, "native")) {
        bkr_str _v2918 = "";
        bkr_str _v2919 = "";
        bkr_i64 _v1168 = 2;
        while ((_v1168 < _v2679)) {
            bkr_str _v1802 = bkr_arg_at(_v1168);
            if ((bkr_str_eq(_v1802, "-o") && ((_v1168 + 1) < _v2679))) {
                _v2919 = bkr_arg_at((_v1168 + 1));
                _v1168 = (_v1168 + 1);
            } else {
                if (((!starts_with(_v1802, "-")) && (bkr_len((bkr_str)(intptr_t)(_v2918)) == 0))) {
                    _v2918 = bkr_arg_at(_v1168);
                }
            }
            _v1168 = (_v1168 + 1);
        }
        if (((bkr_len((bkr_str)(intptr_t)(_v2918)) == 0) || (!file_exists(_v2918)))) {
            bkr_println(bkr_str_concat("Error: input file not found: ", _v2918));
            return 1;
        }
        if ((bkr_len((bkr_str)(intptr_t)(_v2919)) == 0)) {
            _v2919 = substring(_v2918, 0, (bkr_len((bkr_str)(intptr_t)(_v2918)) - 4));
        }
        if ((!_v2917(_v2918, _v2919))) {
            return 1;
        }
        return 0;
    }
    if (bkr_str_eq(_v2926, "parse")) {
        bkr_str _v2918 = "";
        bkr_bool _v2951 = BKR_FALSE;
        bkr_i64 _v1168 = 2;
        while ((_v1168 < _v2679)) {
            bkr_str _v1802 = bkr_arg_at(_v1168);
            if (bkr_str_eq(_v1802, "--ast-json")) {
                _v2951 = BKR_TRUE;
            } else {
                if (((!starts_with(_v1802, "-")) && (bkr_len((bkr_str)(intptr_t)(_v2918)) == 0))) {
                    _v2918 = bkr_arg_at(_v1168);
                }
            }
            _v1168 = (_v1168 + 1);
        }
        if (((bkr_len((bkr_str)(intptr_t)(_v2918)) == 0) || (!file_exists(_v2918)))) {
            bkr_println(bkr_str_concat("Error: input file not found: ", _v2918));
            return 1;
        }
        bkr_str _v1209 = read_file(_v2918);
        bkr_str _v2886 = _v2786(_v1209, _v2773(_v2918));
        _v1187 _v1236 = _v1219(_v2886);
        _v1234 _v1246 = _v1238(_v1236);
        bkr_i64 _v2887 = _v1525(_v1246);
        if (_v1296(_v1246)) {
            bkr_println(_v2847(_v2886, _v1246));
            return 1;
        }
        if (_v2951) {
            bkr_println(_v1990(_v2886, _v2887));
        } else {
            bkr_println(_v1996(_v2886, _v2887));
        }
        return 0;
    }
    if (((bkr_str_eq(_v2926, "self-host-compile") || bkr_str_eq(_v2926, "compile")) || bkr_str_eq(_v2926, "build"))) {
        bkr_str _v2918 = "";
        bkr_str _v2919 = "";
        bkr_i64 _v1168 = 2;
        while ((_v1168 < _v2679)) {
            bkr_str _v1802 = bkr_arg_at(_v1168);
            if ((bkr_str_eq(_v1802, "-o") && ((_v1168 + 1) < _v2679))) {
                _v2919 = bkr_arg_at((_v1168 + 1));
                _v1168 = (_v1168 + 1);
            } else {
                if (((!starts_with(_v1802, "-")) && (bkr_len((bkr_str)(intptr_t)(_v2918)) == 0))) {
                    _v2918 = bkr_arg_at(_v1168);
                }
            }
            _v1168 = (_v1168 + 1);
        }
        if (((bkr_len((bkr_str)(intptr_t)(_v2918)) == 0) || (!file_exists(_v2918)))) {
            bkr_println(bkr_str_concat("Error: input file not found: ", _v2918));
            return 1;
        }
        if ((bkr_len((bkr_str)(intptr_t)(_v2919)) == 0)) {
            _v2919 = bkr_str_concat(_v2918, ".c");
        }
        bkr_str _v1209 = read_file(_v2918);
        bkr_str _v2895 = _v2882(_v1209, _v2773(_v2918));
        bkr_bool _v2952 = write_file(_v2919, _v2895);
        if ((!_v2952)) {
            return 1;
        }
        return 0;
    }
    bkr_str _v2918 = bkr_arg_at(1);
    bkr_str _v2919 = bkr_str_concat(_v2918, ".c");
    bkr_i64 _v1168 = 2;
    while ((_v1168 < _v2679)) {
        bkr_str _v2953 = bkr_arg_at(_v1168);
        if ((bkr_str_eq(_v2953, "-o") && ((_v1168 + 1) < _v2679))) {
            _v2919 = bkr_arg_at((_v1168 + 1));
            _v1168 = (_v1168 + 1);
        }
        _v1168 = (_v1168 + 1);
    }
    if ((!file_exists(_v2918))) {
        bkr_println(bkr_str_concat("Error: input file not found: ", _v2918));
        return 1;
    }
    bkr_str _v1209 = read_file(_v2918);
    bkr_str _v2895 = _v2882(_v1209, _v2773(_v2918));
    bkr_bool _v2952 = write_file(_v2919, _v2895);
    if ((!_v2952)) {
        return 1;
    }
    return 0;
}

int main(int argc, char** argv) {
    bkr_init_args(argc, argv);
    return (int)_v2924();
}
