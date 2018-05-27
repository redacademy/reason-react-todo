let str = ReasonReact.string;

let component = ReasonReact.statelessComponent("TodoItem");

let make = (~item: TodoModel.item, ~onRemove, ~onToggle, _children) => {
  ...component,
  render: _self =>
    <div className="item">
      <input
        _type="checkbox"
        checked=item.completed
        onChange=((_) => onToggle(item.id))
      />
      <p> (str(item.title)) </p>
      <button onClick=((_) => onRemove(item.id))> (str("Remove")) </button>
    </div>,
};