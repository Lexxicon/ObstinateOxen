#include "Rendering.h"

#include "../dataTypes/Positional.h"
#include "../dataTypes/Visuals.h"
#include "../dataTypes/Core.h"


void Rendering::RegisterTypes(flecs::world& ecs)
{
    ecs.type().component<RenderPhases>()
        .add<RenderPhases::Background>()
        .add<RenderPhases::PreDraw>()
        .add<RenderPhases::Draw>()
        .add<RenderPhases::PostDraw>();
}

void Rendering::InitGlobals(flecs::world& ecs)
{
    auto builder = ecs.query_builder()
     .term(flecs::System)
     .order_by(0, [](
         ecs_entity_t e1, const void *ptr1, 
         ecs_entity_t e2, const void *ptr2)
         {
             return (e1 > e2) - (e1 < e2);
         })
     .group_by(flecs::type_id<RenderPhases>(), [](
         flecs::world_t* m_world,
         flecs::type_t m_table_type,
         flecs::entity_t m_grp_type,
         void*)
         {
             flecs::type TableType(m_world, m_table_type);
             for(auto ColId : TableType.vector())
             {
                 flecs::entity e(m_world, ColId);
                 if(e.is_valid() && e.has(flecs::ChildOf, m_grp_type))
                 {
                     int i = 0;
                     auto GrpType = flecs::entity(m_world, m_grp_type).get<flecs::Type>();
                     for(auto TypeID : flecs::type(m_world, GrpType->normalized).vector()){
                         if(ColId == TypeID)
                         {
                             return i;
                         }
                         i++;
                     }
                 }
             }
             ecs_os_err("Failed to find group for %s", TableType.str());
             return 0;
         });
    
    ecs.component<RenderPhases>()
        .children([&](flecs::entity Phase)
        {
            builder.term(Phase).oper(flecs::Or);
        });
    

    ecs.set<RenderPhases>({builder.build()});
}

void Rendering::RegisterSystems(flecs::world& ecs)
{
    ecs.system("Clear Screen")
        .kind(flecs::type_id<RenderPhases::Background>())
        .iter([](flecs::iter& Iter)
        {
            ofBackground(ofColor::black);
        });
    
    ecs.system<Transform, Circle>("Draw Circles")
        .kind(flecs::type_id<RenderPhases::Draw>())
        .each([](Transform& transform, Circle& circle)
        {
            ofSetColor(circle.Color);
            ofDrawCircle(transform.Location, circle.Radius);
        });
}
