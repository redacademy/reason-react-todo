let str = ReasonReact.string;

let component = ReasonReact.statelessComponent("AddTodo");

let make = (~value, ~onInputText, ~submit, _children) => {
  ...component,
  render: _self =>
    <div className="input">
      <input
        value
        placeholder="add item"
        onChange=(
          event =>
            onInputText(
              ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value,
            )
        )
      />
      <button onClick=((_) => submit())> (str("Add")) </button>
    </div>,
};